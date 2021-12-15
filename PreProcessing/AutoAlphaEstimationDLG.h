/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#pragma once
#include "ui_AutoAlphaEstimationDLG.h"
#include <cstdint>
#include "ProcessParameterTypes.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


#define fftshift(in)  shift(in, in.dims(0)/2, in.dims(1)/2)
#define ifftshift(in) shift(in, (in.dims(0)+1)/2, (in.dims(1)+1)/2)

class AlphaEstimationDialog:public QDialog
{
	Q_OBJECT

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);

public:
	AlphaEstimationDialog(QImage image, 
		QString imageName, 
		double meanValue, 
		ProcessParameter param,
		std::vector<float> origImageData,
		QWidget *parent = 0);
	~AlphaEstimationDialog();

	double GetAlphaValue()
	{
		return m_AlphaResult;
	}

	std::string type2str(int type)
	{
		std::string r;

		uchar depth = type & CV_MAT_DEPTH_MASK;
		uchar chans = 1 + (type >> CV_CN_SHIFT);

		switch (depth)
		{
		case CV_8U:  r = "8U"; break;
		case CV_8S:  r = "8S"; break;
		case CV_16U: r = "16U"; break;
		case CV_16S: r = "16S"; break;
		case CV_32S: r = "32S"; break;
		case CV_32F: r = "32F"; break;
		case CV_64F: r = "64F"; break;
		default:     r = "User"; break;
		}

		r += "C";
		r += (chans + '0');

		return r;
	}



private:
	Ui::Dialog_AutoAlpha ui_alpha;

	QImage m_scaledImage;
	QImage m_origImage;

	double m_normMeanValue; // comming from LorentzFilterDialog
	double m_AlphaResult;

	int32_t m_imageW;
	int32_t m_imageH;
	double  m_imageZoomFactor;

	int32_t m_x, m_y;
	QPixmap m_pix;

	QRect m_rectSelection;

	bool m_con1;
	bool m_con2;
	bool m_con3;
	bool m_con4;

	QString m_imageName;

	double m_alphaFrom;
	double m_alphaTo;
	double m_alphaStepSize;
	int32_t m_noSlices;

	ProcessParameter m_param;
	std::vector<float> m_origImageData;

private:
	void DrawRectangle();
	void CalcNoSlices();
	void LorentzFilterKernel(float *filterArray, int32_t szX, int32_t szY);
	void PlotSkewness(std::vector<double> skewVal, std::vector<double> alphaVal);

	void InitCon4Vec()
	{
		m_con1 = false;
		m_con2 = false;
		m_con3 = false;
		m_con4 = false;
	}

	bool IfCon4VecIsTrue()
	{
		if (m_con1 &&
			m_con2 &&
			m_con3 &&
			m_con4)
			return true;
		else
			return false;
	}

private slots:
	void ImageZoom();
	void DrawRectangleP1X();
	void DrawRectangleP1Y();
	void DrawRectangleP2X();
	void DrawRectangleP2Y();
	void ChangeAlpha();
	void StartAlphaEstimationProc();

	void SaveSelection();

 signals:
};
