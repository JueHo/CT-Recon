/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "pre_process_pipeline.h"
#include "utility.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <map>
#include <cstdio>
#include "data_IO.h"
//#include <mpi.h>
#include <iostream>
#include <ctime>

//#include <QtCore/QDebug>
//#include <QtCore/QThread>
//#include <QtCore/QString>
//#include <QtConcurrent/qtconcurrentrun.h>
//#include <QtCore/QCoreApplication>


extern int gNumOfProc;
extern int gProcNumber;

using namespace FDK;
using namespace std;

/////////////////////////////////////////////////////////////////////
// public member functions
/////////////////////////////////////////////////////////////////////

int PreProcessPipeline::PreProcessSinogramsToDisk(int threadNum,
												  int threadId,
												  FILE *fpF32,
												  FILE *fpF32_1,
												  FILE *fpF32_2,
												  FILE *fpSino)
{
	// create IO-object used for 
	// reading and writing of sinograms
	SinoIO sinoIO_Obj(m_parameter);
	sinoIO_Obj.CreateSinoProcessedDir();
	// no file list
	if(!m_parameter.useSinoFileList && !m_parameter.limAngleBProj)
	{
		PreProcessFromSinoDir(sinoIO_Obj,threadNum,threadId,fpF32,fpF32_1,fpF32_2,fpSino);
		return 1;
	}
	// use file list
	if(m_parameter.useSinoFileList && !m_parameter.limAngleBProj)
	{
		PreProcessFromSinoList(sinoIO_Obj, "_SinFList.lst", false);
		return 1;
	}
	// limited angle file list
	if(m_parameter.useSinoFileList && m_parameter.limAngleBProj)
	{
		PreProcessFromSinoList(sinoIO_Obj, "_LimAngFList.lst", true);
		return 1;
	}
	return 1;
}

int PreProcessPipeline::ApplyFilter(cv::Mat &sinoImg)
{
	// weight sinogram using weight mask
	/////////////////////////////////////
	sinoImg = sinoImg.mul(m_weightMask);

	// create filter mask
	//////////////////////
	//CreateComplxFilterFFT();

	// create complex sinogram image
	cv::Mat sino2D_re(sinoImg);
	cv::Mat sino2D_im(sinoImg.size(),sinoImg.type(),cv::Scalar(0.0f));
	vector<cv::Mat> sinoVector(2);
	sinoVector[0] = sino2D_re;
	sinoVector[1] = sino2D_im;
	cv::Mat sino2DCmplxTmp(sinoImg.size(),CV_32FC1);
	cv::merge(sinoVector,sino2DCmplxTmp);
	// create zero padded matrix (using optimal width) and copy
    // original projection on it
	unsigned int zp_size = Utility::ZeroPadBase2Len(2*sinoImg.cols-1);
    cv::Mat sino2DCmplxTmp_ZP(sino2DCmplxTmp.rows, 
							  zp_size,
                              sino2DCmplxTmp.type(), 
                              cv::Scalar::all(0));

    // copy not zero padded complex matrix to zero padded matrix
    cv::Mat roiComplex(sino2DCmplxTmp_ZP,
                       cv::Rect(0,0,
                                sino2DCmplxTmp.cols,
                                sino2DCmplxTmp.rows)
                       );
    sino2DCmplxTmp.copyTo(roiComplex);

	// FFT of sinogram data
	////////////////////////
	cv::dft(sino2DCmplxTmp_ZP,sino2DCmplxTmp_ZP,
		    cv::DFT_ROWS + cv::DFT_COMPLEX_OUTPUT);


    // Spectrum multiplication
    //////////////////////////
    cv::mulSpectrums(sino2DCmplxTmp_ZP,
                     m_filter2DCmplx,	
                     sino2DCmplxTmp_ZP,
                     cv::DFT_ROWS);

    // inverse FFT
    /////////////////
    cv::dft(sino2DCmplxTmp_ZP, 
            sino2DCmplxTmp_ZP, 
            cv::DFT_INVERSE 
            + cv::DFT_SCALE
            + cv::DFT_ROWS 
            + cv::DFT_COMPLEX_OUTPUT);
    // copy the result back to original matrix
    sino2DCmplxTmp_ZP(cv::Rect(0,0,sino2DCmplxTmp.cols,sino2DCmplxTmp.rows)).copyTo(sino2DCmplxTmp);
    
    cv::split(sino2DCmplxTmp,sinoVector);
	// use only real part of image
    sinoVector[0](cv::Rect(0,0,sinoVector[0].cols,sinoVector[0].rows)).copyTo(sinoImg);

	// create zero border by multiplying image with border mask
	////////////////////////////////////////////////////////////
	//-ju-21-Feb-2012 new
	//sinoImg *= m_parameter.pixelSize;
	//-ju-21-Feb-2012
	sinoImg = sinoImg.mul(m_zeroBorderMask);

	return 1;
}

/////////////////////////////////////////////////////////////////////
// private member functions
/////////////////////////////////////////////////////////////////////

int PreProcessPipeline::PreProcessFromSinoDir(SinoIO &sinoIO,
											  int threadNum,
											  int threadId,
											  FILE *fpF32,
											  FILE *fpF32_1,
											  FILE *fpF32_2,
											  FILE *fpSino)
{
	//if(!sinoIO.VerifyImageSize())
	//{
	//	FILTER_ERROR err = err_file_size;
	//	throw FilterException(err, "Difference in specified and actual sinogram file size");
	//}

	// paramters
	int numOfProj  = m_parameter.cntProjection;
	int firstIndex = m_parameter.startIndex;

	int thr = m_parameter.numThreads;

	/*
	int blocks = numOfProj/thr;
	int remain = numOfProj%thr;
	vector<int> blockCount(thr,blocks);
	for(int i = 0; i < thr; i++)
	{
		blockCount[i] *= (i+1);
	}
	blockCount[thr-1] += remain;
	*/

	int index = 0;
	for(int fileNum = firstIndex; fileNum < numOfProj + firstIndex; fileNum++)
	{
		int id = fileNum%threadNum;
		if(id == threadId)
		{
		//__if(fileNum <= blockCount[threadId] && fileNum > threadId*blocks)
		//__{
			cv::Mat sinoImage;
			string datType = m_parameter.inDataType;
			if(datType == "byte")
			{
				sinoIO.ReadSinogramUChar8(sinoImage,fileNum);
			}
			else
			if(datType == "short16")
			{
				sinoIO.ReadSinogramShort16(sinoImage,fileNum);
			}
			else
			if(datType == "ushort16")
			{
				sinoIO.ReadSinogramUShort16(sinoImage,fileNum);
#ifdef _READ_BLOCK_SINO
				sinoIO.ReadBlockSinogramUShort16(sinoImage,index,fpSino);
#endif
			}
			else
			if(datType == "int32")
			{
				sinoIO.ReadSinogramInt32(sinoImage,fileNum);
			}
			else
			if(datType == "real32")
			{
				sinoIO.ReadSinogramFloat32(sinoImage,fileNum);
#ifdef _READ_BLOCK_SINO
				sinoIO.ReadBlockSinogramFloat32(sinoImage,index,fpSino);
#endif
			}
			else
			{
				// unknown data type
				FILTER_ERROR err = err_unknown_data_type;
				throw FilterException(err, datType);
			}
			ApplyFilter(sinoImage);
			if(m_parameter.flipImageFlag != 2)
			{
				cv::flip(sinoImage,sinoImage,m_parameter.flipImageFlag);
				sinoIO.WriteSinogram(sinoImage,fileNum);
			}
			else
			{

				if(m_parameter.sino32BlockWrite)
				{
					sinoIO.WriteBlockSinogram(sinoImage,index,fpF32);
#ifdef _2_GPUS
					sinoIO.WriteBlockSinogramMultGPU(sinoImage,index,fpF32_1,fpF32_2);
#endif
				}
				else
				{
					sinoIO.WriteSinogram(sinoImage,fileNum);
#ifdef _2_GPUS
					sinoIO.WriteSinogramMultGPU(sinoImage,fileNum);
#endif
				}
			}
		}
		index++;
	}
	return 1;
}

int PreProcessPipeline::PreProcessFromSinoList(SinoIO &sinoIO, const char* sinListPost, bool limited)
{
	// path to list file
	size_t pos = m_parameter.parameterFile.find_last_of("/\\");
	if(pos+1 > m_parameter.parameterFile.length())
	{
		return -2;
	}
	string projFile = m_parameter.parameterFile.substr(pos+1);
	string fileListPath = m_parameter.parameterFile.substr(0,pos+1);
	pos = projFile.find_last_of(".");
	string listFile = projFile.substr(0,pos);
	listFile += sinListPost;
	fileListPath += listFile;

	// load filenames to memory
	ifstream listFileStream(fileListPath.c_str());
	string line;
	map<string,float> fileList;
	if(!listFileStream.is_open())
	{
		std::cout << "Can not open >> " << fileListPath << " <<\n";
		return -3;
	}
	string first_file;
	int idx = 0;
	while(!listFileStream.eof())
	{
		string path, isEqual, segment;
		float degree;
		if(limited)
		{
			listFileStream >> segment >> isEqual >> path >> isEqual >> degree;
		}
		else
		{
			listFileStream >> path >> isEqual >> degree;
		}
		if(path.length() > 0)
		{
			fileList.insert(ValuePair(path,degree));
			if(idx == 0)
			{
				first_file = path;
			}
			idx++;
		}
	}

	if(!sinoIO.VerifyImageSize(first_file.c_str()))
	{
		FILTER_ERROR err = err_file_size;
		throw FilterException(err, "Difference in specified and actual sinogram file size");
	}

	FileListMapType::const_iterator iter = fileList.begin();
	//double t, dt = 0.0;
	int i = 0;
	while(iter != fileList.end()) 
	{
		string file = (*iter).first;

		size_t p = file.find_last_of("/\\");
		string projFile = file.substr(p+1);

		pos = file.find_first_of(".");
		string num = file.substr(pos-4,4);
		int inum = atoi(num.c_str());
		int id = inum%gNumOfProc;
		if(id == gProcNumber)
		{
			
			cv::Mat sinoImage;
			string datType = m_parameter.inDataType;
			if(datType == "byte")
			{
				sinoIO.ReadSinogramUChar8(sinoImage,file.c_str());
			}
			else
			if(datType == "short16")
			{
				sinoIO.ReadSinogramShort16(sinoImage,file.c_str());
			}
			else
			if(datType == "ushort16")
			{
				sinoIO.ReadSinogramUShort16(sinoImage,file.c_str());
			}
			else
			if(datType == "int32")
			{
				sinoIO.ReadSinogramInt32(sinoImage,file.c_str());
			}
			else
			if(datType == "real32")
			{
				sinoIO.ReadSinogramFloat32(sinoImage,file.c_str());
			}
			else
			{
				// unknown data type
				FILTER_ERROR err = err_unknown_data_type;
				throw FilterException(err, datType);
			}
			//if(gProcNumber == 0)
			//{
			//	t = MPI_Wtime();
			//}
			ApplyFilter(sinoImage);
			//if(gProcNumber == 0)
			//{
			//	t = MPI_Wtime() - t;
			//	dt += t;
			//}
			if(m_parameter.flipImageFlag != 2)
			{
				cv::flip(sinoImage,sinoImage,m_parameter.flipImageFlag);
				sinoIO.WriteSinogram(sinoImage,projFile);
			}
			else
			{
				sinoIO.WriteSinogram(sinoImage,projFile);
			}
		}
		++iter;
	}
	//MPI::COMM_WORLD.Barrier();
	//if(gProcNumber == 0)
	//{
	//	printf("\n");
	//	printf("\n\tRuntime Filter: %6.2lf s\n", dt);
	//	fflush(stdout);
	//}
	return 1;
}

int PreProcessPipeline::CreateWeightMask()
{
	//take centre of pixel for calculation
	const float pixCentre = 0.5f;

	// get parameters
	int imgWidth  = m_parameter.imageWidth;
	int imgHeight = m_parameter.imageHeight;
	float pixSize = m_parameter.pixelSize;
	float hOffset = m_parameter.horizShift;
	float vOffset = m_parameter.vertShift;

	// distance source detector in pixel size
	double dSrcDet = m_parameter.dsd/pixSize;
	double dzSquare = pow(dSrcDet,2);

	// calculate image centre
	double x_c = static_cast<double>(imgWidth)/2.0f;
	double y_c = static_cast<double>(imgHeight)/2.0f;
	// data storage
	vector<float> maskData(imgWidth*imgHeight);
	// create weight mask considering offsets in width and height
	for(int iy = 0; iy < imgHeight; iy++)
	{
		double dy = iy + pixCentre - y_c - vOffset;
		double dySquare = pow(dy,2);
		for(int ix = 0; ix < imgWidth ; ix++)
		{
			double dx = ix + pixCentre - x_c - hOffset;
			double dxSquare = pow(dx,2);
			double dist = sqrt(dxSquare + dySquare + dzSquare);
			maskData[iy*imgWidth+ix] = static_cast<float>(dSrcDet/dist);
		}
	}
	cv::Mat tmpMat(imgHeight,imgWidth,CV_32F,&maskData[0]);
	tmpMat.copyTo(m_weightMask);

#if 0
	ofstream testfile("weight.bin",ios::binary);
	testfile.write((char*) m_weightMask.data, sizeof(float)*m_weightMask.cols*m_weightMask.rows);
	testfile.close();
#endif

	return 0;
}

void PreProcessPipeline::CreateComplxFilterFFT()
{
	//cv::Mat filterImg;
	// for phase contrast filter the ramp filter is created as well but not used
	m_filter.Create2DSpaceDomainFilter();
	if(m_parameter.useDCPFilter)
	{
		m_filter.CalcComplxFilterFFTPhaseContrast();
	}
	else
	{
		m_filter.CalcComplxFilterFFT();
	}

}

int PreProcessPipeline::CreateZeroBorderMask()
{
	cv::Mat borderMask(m_parameter.imageHeight,
		               m_parameter.imageWidth,
					   CV_32F,
					   cv::Scalar::all(0.0f));
	m_zeroBorderMask = borderMask;
	// mark roi inside of border mask image
    cv::Mat roiImage(m_zeroBorderMask,
		             cv::Rect(1,1,m_zeroBorderMask.cols-2,m_zeroBorderMask.rows-2));
	// change value of roi to 1.0
	roiImage.setTo(cv::Scalar(1.0f));
	m_zeroBorderMask.copyTo(roiImage);
	return 1;
}