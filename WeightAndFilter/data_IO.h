/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _DATA_IO_H
#define _DATA_IO_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "parameter.h"
#include <windows.h>
#include "FilterException.h"
#include <cstdio>
#include <QtCore/QFileInfo>

using namespace std;
using namespace boost;

const size_t PATH_LEN=261; // max. 260 char. for windows
const size_t FILE_NUMBER_LEN=5;
const int CAN_NOT_OPEN_FILE=-101;

namespace FDK {
class SinoIO
{
public:
	SinoIO(FDK::FDK_Parameters &param)
		:m_parameter(param){}

	bool VerifyImageFile(char *filepath)
	{
		QFileInfo sinoFile(filepath);
		long long w = m_parameter.imageWidth;
		long long h = m_parameter.imageHeight;
		string datType = m_parameter.inDataType;
		long long dataTypeLength;
		if(datType == "byte")
		{
			dataTypeLength = 1;
		}
		else
		if(datType == "short16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "ushort16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "int32")
		{
			dataTypeLength = 4;
		}
		else
		if(datType == "real32")
		{
			dataTypeLength = 4;
		}
		long long imgFileSizeFromParam = w*h*dataTypeLength;

		if(!sinoFile.exists())
		{
			std::cout << "File: " << filepath << " does not exist!\n";
			return false;
		}
		if(sinoFile.size() != imgFileSizeFromParam)
		{
			std::cout << "Sinogram file size is not correct. Check parameters!\n";
			return false;
		}

		return true;
	}

	bool VerifyImageSize()
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",m_parameter.startIndex);
		string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		// get file size
		sinoFile.seekg(0, ios_base::end);
		size_t image_size = sinoFile.tellg();
		// compare
		int w = m_parameter.imageWidth;
		int h = m_parameter.imageHeight;
		string datType = m_parameter.inDataType;
		int dataTypeLength;
		if(datType == "byte")
		{
			dataTypeLength = 1;
		}
		else
		if(datType == "short16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "ushort16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "int32")
		{
			dataTypeLength = 4;
		}
		else
		if(datType == "real32")
		{
			dataTypeLength = 4;
		}
		else
		{
			FILTER_ERROR err = err_unknown_data_type;
			throw FilterException(err, datType);
		}
		long long diff = image_size - w*h*dataTypeLength;
		if(diff) return false;
		return true;
	}

	//-ju-29-June-2011 add for listfile
	bool VerifyImageSize(const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		// get file size
		sinoFile.seekg(0, ios_base::end);
		size_t image_size = sinoFile.tellg();
		// compare
		int w = m_parameter.imageWidth;
		int h = m_parameter.imageHeight;
		string datType = m_parameter.inDataType;
		int dataTypeLength;
		if(datType == "byte")
		{
			dataTypeLength = 1;
		}
		else
		if(datType == "short16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "ushort16")
		{
			dataTypeLength = 2;
		}
		else
		if(datType == "int32")
		{
			dataTypeLength = 4;
		}
		else
		if(datType == "real32")
		{
			dataTypeLength = 4;
		}
		else
		{
			FILTER_ERROR err = err_unknown_data_type;
			throw FilterException(err, datType);
		}
		long long diff = image_size - w*h*dataTypeLength;
		if(diff) return false;
		return true;
	}

	bool CreateSinoProcessedDir()
	{
		if(CreateDirectoryA(m_parameter.sinoDir32.c_str(),0) == 0)
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

	// read 4-Byte float sinogramms
	void ReadSinogramFloat32(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.read((char*)&sinogram_out[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
	}

	// read 1-byte unsigned char sinograms
	void ReadSinogramUChar8(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		vector<unsigned char> imageData(m_parameter.imageWidth*m_parameter.imageHeight);
		sinoFile.read((char*)&imageData[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned char)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinogram_out.resize(m_parameter.imageWidth*m_parameter.imageHeight);
        vector<unsigned char>::const_iterator read_iter = imageData.begin();
        vector<float>::iterator convert_iter = sinogram_out.begin();
        while(read_iter != imageData.end())
        {
			*convert_iter = static_cast<float>(*read_iter);
            read_iter++;
			convert_iter++;
        }
	}

	// read 2-Byte unsigned short sinogramms
	void ReadSinogramUShort16(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		vector<unsigned short> imageData(m_parameter.imageWidth*m_parameter.imageHeight);
		sinoFile.read((char*)&imageData[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinogram_out.resize(m_parameter.imageWidth*m_parameter.imageHeight);
        vector<unsigned short>::const_iterator read_iter = imageData.begin();
        vector<float>::iterator convert_iter = sinogram_out.begin();
		int cnt = 0;
        while(read_iter != imageData.end())
        {
			*convert_iter = static_cast<float>(*read_iter);
            read_iter++;
			convert_iter++;
        }
	}

	// read 2-Byte short sinogramms
	void ReadSinogramShort16(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		vector<short> imageData(m_parameter.imageWidth*m_parameter.imageHeight);
		sinoFile.read((char*)&imageData[0],
			          m_parameter.imageWidth*m_parameter.imageWidth*sizeof(short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinogram_out.resize(m_parameter.imageWidth*m_parameter.imageHeight);
        vector<short>::const_iterator read_iter = imageData.begin();
        vector<float>::iterator convert_iter = sinogram_out.begin();
        while(read_iter != imageData.end())
        {
			*convert_iter = static_cast<float>(*read_iter);
            read_iter++;
			convert_iter++;
        }
	}

	// read 4-byte unsigned int sinograms
	void ReadSinogramUInt32(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		vector<unsigned int> imageData(m_parameter.imageWidth*m_parameter.imageHeight);
		sinoFile.read((char*)&imageData[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned int)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinogram_out.resize(m_parameter.imageWidth*m_parameter.imageHeight);
        vector<unsigned int>::const_iterator read_iter = imageData.begin();
        vector<float>::iterator convert_iter = sinogram_out.begin();
        while(read_iter != imageData.end())
        {
			*convert_iter = static_cast<float>(*read_iter);
            read_iter++;
			convert_iter++;
        }
	}

	// read 4-byte int sinograms
	void ReadSinogramInt32(vector<float> &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		vector<int> imageData(m_parameter.imageWidth*m_parameter.imageHeight);
		sinoFile.read((char*)&imageData[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(int)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinogram_out.resize(m_parameter.imageWidth*m_parameter.imageHeight);
        vector<int>::const_iterator read_iter = imageData.begin();
        vector<float>::iterator convert_iter = sinogram_out.begin();
        while(read_iter != imageData.end())
        {
			*convert_iter = static_cast<float>(*read_iter);
            read_iter++;
			convert_iter++;
        }
	}

	// write float sinograms
	void WriteSinogram(vector<float> &sinogram_in, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s.sinoF32",m_parameter.sinoDir32.c_str(),filename.c_str());
		ofstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_w_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.write((char*)&sinogram_in[0],
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_write_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
	}


	// cv::Mat output
	///////////////////////////////////////
	// read 4-Byte float sinogramms
	void ReadSinogramFloat32(cv::Mat &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}

		//-ju-11-Feb-2011 allocate memory for temp. mat
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_32F);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		//-ju-11-Feb-2011 copy temp mat to output mat memory allocation is done by copyTo function
		mat_tmp.copyTo(sinogram_out);
	}

	//-ju-29-June-2011 add for listfile; read 4-Byte float sinogramms
	void ReadSinogramFloat32(cv::Mat &sinogram_out, const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}

		//-ju-11-Feb-2011 allocate memory for temp. mat
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_32F);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		//-ju-11-Feb-2011 copy temp mat to output mat memory allocation is done by copyTo function
		mat_tmp.copyTo(sinogram_out);
	}

	//-ju-24-Okt-2011 read sino blockfile
	//////////////////////////////////////
	void ReadBlockSinogramFloat32(cv::Mat &sinogram_out, int index, FILE *fpSino)
	{
		//-ju-11-Feb-2011 allocate memory for temp. mat
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_32F);

		unsigned long long fileOffset = (unsigned long long)m_parameter.imageHeight*
										(unsigned long long)m_parameter.imageWidth*
										(unsigned long long)sizeof(float)*
										(unsigned long long)index;
		_fseeki64(fpSino,fileOffset,0);		

		fread((char*)mat_tmp.data,m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float),1,fpSino);
		//-ju-11-Feb-2011 copy temp mat to output mat memory allocation is done by copyTo function
		mat_tmp.copyTo(sinogram_out);
	}

	void ReadBlockSinogramUShort16(cv::Mat &sinogram_out, int index, FILE *fpSino)
	{
		//-ju-11-Feb-2011 allocate memory for temp. mat
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_16U);

		unsigned long long fileOffset = (unsigned long long)m_parameter.imageHeight*
										(unsigned long long)m_parameter.imageWidth*
										(unsigned long long)sizeof(unsigned short)*
										(unsigned long long)index;
		_fseeki64(fpSino,fileOffset,0);		

		fread((char*)mat_tmp.data,m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned short),1,fpSino);
		//-ju-11-Feb-2011 copy temp mat to output mat memory allocation is done by copyTo function
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	// read 1-byte unsigned char sinograms
	void ReadSinogramUChar8(cv::Mat &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_8U);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned char)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	//-ju-29-June-2011 add for listfile; read 1-byte unsigned char sinograms
	void ReadSinogramUChar8(cv::Mat &sinogram_out, const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_8U);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned char)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	// read 2-Byte unsigned short sinogramms
	void ReadSinogramUShort16(cv::Mat &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_16U);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	//-ju-28-June-2011 add for listfile; read 2-Byte unsigned short sinogramms
	void ReadSinogramUShort16(cv::Mat &sinogram_out, const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_16U);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(unsigned short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}


	// read 2-Byte short sinogramms
	void ReadSinogramShort16(cv::Mat &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(sinoFile.exceptions()) throw "Error open sinogram";
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_16S);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	//-ju-29-June-2011 add for listfile; read 2-Byte short sinogramms
	void ReadSinogramShort16(cv::Mat &sinogram_out, const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(sinoFile.exceptions()) throw "Error open sinogram";
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_16S);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(short)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	// read 4-byte int sinograms
	void ReadSinogramInt32(cv::Mat &sinogram_out, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s",m_parameter.sinoDir.c_str(),filename.c_str());
		//-ju-08-Sep-2014
		if(!VerifyImageFile(path_file))
		{
				exit(-11);
		}
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_32S);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(int)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	//-ju-29-June-2011 add for listfile; read 4-byte int sinograms
	void ReadSinogramInt32(cv::Mat &sinogram_out, const char* path_file)
	{
		ifstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_r_sinogram;
			throw FilterException(err, path_file);
		}
		cv::Mat mat_tmp(m_parameter.imageHeight,m_parameter.imageWidth,CV_32S);
		sinoFile.read((char*)mat_tmp.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(int)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_read_sinogram;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		mat_tmp.convertTo(sinogram_out, CV_32F);
	}

	// write float sinograms
	void WriteSinogram(cv::Mat &sinogram_in, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];
		sprintf_s(path_file,PATH_LEN,"%s%s.sinoF32",m_parameter.sinoDir32.c_str(),filename.c_str());
		ofstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_w_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.write((char*)sinogram_in.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_write_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinoFile.flush();
	}


	//-ju-June-2011 add for file list; write float sinograms
	void WriteSinogram(cv::Mat &sinogram_in, string filename)
	{
		char path_file[PATH_LEN];
		string preProcDir;
		if(m_parameter.limAngleBProj)
		{
			preProcDir = m_parameter.sinoDir32;
		}
		else
		{
			preProcDir = m_parameter.sinoDirLim32;
		}
		sprintf_s(path_file,PATH_LEN,"%s%s.sinoF32",preProcDir.c_str(),filename.c_str());
		ofstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_w_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.write((char*)sinogram_in.data,
			          m_parameter.imageWidth*m_parameter.imageHeight*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_write_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinoFile.flush();
	}

	//-ju-21-Oct-2011 split in upper and lower part for multiple GPU device support
	void WriteBlockSinogramMultGPU(cv::Mat &sinogram_in,const unsigned int &index,FILE *fpF32_1,FILE *fpF32_2)
	{
			//unsigned long long fileOffset = 
			//	((unsigned long long)param.volY - (unsigned long long)(ii+startIdx))*(unsigned long long)param.volX*(unsigned long long)param.volZ;//(unsigned long long)yChunkStart + offset;
			//_fseeki64(fpVol,fileOffset*sizeof(float),0);
			//fwrite((char*)&h_backproj_chunk[offset], param.volX*param.volZ*sizeof(float), 1, fpVol);
			//index++;


		int hHalf = (int)(m_parameter.imageHeight/2);

		unsigned long long imgBytesSize = (unsigned long long)m_parameter.imageWidth*
								          (unsigned long long)(hHalf+1)*
								          (unsigned long long)sizeof(float);

		unsigned long long fileOffset = imgBytesSize*(unsigned long long)index;

		_fseeki64(fpF32_1,fileOffset,0);		
		_fseeki64(fpF32_2,fileOffset,0);		

		fwrite((char*)sinogram_in.data,
			    imgBytesSize,
				1,
				fpF32_1);
		fflush(fpF32_1);
		fwrite((char*)sinogram_in.ptr(hHalf-1),
			   imgBytesSize,
			   1,
			   fpF32_2);
		fflush(fpF32_2);
	}

	//-ju-27-Oct-2011 write block 
	void WriteBlockSinogram(cv::Mat &sinogram_in,const unsigned int &index,FILE *fpF32)
	{
		unsigned long long imgBytesSize = (unsigned long long)m_parameter.imageWidth*
								          (unsigned long long)m_parameter.imageHeight*
								          (unsigned long long)sizeof(float);

		unsigned long long fileOffset = imgBytesSize*(unsigned long long)index;

		_fseeki64(fpF32,fileOffset,0);		

		fwrite((char*)sinogram_in.data,
			    imgBytesSize,
				1,
				fpF32);
		fflush(fpF32);
	}

	void WriteSinogramMultGPU(cv::Mat &sinogram_in, const unsigned int &fileIndex)
	{
        char filenumber[FILE_NUMBER_LEN];
		string filename_template(m_parameter.sinoName);
        sprintf_s(filenumber,FILE_NUMBER_LEN,"%04d",fileIndex);
        string filename = replace_first_copy(filename_template,"****",filenumber);
		char path_file[PATH_LEN];

		int hHalf = (int)(m_parameter.imageHeight/2);

		sprintf_s(path_file,PATH_LEN,"%s%s.1.sinoF32",m_parameter.sinoDir32.c_str(),filename.c_str());
		ofstream sinoFile(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_w_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.write((char*)sinogram_in.data,
			          m_parameter.imageWidth*(hHalf+1)*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_write_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinoFile.flush();

		sprintf_s(path_file,PATH_LEN,"%s%s.2.sinoF32",m_parameter.sinoDir32.c_str(),filename.c_str());
		sinoFile.open(path_file,ios::binary);
		if(!sinoFile.is_open())
		{
			FILTER_ERROR err = err_open_w_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.write((char*)sinogram_in.ptr(hHalf-1),
			          m_parameter.imageWidth*(hHalf+1)*sizeof(float)
					  );
		if(!sinoFile.good())
		{
			FILTER_ERROR err = err_write_pre_sino;
			throw FilterException(err, path_file);
		}
		sinoFile.close();
		sinoFile.flush();
	}

private:
	FDK::FDK_Parameters m_parameter;
};


}
#endif // _DATA_IO_H