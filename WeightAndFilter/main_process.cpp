/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "filter.h"
#include "parameter.h"
#include "pre_process_pipeline.h"
#include "data_IO.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
//#include <opencv/cv.h>
#include "utility.h"
//#include <mpi.h>
#include <windows.h>
#include "FilterException.h"
#include "utils.h"
#include <ctime>

/*
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
*/

//-ju-05-Mar-2014
#ifdef _OPENMP
	#include <omp.h>
#endif


int gNumOfProc;
int gProcNumber;

using namespace std;
using namespace FDK;


struct Files
{
	FILE *sinoF32;
	FILE *sinoF32_1;
	FILE *sinoF32_2;
	FILE *sino;
};

// c++ to c wrapper; C-function used for QtConcurrent::run()
int ExecPreProcessPipline(int threadNum,int threadId,Files files,FDK_Parameters fdkPar)
{
	PreProcessPipeline preProcPipe(fdkPar);
	preProcPipe.PreProcessSinogramsToDisk(threadNum,threadId,files.sinoF32,files.sinoF32_1,files.sinoF32_2,files.sino);
	return 0;
}

int main(int argc, char* argv[])
{
	//QCoreApplication a(argc, argv);

#ifdef _TIMING_ON
	clock_t r_start, r_stop;
#endif

	if(argc != 2)
	{
		cerr << "Usage: FTK_Filter.exe parameter_file\n";
		exit(-1);
	}
	PrintVersion(&argv[0]);
	Parameter par(argv[1]);
	FDK_Parameters fdkPar = par.GetParameters();

	/*
	//-ju-25-Nov-2011 use registry 
	QSettings SoftwareSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\EMPA_SOFTWARE\\Recon_Software", QSettings::NativeFormat);
	QString regPreProcBlockFile = SoftwareSettings.value("PRE_PROC_BLOCKFILE").toString();
	if(regPreProcBlockFile.isEmpty())
	{
		//cerr << ">>> Warning! <<< Pre-Processed Sinogram Block File Name is not specified.\n\tUse ConfigFDK.exe to change configuration.\n";
	}
	else
	{
		fdkPar.sino32BlockFile.resize(regPreProcBlockFile.size());
		for(int i = 0; i < regPreProcBlockFile.size(); i++)
		{
			fdkPar.sino32BlockFile[i] = regPreProcBlockFile[i].toLatin1();
		}
		//fdkPar.sino32BlockFile = regPreProcBlockFile.toStdString();
	}
	*/

	/*-ju-25-Nov-2011 don't use environment variable anymore
	//-ju-10-Nov-2011 add setup of blockfile writing 
	//				  file name specified with env. variable
	char* envBlock = getenv("PRE_PROC_BLOCKFILE");
	if(envBlock)
	{
		fdkPar.sino32BlockFile = envBlock;
	}
	else
	{
		cerr << ">>> Warning! <<< Environment variable:\n\t PRE_PROC_BLOCKFILE \n   not specified\n";
	}
	*/

	//-ju-21-10-2011 <--
	int threadNum = fdkPar.numThreads;
//	QVector<QFuture<int> > futureVec(threadNum);
	// block file pointers
	Files files;
	files.sino      = 0;
	files.sinoF32   = 0;
	files.sinoF32_1 = 0;
	files.sinoF32_2 = 0;
/*-ju

	if(fdkPar.sino32BlockWrite)
	{
		if(regPreProcBlockFile.isEmpty())
		{
			regPreProcBlockFile = "- undef file -";
		}
		QFile file(regPreProcBlockFile);
		if(!file.exists())
		{
			cerr << ">>> Error! << Pre-Processed Sinogram Block File: " << regPreProcBlockFile.toStdString() << " does not exist.\n";
			return -1;
		}
		//if(envBlock == 0)
		//{
		//	cerr << ">>> Error! <<< Environment variable: PRE_PROC_BLOCKFILE not set\n";
		//	exit(-2);
		//}

		// check if block file is large enough
		QFile ckFile(fdkPar.sino32BlockFile.c_str());
		long long projBlockSize = 
			(long long)fdkPar.imageWidth*
			(long long)fdkPar.imageHeight*
			(long long)fdkPar.cntProjection*
			(long long)sizeof(float);
		if(ckFile.size() < projBlockSize)
		{
			fprintf(stderr,">>> Error! <<< File size of %s is to small!\n",fdkPar.sino32BlockFile.c_str());
			exit(-2);
		}

		files.sinoF32 = fopen(fdkPar.sino32BlockFile.c_str(),"r+b");
		if(!files.sinoF32)
		{
			fprintf(stderr,">>> Error! <<< Can not open Pre-Processed Sinogram block file!\n");
			exit(-2);
		}
	}
-ju-*/

	// implementation for 2 GPUs - in work
#ifdef _2_GPUS
	files.sinoF32_1 = fopen("F:/Data/CT-Data/coffee/Seq_Sino.sin.1.sinoF32","r+b");
	if(!files.sinoF32_1)
	{
		fprintf(stderr,"can not open F:/Data/CT-Data/coffee/Seq_Sino.sin.1.sinoF32\n");
		return -1;
	}
	files.sinoF32_2 = fopen("F:/Data/CT-Data/coffee/Seq_Sino.sin.2.sinoF32","r+b");
	if(!files.sinoF32_2)
	{
		fprintf(stderr,"can not open F:/Data/CT-Data/coffee/Seq_Sino.sin.2.sinoF32\n");
		return -1;
	}
#endif

	// reading from block sinogramm - not used
#ifdef _READ_BLOCK_SINO
	files.sino = fopen("F:/Data/CT-Data/coffee/SinoBlock/sino1120x1184_720.raw","r+b");
	if(!files.sino)
	{
		fprintf(stderr,"can not open F:/Data/CT-Data/coffee/SinoBlock/sino1120x1184_720.raw\n");
		return -1;
	}
#endif

#ifdef _TIMING_ON
	r_start = clock();
#endif
	//-ju-05-Mar-2014
	int i;
	omp_set_num_threads(threadNum);
	printf("Total number of threads %d\n",omp_get_max_threads());
#pragma omp parallel for shared(i,files) firstprivate(fdkPar,threadNum)
	for(i = 0; i < threadNum; i++)
	{
		printf("Run thread %d\n",omp_get_thread_num());
		ExecPreProcessPipline(threadNum,i,files,fdkPar);
	}
#ifdef _TIMING_ON
	r_stop = clock();
	float r_time = (float)(r_stop - r_start) / CLOCKS_PER_SEC;
	printf("Total run time: %#4.1f seconds\n", r_time);
#endif

	if(files.sinoF32 != 0)
		fclose(files.sinoF32);

#ifdef _2_GPUS
	fclose(files.sinoF32_1);
	fclose(files.sinoF32_2);
#endif

#ifdef _READ_BLOCK_SINO
	fclose(files.sino);
#endif

	return 0;
}