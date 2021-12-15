/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

/**********************************************************
*
* $Log: main.cpp $
* Revision 1.2  2010/12/21 06:47:32  Hofmann
* remove not used keywords
*
* Revision 1.1  2010/12/15 09:52:49  Hofmann
* Initial revision
*
* Revision 1.1  2010/10/19 13:16:00  Hofmann
* Initial revision
*
*
**********************************************************/
#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtCore/QFile>

#include <QtWidgets/QApplication>
#include "mainwindow.h"

#include "plot_struct.h"

#include "recon.h"
#include "typesFDK.h"
#include <windows.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <cfloat>
#include "parameter.h"
#include "utils.h"
#include <fstream>
#include <cstdlib>
#include "convert.h"

#include <Eigen/Dense>


#include <ctime>

using namespace std;

#define MBYTE(bytes) bytes/(1024*1024) 
#define KBYTE(bytes) bytes/(1024)

#include <LIMITS.H>

extern const float gMaxFLT = FLT_MAX;

char *parafilename;

int gMultiRowFlag = 0;
int gCurrentSlice;

QVector<double> g_X;
QVector<double> g_Y;

//-ju- vector for linear square fit
std::vector<float> h_val;
std::vector<float> h_slice;


int main(int argc, char* argv[])
{
	// Print version info
	/////////////////////
	PrintVersion(&argv[0]);

	// parameter file input
	///////////////////////
	if (argc < 2)
	{
		std::cout << "Missing parameter file! --> Quit program\n";
		exit(-1);
	}
	FDK::Parameter par(argv[1]);
	parafilename = argv[1];

	//-ju-25-Mai-2015
	// slice which should be used
	// set default interval
	///////////////////////////////
	int rowSelection = -1;
	float pixShiftMin = -15.0f;
	float pixShiftMax = 15.0f;
	float shiftStep = 0.1f;
	int numberSlices = 1;
	int rowStep = 1;
	if (argc == 6)
	{
		rowSelection = atoi(argv[2]);
		pixShiftMin = atof(argv[3]);
		pixShiftMax = atof(argv[4]);
		shiftStep = atof(argv[5]);
	}
	if (argc == 8)
	{
		rowSelection = atoi(argv[2]);
		pixShiftMin = atof(argv[3]);
		pixShiftMax = atof(argv[4]);
		shiftStep = atof(argv[5]);
		numberSlices = atoi(argv[6]);
		rowStep = atoi(argv[7]);
		gMultiRowFlag = 1;
	}
	//-ju-16-June-2015
	PlotData plData;

	clock_t start, stop;
	if (gMultiRowFlag == 1)
	{
		start = clock();
	}



	//-ju-loop over slice stack --> multirow
	/////////////////////////////////////////
	//-ju- container for selected slices
	std::vector<int> sel_slices;
	for (int i = 0; i < numberSlices*rowStep; i += rowStep)
	{
		int sl = rowSelection;
		sl += i;
		gCurrentSlice = sl;
		int sliceSelection = sl;

		int cntOfShiftSlices = static_cast<int>((pixShiftMax - pixShiftMin) / shiftStep) + 1;

		if (gMultiRowFlag == 0)
		{
			cout << "\n\n*************** rotation estimation parameters ***************\n";
			cout << "\tSlice selection: " << sliceSelection << endl;
			cout << "\tInterval minimum: " << pixShiftMin << endl;
			cout << "\tInterval maximum: " << pixShiftMax << endl;
			cout << "\tShift stepping: " << shiftStep << endl;
			cout << "**************************************************************\n\n";

		}
		else
		{
			cout << " ==> Slice: " << sliceSelection 
				 << "  cnt/interval: " << cntOfShiftSlices 
				 << "  shift interval [" << pixShiftMin << "," << pixShiftMax << "]  step: " 
				 << shiftStep << endl;
			sel_slices.push_back(sliceSelection);
		}
		// calculate cpu memory consumption
		///////////////////////////////////


		// get phys. available memory in MBytes
		///////////////////////////////////////
		size_t availPhysMem;
#if defined(_WIN64)
		MEMORYSTATUSEX memStatEx;
		memStatEx.dwLength = sizeof(memStatEx);
		GlobalMemoryStatusEx(&memStatEx);
		availPhysMem = MBYTE(memStatEx.ullAvailPhys);
#else
		MEMORYSTATUS memStat;
		memStat.dwLength = sizeof(memStat);
		GlobalMemoryStatus(&memStat);
		availPhysMem = MBYTE(memStat.dwAvailPhys);
#endif
		if (gMultiRowFlag == 0)
		{
			cout << "Available physical memory: " << availPhysMem << " MBytes\n";
		}

		// GPU properties
		vector<GraphicCardProp> gpuPropV;
		GetGraphicCardProp(gpuPropV);

		// check for Cuda enabled devices
		if (gpuPropV.size() < 1)
		{
			cout << "No Cuda enabled device --> found: "
				<< gpuPropV.size() << " device(s)\n";
			exit(-3);
		}
		else
		{
			if (gpuPropV.size() > 1)
			{
				if (gMultiRowFlag == 0)
				{
					cout << "Found " << gpuPropV.size() << " Cuda enabled devices.\n"; // Cuda enabled devices. Use device 2\n";
				}
				cudaSetDevice(0);
			}
		}
		cout.flush();
		// calculate chunks for gpu- and cpu-memory
		///////////////////////////////////////////
		FDK::FDK_Parameters para = par.GetParameters();
		int cpuMemUsage = static_cast<int>(para.cpuMemoryUsage);
		int gpuMemUsage = static_cast<int>(para.gpuMemoryUsage);
		//-ju-05-July-2011 using file list or lim. angle file list
		//				   count number of projections from file
		//////////////////////////////////////////////////////////
		if (para.useSinoFileList == 1 || para.limAngleBProj == 1)
		{
			// clear up lists
			para.angleList.clear();
			para.fileList.clear();
			string paramFile = argv[1];
			size_t pos = paramFile.find_last_of(".");
			paramFile = paramFile.substr(0, pos);
			string filename;
			float angle;
			string seperator;
			string segment;
			if (para.useSinoFileList == 1 && para.limAngleBProj == 0)
			{
				paramFile += "_SinFList.lst";
				ifstream fList(paramFile.c_str());
				if (!fList.is_open())
				{
					cout << "Can not open list file >> " << paramFile << " >>\n";
					return -2;
				}
				int fileCnt = 0;
				while (!fList.eof())
				{
					angle = -1.0f;
					filename = "";
					// example
					// D:\Projekte\ProjektDaten\SteelSpheres\sino\sinoMorRef0002.raw = 2.6
					fList >> filename >> seperator >> angle;
					if (filename.length() > 0 && angle >= 0.0f)
					{
						para.angleList.push_back(angle);
						para.fileList.push_back(filename);
						fileCnt++;
					}
				}
				para.cntProjection = fileCnt;
			}
			if (para.limAngleBProj == 1)
			{
				paramFile += "_LimAngFList.lst";
				ifstream fList(paramFile.c_str());
				if (!fList.is_open())
				{
					cout << "Can not open list file >> " << paramFile << " >>\n";
					return -2;
				}
				int fileCnt = 0;
				while (!fList.eof())
				{
					angle = -1.0f;
					filename = "";
					// example
					// Segment-01 = D:/Projekte/ProjektDaten/wuerfel/sino/Sin3gramrfre_0001.sin = 0.00
					fList >> segment >> seperator >> filename >> seperator >> angle;
					if (filename.length() > 0 && angle >= 0.0f)
					{
						para.angleList.push_back(angle);
						para.fileList.push_back(filename);
						fileCnt++;
					}
				}
				para.cntProjection = fileCnt;
			}
		}
		//////////////////////////////////////
		//-ju- prepare for auto rot. ax. det.
		//////////////////////////////////////
		int	numOfProjections = para.cntProjection;
		int imageWidth = para.imageWidth;
		int imageHeight = para.imageHeight;
		int volXLength = para.volumeX;

		//-ju- take here stack of shifted slices
		//	   instead of volume stack
		int volYLength = cntOfShiftSlices;

		int volZLength = para.volumeZ;
		int wOrigX = 0;
		//-ju-25-may-2015 use central slice as default
		///////////////////////////////////////////////
		int wOrigY = (int)((float)imageHeight / 2.0f);
		if (sliceSelection != -1)
		{
			//-ju- Set origin of reconstruction
			//     stack stack to selected slice.
			//     Stack size height is 1!
			//     Meaning: Only wOrigY with index iy = 0 
			//     will be reconstructed.
			//     Valid for single and multi row case.
			wOrigY = sliceSelection; 
		}
		int wOrigZ = 0;
		int binFactor = para.previewScale;

		if (gMultiRowFlag == 0)
		{
			cout << "px=" << para.winVolOrigX << "  py=" << para.winVolOrigY << "  pz=" << para.winVolOrigZ << endl;
			cout << "lx=" << volXLength << "  ly=" << volYLength << "  lz=" << volZLength << endl;
		}


		// gpu memory; all projections (data type is float)
		unsigned int totalMemGpu = KBYTE(KBYTE(imageWidth*imageHeight * sizeof(float))*numOfProjections);
		//-ju-14-July-2011 take at least 1 KB to prevent for div. with 0
		if (totalMemGpu == 0)
		{
			totalMemGpu = 1;
		}
		// take gpu memory usage into account
		size_t memGpuMB = gpuPropV[0].globalMem*gpuMemUsage / 100;
		// calculate number of projection chunks
		size_t gpuChunk = totalMemGpu / memGpuMB;
		unsigned int gpuChunkRemainder = totalMemGpu % memGpuMB;
		if (gpuChunkRemainder != 0)
		{
			gpuChunk++;
		}

		unsigned long long reconVolMemMB;
		if (binFactor == 1)
		{
			reconVolMemMB = KBYTE(KBYTE(sizeof(float)*volXLength*volYLength)*volZLength);
		}
		else
		{
			reconVolMemMB =
				KBYTE(KBYTE(sizeof(float)*volXLength / binFactor * volYLength / binFactor)*volZLength / binFactor);
		}

		//-ju-14-July-2011 take at least 1MB of memory
		if (reconVolMemMB == 0)
		{
			reconVolMemMB = 1;
		}
		size_t totalCpuMem = reconVolMemMB + totalMemGpu / gpuChunk;
		// add a safety buffer of 10%
		totalCpuMem = totalCpuMem * 110 / 100;
		// take memory usage into account
		availPhysMem = availPhysMem * cpuMemUsage / 100;
		size_t cpuChunk = totalCpuMem / availPhysMem;
		size_t cpuChunkRemainder = totalCpuMem % availPhysMem;
		if (cpuChunkRemainder != 0)
		{
			cpuChunk++;
		}

		// fill parameter struct used for backprojection
		////////////////////////////////////////////////
		BackProjParam backProjParam;
		backProjParam.numProj = numOfProjections;
		backProjParam.projectionChunkSize = gpuChunk;
		backProjParam.sliceChunkSize = cpuChunk;
		backProjParam.binFac = binFactor;
		//-ju-05-July-2011 set file list switches
		backProjParam.useFileList = para.useSinoFileList;
		backProjParam.useLimAngle = para.limAngleBProj;
		if (para.useSinoFileList == 1 || para.limAngleBProj == 1)
		{
			backProjParam.angleList = para.angleList;
			backProjParam.sinoList = para.fileList;
		}
		//-ju-14-Nov-2011 add block IO parameters
		backProjParam.sino32BlockUse = para.sino32BlockUse;
		backProjParam.tomoBlockWrite = para.tomoBlockWrite;
		//-ju-25-Nov-2011 check registry settings
		//////////////////////////////////////////
		QSettings SoftwareSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\EMPA_SOFTWARE\\Recon_Software", QSettings::NativeFormat);
		QString val = SoftwareSettings.value("PRE_PROC_BLOCKFILE").toString();
		if (val.isEmpty())
		{
			//-ju-18-Nov-2013 cerr << ">>> Warning! <<< Pre-Processed Sinogram Block File Name is not specified.\n\tUse ConfigFDK.exe to change configuration.\n";
		}
		else
		{
			backProjParam.sino32BlockFile = val.toStdString();
			para.sino32BlockFile = backProjParam.sino32BlockFile;
		}

		//-ju-25-may-2015 extensions for rotation axis determination
		////////////////////////////////////////////////////////////////////
		backProjParam.sliceSelection = wOrigY;
		// negative interval part
		backProjParam.pixShiftMin = static_cast<int>(pixShiftMin / shiftStep);
		// positive interval part
		backProjParam.pixShiftMax = static_cast<int>(pixShiftMax / shiftStep);
		// number of shift steps
		backProjParam.cntShiftSteps = cntOfShiftSlices;
		// step size
		backProjParam.shiftStep = shiftStep;
		//-ju-25-may-2015
		/////////////////////////////////////////////////////////////////////

		// does not work anymore!
		val = SoftwareSettings.value("TOMO_BLOCK_FILE").toString();
		if (val.isEmpty())
		{
			//cerr << ">>> Warning! <<< Tomogram Block File Name is not specified.\n\tUse ConfigFDK.exe to change configuration.\n";
		}
		else
		{
			backProjParam.tomoBlockFile = val.toStdString();
			para.tomoBlockFile = backProjParam.tomoBlockFile;
		}

		// parameters of backprojection volume
		// x,y,z-edge length and 3D-window origin position
		float winOrigX = 0.0f;
		float winOrigY = 0.0f;
		float winOrigZ = 0.0f;
		if (binFactor == 1)
		{
			backProjParam.volX = volXLength;
			backProjParam.volY = volYLength;
			backProjParam.volZ = volZLength;
			winOrigX = static_cast<float>(wOrigX);
			winOrigY = static_cast<float>(wOrigY);
			winOrigZ = static_cast<float>(wOrigZ);
			backProjParam.useVolWin = true;
		}
		else
		{
			backProjParam.volX = imageWidth / binFactor;
			backProjParam.volY = imageHeight / binFactor;
			backProjParam.volZ = imageWidth / binFactor;
			backProjParam.useVolWin = false;
		}
		backProjParam.wVolOrigX = winOrigX;
		backProjParam.wVolOrigY = winOrigY;
		backProjParam.wVolOrigZ = winOrigZ;

		backProjParam.dso = para.dso;
		backProjParam.magnification = para.dsd / para.dso;
		backProjParam.imgWidth = para.imageWidth;
		backProjParam.imgHeight = para.imageHeight;
		backProjParam.pixSize = para.pixelSize;
		backProjParam.shiftX = para.horizShift;
		backProjParam.shiftY = para.vertShift;
		backProjParam.outDataType = para.outDataType;
		backProjParam.startIndex = para.startIndex;
		backProjParam.startAngle = para.startAngle;
		backProjParam.sinoPreProcDir = para.sinoDir32;
		backProjParam.sinoLimPreProcDir = para.sinoDirLim32; //-ju-05-July-2011 new
		backProjParam.sinoName = para.sinoName;
		//-ju-22-Nov-2017 Create a different directory for Rotation Axis Determination (extension _RAD
		size_t len = para.tomoDir.size() - 1;
		para.tomoDir.resize(len);
		backProjParam.tomoDir = para.tomoDir + "_RAD/";
		//backProjParam.tomoDir				= para.tomoDir;
		//-ju-22-Nov-2017 Create a different directory for Rotation Axis Determination (extension _RAD
		backProjParam.tomoName = para.tomoName;
		backProjParam.threadX = para.threadsX;
		backProjParam.threadY = para.threadsY;
		//-ju-15-Nov-2011 
		backProjParam.convertBlockInternal = para.convertBlockInternal;
		//-ju-11-July-2011 add project name
		backProjParam.projectName = argv[1];

		if (binFactor == 1)
		{
			// check if 3D-window is within image size
			if (winOrigX + volXLength - imageWidth > FLT_EPSILON)
			{
				cout << "   Warning: Selected window width exceeds maximal size!\n";
				cout << "   Reset volume reconstruction length in x direction to: " << imageWidth - winOrigX << endl;
				backProjParam.volX = volXLength = imageWidth - static_cast<int>(winOrigX);
				if (imageWidth - winOrigX < 1)
				{
					cout << "   Offset to sub volume origin point exceeds volume dimension --> Exit\n";
					exit(-1);
				}
			}
			if (winOrigY + volYLength - imageHeight > FLT_EPSILON)
			{
				//cout << "   Warning: Selected window height >> " << winOrigY + volYLength << " << exceeds maximal size!\n";
				//cout << "   Reset volume reconstruction length in y direction to: " << imageHeight - winOrigY << endl;
				//-ju-26-May-2015
				//////////////////
				backProjParam.volY = volYLength;// = imageHeight - static_cast<int>(winOrigY);
				//if(imageHeight - winOrigY < 1)
				//{
				//	cout << "   Offset to sub volume origin point exceeds volume dimension --> Exit\n";
				//	exit(-1);
				//}
			}
			if (winOrigZ + volZLength - imageWidth > FLT_EPSILON)
			{
				cout << "   Warning: Selected window depth exceeds maximal size!\n";
				cout << "   Reset volume reconstruction length in z direction to: " << imageWidth - winOrigZ << endl;
				backProjParam.volZ = volZLength = imageWidth - static_cast<int>(winOrigZ);
				if (imageWidth - winOrigX < 1)
				{
					cout << "   Offset to sub volume origin point exceeds volume dimension --> Exit\n";
					exit(-1);
				}
			}
		}
		float maxGray, minGray;

		////-ju-25-Nov-2011 check if block files exist are large enough (if used)
		//////////////////////////////////////////////////////////////////////////
		if (para.tomoBlockWrite)
		{
			QString val = SoftwareSettings.value("TOMO_BLOCK_FILE").toString();
			if (val.isEmpty())
			{
				val = "- undef file -";
			}
			QFile file(val);
			if (!file.exists())
			{
				cerr << ">>> Error! << Tomogram Block File: " << val.toStdString() << " does not exist.\n";
				return -1;
			}
			qint64 sz = file.size();
			// data from parameter file
			qint64 w = para.volumeX;
			qint64 h = para.volumeY;
			qint64 d = para.volumeZ;
			qint64 szVol = w * h*d * sizeof(float);
			if (szVol > sz)
			{
				cerr << ">>> Error! << Tomogram Block File: " << val.toStdString() << " File Size is too small.\n";
				return -1;
			}
		}
		if (para.sino32BlockUse)
		{
			QString val = SoftwareSettings.value("PRE_PROC_BLOCKFILE").toString();
			if (val.isEmpty())
			{
				val = "- undef file -";
			}
			QFile file(val);
			if (!file.exists())
			{
				cerr << ">>> Error! << Pre-Processed Sinogram Block File: " << val.toStdString() << " does not exist.\n";
				return -1;
			}
			qint64 sz = file.size();
			// data from parameter file
			qint64 w = para.imageWidth;
			qint64 h = para.imageHeight;
			qint64 p = para.cntProjection;
			qint64 szProj = w * h*p * sizeof(float);
			if (szProj > sz)
			{
				cerr << ">>> Error! << Pre-Processed Sinogram Block File: " << val.toStdString() << " File Size is too small.\n"
					"\tInput File is invalid.\n";
				return -1;
			}
		}

		//-ju-18-10-2011 use block volume file for output
		FILE *fpVol = 0;
		if (para.tomoBlockWrite)
		{
			cout << "  >> using tomo block file: " << para.tomoBlockFile.c_str() << endl;
			fpVol = fopen(para.tomoBlockFile.c_str(), "r+b");
			if (fpVol == 0)
			{
				fprintf(stderr, "Can not open %s --> exit\n", para.tomoBlockFile.c_str());
				return -1;
			}
		}
		//////////////////////
		// Run Reconstruction
		//////////////////////
		runFDK(backProjParam, 0, &minGray, &maxGray, fpVol, &plData);
		cout.flush();
		cerr.flush();

		if (para.tomoBlockWrite)
		{
			fclose(fpVol);
			fflush(fpVol);
		}

		//-ju-03-10-2011 data conversion
		////////////////////////////////////////////////////////////////////////////
		float maxGrayGlobal = maxGray;
		float minGrayGlobal = minGray;
		if (backProjParam.outDataType == "byte")
		{
			printf("\n--------------------------------------------\n");
			printf("  Converting Real 32-Bit to 8-Bit tomgrams ...\n");
			fflush(stdout);
			fflush(stderr);
			if (!backProjParam.tomoBlockWrite && !backProjParam.convertBlockInternal)
			{
				// float multi file to convert multi file
				ConvertTomoDataUC8(backProjParam, maxGrayGlobal, minGrayGlobal);
				printf("  Converting finished\n");
				fflush(stdout);
				fflush(stderr);
			}
			else
				if (backProjParam.tomoBlockWrite && !backProjParam.convertBlockInternal)
				{
					// float block file to convert multi file
					ConvertBlockTomoDataUC8(backProjParam, maxGrayGlobal, minGrayGlobal);
					printf("  Converting finished\n");
					fflush(stdout);
					fflush(stderr);
				}
				else
					if (backProjParam.tomoBlockWrite && backProjParam.convertBlockInternal)
					{
						// float block internal convert block
						ConvertBlockInternalTomoDataUC8(backProjParam, maxGrayGlobal, minGrayGlobal);
						printf("  Converting finished\n");
						fflush(stdout);
						fflush(stderr);
					}
					else
					{
						printf("  Converting multi tomo file to block file not supported\n");
					}
			printf("--------------------------------------------\n");
			fflush(stdout);
			fflush(stderr);
		}
		if (backProjParam.outDataType == "short16")
		{
			printf("\n----------------------------------------------------\n");
			printf("  Converting Real 32-Bit to Signed 16-Bit tomgrams ...\n");
			fflush(stdout);
			fflush(stderr);
			if (!backProjParam.tomoBlockWrite && !backProjParam.convertBlockInternal)
			{
				// float multi file to convert multi file
				ConvertTomoDataI16(backProjParam, maxGrayGlobal, minGrayGlobal);
				printf("  Converting finished\n");
				fflush(stdout);
				fflush(stderr);
			}
			else
				if (backProjParam.tomoBlockWrite && !backProjParam.convertBlockInternal)
				{
					// float block file to convert multi file
					ConvertBlockTomoDataI16(backProjParam, maxGrayGlobal, minGrayGlobal);
					printf("  Converting finished\n");
					fflush(stdout);
					fflush(stderr);
				}
				else
					if (backProjParam.tomoBlockWrite && backProjParam.convertBlockInternal)
					{
						// float block internal convert block
						ConvertBlockInternalTomoDataI16(backProjParam, maxGrayGlobal, minGrayGlobal);
						printf("  Converting finished\n");
						fflush(stdout);
						fflush(stderr);
					}
					else
					{
						printf("  Converting multi tomo file to block file not supported\n");
						fflush(stdout);
						fflush(stderr);
					}
			printf("----------------------------------------------------\n");
			fflush(stdout);
			fflush(stderr);
		}
		if (backProjParam.outDataType == "ushort16")
		{
			printf("\n----------------------------------------------------\n");
			printf("  Converting Real 32-Bit to unsigned 16-Bit tomgrams ...\n");
			fflush(stdout);
			fflush(stderr);
			if (!backProjParam.tomoBlockWrite && !backProjParam.convertBlockInternal)
			{
				// float multi file to convert multi file

				clock_t s, e;
				s = clock();
#define USE_PARALLEL
#ifdef USE_PARALLEL
				omp_set_num_threads(8);
				ConvertTomoDataUI16MT(backProjParam, maxGrayGlobal, minGrayGlobal);
#else
				ConvertTomoDataUI16(backProjParam, maxGrayGlobal, minGrayGlobal);
#endif
				e = clock();
				float dur = (float)(e - s) / CLOCKS_PER_SEC;
				printf("%5.2fs  Converting finished!\n", dur);
				fflush(stdout);
				fflush(stderr);
			}
			printf("----------------------------------------------------\n");
			fflush(stdout);
			fflush(stderr);
		}
		if (backProjParam.outDataType == "real32")
		{
			// do nothing
		}

	} // end multislice loop
	/////////////////////////////

	if (gMultiRowFlag == 1)
	{
		stop = clock();
		float duration = (float)(stop - start) / CLOCKS_PER_SEC;
		printf("\nTotal runtime:%#4.1f seconds\n", duration);

		//-ju- Linear square fit
		Eigen::VectorXf val(h_val.size());
		for (int i = 0; i < h_val.size(); i++)
		{
			val(i) = h_val[i];
		}
		Eigen::MatrixXf A(h_slice.size(), 2);
		for (int k = 0; k < h_slice.size(); k++)
		{
			A(k, 0) = 1.0f;
			A(k, 1) = static_cast<float>(sel_slices[k]);//h_slice[k];
		}
		//std::cout << "Eigen val:\n" << val << std::endl;
		//std::cout << "Eigen A:\n" << A << std::endl;
		Eigen::VectorXf s = A.colPivHouseholderQr().solve(val);
		std::cout << "\nLSQ solution using QR decomposition of Ax - b = 0 \nfor >> y = mx + c <<  is:\n" 
			      << "m = " << s(1) << ", c = " << s(0) << std::endl;
		//std::cout << "Residues:\n" << (A * s - val) << std::endl;
		Eigen::VectorXf res = (A * s - val);
		std::cout << "\nResidues:\n";
		for (int i = 0; i < res.size(); i++)
		{
			if (res.size() > 10)
			{
				if (i < 10)
				{
					printf_s("R(%d)  = % 3.7f\n", i, res[i]);
				}
				else
				{
					printf_s("R(%d) = % 3.7f\n", i, res[i]);
				}
			}
			else
			{
				printf_s("R(%d) = % 3.7f\n", i, res[i]);
			}
		}
	}

	//gMultiRowFlag = 0; //-ju-25-Oct-2016 only command line output
	if (gMultiRowFlag == 0)
	{
		QApplication a(argc, argv);
		MainWindow w(0, plData);
		w.show();

		return a.exec();
	}

	return 0;
}