#ifndef _STRIPE_RING_FILTER_H
#define _STRIPE_RING_FILTER_H

// windows header must be on first position
// else get conflict with std namespace
#include <windows.h> 
#include <fstream>
#include <cstdio>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>
#include <blitz/array.h>
#include <cstdint>
#include <ctime> 
#ifdef _OPENMP
#include <omp.h>
#endif

#include <boost/signals2/signal.hpp>

#include "definitions_public.h"
#include "preprocessor_handler.h"
#include "io_memory_handler.h"

using namespace cv;
using namespace std;
using namespace blitz;

class ProjectionPreprocessor
{
public:
	ProjectionPreprocessor(QString parameterFile, bool createNew = false);

	// public member functions
	///////////////////////////
	virtual MSG_CODE InitParametersNew();
	virtual MSG_CODE InitParameters();
	virtual MSG_CODE RunPrepocessor();
	Mat GetProjectionsSumImage(float *VolMem); // need for windows selection -> normalize
	void SetNormalizationWindow(Rect normWin);
	Rect GetNormalizationWindow();
	Mat GetFlatImage(string filename); // if not apply norm. win use flat for norm.
private:
	// hide std ctor
	ProjectionPreprocessor(){};

	// private member functions
	///////////////////////////
	// FFT functions
	/////////////////
	MSG_CODE FFTSinoStripeReductionFilter(float *VolMem);
	virtual void ShiftFFT(Mat &image);
	virtual uint64_t CalcFFTMinSize(uint64_t imgWidth, uint64_t imgHeight);
	virtual void CreateFFTFilterKernel(Mat &FFTFilterKernel,
		int32_t maskHeight = 0, 
		int32_t maskWidth = 0);
	// outliers
	////////////
	MSG_CODE ApplyOutlierReductionFilter(float *VolMem, 
		vector<Vec2i> &outlierPixelList);
	MSG_CODE RingArtefactReplaceByMean9(Mat &projection, Vec2i &pixCoord);
	MSG_CODE RingArtefactReplaceByMean13(Mat &projection, Vec2i &pixCoord);
	MSG_CODE RingArtefactReplaceByMean24(Mat &projection, Vec2i &pixCoord);
	MSG_CODE RingArtefactReplaceByMedian9(Mat &projection, Vec2i &pixCoord);
	MSG_CODE FindOutliers(Mat binOutlierImage, vector<Vec2i> &outlierPixelList);
	// binarized (segmented outlier image)
	MSG_CODE SegmentForOutliers(Mat &binOutlierImage); 

	MSG_CODE NormalizeImages(float *VolMem);
	MSG_CODE LogImage(Mat &image);

	MSG_CODE GetMeanFromFlatField(QString filename, float &meanVal);

private:
	PreprocParam m_paramObj;
	PreprocParamHandler m_preHnd;
	QString m_parameterFile;
	bool m_createNewParam;

	Mat m_projSumImage;
	Mat m_flatImage;
	Rect m_normalizeWindow;

	// for now fixed median window size -> 3x3
	///////////////////////////////////////////
	uint32_t m_medianMaskSize = 3;

	//uint64_t m_FFTMinalPadSize;
private:
	//vector<Mat> m_projectionList;
};

#endif // _STRIPE_RING_FILTER_H