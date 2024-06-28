/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef _THREAD_PROCESSING_H
#define _THREAD_PROCESSING_H

#include <QtCore/QThread>
#include <QtCore/QMutex> 
#include "ui_projectionpreprocessor.h"
#include <memory.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "ProcessParameterTypes.h"
#include <vector>
#include <fstream>

#define fftshift(in)  shift(in, in.dims(0)/2, in.dims(1)/2)
#define ifftshift(in) shift(in, (in.dims(0)+1)/2, (in.dims(1)+1)/2)

enum OutTypes
{
	REAL32,
	USHORT16,
};

using namespace std;

class ProjectionPreProcessor;

class ThreadProcessing : public QThread
{
	Q_OBJECT

public:
	ThreadProcessing(QObject *parent, bool intrp = false, bool thsp = false);
	~ThreadProcessing();

	void run();


	// interrupting thread
	bool m_interrupt;
	bool m_thread_stopped;

signals:
	void valueChanged(QString);
	void updateProgressBar(int);
	void threadStart();
	void threadEnd();
	void threadStopped();

private:
	// image processing routines
	/////////////////////////////
	void GetProjectionsSumImage(float *VolMem);
	void GetProjectionsSumTileImage(float *VolMem, uint32_t tileNo);
	void ApplyOutlierReductionFilter(float *VolMem, vector<cv::Vec2i> &outlierPixelList);
	void ApplyOutlierReductionFilter(float *VolMem, vector<cv::Vec2i> &outlierPixelList, uint64_t rows, uint64_t cols);
	void RingArtefactReplaceByMean9(cv::Mat &projection, cv::Vec2i &pixCoord);
	void RingArtefactReplaceByMedian9(cv::Mat &projection, cv::Vec2i &pixCoord);
	void FindOutliers(cv::Mat binOutlierImage, vector<cv::Vec2i> &outlierPixelList);
	// binarized (segmented outlier image)
	void SegmentForOutliers(cv::Mat &binOutlierImage);
	//-ju-09-Oct-2015 add RAC processing for tiles
	void ApplyRACOnTile();
	void NormalizeAndSaveForTiles();
	//-ju-
	void NormalizeImages(float *VolMem);
	void NormalizeImages(float *VolMem, uint64_t tileHeight, uint64_t tileWidth);
	void LogImage(cv::Mat &image);
	void GetMeanFromFlatField(QString filename, float &meanVal);
	void SaveProjections(float *VolMem);
	void SaveProjections(float *VolMem, uint32_t proNum);
	//-ju-11-Apr-2017
	void LorentzFilterKernel(float *pFilterArray, int32_t szX, int32_t szY);
	void ApplyLorentzFilter(cv::Mat &image, float *filterKernelRaw, float *pTemp);
	//-ju-24-June-2024 local tomography
	void ApplyROIPadding(float *projection, std::vector<float> &projection_pad);


private:
	QMutex m_mutex;
	ProjectionPreProcessor *m_parentObject;

	cv::Mat m_projSumImage;
	ProcessParameter m_procPara;
	uint32_t m_medianMaskSize = 3;
};

#endif // _THREAD_PROCESSING_H
