/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "reconFDK_kernel.cuh"
#include "recon.h"
#include "typesFDK.h"
#include <cfloat>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include "helper_cuda.h"
#include "reader.h"
#include <cstdio>

#include <omp.h>

//-ju-19-Jan-2011 set PRINT_INFO to 1 to print out add. information
///////////////////////////////////////////////////////////////////
#define PRINT_INFO 0

//const size_t FILE_NUMBER_LEN=5;

inline float ROUND(float x)
{
	return x > 0.0f ? x + 0.5f : x - 0.5f;
}

// algorithms used in transform
///////////////////////////////
class RangeMapI16
{
public:
	RangeMapI16(float mapFactor, float f32min)
		:m_mapFactor(mapFactor),m_f32min(f32min){}
	short operator() (float inVal)
	{
		return static_cast<short>(ROUND((inVal - m_f32min)*m_mapFactor + SHRT_MIN));
	}
private:
	float m_mapFactor;
	float m_f32min;
};

class RangeMapUI16
{
public:
	RangeMapUI16(float mapFactor, float f32min)
		:m_mapFactor(mapFactor),m_f32min(f32min){}
	unsigned short operator() (float inVal)
	{
		return static_cast<unsigned short>(ROUND((inVal - m_f32min)*m_mapFactor));
	}
private:
	float m_mapFactor;
	float m_f32min;
};

class RangeMapUC8
{
public:
	RangeMapUC8(float mapFactor, float f32min)
		:m_mapFactor(mapFactor),m_f32min(f32min){}
	unsigned char operator() (float inVal)
	{
		return static_cast<unsigned char>(ROUND((inVal - m_f32min)*m_mapFactor));
	}
private:
	float m_mapFactor;
	float m_f32min;
};


void InitAngleTable(const BackProjParam &param)
{
	if(param.angleList.size() > MAX_PROJ_NUM)
	{
		cout << "Number of angle table entries (" 
			 << param.angleList.size() 
			 << ") exceeds pre-defined max.size of " 
			 << MAX_PROJ_NUM << endl;
		exit(-2);
	}
	vector<float> rads_temp(param.angleList.size());
	float angle2rad = 2.0f*PI/360.0f;
	for(int i = 0; i < rads_temp.size(); i++)
	{
		rads_temp[i] = param.angleList[i]*angle2rad;
	}
	HANDLE_ERROR(cudaMemcpyToSymbol(radsConst, &rads_temp[0], sizeof(float)*rads_temp.size()));
}


extern "C"
int runFDK(BackProjParam param, int devNo, float *minGray, float *maxGray, FILE *fpVol)
{
    //cudaSetDevice(0);
    //-ju-19-Nov-2013 automatically select device with highest performance 
    //                 ==> max. number of multiprocessors
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
        printf("\nSelect GPU device number: %d\nDevice name: %s\n\n",maxDevice,deviceName.c_str());
		cudaSetDevice(maxDevice);
    }
	//cudaSetDevice(0);

    clock_t start, stop, io_start, io_stop;
	float io_time = 0;
	start = clock();

	if(param.useFileList == 1)
	{
		InitAngleTable(param);
	}

	// estimate number of chunks of z-slices
	// depending on available memory
	//int number_z_chunks = 17;  // hard coded
	int number_y_chunks = static_cast<int>(param.sliceChunkSize);
	// stacksize of z-slices process as a block at once
	int backproj_chunks	= param.volY/number_y_chunks;
	const int backproj_chunks_remainder = param.volY%number_y_chunks;
	bool hasYChunkRemainder = false;
	if(backproj_chunks_remainder != 0)
	{
		number_y_chunks += 1;
		hasYChunkRemainder = true;
		cout << "Y Chunk Remainder is true\n\n";
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
		cout << "Projection Chunk Remainder is true\n\n";
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

	cout << "Volume dimensions: [" << param.volX << "," << param.volY << "," << param.volZ << "]\n";
	cout.flush();

	HANDLE_ERROR(cudaMemcpyToSymbol(fdkConst, tmp_c, sizeof(FDK_Constants)));
	free(tmp_c);

	unsigned int dimThreadsX = param.threadX;
	unsigned int dimThreadsY = param.threadY;
	dim3 threads(dimThreadsX,dimThreadsY);

	// blocks in grid
	//int dimBlocksX, dimBlocksY;
	int dimBlocksX, dimBlocksZ;
	dimBlocksX = (param.volX  + threads.x - 1)/threads.x;
	dimBlocksZ = (param.volZ + threads.y - 1)/threads.y;
	dim3 blocks(dimBlocksX,dimBlocksZ);

	// min and max values in tomograms
	// used for scaling from float to integer
	float tomoMax = FLT_MIN;
	float tomoMin = FLT_MAX;

	for(int nck = 0; nck < number_y_chunks; nck++)
	{
		// dynamic z chunk size
		// if last chunk and has remainder
		int yChunkEnd;
		int yChunkStart;
		if(nck == number_y_chunks-1 && hasYChunkRemainder)
		{
			// save start condtion before change backproj_chunks
			yChunkStart = nck*backproj_chunks;
			backproj_chunks = backproj_chunks_remainder;
			yChunkEnd = param.volY;
		}
		else
		{
			yChunkStart = nck*backproj_chunks;
			yChunkEnd = (nck+1)*backproj_chunks;
		}

		printf("Reconstruction of slices: %4d - %4d  of total %d  slices\n", 
			yChunkStart+1, yChunkEnd, param.volY);
		fflush(stdout);

		//-ju- allocate memory for a chunk of sinograms
		unsigned long long sinChunkSize = (size_t)param.imgWidth*(size_t)param.imgHeight*(size_t)nProjUse;
		float *h_sinoData = new float[sinChunkSize]();
		//-ju- allocate memory for backprojection for one slice on host 

		/*-ju-27-Oct-2011 new */
		unsigned long long chunkSize = (unsigned long long)param.volX*(unsigned long long)param.volZ*(unsigned long long)backproj_chunks;
#ifdef _ASYNC_IO
		float *h_backproj_chunk;
		chunkSize = chunkSize*(unsigned long long)sizeof(float);
		HANDLE_ERROR(cudaMallocHost((void**)&h_backproj_chunk, chunkSize));
#else
		float *h_backproj_chunk = new float[chunkSize];
#endif

		for(int np=0; np<proj_blcks; np++) // projection blocks
		{
			//-ju-13-Dec-2010 add projection remainder handling
			int start_value;
			int end_value;
			if(hasRemainder && np == proj_blcks-1)
			{
				start_value = np*nProjUse;
				end_value = np*nProjUse + remainProj;
				//nProjUse = remainProj;
			}
			else
			{
				start_value = np*nProjUse;
				end_value = (np+1)*nProjUse;
			}

			printf(" processing: projection block %2d of %2d projection blocks\n", np+1, proj_blcks);
			fflush(stdout);
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
#if 0
					char buf[64];
					sprintf(buf,"Block%04d_%04d.buf",np,proj_blcks);
					std::ofstream blkwrite(buf,std::ios::binary);
					if(blkwrite.is_open())
					{
						blkwrite.write((char*) &h_sinoData[0],(size_t)param.imgWidth*(size_t)param.imgHeight*(size_t)nProjUse*4); 
						blkwrite.close();
					}
#endif
				}
			}
			io_stop = clock();
			io_time += (float)(io_stop - io_start) / CLOCKS_PER_SEC;
			cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(32,0,0,0,cudaChannelFormatKindFloat);
			//-ju- device memory sinogram
			cudaArray *d_sino;
			//-ju- allocate memory holding texture device memory
			const cudaExtent volumeSize = make_cudaExtent(param.imgWidth, param.imgHeight, nProjUse);
			//HANDLE_ERROR(cudaMalloc3DArray(&d_sino, &channelDesc, volumeSize));
			HANDLE_ERROR(cudaMalloc3DArray(&d_sino, &channelDesc, volumeSize, cudaArrayLayered));
			//-ju- copy memory host to device
			cudaMemcpy3DParms copyParams = {0};
			copyParams.srcPos   = make_cudaPos(0,0,0);
			copyParams.dstPos   = make_cudaPos(0,0,0);
			copyParams.extent   = make_cudaExtent(param.imgWidth, param.imgHeight, nProjUse);
			copyParams.kind     = cudaMemcpyHostToDevice;
			copyParams.dstArray = d_sino;
			copyParams.srcPtr   = make_cudaPitchedPtr(h_sinoData,
													  volumeSize.width*sizeof(float),
													  volumeSize.width,
													  volumeSize.height);
			HANDLE_ERROR(cudaMemcpy3D(&copyParams));

			//-ju- channel descriptor
			//cudaChannelFormatDesc desc = cudaCreateChannelDesc<float>();
			//texSino.addressMode[0]     = cudaAddressModeClamp;
			texSinoLay.addressMode[0]     = cudaAddressModeBorder; //-ju- -> set out of border access to 0
			//texSino.addressMode[1]     = cudaAddressModeClamp;
			texSinoLay.addressMode[1]     = cudaAddressModeBorder;
			texSinoLay.filterMode         = cudaFilterModeLinear;
            //texSino.filterMode         = cudaFilterModePoint;
			texSinoLay.normalized         = false;

			//-ju- bind texture to array device memory
			HANDLE_ERROR(cudaBindTextureToArray(texSinoLay, d_sino, channelDesc));

			//-ju-11-Dec-2015 add streams
			cudaStream_t *stream = (cudaStream_t *)malloc(STREAM_SIZE * sizeof(cudaStream_t));
			for (int i = 0; i < STREAM_SIZE; i++)
			{
				cudaStreamCreate(&(stream[i]));
			}


			int index = 0;
			////float *d_backProj[STREAM_SIZE];
			////for (int i = 0; i < STREAM_SIZE; i++)
			////{
			////	HANDLE_ERROR(cudaMalloc((void**)&d_backProj[i], MAP*param.volX*param.volZ*sizeof(float)));
			////}
			//for(int iy=yChunkStart; iy<yChunkEnd; iy++)
			for (int iy = yChunkStart; iy<yChunkEnd; iy = iy + MAP*STREAM_SIZE)
			{
				// Allocate and initialize an array of stream handles
				//-ju- allocate memory for one backprojection slice on device
				float *d_backProj[STREAM_SIZE];
				for (int i = 0; i < STREAM_SIZE; i++)
				{
					HANDLE_ERROR(cudaMalloc((void**)&d_backProj[i], MAP*param.volX*param.volZ*sizeof(float)));
				}

				//-ju-11-Dec-2015 loop over stream
				//////////////////////////////////
				unsigned long long offset[STREAM_SIZE];
				for (int istm = 0; istm < STREAM_SIZE; istm++)
				{
					//-ju- (re-)copy host memory for backprojection to device
					offset[istm] = (unsigned long long)param.volX*(unsigned long long)param.volZ*(unsigned long long)(index + istm*MAP);
					cudaMemcpyAsync(d_backProj[istm], 
									(char*)&h_backproj_chunk[offset[istm]], 
									MAP*param.volX*param.volZ*sizeof(float), 
									cudaMemcpyHostToDevice, 
									stream[istm]);

					//-ju- Run Backprojection Kernel
					/////////////////////////////////
					int   y_c = iy + istm*MAP;     // current z slice

					float offset_current = param.shiftX;

					if (param.applyTiltCorr == 1)
					{
						// Values from regression
						// y = mx + c
						float m = static_cast<float>(param.slopeTiltCorr);
						float c = static_cast<float>(param.constTiltCorr);
						offset_current = m * static_cast<float>(y_c) + c;
						if ((y_c % 100) == 0)
						{
							std::cout << "Using horizontal offset=" << offset_current << " at slice=" << y_c << std::endl;
						}
					}


					// 3D-Window volume selection reconstruction
					if (param.useVolWin)
					{
						if (hasRemainder && np == proj_blcks - 1) // process remainder
						{
							//-ju-03-Nov switch between fast and high acc. bi-linear interpolation
							///////////////////////////////////////////////////////////////////////
							if (param.highAcc == 0)
							{
								fdk_kernel_3DW_R << <blocks, threads >> >(d_backProj[istm], y_c,
									cuProjBlockIdx, remainProj,
									param.volX, param.volZ,
									offset_current, param.shiftY,
									param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ);
							}
							else
							{
								fdk_kernel_3DW_R_HA << <blocks, threads >> >(d_backProj[istm], y_c,
									cuProjBlockIdx, remainProj,
									param.volX, param.volZ,
									offset_current, param.shiftY,
									param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ);
							}
						}
						else
						{
							//-ju-03-Nov switch between fast and high acc. bi-linear interpolation
							///////////////////////////////////////////////////////////////////////
							if (param.highAcc == 0)
							{
								//-ju-05-03-2014 standard kernel
								fdk_kernel_3DW << <blocks, threads >> >(d_backProj[istm], y_c,
									cuProjBlockIdx,
									param.volX, param.volZ,
									offset_current, param.shiftY,
									param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ);
							}
							else
							{
								fdk_kernel_3DW_HA << <blocks, threads >> >(d_backProj[istm], y_c,
									cuProjBlockIdx,
									param.volX, param.volZ,
									offset_current, param.shiftY,
									param.wVolOrigX, param.wVolOrigY, param.wVolOrigZ);
							}
						}
					}
					getLastCudaError("Kernel execution failed");

					cudaMemcpyAsync((char*)&h_backproj_chunk[offset[istm]],
									d_backProj[istm],
						            MAP*param.volX*param.volZ*sizeof(float),
									cudaMemcpyDeviceToHost,
						            stream[istm]);

				} //-ju-11-Dec-2015 streams end

				for (int i = 0; i < STREAM_SIZE; i++)
				{
					HANDLE_ERROR(cudaFree(d_backProj[i]));
				}
				index = index + MAP*STREAM_SIZE;

			}
			////for (int i = 0; i < STREAM_SIZE; i++)
			////{
			////	HANDLE_ERROR(cudaFree(d_backProj[i]));
			////}
			//-ju-11-Dec-2015 add streams
			// release all stream
			for (int i = 0; i < STREAM_SIZE; i++)
			{
				cudaStreamDestroy(stream[i]);
			}

			//-ju- unbind texture
			cudaUnbindTexture(texSinoLay);

			//-ju- free device memory used for sinograms (chunks wise)
			HANDLE_ERROR(cudaFreeArray(d_sino));

		}

		// Write tomgrams
		//////////////////
		io_start = clock();
		ofstream s_backProjFile;
		int index = 0;
		if(!CreateTomoDir(param.tomoDir.c_str()))
		{
			cout << "Can not create >> " << param.tomoDir << endl;
			cout.flush();
			exit(-3);
		};
		int startIdx = param.startIndex;
		char tomgramFile[500];
        
		//-ju-18-Dec-2015 add openmp
//		omp_set_num_threads(2);
//#pragma omp parallel for shared(h_backproj_chunk)
		for(int i =yChunkStart; i<yChunkEnd; i++)
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
				//index++;
			}
			else
			{
                //-ju-14-Apr-2015 --> add
                int id;
                if(1 == param.viewDirection)
                {
                    id = i+startIdx;
                    //printf("DPC Write id=%d\n", id);
                }
                else
                {
                    id = param.volY - (i+startIdx) + 1;
                    //printf("ABS Write id=%d\n", id);
                }
                //-ju-14-Apr-2015 <-- add
				//-ju-14-Apr-2015 int id = param.volY - (i+startIdx) + 1;
				sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
					param.tomoDir.c_str(),param.tomoName.c_str(),
					param.volX,param.volZ,param.volY,
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
			index++;
		}
        
		io_stop = clock();
		io_time += (float)(io_stop - io_start) / CLOCKS_PER_SEC;

#ifdef _ASYNC_IO
		cudaFreeHost(h_backproj_chunk);
#else
		delete[] h_backproj_chunk;
#endif
		delete[] h_sinoData;
		//-ju-27-Oct-2011delete [] h_backProj;
	}
	//-ju-15-Mar-2011 release resources lookup
	//ReleaseLookUpResources();

	//-ju-21-Oct-2014 cudaThreadExit(); --> replaced by cudaDeviceReset()
    cudaDeviceReset();
	stop = clock();
	float duration = (float)(stop - start) / CLOCKS_PER_SEC;
	*maxGray = tomoMax;
	*minGray = tomoMin;

	/*
	if(param.outDataType == "byte")
	{
		printf("\n\n--------------------------------------------\n");
		printf("  Converting Real 32-Bit to 8-Bit tomgrams\n");
		ConvertTomoDataUC8(param, tomoMax, tomoMin);
		printf("--------------------------------------------\n");
	}
	if(param.outDataType == "short16")
	{
		printf("\n\n----------------------------------------------------\n");
		printf("  Converting Real 32-Bit to Signed 16-Bit tomgrams\n");
		ConvertTomoDataI16(param, tomoMax, tomoMin);
		printf("----------------------------------------------------\n");
	}
	if(param.outDataType == "ushort16")
	{
		printf("\n\n----------------------------------------------------\n");
		printf("  Converting Real 32-Bit to unsigned 16-Bit tomgrams\n");
		ConvertTomoDataUI16(param, tomoMax, tomoMin);
		printf("----------------------------------------------------\n");
	}
	if(param.outDataType == "real32")
	{
		// do nothing
	}
    */

	size_t pos = param.projectName.find(".");
	string scalename = param.projectName.substr(0,pos);
	scalename += ".log";

	printf("\n--------------Timming----------------------\n");
	printf("Total runtime:              %#4.1f seconds\n", duration );
	printf("IO time without conversion: %#4.1f seconds\n", io_time );
	printf("Runtime without io:         %#4.1f seconds\n", duration-io_time);
	printf("Minimal gray value:         %f\n", tomoMin);
	printf("Maximal gray value:         %f\n", tomoMax);
	printf("---------------------------------------------\n");

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
