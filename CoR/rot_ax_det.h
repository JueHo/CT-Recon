/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

//////////////////
#ifndef _ROT_AX_DET_H
#define _ROT_AX_DET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;

int CalVarStdDevFromFile(char *tomo, unsigned int width, unsigned int height, 
                         Mat &origImg, Mat &varImg, Scalar &sumVar, 
                         Mat &stdDev, Scalar &sumStdDev
#ifdef _DO_TEST
						 , int i
#endif
						 );

int CalVarStdDevFromFile_BiLat(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev
#ifdef _DO_TEST
	, int i
#endif
	);

int CalVarStdDevFromFileNew(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev, int i);

int CalVarStdDevFromFile_HistEqua(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev, int &do_dummy
#ifdef _DO_TEST
	, int i
#endif
	);


int CalVarFilterUseGuidedFilter_HistEqua(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev, int &do_dummy
#ifdef _DO_TEST
	, int i
#endif
	);

int CalVarFilterUseGuidedFilter(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev
#ifdef _DO_TEST
	, int i
#endif
	);

void EqualizeHistogram(unsigned short* pdata, int width, int height, int max_val = 255);

int CalGradientFilter(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev, int &do_dummy
#ifdef _DO_TEST
	, int i
#endif
	);

int GradientSquaredFromBiLat(char *tomo, unsigned int width, unsigned int height,
	Mat &origImg, Mat &varImg, Scalar &sumVar,
	Mat &stdDev, Scalar &sumStdDev/*, FILE *fp*/
#ifdef _DO_TEST
	, int i
#endif
	);

#endif //_ROT_AX_DET_H

