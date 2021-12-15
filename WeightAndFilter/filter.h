/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _FILTER_H
#define _FILTER_H

#include <opencv2/opencv.hpp>
//#include <opencv/cv.h>
#include "parameter.h"
#include "space_domain_filter_def.h"

namespace FDK {
class Filter
{
public:
	Filter(FDK_Parameters &param)
		:m_parameter(param)
	{};

	// create zero-padded filter ( zero pad of 2N-1)
	int Create2DSpaceDomainFilter();
	int CalcComplxFilterFFT();
	int CalcComplxFilterFFTPhaseContrast();
	cv::Mat GetFilterCmplx()
	{
		return m_filterCmplx;
	}
	cv::Mat GetFilterMagnitude()
	{
		return m_filterMagnitude;
	}

private:
	// get one row of space domain filter
	SpaceDomainFilterFunction GetSpaceDomainFilterRow(const char* filterName);
	// make standard constructor none accessible from outside
	Filter(){};

private:
	FDK_Parameters m_parameter;
	cv::Mat m_filterCmplx;
	cv::Mat m_filterMagnitude;
	cv::Mat m_filterSpaceDomain;

};
}
#endif // _FILTER_H