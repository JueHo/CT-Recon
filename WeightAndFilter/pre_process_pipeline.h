/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _PRE_PROCESS_PIPELINE_H
#define _PRE_PROCESS_PIPELINE_H

#include <opencv2/opencv.hpp>
//#include <opencv/cv.h>
#include "parameter.h"
#include "filter.h"
#include "data_IO.h"
#include <map>

typedef map<std::string, float> FileListMapType;
typedef FileListMapType::value_type ValuePair;

namespace FDK {
class PreProcessPipeline
{
public:
	PreProcessPipeline(FDK::FDK_Parameters &param)
		:m_parameter(param), m_filter(param)
	{
		//-ju-	the same weight mask and filter
		//		can be used for all projections
		////////////////////////////////////////
		CreateWeightMask();
		// create filter mask
		//////////////////////
		CreateComplxFilterFFT();
		CreateZeroBorderMask();
		// create complex filter
		/////////////////////////

		// use phase contrast filter
		if(m_parameter.useDCPFilter)
		{
			cv::Mat matrix = m_filter.GetFilterCmplx();
			matrix.copyTo(m_filter2DCmplx);
		}
		else // use absorption filter
		{
			cv::Mat matrix = m_filter.GetFilterMagnitude();
			cv::Mat filter2D_re(matrix);
			cv::Mat filter2D_im(matrix.size(),matrix.type(),cv::Scalar(0.0f));
			vector<cv::Mat> filterVector(2);
			filterVector[0] = filter2D_re;
			filterVector[1] = filter2D_im;
			cv::Mat filter2DCmplxTmp(matrix.size(),CV_32FC1);
			cv::merge(filterVector,filter2DCmplxTmp);
			filter2DCmplxTmp.copyTo(m_filter2DCmplx);
		}

	}
public:
	int PreProcessSinogramsToDisk(int threadNum,
								  int threadId,
								  FILE *fpF32,
								  FILE *fpF32_1,
								  FILE *fpF32_2,
								  FILE *fpSino);
	int PreProcessSinogramsToMemory(cv::Mat &sinoStack);
	int ApplyFilter(cv::Mat &sinoImg);
private:
	// declare standard constructor to private
	PreProcessPipeline();
	int  WeightSinogram(cv::Mat &sinoImg);
	int  CreateWeightMask();
	int  CreateZeroBorderMask();
	void CreateComplxFilterFFT();
	int PreProcessFromSinoDir(SinoIO &sinoIO,
							  int threadNum,
							  int threadId,
							  FILE *fpF32,
							  FILE *fpF32_1,
							  FILE *fpF32_2,
							  FILE *fpSino);
	int PreProcessFromSinoList(SinoIO &sinoIO,const char* sinListPost,bool limited);
private:
	cv::Mat m_weightMask;
	cv::Mat m_zeroBorderMask;
	cv::Mat m_filter2DCmplx;
	FDK::Filter m_filter;
	FDK::FDK_Parameters m_parameter;
};
}
#endif // _PRE_PROCESS_PIPELINE_H