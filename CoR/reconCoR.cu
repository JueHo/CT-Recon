/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "reconFDK_kernelCoR.cuh"
#include "recon.h"
#include "typesFDK.h"
#include <cfloat>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include "helper_cuda.h"
#include "reader.h"
#include <cstdio>

extern char *parafilename;

extern int gMultiRowFlag;
extern int gCurrentSlice;


extern QVector<double> g_X;
extern QVector<double> g_Y;

//-ju- vector for linear square fit
extern std::vector<float> h_val;
extern std::vector<float> h_slice;



#include "rot_ax_det.h"
using namespace cv;


//-ju-19-Jan-2011 set PRINT_INFO to 1 to print out add. information
///////////////////////////////////////////////////////////////////
#define PRINT_INFO 0

//const size_t FILE_NUMBER_LEN=5;

inline float ROUND(float x)
{
    return x > 0.0f ? x + 0.5f : x - 0.5f;
}

extern "C"
    int runFDK(BackProjParam param, int devNo, float *minGray, float *maxGray, FILE *fpVol, PlotData *plData)
{
    int numberDevice, device;
    cudaGetDeviceCount(&numberDevice);
    if (numberDevice > 0) 
    {
        int maxMultiprocessors = 0, maxDevice = 0, maxMajor = 0;
        string deviceName = "none";
        for (device = 0; device < numberDevice; device++) 
        {
            cudaDeviceProp prop;
            cudaGetDeviceProperties(&prop, device);
            if (maxMajor <= prop.major && maxMultiprocessors <= prop.multiProcessorCount) 
            {
                maxMultiprocessors = prop.multiProcessorCount;
                maxMajor = prop.major;
                maxDevice = device;
                deviceName = prop.name;
            }
        }
        if(gMultiRowFlag == 0)
        {
            printf("\nSelect GPU device number: %d\nDevice name: %s\n\n",maxDevice,deviceName.c_str());
        }
        cudaSetDevice(maxDevice);
    }
    cudaSetDevice(0);

    clock_t start, stop, io_start, io_stop;
    float io_time = 0;
    start = clock();


    // estimate number of chunks of z-slices
    // depending on available memory
    int number_y_chunks = static_cast<int>(param.sliceChunkSize);
    // stacksize of z-slices process as a block at once
    int backproj_chunks	= param.volY/number_y_chunks;
    const int backproj_chunks_remainder = param.volY%number_y_chunks;
    bool hasYChunkRemainder = false;
    if(backproj_chunks_remainder != 0)
    {
        number_y_chunks += 1;
        hasYChunkRemainder = true;
        if(gMultiRowFlag == 0)
        {
            cout << "Y Chunk Remainder is true\n\n";
        }
    }

    // number of projections processed at once (depends on gpu memory)
    // number of projection blocks depends on avail. graphic card memory
    int proj_blcks = static_cast<int>(param.projectionChunkSize); 
    int nProjUse = param.numProj/proj_blcks;    // number of projections to use
    int remainProj = param.numProj%proj_blcks;
    bool hasRemainder = false;
    // if has remainder
    if(remainProj != 0)
    {
        proj_blcks += 1;
        hasRemainder = true;
        if(gMultiRowFlag == 0)
        {
            cout << "Projection Chunk Remainder is true\n\n";
        }
    }


    FDK_Constants *tmp_c= (FDK_Constants*)malloc(sizeof(FDK_Constants));
    tmp_c->imgWidth		= param.imgWidth;
    tmp_c->imgHeight	= param.imgHeight;
    tmp_c->numProj		= param.numProj;
    tmp_c->projProcSize = nProjUse;
    tmp_c->angleIncr	= 2.0f*PI/param.numProj;
    tmp_c->voxSize		= param.binFac*param.pixSize/param.magnification; // pixel-size / magnification
    tmp_c->distSrcObj	= param.dso;
    tmp_c->offsetX = (float)(param.imgWidth)/2.0f - 0.5f;
    tmp_c->offsetY = (float)(param.imgHeight)/2.0f - 0.5f;

#if PRINT_INFO == 1
    cout << "Offset x: " << tmp_c->offsetX << endl;
    cout << "Offset y: " << tmp_c->offsetY << endl;
#endif

    if(gMultiRowFlag == 0)
    {
        cout << "Volume dimensions: [" << param.volX << "," << param.volY << "," << param.volZ << "]\n";
        cout.flush();
    }

    HANDLE_ERROR(cudaMemcpyToSymbol(fdkConst, tmp_c, sizeof(FDK_Constants)));
    free(tmp_c);

    unsigned int dimThreadsX = param.threadX;
    unsigned int dimThreadsY = param.threadY;
    dim3 threads(dimThreadsX,dimThreadsY);

    // blocks in grid
     int dimBlocksX, dimBlocksZ;
    dimBlocksX = (param.volX  + threads.x - 1)/threads.x;
    dimBlocksZ = (param.volZ + threads.y - 1)/threads.y;
    dim3 blocks(dimBlocksX,dimBlocksZ);

    // min and max values in tomograms
    // used for scaling from float to integer
    float tomoMax = FLT_MIN;
    float tomoMin = FLT_MAX;

    //-ju-25-May-2015 out put to file calculating rotation axis
    ////////////////////////////////////////////////////////////
    FILE *varMax;
    char varMaxFile[256];
    sprintf(varMaxFile,"%s.rotaxis",parafilename);
    varMax = fopen(varMaxFile,"w");
    if(varMax == 0)
    {
        std::cerr << "Can not open calc. rotation axis out put file:" << varMaxFile << endl;
        exit(-346);
    }

    FILE *excelIn;
    char excelInFile[256];
    sprintf(excelInFile,"%s.rot_axis.ExcelIn",parafilename);
    excelIn = fopen(excelInFile,"w");
    if(varMax == 0)
    {
        std::cerr << "Can not open calc. rotation axis excel input file:" << varMaxFile << endl;
        exit(-347);
    }

    //-ju-25-May-2015 out put to file calculating rotation axis
    ////////////////////////////////////////////////////////////
    int indexSh         = 0;
    int indexShSD       = 0;
	float maxVariance	= 0.0f;
	float minVariance	= FLT_MAX;
    float maxStddev     = 0.0f;
    float maxShift      = 0.0f;
    float maxShiftSD    = 0.0f;

    for(int nck = 0; nck < number_y_chunks; nck++)
    {
        // dynamic z chunk size
        // if last chunk and has remainder
        int yChunkEnd;
        int yChunkStart;
        if(nck == number_y_chunks-1 && hasYChunkRemainder)
        {
            // save start condition before change backproj_chunks
            yChunkStart = nck*backproj_chunks;
            backproj_chunks = backproj_chunks_remainder;
            yChunkEnd = param.volY;
        }
        else
        {
            yChunkStart = nck*backproj_chunks;
            yChunkEnd = (nck+1)*backproj_chunks;
        }

        if(gMultiRowFlag == 0)
        {
            printf("Reconstruction of slices: %4d - %4d  of total %d  slices\n", 
                yChunkStart+1, yChunkEnd, param.volY);
            fflush(stdout);
        }
        //-ju- allocate memory for a chunk of sinograms
        unsigned long long sinChunkSize = (size_t)param.imgWidth*(size_t)param.imgHeight*(size_t)nProjUse;
        float *h_sinoData = new float[sinChunkSize]();

        /*-ju-27-Oct-2011 new */
        unsigned long long chunkSize = (unsigned long long)param.volX*(unsigned long long)param.volZ*(unsigned long long)backproj_chunks;
        float *h_backproj_chunk = new float[chunkSize];


        for(int np=0; np<proj_blcks; np++) // projection blocks
        {
            //-ju-13-Dec-2010 add projection remainder handling
            int start_value;
            int end_value;
            if(hasRemainder && np == proj_blcks-1)
            {
                start_value = np*nProjUse;
                end_value = np*nProjUse + remainProj;
            }
            else
            {
                start_value = np*nProjUse;
                end_value = (np+1)*nProjUse;
            }

            if(gMultiRowFlag == 0)
            {
                printf(" processing: projection block %2d of %2d projection blocks\n", np+1, proj_blcks);
                fflush(stdout);
            }
            int   cuProjBlockIdx	= np; // current projection block index

            // read chunk of sinograms
            //////////////////////////
            io_start = clock();
            int rval;
            if(param.useFileList == 1)
            {
                if((rval = ReadChunkOfSinogramsFromFileList(start_value,
                    end_value,
                    param,
                    &h_sinoData[0]))!=0)
                {
                    fprintf(stderr,"\n\t==> Error reading chunk of sinograms!\n\n");
                    return rval;
                }
            }
            else
            {
                if(param.sino32BlockUse)
                {
                    if((rval = ReadBlockChunkOfSinograms(start_value,
                        end_value,
                        param,
                        &h_sinoData[0]))!=0)
                    {
                        fprintf(stderr,"\n\t==> Error reading block chunk of sinograms!\n\n");
                        return rval;
                    }
                }
                else
                {
                    if((rval = ReadChunkOfSinograms(start_value,
                        end_value,param,
                        &h_sinoData[0]))!=0)
                    {
                        fprintf(stderr,"\n\t==> Error reading chunk of sinograms!\n\n");
                        return rval;
                    }
                }
            }
            io_stop = clock();
            io_time += (float)(io_stop - io_start) / CLOCKS_PER_SEC;
			
            cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(32,0,0,0,cudaChannelFormatKindFloat);
            //-ju- device memory of sinogram data
            cudaArray *d_sino;
            //-ju- allocate memory holding texture device memory
	    	const cudaExtent volumeSize = make_cudaExtent((size_t)param.imgWidth, (size_t)param.imgHeight, (size_t)nProjUse);
            checkCudaErrors(cudaMalloc3DArray(&d_sino, &channelDesc, volumeSize, cudaArrayLayered));
            //-ju- copy memory host to device
            cudaMemcpy3DParms copyParams = {0};
			copyParams.srcPos = make_cudaPos((size_t)0, (size_t)0, (size_t)0);
			copyParams.dstPos = make_cudaPos((size_t)0, (size_t)0, (size_t)0);
			copyParams.extent = make_cudaExtent((size_t)param.imgWidth, (size_t)param.imgHeight, (size_t)nProjUse);
            copyParams.kind     = cudaMemcpyHostToDevice;
            copyParams.dstArray = d_sino;
            copyParams.srcPtr   = make_cudaPitchedPtr(h_sinoData,
                volumeSize.width*sizeof(float),
                volumeSize.width,
                volumeSize.height);
            checkCudaErrors(cudaMemcpy3D(&copyParams));
			
	    	cudaTextureObject_t tex3DLayObj = 0;
			cudaResourceDesc texRes;
			memset(&texRes, 0, sizeof(cudaResourceDesc));

			texRes.resType = cudaResourceTypeArray;
			texRes.res.array.array = d_sino;

			cudaTextureDesc texDescr;
			memset(&texDescr, 0, sizeof(cudaTextureDesc));

			texDescr.normalizedCoords = false;
			texDescr.filterMode = cudaFilterModeLinear;
			texDescr.addressMode[0] = cudaAddressModeBorder;
			texDescr.addressMode[1] = cudaAddressModeBorder;
			texDescr.readMode = cudaReadModeElementType;

			checkCudaErrors(cudaCreateTextureObject(&tex3DLayObj, &texRes, &texDescr, NULL));

            int index = 0;
            for(int iy=yChunkStart; iy<yChunkEnd; iy++)
            {
                //-ju- allocate memory for one backprojection slice on device
                float *d_backProj;
                checkCudaErrors(cudaMalloc( (void**)&d_backProj, param.volX*param.volZ*sizeof(float)));

                unsigned long long offset = (unsigned long long)param.volX*(unsigned long long)param.volZ*(unsigned long long)index;
                checkCudaErrors(cudaMemcpy(d_backProj,
                    (char*)&h_backproj_chunk[offset], 
                    param.volX*param.volZ*sizeof(float),
                    cudaMemcpyHostToDevice));

                //////////////////////////////////
				//-ju- Run Backprojection Kernel
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
				// using a "one slice size" block ==> index of it is 0
				int   y_c = 0; 


                float horizShift = (float(iy)+(float)param.pixShiftMin)*param.shiftStep;

                //-ju- Run Backprojection Kernel
                /////////////////////////////////
                 if(hasRemainder && np == proj_blcks-1) // process remainder
                {
                    fdk_kernel_3DW_R_HA<<<blocks,threads>>>(d_backProj, y_c, 
                        cuProjBlockIdx, remainProj, 
                        param.volX, param.volZ, 
                        horizShift, param.shiftY, 
                        param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ,
                        tex3DLayObj);
                }
                else
                {
                    //-ju-05-03-2014 standard kernel
                    ////////////////////////////////
                    fdk_kernel_3DW_HA<<<blocks,threads>>>(d_backProj, y_c, 
                        cuProjBlockIdx, 
                        param.volX, param.volZ, 
                        horizShift, param.shiftY, 
                        param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ,
                        tex3DLayObj);
                }

                getLastCudaError("Kernel execution failed");

                checkCudaErrors(cudaMemcpy((char*)&h_backproj_chunk[offset], d_backProj, (size_t)param.volX*param.volZ*sizeof(float), cudaMemcpyDeviceToHost));
                //-ju- free memory for one z-slice
                checkCudaErrors(cudaFree(d_backProj));
                index++;
            }

            //-ju- free device memory used for sinograms (chunks wise)
			checkCudaErrors(cudaDestroyTextureObject(tex3DLayObj));
            checkCudaErrors(cudaFreeArray(d_sino));
        }


        // Write tomgrams
        //////////////////
        io_start = clock();
        ofstream s_backProjFile;
        int index = 0;
		if (!CreateTomoDir(param.tomoDir.c_str()))
		{
            cout << "Can not create >> " << param.tomoDir << endl;
            cout.flush();
            exit(-3);
        };
        int startIdx = param.startIndex;
        char tomgramFile[500];


		double bilat_time_start, bilat_time_stop, bilat_sum = 0.0;
        for(int i=yChunkStart; i<yChunkEnd; i++)
        {
            // offset in memory block
            unsigned long long offset = (unsigned long long)param.volX*(unsigned long long)param.volZ*(unsigned long long)index;
            //-ju-19-Oct-2011 calc. min/max
            unsigned long long endSeq = offset + (unsigned long long)param.volX*(unsigned long long)param.volZ;
            for(unsigned long long  k = offset; k < endSeq; k++)
            {
                if(h_backproj_chunk[k] < tomoMin)
                    tomoMin = h_backproj_chunk[k];
                if(h_backproj_chunk[k] > tomoMax)
                    tomoMax = h_backproj_chunk[k];
            }

            long long ii = i;
            // file offset
            unsigned long long fileOffset = 
                ((unsigned long long)param.volY - (unsigned long long)(ii+startIdx))*(unsigned long long)param.volX*(unsigned long long)param.volZ;
            if(param.tomoBlockWrite)
            {
                _fseeki64(fpVol,fileOffset*sizeof(float),0);
                fwrite((char*)&h_backproj_chunk[offset], param.volX*param.volZ*sizeof(float), 1, fpVol);
            }
            else
            {
                //-ju-14-Apr-2015 --> add
                int id;
				//-ju-25-may-2015 for rotation axis determination  
				// reverse projection stack orientation is not implemented
				// (to be done ???)
                if(1 == 1/*param.viewDirection*/) 
                {
                    id = i+startIdx;
                }
                else
                {
                    id = param.volY - (i+startIdx) + 1;
                }
                //-ju-14-Apr-2015 <-- add
                 if(gMultiRowFlag == 0)
                {
                    sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
                        param.tomoDir.c_str(),param.tomoName.c_str(),
                        param.volX,param.volY,param.volZ,
                        id);
                    s_backProjFile.open(tomgramFile, ios::binary);
                    if(!s_backProjFile.is_open())
                    {
                        cout << "Can not open " << tomgramFile << "  -  Exit program!\n";
                        cout.flush();
                        return -1;
                    }
                    if(!s_backProjFile.write((char*)&h_backproj_chunk[offset], param.volX*param.volZ*sizeof(float)))
                    {
                        cout << "\nError writing tomogram\n";
                        cout.flush();
                        return -2;
                    }
                s_backProjFile.close();
                }

                //-ju-25-May-2015 calculation for rotation axis determination
                /////////////////////////////////////////////////////////////
                float horizShift = (float(i)+(float)param.pixShiftMin)*param.shiftStep;
                //-ju-28-may-2015 in memory calculation Mat orig, var, stddev;
                Mat var, stddev;
                Scalar var_sum, stddev_sum;
                unsigned w = param.volX;
                unsigned h = param.volZ;
                //-ju-28-may-2015 in memory calculation
                ////////////////////////////////////////
                Mat orig = Mat::zeros(h, w, CV_32F);
                memcpy(orig.data, &h_backproj_chunk[offset], param.volX*param.volZ*sizeof(float));
				bilat_time_start = clock();
				
				//////////////////////////////////////
				//-ju-22-Jan-2017 actual used filter
				/////////////////////////////////////
				// Run Sharpness Filter
				//////////////////////////////////////////////////////////////////////////////////////
				GradientSquaredFromBiLat(tomgramFile, w, h, orig, var, var_sum, stddev, stddev_sum);//
				//////////////////////////////////////////////////////////////////////////////////////

				bilat_time_stop = clock();
				bilat_sum += (float)(bilat_time_stop - bilat_time_start) / CLOCKS_PER_SEC;
                if(gMultiRowFlag == 0)
                {
                    printf("Index=%+4d\tShift=%+7.4f\tSharpness=%+8.5f\t\n",i,horizShift,var_sum.val[0]);
                    fprintf(varMax,"%+10d %+10.3f %+10.6f\n",i,horizShift,var_sum.val[0]);
                    fprintf(excelIn,"%+10.3f %+10.6f\n",horizShift,var_sum.val[0]);
                    g_X.push_back(horizShift);
                    g_Y.push_back(var_sum.val[0]);
                }
				// ju-08-07-2015
				if (var_sum.val[0]>maxVariance)
                {
                    maxVariance = var_sum.val[0];
                    indexSh   = i;
                    maxShift = horizShift;
                }
				
                if(stddev_sum.val[0]>maxStddev)
                {
                    maxStddev = stddev_sum.val[0];
                    indexShSD   = i;
                    maxShiftSD  = horizShift;
                }
            }
            index++;
        }
#ifdef _PRINT_OUT
		printf("\n\n\t--->Filtering takes %f s time\n\n", bilat_sum);
#endif

        io_stop = clock();
        io_time += (float)(io_stop - io_start) / CLOCKS_PER_SEC;

        delete [] h_backproj_chunk;
        delete [] h_sinoData;
    }


    if(gMultiRowFlag == 0)
    {
		//-ju-08-07-2015
		printf("\n\n\nMaximum:\n\tSlice No=%d\th-shift=%f\tsharp coef=%f\n", indexSh + 1, maxShift, maxVariance);
		plData->maxYVal = maxVariance;
		plData->maxXVal = maxShift;
	}
    else
    {
		printf("     Maximum:\tat image slice no=%d\th-shift=%f\tsharp coef=%f\n\n", indexSh + 1, maxShift, maxVariance);
		//-ju-linear square fit
		h_val.push_back(maxShift);
		h_slice.push_back((float)(indexSh + 1)); //
	}
	fprintf(varMax, "\n\n\nSharpness (best value):\nslice no=%d\n\th-shift=%f\n\tvalue=%f\n", indexSh + 1, maxShift, minVariance);
    fclose(varMax);
    fclose(excelIn);


     //-ju-21-Oct-2014 cudaThreadExit(); --> replaced by cudaDeviceReset()
    cudaDeviceReset();
    stop = clock();
    float duration = (float)(stop - start) / CLOCKS_PER_SEC;
    *maxGray = tomoMax;
    *minGray = tomoMin;


    size_t pos = param.projectName.find(".");
    string scalename = param.projectName.substr(0,pos);
    scalename += ".log";

    if(gMultiRowFlag == 0)
    {

        printf("\n--------------Timming----------------------\n");
        printf("Total runtime:              %#4.1f seconds\n", duration );
        printf("IO time without conversion: %#4.1f seconds\n", io_time );
        printf("Runtime without io:         %#4.1f seconds\n", duration-io_time);
        printf("Minimal gray value:         %f\n", tomoMin);
        printf("Maximal gray value:         %f\n", tomoMax);
        printf("---------------------------------------------\n");
    }
    FILE *fp;
    fp = fopen(scalename.c_str(),"w");
    if(fp == 0)
    {
        printf("Can not open for writing: %s\n", scalename.c_str());
        return -1;
    }
    fprintf(fp,"\n---------------------------------------------\n");
    fprintf(fp,"Total runtime:              %#4.1f seconds\n", duration );
    fprintf(fp,"IO time without conversion: %#4.1f seconds\n", io_time );
    fprintf(fp,"Runtime without io:         %#4.1f seconds\n", duration-io_time);
    fprintf(fp,"Tomo datatype:				%s\n", param.outDataType.c_str());
    fprintf(fp,"Tomo width:					%4d\n", param.volX);
    fprintf(fp,"Tomo depth:					%4d\n", param.volZ);
    fprintf(fp,"Tomo height:				%4d\n", param.volY);
    fprintf(fp,"Minimal gray value:         %f\n", tomoMin);
    fprintf(fp,"Maximal gray value:         %f\n", tomoMax);
    fprintf(fp,"---------------------------------------------\n");

    fclose(fp);

    return 0;
}


