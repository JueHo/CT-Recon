/**
*  Copyright © [2012], Empa, Juergen Hofmann
*/

#ifndef HISTOGRAMREMAP_H
#define HISTOGRAMREMAP_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <QtGui/QMouseEvent>
#include <qfiledialog.h>
#include <QColorDialog>
#include <qmessagebox.h>
#include "ui_histogramremap.h"
#include <qwt_scale_engine.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_item.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_intervalcurve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_grid.h>
#include <qwt_text.h>
#include <qstring.h>
#include <qdir.h>
#include <qfile.h>
#include <qstringlist.h>
#include <qwt_scale_engine.h>

#include <vector>
#include <algorithm>
#include <fstream>

#include "histPicker.h"

inline float ROUND(float x)
{
	return x > 0.0f ? x + 0.5f : x - 0.5f;
}

class RangeMapUC8
{
public:
	RangeMapUC8(float mapFactor, float f32min, float f32max)
		:m_mapFactor(mapFactor),m_f32min(f32min),m_f32max(f32max)
	{}
	unsigned char operator() (float inVal)
	{
		if(inVal > m_f32max || inVal < m_f32min) return 0;
		return static_cast<unsigned char>(ROUND((inVal - m_f32min)*m_mapFactor));
	}
private:
	float m_mapFactor;
	float m_f32min;
	float m_f32max;
};

class RangeMapUShort
{
public:
	RangeMapUShort(float mapFactor, float f32min, float f32max)
		:m_mapFactor(mapFactor),m_f32min(f32min),m_f32max(f32max)
	{}
	unsigned short operator() (float inVal)
	{
		if(inVal > m_f32max || inVal < m_f32min) return 0;
		return static_cast<unsigned short>(ROUND((inVal - m_f32min)*m_mapFactor));
	}
private:
	float m_mapFactor;
	float m_f32min;
	float m_f32max;
};

class HistogramRemap : public QMainWindow
{
	Q_OBJECT

public:
	HistogramRemap(QWidget *parent = 0);
	~HistogramRemap();

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);

private:
	void ConvertFloatToUShort(QString inputFile,
							  const long long &imageSize,
							  const float &minVal,
							  const float &maxVal)
	{
		std::ifstream inFile;
		std::vector<float> filebuffer(imageSize);

		float mapRange = USHRT_MAX/(maxVal - minVal);

		inFile.open(inputFile.toStdString().c_str(),std::ios::binary);
		if(!inFile.is_open())
		{
			QString errMsg = QString("Can not open %1!").arg(inputFile);
			QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		inFile.read((char*) &filebuffer[0],imageSize*sizeof(float));
		inFile.close();

		std::vector<unsigned short> mapUShort(filebuffer.size());
		transform(filebuffer.begin(), filebuffer.end(), mapUShort.begin(), RangeMapUShort(mapRange, minVal, maxVal));

		QFileInfo convertedFile(inputFile);
		QString base = convertedFile.baseName();
		QString byteFileName = m_imageDestinationDirectory + tr("/") + base + tr(".ui16");
		std::ofstream uShortOut;
		uShortOut.open(byteFileName.toStdString().c_str(), std::ios::binary);
		if(!uShortOut.is_open())
		{
			QString errMsg = QString("Can not open %1!").arg(byteFileName);
			QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		uShortOut.write((char*)&mapUShort[0],imageSize*sizeof(unsigned short));
		uShortOut.close();	
	}

	void ConvertFloatToByte(QString inputFile,
							const long long &imageSize,
							const float &minVal,
							const float &maxVal)
	{
		std::ifstream inFile;
		std::vector<float> filebuffer(imageSize);

		float mapRange = UCHAR_MAX/(maxVal - minVal);

		inFile.open(inputFile.toStdString().c_str(), std::ios::binary);
		if(!inFile.is_open())
		{
			QString errMsg = QString("Can not open %1!").arg(inputFile);
			QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		inFile.read((char*) &filebuffer[0],imageSize*sizeof(float));
		inFile.close();

		std::vector<unsigned char> mapByte(filebuffer.size());
		transform(filebuffer.begin(), filebuffer.end(), mapByte.begin(), RangeMapUC8(mapRange, minVal, maxVal));

		QFileInfo convertedFile(inputFile);
		QString base = convertedFile.baseName();
		QString byteFileName = m_imageDestinationDirectory + tr("/") + base + tr(".uchar");
		std::ofstream ucharOut;
		ucharOut.open(byteFileName.toStdString().c_str(), std::ios::binary);
		if(!ucharOut.is_open())
		{
			QString errMsg = QString("Can not open %1!").arg(byteFileName);
			QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		ucharOut.write((char*)&mapByte[0],imageSize*sizeof(unsigned char));
		ucharOut.close();	
	}

	bool ReadSettings();
	void WriteSettings();
	void FallBackSettings();
private:
	QString m_iniSrcDir;
	QString m_iniDestDir;
	int m_iniHistRed;
	int m_iniHistGreen;
	int m_iniHistBlue;
	int m_iniHistAlpha;
	int m_iniPlotRed;
	int m_iniPlotGreen;
	int m_iniPlotBlue;
	int m_iniPlotAlpha;

private:
	bool GetMinMax(const QString &fileName);

	Ui::HistogramRemapClass ui;
	QwtPlotIntervalCurve *m_pHistoCurve;
	QwtPlotCurve m_rightBound;
	QwtPlotCurve m_leftBound;

	QwtPlotMarker m_markerLeft, m_markerRight;

	double m_lbX[2];
	double m_lbY[2];
	double m_rbX[2];
	double m_rbY[2];

	HistPicker *m_pPicker;

	QString m_imageStackDirectory;
	QString m_imageDestinationDirectory;
	QString m_logFileName;
	QString m_usedFilter;
	double m_minGray;
	double m_maxGray;
	QColor m_histColor;

	std::vector<unsigned int> m_volumeHistogram;
	double m_histoIntervalLen;

private slots:
	void SetRightBound();
	void SetRightBound(QPointF &fPos);
	void SetLeftBound();
	void SetLeftBound(QPointF &fPos);
	void GetImageStackDirectory();
	void GetImageDestinationDirectory();
	void ReadImageStack();
	void SetMinMaxLogGroupState();
	void GetMinMaxFromLogFile();
	bool PopulateHistogram();
	void SelectHistogramColor();
	void SelectPlotColor();
	void ConvertToUChar();
	void ConvertToUShort();
};

#endif // HISTOGRAMREMAP_H
