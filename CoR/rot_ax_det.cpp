/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include <iostream>
#include <fstream>
#include <vector>
//#include <boost/algorithm/string.hpp>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
//#include <opencv2/ximgproc.hpp>

//-ju-10-may-2016 kurtosis
//////////////////////////
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/variance.hpp>


using namespace std;
using namespace cv;
//using namespace cv::ximgproc;

#define _DISPLAY_ON 0
#define _USE_BILATERAL_FILTER 1

static bool flag = false;
static float scale = 1.0f;

void EqualizeHistogram(unsigned short* pdata, int width, int height, int max_val = 255)
{
	int total = width*height;
	int n_bins = max_val + 1;

	// Compute histogram
	vector<int> hist(n_bins, 0);
	for (int i = 0; i < total; ++i) {
		hist[pdata[i]]++;
	}

	// Build LUT from cumulative histrogram

	// Find first non-zero bin
	int i = 0;
	while (!hist[i]) ++i;

	if (hist[i] == total) {
		for (int j = 0; j < total; ++j) {
			pdata[j] = i;
		}
		return;
	}

	// Compute scale
	float scale = (n_bins - 1.f) / (total - hist[i]);

	// Initialize lut
	vector<int> lut(n_bins, 0);
	i++;

	int sum = 0;
	for (; i < hist.size(); ++i) {
		sum += hist[i];
		// the value is saturated in range [0, max_val]
		lut[i] = max(0, min(int(round(sum * scale)), max_val));
	}

	// Apply equalization
	for (int i = 0; i < total; ++i) {
		pdata[i] = lut[pdata[i]];
	}
}


///////////////////////////////////
// Sharpness function squared gradient using
// using bilateral filter for mean ==> Nov 2017 used filter
///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
int GradientSquaredFromBiLat(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev/*, FILE *fp*/
#ifdef _DO_TEST
	, int i
#endif
	)
{
	// taking 50% of the image
	///////////////////////////
	//int w = (int)((float)width*0.5f);
	//int h = (int)((float)height*0.5f);
	//int pos_x = (int)((float)(width - w)*0.5f);
	//int pos_y = (int)((float)(height - h)*0.5f);
	int w = (int)((float)width*0.68f); // scale factor < 1/sqrt(2)
	int h = (int)((float)height*0.68f);
	int pos_x = (width - w)/2;
	int pos_y = (height - h)/2;

	Mat sub(w, h, CV_32F);

	origImg(Rect(pos_x, pos_y, w, h)).copyTo(sub);

//-ju-14-Oct-2016 definition for skew und kurt
//////////////////////////////////////////////
#define _AFTER_ORIG_
#ifdef _AFTER_ORIG
	std::vector<float> array(sub.rows*sub.cols);
	if (sub.isContinuous())
		array.assign(sub.datastart, sub.dataend);
#endif


	double scaleUp = 1.0;
	Scalar meanVal;
	meanVal = cv::mean(sub);
	if (fabs(meanVal.val[0]) < 0.001)	scaleUp = 10.0;
	if (fabs(meanVal.val[0]) < 0.0001)	scaleUp = 100.0;
	origImg.convertTo(origImg, -1, scaleUp);


	double scale = 1;
	do
	{
		//printf("###### SumVariance=%f Scale=%f #######\n", sumVar.val[0], scale);

		// need a copy to get a valid image
		origImg(Rect(pos_x, pos_y, w, h)).copyTo(sub);
		sub = sub / scale;

		Mat img;

		int pixRange = 15;
		double sigma = pixRange*0.3;


#define _SMOOTH_BIL
#ifdef _SMOOTH_BIL
		cv::bilateralFilter(sub, img, pixRange, sigma, sigma);
#endif
#ifdef _DO_TEST_
		char origFileName[100];
		sprintf(origFileName, "F:/Data/Orig_BIL/Orig_File_w%04d_h%04d_no%04d.raw", img.cols, img.rows, i);
		std::ofstream fpOrigImg(origFileName, std::ios::binary);
		fpOrigImg.write((char*)img.data, w*h*sizeof(float));
		fpOrigImg.close();
#endif //_DO_TEST

		//-ju-11-Oct-2016
		/////////////////
		cv::Sobel(img, varImg, CV_32F, 1, 1);
		//cv::imwrite("SobelImage.tif", varImg);
		cv::multiply(varImg, varImg, varImg);
		//-ju-11-Oct-2016
		/////////////////


		sumVar = sum(varImg);
#ifdef _DO_TEST_
		char varFileName[100];
		sprintf(varFileName, "F:/Data/BILIN_Files/Variance_Filter_File_w%04d_h%04d_no%04d_sc%f.raw", w, h, i+1, scale);
		std::ofstream fpVarImg(varFileName, std::ios::binary);
		fpVarImg.write((char*)varImg.data, w*h*sizeof(float));
		fpVarImg.close();
#endif //_DO_TEST

		scale = scale * 10; // scale to avoid numerical instability
	} while (sumVar.val[0] > 100000000.0);

	return 0;
}