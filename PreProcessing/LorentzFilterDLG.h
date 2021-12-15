/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#pragma once
#include "ui_LorentzFilter.h"
#include "CrossPlotPicker.h"
#include <cstdint>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "ProcessParameterTypes.h"


enum ZoomFactor
{
	Percent25, Percent50, Percent75, Percent100, Percent200,
};

class LorentzFilterDialog:public QDialog
{
	Q_OBJECT

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);
	void PlotCrossSection();
	void GetCrossSectionPlotData(std::vector<float> imageData, 
		std::vector<float> &crossSectionLine);

public:
	LorentzFilterDialog(ProcessParameter param, QWidget *parent = 0, double alphaVal = 2.0);
	~LorentzFilterDialog();

	double m_detAlpha;

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


	void SetNormValue(float normVal)
	{
		m_normValue = normVal;
	}

	double GetNormMeanValue()
	{
		return m_normValue;
	}

	QPixmap Raw2Pixmap(float *rawData,
		uint32_t width, uint32_t height);

	void LorentzFilterKernel(float *filterArray, int32_t szX, int32_t szY);

private:
	Ui::Dialog ui;


	// member variables
	///////////////////
	double m_ZoomFacLeft;
	double m_ZoomFacRight;
	bool m_validProjFile;
	QVector<QRgb>  m_ColorTable;
	QString m_imageName;

	QImage m_projectionImage;
	QImage m_lorentzImage;

	QPixmap m_pixLorentzFilter;

	double m_normValue;
	double m_alpha;

	bool m_ImageVisLeft;
	bool m_ImageVisRight;

	bool m_fullSelection;
	bool m_plotEnabled;

	// to hold image data
	std::vector<float> m_origImageData;
	std::vector<float> m_lorentzImageData;
	std::vector<float> m_origLineData;
	std::vector<float> m_lorentzLineData;
	std::vector<float> m_crossLineSpaceX;

	double m_xLeft;
	double m_xRight;
	double m_yTop;
	double m_yBottom;
	double m_width;
	double m_height;

	CrossPlotPicker *m_pPicker;
	QPointF m_pntSelectRectStart;
	QPointF m_pntSelectRectEnd;

	ProcessParameter m_param;


private slots:
	void ZoomLeftImage();
	void ZoomRightImage();
	void OpenProjectionFile();
	void ValidateFile();
	void OpenAlphaEstimatorDialog();
	void ProcessLorentzFilter();
	void ApplyLorentzFilterByStep();
	void ChangeCrossSection();
	void SetZoomWindow();
	void ResetZoomWindow();
	void DrawZoomWindow();
	void ChangeAlpha();

};
