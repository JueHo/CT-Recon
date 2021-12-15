/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _CONVERT_H
#define _CONVERT_H

#include <cfloat>
#include <climits>
#include <algorithm>

//-ju-27-Feb-2014 multithreaded version
#ifdef _OPENMP
	#include <omp.h>
#endif

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

// converter functions
//////////////////////
void ConvertTomoDataI16(const BackProjParam &param, const float &tomoMax, const float &tomoMin)
{
	float mapRange = (SHRT_MAX - SHRT_MIN)/(tomoMax - tomoMin);
	int tomoSize = param.volX*param.volZ;
	ifstream tomoReal;
	ofstream tomoShort;
	char tomgramFile[500];
	char tomgramFileConvert[500];
	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{

		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		tomoReal.open(tomgramFile, ios::binary);
		if(!tomoReal.is_open())
		{
			cout << "Can not open " << tomgramFile << "  -  Exit program!\n";
			return;
		}
		vector<float> readDataVector(tomoSize);
		if(!tomoReal.read((char*)&readDataVector[0], tomoSize*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		tomoReal.close();
		vector<short> mapShort(readDataVector.size());
		transform(readDataVector.begin(), readDataVector.end(), mapShort.begin(), RangeMapI16(mapRange, tomoMin));
		sprintf(tomgramFileConvert,"%s.i16",tomgramFile);
		tomoShort.open(tomgramFileConvert, ios::binary);
		if(!tomoShort.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoShort.write((char*)&mapShort[0],tomoSize*sizeof(short));
		tomoShort.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
			//fflush(stdout);
		}
	}
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertTomoDataUI16(const BackProjParam &param, const float &tomoMax, const float &tomoMin)
{
	float mapRange = USHRT_MAX/(tomoMax - tomoMin);
	int tomoSize = param.volX*param.volZ;
	ifstream tomoReal;
	ofstream tomoUShort;
	char tomgramFile[500];
	char tomgramFileConvert[500];
	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		tomoReal.open(tomgramFile, ios::binary);
		if(!tomoReal.is_open())
		{
			cout << "Can not open " << tomgramFile << "  -  Exit program!\n";
			return;
		}
		vector<float> readDataVector(tomoSize);
		if(!tomoReal.read((char*)&readDataVector[0], tomoSize*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		tomoReal.close();
		vector<unsigned short> mapUShort(readDataVector.size());
		transform(readDataVector.begin(), readDataVector.end(), mapUShort.begin(), RangeMapUI16(mapRange, tomoMin));
		sprintf(tomgramFileConvert,"%s.ui16",tomgramFile);
		tomoUShort.open(tomgramFileConvert, ios::binary);
		if(!tomoUShort.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoUShort.write((char*)&mapUShort[0],tomoSize*sizeof(unsigned short));
		tomoUShort.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	printf("  100 %% done\n");
	fflush(stdout);
}

//-ju-27-03-2014 multithreaded version
////////////////////////////////////////
void ConvertTomoDataUI16MT(const BackProjParam &param, const float &tomoMax, const float &tomoMin)
{
	float mapRange = USHRT_MAX/(tomoMax - tomoMin);
	int tomoSize = param.volX*param.volZ;
	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	int i;
#pragma omp parallel for shared(mapRange,tomoSize,i)
	for(i = 0; i<param.volY; i++)
	{
		ifstream tomoReal;
		ofstream tomoUShort;
		char tomgramFile[500];
		char tomgramFileConvert[500];
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		tomoReal.open(tomgramFile, ios::binary);
		if(!tomoReal.is_open())
		{
			cout << "Can not open " << tomgramFile << "  -  Exit program!\n";
			//??return;
		}
		vector<float> readDataVector(tomoSize);
		if(!tomoReal.read((char*)&readDataVector[0], tomoSize*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			//??return;
		}
		tomoReal.close();
		vector<unsigned short> mapUShort(readDataVector.size());
		transform(readDataVector.begin(), readDataVector.end(), mapUShort.begin(), RangeMapUI16(mapRange, tomoMin));
		sprintf(tomgramFileConvert,"%s.ui16",tomgramFile);
		tomoUShort.open(tomgramFileConvert, ios::binary);
		if(!tomoUShort.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			//??return;
		}
		tomoUShort.write((char*)&mapUShort[0],tomoSize*sizeof(unsigned short));
		tomoUShort.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
#pragma omp barrier
	printf("  100 %% done\n");
	fflush(stdout);
}
/*
void BlockConvertTomoDataUI16(const BackProjParam &param, const float &tomoMax, const float &tomoMin)
{
	cout << "Start converting data to unsigned short ...\n";
	ifstream tomoReal("f:/data/CT-data/coffee/BlockTomo/coffee_R32.raw",
		ios::in|ios::out|ios::binary);
	if(!tomoReal.is_open())
	{
		cout << "can not open f:/data/CT-data/coffee/BlockTomo/coffee_R32.raw" << endl;
		return;
	}
	fstream tomoUShort("f:/data/CT-data/coffee/BlockTomo/coffee_UI16.raw",
		ios::in|ios::out|ios::binary);
	if(!tomoUShort.is_open())
	{
		cout << "can not open f:/data/CT-data/coffee/BlockTomo/coffee_UI16.raw" << endl;
		return;
	}

	unsigned int remainder = param.volY%64;
	unsigned int chunk     = param.volY/64;
	unsigned int range     = chunk*64;
	float mapRange = USHRT_MAX/(tomoMax - tomoMin);
	int tomoSize = param.volX*param.volZ*64;
	vector<float> readDataVector(tomoSize);
	vector<unsigned short> mapUShort(readDataVector.size());
	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	//for(int i = 0; i<param.volY; i++)
	for(unsigned int i = 0; i<range; i+=64)
	{
		if(!tomoReal.read((char*)&readDataVector[0], tomoSize*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		transform(readDataVector.begin(), readDataVector.end(), mapUShort.begin(), RangeMapUI16(mapRange, tomoMin));
		tomoUShort.write((char*)&mapUShort[0],tomoSize*sizeof(unsigned short));
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	if(remainder > 0)
	{
		int tomoSizeR = param.volX*param.volZ*remainder;
		vector<float> readDataVectorR(tomoSize);
		vector<unsigned short> mapUShortR(readDataVectorR.size());
		if(!tomoReal.read((char*)&readDataVectorR[0], tomoSizeR*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		transform(readDataVectorR.begin(), readDataVectorR.end(), mapUShortR.begin(), RangeMapUI16(mapRange, tomoMin));
		tomoUShort.write((char*)&mapUShortR[0],tomoSizeR*sizeof(unsigned short));
	}
	tomoReal.close();
	tomoUShort.close();
	printf("  100 %% done\n");
}
*/

void ConvertTomoDataUC8(const BackProjParam &param, const float &tomoMax, const float &tomoMin)
{
	float mapRange = UCHAR_MAX/(tomoMax - tomoMin);
	int tomoSize = param.volX*param.volZ;
	ifstream tomoReal;
	ofstream tomoByte;
	char tomgramFile[500];
	char tomgramFileConvert[500];
	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		tomoReal.open(tomgramFile, ios::binary);
		if(!tomoReal.is_open())
		{
			cout << "Can not open " << tomgramFile << "  -  Exit program!\n";
			return;
		}
		vector<float> readDataVector(tomoSize);
		if(!tomoReal.read((char*)&readDataVector[0], tomoSize*sizeof(float)))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		tomoReal.close();
		vector<unsigned char> mapByte(readDataVector.size());
		transform(readDataVector.begin(), readDataVector.end(), mapByte.begin(), RangeMapUC8(mapRange, tomoMin));
		sprintf(tomgramFileConvert,"%s.uc8",tomgramFile);
		tomoByte.open(tomgramFileConvert, ios::binary);
		if(!tomoByte.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoByte.write((char*)&mapByte[0],tomoSize*sizeof(unsigned char));
		tomoByte.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
			//fflush(stdout);
		}
	}
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertBlockTomoDataUC8(const BackProjParam &param, 
							 const float &tomoMax, 
							 const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}

	ofstream tomoByte;
	char tomgramFile[500];
	char tomgramFileConvert[500];

	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<unsigned char> mapByte(sliceSize);
	float mapRange = UCHAR_MAX/(tomoMax - tomoMin);
	float *bufferIn  = new float[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(), readDataVector.end(), mapByte.begin(), RangeMapUC8(mapRange, tomoMin));

		sprintf(tomgramFileConvert,"%s.uc8",tomgramFile);
		tomoByte.open(tomgramFileConvert, ios::binary);
		if(!tomoByte.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoByte.write((char*)&mapByte[0],sliceSize*sizeof(unsigned char));
		tomoByte.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertBlockTomoDataI16(const BackProjParam &param, 
							 const float &tomoMax, 
							 const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}

	ofstream tomoShort;
	char tomgramFile[500];
	char tomgramFileConvert[500];

	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<short> mapShort(sliceSize);
	float mapRange = (SHRT_MAX - SHRT_MIN)/(tomoMax - tomoMin);
	float *bufferIn  = new float[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(), readDataVector.end(), mapShort.begin(), RangeMapI16(mapRange, tomoMin));

		sprintf(tomgramFileConvert,"%s.i16",tomgramFile);
		tomoShort.open(tomgramFileConvert, ios::binary);
		if(!tomoShort.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoShort.write((char*)&mapShort[0],sliceSize*sizeof(short));
		tomoShort.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertBlockTomoDataUI16(const BackProjParam &param, 
							  const float &tomoMax, 
							  const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}

	ofstream tomoUShort;
	char tomgramFile[500];
	char tomgramFileConvert[500];

	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<unsigned short> mapUShort(sliceSize);
	float mapRange = USHRT_MAX/(tomoMax - tomoMin);
	float *bufferIn  = new float[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}
	for(int i = 0; i<param.volY; i++)
	{
		sprintf(tomgramFile,"%s%s%04dx%04dx%04d_%04d.raw", 
			param.tomoDir.c_str(),param.tomoName.c_str(),
			param.volX,param.volY,param.volZ,
			i+param.startIndex);
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(), readDataVector.end(), mapUShort.begin(), RangeMapUI16(mapRange, tomoMin));

		sprintf(tomgramFileConvert,"%s.ui16",tomgramFile);
		tomoUShort.open(tomgramFileConvert, ios::binary);
		if(!tomoUShort.is_open())
		{
			cout << "Can not open " << tomgramFileConvert << "  -  Exit program!\n";
			return;
		}
		tomoUShort.write((char*)&mapUShort[0],sliceSize*sizeof(unsigned short));
		tomoUShort.close();
		if(param.tomoBlockWrite != 1)
		{
			if(remove(tomgramFile))
			{
				cout << "Can not delete file: " << tomgramFile << endl;
			}
		}
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertBlockInternalTomoDataUC8(const BackProjParam &param, 
									 const float &tomoMax, 
									 const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}
	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<unsigned char> mapByte(sliceSize);
	float mapRange = UCHAR_MAX/(tomoMax - tomoMin);

	float         *bufferIn  = new float[sliceSize];
	unsigned char *bufferOut = new unsigned char[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}

	for(int i = 0; i<param.volY; i++)
	{
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(),readDataVector.end(),mapByte.begin(),RangeMapUC8(mapRange,tomoMin));
		// copy vector to array
		std::copy(mapByte.begin(),mapByte.end(),bufferOut);
		_fseeki64(fpVol,fileOffset*sizeof(unsigned char),0);
		fwrite(bufferOut,sliceSize*sizeof(unsigned char),1,fpVol);
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	delete [] bufferOut;
	fclose(fpVol);
	printf("  100 %% done\n");
	fflush(stdout);
}


void ConvertBlockInternalTomoDataI16(const BackProjParam &param, 
									 const float &tomoMax, 
									 const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}
	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<short> mapShort(sliceSize);
	float mapRange = (SHRT_MAX - SHRT_MIN)/(tomoMax - tomoMin);

	float *bufferIn  = new float[sliceSize];
	short *bufferOut = new short[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}

	for(int i = 0; i<param.volY; i++)
	{
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(),readDataVector.end(),mapShort.begin(),RangeMapI16(mapRange,tomoMin));
		// copy vector to array
		std::copy(mapShort.begin(),mapShort.end(),bufferOut);
		_fseeki64(fpVol,fileOffset*sizeof(short),0);
		fwrite(bufferOut,sliceSize*sizeof(short),1,fpVol);
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	delete [] bufferOut;
	fclose(fpVol);
	printf("  100 %% done\n");
	fflush(stdout);
}

void ConvertBlockInternalTomoDataUI16(const BackProjParam &param, 
									  const float &tomoMax, 
									  const float &tomoMin)
{
	FILE *fpVol = fopen(param.tomoBlockFile.c_str(), "r+b");
	if(fpVol == 0)
	{
		fprintf(stderr,"Can not open %s --> exit\n", param.tomoBlockFile.c_str());
		return;
	}
	unsigned int sliceSize = param.volX*param.volZ;
	// input data
	vector<float> readDataVector(sliceSize);
	// output data
	vector<unsigned short> mapUShort(sliceSize);
	float mapRange = USHRT_MAX/(tomoMax - tomoMin);

	float          *bufferIn  = new float[sliceSize];
	unsigned short *bufferOut = new unsigned short[sliceSize];

	int onePercent = param.volY/100;
	if(param.volY%100 != 0)
	{
		onePercent++;
	}

	for(int i = 0; i<param.volY; i++)
	{
		unsigned long long fileOffset = (unsigned long long)(i)*(unsigned long long)sliceSize;
		_fseeki64(fpVol,fileOffset*sizeof(float),0);
		if(!fread(bufferIn, sliceSize*sizeof(float),1,fpVol))
		{
			cout << "\nError writing tomogram\n";
			return;
		}
		// copy array to vector
		readDataVector.assign(bufferIn,bufferIn+sliceSize);
		transform(readDataVector.begin(),readDataVector.end(),mapUShort.begin(),RangeMapUI16(mapRange,tomoMin));
		// copy vector to array
		std::copy(mapUShort.begin(),mapUShort.end(),bufferOut);
		_fseeki64(fpVol,fileOffset*sizeof(unsigned short),0);
		fwrite(bufferOut,sliceSize*sizeof(unsigned short),1,fpVol);
		if(i%onePercent == 0)
		{
			printf("  %3d %% done\r",i/onePercent);
		}
	}
	delete [] bufferIn;
	delete [] bufferOut;
	fclose(fpVol);
	printf("  100 %% done\n");
	fflush(stdout);
}

#endif // _CONVERT_H