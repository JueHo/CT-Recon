/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include <algorithm>
#include "FilterException.h"
#include "typesFDK.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>
#include <boost/foreach.hpp>
#include <cstdio> //-ju-10-10-2011 block reading

using namespace std;

// Utility functions
////////////////////
bool CheckImageSize(const char *filename, const int &width, const int &height, long long &diff, int datatype=4)
{
	ifstream sinoFile(filename,ios::binary);
	if(!sinoFile.is_open())
	{
		FILTER_ERROR err = err_read_pre_sino;
		throw FilterException(err, filename);
	}
	// get file size
	sinoFile.seekg(0, ios_base::end);
	size_t image_size = sinoFile.tellg();
	sinoFile.close();
	// compare
	int w = width;
	int h = height;
	diff = image_size - static_cast<size_t>(w*h*datatype);
	if(diff) return false;
	return true;
}

bool CreateTomoDir(const char *tomoDir)
{
	if(CreateDirectoryA(tomoDir,0) == 0)
	{
		DWORD dw = GetLastError();
		if(dw == ERROR_ALREADY_EXISTS)
		{
			return true;
		}
		return false;
	}
	return true;
}


void print(vector<int> v)
{
    BOOST_FOREACH(int i, v)
    {
        printf("%2d  ",i);
    }
	std::cout << endl;
}


void CreateReorderedIndex(const BackProjParam &param, vector<int> &reoderedIndices)
{
	int np			 = param.numProj;
	float startAngle = param.startAngle;
	int start_idx	 = param.startIndex;
	int angleIndex	 = static_cast<int>(startAngle*np/360.0f);
	reoderedIndices.resize(np);

	//-ju-04-July-2011 cout << "------------------>" << startAngle << endl;

	for(int i = 0; i < np; i++)
	{
		reoderedIndices[i] = i + start_idx;
	}
	//print(reoderedIndices);
	//cout << "angleIndex=" << angleIndex << endl;
	//cout << endl << endl;
	vector<int>::iterator iter_start  = reoderedIndices.begin();
	vector<int>::iterator iter_middle = iter_start + angleIndex;
	vector<int>::iterator iter_end    = reoderedIndices.end();
	rotate(iter_start,iter_middle,iter_end);
	//print(reoderedIndices);
	//cout << endl << endl;
}

//-ju-10-10-2011 add block file reading
int ReadBlockChunkOfSinograms(const int &start_value, 
							  const int &end_value,
							  const BackProjParam &param,
							  float *h_sinoData)
{
	FILE *fp;
	string filename = param.sino32BlockFile;
	fp = fopen(filename.c_str(),"rb");
	if(fp != 0)
	{
		long long offset = param.imgWidth * param.imgHeight * sizeof(float) * start_value;
		long long dataLen = param.imgWidth * param.imgHeight * (end_value - start_value);
		//printf("start_value=%d end_value= %d diff=%d Offset: %I64d\n", start_value, end_value, end_value - start_value, offset);
		_fseeki64(fp,offset,0);
		fread((char*) &h_sinoData[0], sizeof(float)*dataLen, 1, fp);
		fclose(fp);
	}
	else
		cout << " ===> error opening " << filename << endl;;
	return 0;
}


int ReadChunkOfSinograms(const int &start_value, 
						 const int &end_value,
						 const BackProjParam &param,
						 float *h_sinoData)
{
	// create file number sequence
	vector<int> angleIndices;
	CreateReorderedIndex(param,angleIndices);
	// read chunk of sinograms
	//////////////////////////
	char sinogram_name[256];
	ifstream s_sinoFile; // FILE benutzen
	int startIdx = param.startIndex;
	char filenumber[FILE_NUMBER_LEN];
	string filename_template(param.sinoName);
	filename_template += ".sinoF32";

	sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",startIdx);
	string sinogram_preprocess = param.sinoPreProcDir;
	size_t pos = filename_template.find_first_of("****");
	filename_template.replace(pos,4,filenumber);
	sinogram_preprocess += filename_template;
	long long diff;
	try
	{
		if(!CheckImageSize(sinogram_preprocess.c_str(),param.imgWidth,param.imgHeight,diff))
		{
			cout << "\nInconsistence image size in: " << sinogram_preprocess 
				<< " !\nDifference: " << diff << " bytes --> check file size parmeters\n\n";
			cout.flush();
			exit(-3);
		}
	}
	catch(FilterException err)
	{
		cout << err.GetErrorMessage() << endl;
		cout.flush();
		exit(-3);
	}

	unsigned long long idx = 0;
	for(int i = start_value; i < end_value; i++)
	{
		// re-initialize because is filled with old value
		filename_template = param.sinoName;
		filename_template += ".sinoF32";

		//-ju-31-Mar-2011 get reordered index
		int newIndex = angleIndices[i];

		sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",newIndex);
		//sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",i+startIdx);
		string sinogram_preprocess = param.sinoPreProcDir;
		size_t pos = filename_template.find_first_of("****");
		filename_template.replace(pos,4,filenumber);
		sinogram_preprocess += filename_template;
		s_sinoFile.open(sinogram_preprocess.c_str(), ios::binary);
		if(!s_sinoFile.is_open())
		{
			cout << "1 Can not open " << sinogram_name << "  -  Exit program!\n";
			return -1;
		}
		if(!s_sinoFile.read((char*)&(h_sinoData[idx]), param.imgWidth*param.imgHeight*sizeof(float)))
		{
			cout << "\nError reading pre-proc-sinogram\n";
			return -2;
		}
		s_sinoFile.close();
		idx += static_cast<unsigned long long>(param.imgWidth*param.imgHeight);
	}
#if 0
	char buffer[64];
	sprintf(buffer,"subblock-%04d-%04d.bin",start_value,end_value);
	long long dataLen = param.imgWidth * param.imgHeight * (end_value - start_value);
	printf("Data size: %d\n", dataLen*4/(1024*1024));
	ofstream tempStream(buffer,ios::binary);
	if(tempStream.is_open())
	{
		printf("Try to write ...");
		tempStream.write((char*)&(h_sinoData[0]),sizeof(float)*dataLen);
		tempStream.close();
		printf("Close File\n");
	}
#endif
	return 0;
}

//-ju-05-July-2011 adaption to file list
int ReadChunkOfSinogramsFromFileList(const int &start_value, 
						 			 const int &end_value,
						 			 const BackProjParam &param,
						 			 float *h_sinoData)
{
	ifstream s_sinoFile;

	int idx = 0;
	for(int i = start_value; i < end_value; i++)
	{
		// re-initialize because is filled with old value
		//filename_template = param.sinoName;
		string sinoFilename = param.sinoList[i];
		size_t lastPos = sinoFilename.find_last_of("/\\");
		if(lastPos == string::npos)
		{
			cout << "No Delimiter found in >> " << sinoFilename << " <<\n";
			cout.flush();
			return -1;
		}
		string baseName = sinoFilename.substr(lastPos+1);
		// prepare file name for preprocessed sinograms
		string sinoFilenamePre =  baseName + ".sinoF32";
		if(param.useFileList == 1 && param.useLimAngle == 0)
		{
			sinoFilenamePre = param.sinoPreProcDir + sinoFilenamePre;
		}
		else
		{
			sinoFilenamePre = param.sinoLimPreProcDir + sinoFilenamePre;
		}
		if(idx == 0)
		{
			long long diff;
			try
			{
				if(!CheckImageSize(sinoFilenamePre.c_str(),param.imgWidth,param.imgHeight,diff))
				{
					cout << "\nInconsistence image size in: " << sinoFilenamePre 
						<< " !\nDifference: " << diff << " bytes --> check file size parmeters\n\n";
					cout.flush();
					exit(-3);
				}
			}
			catch(FilterException err)
			{
				cout << err.GetErrorMessage() << endl;
				cout.flush();
				exit(-3);
			}
		}

		s_sinoFile.open(sinoFilenamePre.c_str(), ios::binary);
		if(!s_sinoFile.is_open())
		{
			cout << "Can not open " << sinoFilenamePre << "  -  Exit program!\n";
			cout.flush();
			return -1;
		}
		if(!s_sinoFile.read((char*)&h_sinoData[idx], param.imgWidth*param.imgHeight*sizeof(float)))
		{
			cout << "\nError reading sinogram\n";
			cout.flush();
			return -2;
		}
		s_sinoFile.close();
		idx += param.imgWidth*param.imgHeight;	
	}
	return 0;
}
