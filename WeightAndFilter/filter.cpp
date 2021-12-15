/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "filter.h"
#include "space_domain_filter_def.h"
#include "utility.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "FilterException.h"

using namespace FDK;
using namespace std;

SpaceDomainFilterFunction Filter::GetSpaceDomainFilterRow(const char* filterName)
{
	std::string inNam(filterName);
	std::string fiNam;
	int i = 0;
	while(filterFunctionList[i].filterFunc != 0)
	{
		fiNam = filterFunctionList[i].filterName;
		if(fiNam.compare(inNam) == 0)
		{
			return filterFunctionList[i].filterFunc;
		}
		i++;
	}
	// nothing found in list
	FILTER_ERROR err = err_filter_type;
	string msg = "unkown or unregistered filter type >> ";
	msg += m_parameter.applyFilter;
	msg += " <<";
	throw FilterException(err, msg);
	return 0;
}

int Filter::Create2DSpaceDomainFilter()
{
	int cols = m_parameter.imageWidth;
	int rows = m_parameter.imageHeight;
	vector<float> filterData;
	// select filter specified in parameter file
	SpaceDomainFilterFunction FilterFunction 
		= GetSpaceDomainFilterRow(m_parameter.applyFilter.c_str());
	// get row filter data
	FilterFunction(cols,filterData);
	// assemble 2D filter using zero padding
	unsigned int zp_size = Utility::ZeroPadBase2Len(filterData.size());
	vector<float> filterDataZP(zp_size);
	// zeropad row
	copy(filterData.begin(), filterData.end(), filterDataZP.begin());
	vector<float> filterDataZP2D(zp_size*rows);
	vector<float>::iterator itDest = filterDataZP2D.begin();
	// use linear memory layout (pseudo 2D)
	for(int i = 0; i < rows; i++)
	{
		copy(filterDataZP.begin(), filterDataZP.end(), itDest);
		itDest = itDest + zp_size;
	}
	cv::Mat tmpMat(rows,zp_size,CV_32F,&filterDataZP2D[0]);
	tmpMat.copyTo(m_filterSpaceDomain);

#if 0
	ofstream fftf("filterSPZP.raw", ios::binary);
	fftf.write((char*)filter2D.data, filter2D.cols*filter2D.rows*4);
	fftf.close();
#endif

	return 1;
}

int Filter::CalcComplxFilterFFT()
{
	cv::Mat filter2D_re(m_filterSpaceDomain);
	cv::Mat filter2D_im(m_filterSpaceDomain.size(),CV_32F,cv::Scalar(0.0f));
	vector<cv::Mat> filterVector(2);
	filterVector[0] = filter2D_re;
	filterVector[1] = filter2D_im;
	cv::Mat filter2DCmplxTmp(m_filterSpaceDomain.size(),CV_32FC1);
	cv::merge(filterVector,filter2DCmplxTmp);
	cv::dft(filter2DCmplxTmp, m_filterCmplx,
		cv::DFT_ROWS + cv::DFT_COMPLEX_OUTPUT);
	//-ju-17-Feb-2012 scaling
	int sz = cv::getOptimalDFTSize(m_parameter.imageWidth);
	//double scalFac = 100*(1-300.0/1024);
	//double pixSize = 1.0;
	
	double w_orig = static_cast<double>(m_parameter.imageWidth);
	double w_pad = static_cast<double>(filter2DCmplxTmp.cols);
	//double scalFac = 100.0*(1.0-w_orig/w_pad);
	double scalFac = m_parameter.cntProjection;//*(w_orig/w_pad);
	double pixSize = static_cast<double>(m_parameter.pixelSize);
	
	//double pixSize = 2.0;
	//double scalFac = 100.0*(1.0-150.0/512);
	//double pixSize = 2.0;
	//m_filterCmplx = m_filterCmplx*150/(75*2*512);
	//m_filterCmplx = m_filterCmplx*300/(scalFac*pixSize*1024);
	//m_filterCmplx = m_filterCmplx*150/(scalFac*pixSize*512);
	
	//m_filterCmplx = m_filterCmplx*4.0*M_PI/(m_parameter.cntProjection*pixSize*pixSize); //-ju- Abhaenigkeit von der Anzahl Winkel !!!!

    //-ju-29-01-2015 remove scaling for Test
    /////////////////////////////////////////
    //-ju-29-01-2015 wieder aktiviert
	//-ju-31-Aug-2016 remove dependencies on projections
	//m_filterCmplx = 2*M_PI*m_filterCmplx/(m_parameter.cntProjection); //-ju- Abhaenigkeit von der Anzahl Winkel !!!!
    //-ju-29-01-2015 remove scaling for Test

	//-ju-21-Feb-2012 test m_filterCmplx = m_filterCmplx/(scalFac);
	//m_filterCmplx = m_filterCmplx*w_orig/(scalFac*pixSize*w_pad);
	//m_filterCmplx = m_filterCmplx*0.4*w_orig/(w_pad*4*M_PI*M_PI);
#if 0
	for(int i = 0; i < filter2DFFT.cols ; i++)
	{
		cout << filter2DFFT.at<cv::Complexf>(0,i).re << "  \t\t" 
			 << filter2DFFT.at<cv::Complexf>(0,i).im << endl;
	}
#endif
	// create magnitude filter
	vector<cv::Mat> imageVec(2);
    cv::split(m_filterCmplx,imageVec);
	cv::magnitude(imageVec[0],imageVec[1],m_filterMagnitude);

#if 0
	ofstream fftfm("filterFFTm.raw", ios::binary);
	fftfm.write((char*)m_filterMagnitude.data, m_filterMagnitude.cols*m_filterMagnitude.rows*4);
	fftfm.close();
#endif
	return 1;
}

int Filter::CalcComplxFilterFFTPhaseContrast()
{
	///////////////////////////////////////->
	int cols = m_filterSpaceDomain.cols;
	int rows = m_filterSpaceDomain.rows;
	int filterPartSize = cols/2;
	vector<float> filterPart1(filterPartSize,-1/(2*M_PI)); // -i/2*Pi
	vector<float> filterPart2(filterPartSize,1/(2*M_PI));  //  i/2*Pi
	// container for filter image
	vector<float> pcImgFilter(cols*rows);
	vector<float>::iterator itPCImg = pcImgFilter.begin();
	// linear memory layout
	for(int i = 0; i < rows; i++)
	{
		copy(filterPart1.begin(), filterPart1.end(), itPCImg);
		itPCImg += filterPartSize;
		copy(filterPart2.begin(), filterPart2.end(), itPCImg);
		itPCImg += filterPartSize;
	}

#undef DEB_OUT
#ifdef DEB_OUT
	ofstream fil("filter.raw", ios::binary);
	fil.write((char*)&pcImgFilter[0],cols*rows*4);
	fil.close();
	//exit(-999);
#endif
	cv::Mat reMat(rows,cols,CV_32F,cv::Scalar(0.0f));
	cv::Mat imMat(rows,cols,CV_32F,&pcImgFilter[0]);
	vector<cv::Mat> filterVector(2);
	filterVector[0] = reMat;
	filterVector[1] = imMat;
	cv::Mat cmplxFilTemp;
	// create complex FFT filter and copy to member variable
	cv::merge(filterVector,cmplxFilTemp);
	cmplxFilTemp.copyTo(m_filterCmplx);
#ifdef DEB_OUT
	ofstream fftfm("filterImaginaer.raw", ios::binary);
	for(int i = 0; i < m_filterCmplx.cols; i++)
	{
		float v = m_filterCmplx.at<cv::Complexf>(0,i).im;
		fftfm.write((char*)&v,4);
	}
	fftfm.close();
	//exit(-999);
#endif

	return 1;
}

