/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "LorentzFilterDLG.h"
#include <QtGui> 
#include <QColor> 
#include <QFileDialog>
#include <QMessageBox> 
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_canvas.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "NormalizeImageDLG.h"
#include "AutoAlphaEstimationDLG.h"
#include <arrayfire.h>
#include "XRA_HelperFunc.h"


/*
	Desrc.:	Plot cross section of projection
	Author:	Juergen Hofmann ( (c) Empa Duebendorf / Abt499)
	Date:	01-Mar-2017
*/


LorentzFilterDialog::LorentzFilterDialog(ProcessParameter param, QWidget *parent, double alphaVal)
{
	ui.setupUi(this);
	ui.qwtPlot_CrossSection->installEventFilter(this);

	// initialize member variables
	//////////////////////////////
	m_ZoomFacLeft = 4;
	m_ZoomFacRight = 4;
	m_ImageVisLeft = false;
	m_ImageVisRight = false;
	m_validProjFile = false;
	m_fullSelection = true;
	m_plotEnabled = false;
	m_param = param;

	//-ju-02-Mar-2018
	ui.doubleSpinBox_alphaProp->setValue(alphaVal);

	
	// signal slot connections
	///////////////////////////

	//-ju- need a pointer to a function, because currentIndexChanged is overloaded and we have to decide 
	//     between int and string argument of the signal
	void (QComboBox::*signalChange)(int) = &QComboBox::currentIndexChanged;
	connect(ui.comboBox_ZoomLeftImage, signalChange, this, &LorentzFilterDialog::ZoomLeftImage);
	connect(ui.comboBox_ZoomRightImage, signalChange, this, &LorentzFilterDialog::ZoomRightImage);

	// open projection file
	connect(ui.pushButton_OpenProjection, &QPushButton::clicked, this, &LorentzFilterDialog::OpenProjectionFile);
	connect(ui.lineEdit_OpenProjectionFile, &QLineEdit::textChanged, this, &LorentzFilterDialog::ValidateFile);
	// open auto alpha estimation dialog
	connect(ui.pushButton_alphaEstimator, &QPushButton::clicked, this, &LorentzFilterDialog::OpenAlphaEstimatorDialog);
	connect(ui.pushButton_processAlphaStepwise, &QPushButton::clicked, this, &LorentzFilterDialog::ApplyLorentzFilterByStep);

	// change cross section profile
	void (QSpinBox::*valueSet)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox_profile, valueSet, this, &LorentzFilterDialog::ChangeCrossSection);

	// zooming in plot
	connect(ui.pushButton_setSelection, &QPushButton::clicked, this, &LorentzFilterDialog::SetZoomWindow);
	// zooming out plot
	connect(ui.pushButton_Reset, &QPushButton::clicked, this, &LorentzFilterDialog::ResetZoomWindow);

	// windows selection
	void (QDoubleSpinBox::*signalValChanged)(double) = &QDoubleSpinBox::valueChanged;
	connect(ui.doubleSpinBox_Width, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
	connect(ui.doubleSpinBox_Height, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
	connect(ui.doubleSpinBox_Px, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
	connect(ui.doubleSpinBox_Py, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);

	// alpha value
	connect(ui.doubleSpinBox_alphaProp, 
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), 
		this, 
		&LorentzFilterDialog::ChangeAlpha);
}



LorentzFilterDialog::~LorentzFilterDialog()
{

}

bool LorentzFilterDialog::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if (m_fullSelection && m_plotEnabled == true)
	{
		if (targetCtrl == ui.qwtPlot_CrossSection)
		{
			if (event->type() == QEvent::MouseButtonPress)
			{
				QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
				if (mEvt->button() == Qt::LeftButton)
				{
					QPoint pointPos = m_pPicker->trackerPosition();
					m_pntSelectRectStart = m_pPicker->posToPlotCoord(pointPos);

				}
				if (mEvt->button() == Qt::RightButton)
				{
					// disconnect slots to avoid round up update
					disconnect(ui.doubleSpinBox_Px, 0, 0, 0);
					disconnect(ui.doubleSpinBox_Py, 0, 0, 0);
					disconnect(ui.doubleSpinBox_Width, 0, 0, 0);
					disconnect(ui.doubleSpinBox_Height, 0, 0, 0);

					QPoint currentPnt = m_pPicker->trackerPosition();
					// translate to plot coordinates
					m_pntSelectRectEnd = m_pPicker->posToPlotCoord(currentPnt);
					// todo reorder points left to right; no neg. distances
					m_xLeft = m_pntSelectRectStart.rx();
					m_xRight = m_pntSelectRectEnd.rx();
					m_yTop = m_pntSelectRectStart.ry();
					m_yBottom = m_pntSelectRectEnd.ry();
					if (m_xLeft > m_xRight)
					{
						double tmp = m_xLeft;
						m_xLeft = m_xRight;
						m_xRight = tmp;
					}
					if (m_yBottom > m_yTop)
					{
						double tmp = m_yBottom;
						m_yBottom = m_yTop;
						m_yTop = tmp;
					}
					m_width = m_xRight - m_xLeft;
					m_height = m_yTop - m_yBottom;

					ui.doubleSpinBox_Px->setValue(m_xLeft);
					ui.doubleSpinBox_Py->setValue(m_yBottom);
					ui.doubleSpinBox_Width->setValue(m_width);
					ui.doubleSpinBox_Height->setValue(m_height);

					// re-connect
					void (QDoubleSpinBox::*signalValChanged)(double) = &QDoubleSpinBox::valueChanged;
					connect(ui.doubleSpinBox_Width, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
					connect(ui.doubleSpinBox_Height, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
					connect(ui.doubleSpinBox_Px, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
					connect(ui.doubleSpinBox_Py, signalValChanged, this, &LorentzFilterDialog::DrawZoomWindow);
				}

			}
			if (event->type() == QEvent::MouseMove)
			{
				QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);

				QPoint currentPnt = m_pPicker->trackerPosition();
				m_pntSelectRectEnd = m_pPicker->posToPlotCoord(currentPnt);
				m_xLeft = m_pntSelectRectStart.rx();
				m_xRight = m_pntSelectRectEnd.rx();
				m_yTop = m_pntSelectRectStart.ry();
				m_yBottom = m_pntSelectRectEnd.ry();
				// RTTI in ProcessLorentzFilter() resets m_pPicker object
				ProcessLorentzFilter();
			}
		}
	}
	this->update();
	return QDialog::eventFilter(targetCtrl, event);
}


// slots
////////////////////////////////////////////////

void LorentzFilterDialog::SetZoomWindow()
{
	double px = ui.doubleSpinBox_Px->value();
	double py = ui.doubleSpinBox_Py->value();
	m_width = ui.doubleSpinBox_Width->value();
	m_height = ui.doubleSpinBox_Height->value();
	m_xRight = px + m_width;
	m_xLeft = px;
	m_yTop = py + m_height;
	m_yBottom = py;
	m_fullSelection = false;
	PlotCrossSection();
}

void LorentzFilterDialog::ResetZoomWindow()
{
	m_fullSelection = true;
	PlotCrossSection();
}

void LorentzFilterDialog::DrawZoomWindow()
{

	double px = ui.doubleSpinBox_Px->value();
	double py = ui.doubleSpinBox_Py->value();
	m_width = ui.doubleSpinBox_Width->value();
	m_height = ui.doubleSpinBox_Height->value();
	m_xRight = px + m_width;
	m_xLeft = px;
	m_yTop = py + m_height;
	m_yBottom = py;
	PlotCrossSection();
}

// zooming left image
void LorentzFilterDialog::ZoomLeftImage()
{
	if (m_ImageVisLeft)
	{
		uint32_t idx = ui.comboBox_ZoomLeftImage->currentIndex();
		switch (idx)
		{
		case Percent25:
			m_ZoomFacLeft = 4.0;
			break;
		case Percent50:
			m_ZoomFacLeft = 2.0;
			break;
		case Percent75:
			m_ZoomFacLeft = 1.25;
			break;
		case Percent100:
			m_ZoomFacLeft = 1.0;
			break;
		case Percent200:
			m_ZoomFacLeft = 0.5;
			break;
		default:
			m_ZoomFacLeft = 2.0;
			break;
		}

		//-ju-18-Apr-2017
		QPixmap ipix = Raw2Pixmap(m_origImageData.data(), m_projectionImage.width(), m_projectionImage.height());
		QPixmap imgPix = ipix.scaled(
			ipix.width() / m_ZoomFacLeft,
			ipix.height() / m_ZoomFacLeft);
		//-ju-18-Apr-2017

		uint32_t x0 = 0;
		uint32_t x1 = (uint32_t)((float)m_projectionImage.width() / m_ZoomFacLeft);
		uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacLeft);
		QPoint pntStart(x0, y - 1);
		QPoint pntEnd(x1, y - 1);
		QLine crossSectionLine(pntStart, pntEnd);
		QPixmap pix(imgPix);
		QPainter paint(&pix);
		QPen pen(Qt::red, 1);
		paint.setPen(pen);
		paint.drawLine(crossSectionLine);
		ui.label_OrigImageLeft->setPixmap(pix);
		ui.label_OrigImageLeft->show();
	}
}

// zooming right image
void LorentzFilterDialog::ZoomRightImage()
{
	if (m_ImageVisRight)
	{
		uint32_t idx = ui.comboBox_ZoomRightImage->currentIndex();
		switch (idx)
		{
		case Percent25:
			m_ZoomFacRight = 4.0;
			break;
		case Percent50:
			m_ZoomFacRight = 2.0;
			break;
		case Percent75:
			m_ZoomFacRight = 1.25;
			break;
		case Percent100:
			m_ZoomFacRight = 1.0;
			break;
		case Percent200:
			m_ZoomFacRight = 0.5;
			break;
		default:
			m_ZoomFacRight = 2.0;
			break;
		}

		// scale pixmap according zoom
		QPixmap pixmap = m_pixLorentzFilter.scaled(
			(int)((float)m_pixLorentzFilter.width() / m_ZoomFacRight),
			(int)((float)m_pixLorentzFilter.height() / m_ZoomFacRight)
		);
		uint32_t x0 = 0;
		uint32_t x1 = (uint32_t)((float)pixmap.width());
		uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacRight);
		QPoint pntStart(x0, y - 1);
		QPoint pntEnd(x1, y - 1);
		QLine crossSectionLine(pntStart, pntEnd);
		QPixmap pix(pixmap);
		QPainter paint(&pix);
		QPen pen(Qt::red, 1);
		paint.setPen(pen);
		// draw cross section line
		paint.drawLine(crossSectionLine);
		ui.label_FilteredImageRight->setPixmap(pix);
		ui.label_FilteredImageRight->show();
	}
}

// open projection file
void LorentzFilterDialog::OpenProjectionFile()
{
	QString ProjectionImage = QFileDialog::getOpenFileName(this, tr("Select Projection Image"),
		tr(""),
		tr("Projection Image File (*.tif *.tiff)"));
	if (!ProjectionImage.isEmpty())
	{
		NormalizeImageDLG normDialog(ProjectionImage, this);
		if (QDialog::Accepted == normDialog.exec())
		{
			m_normValue = normDialog.m_normValue;
			if (m_normValue <= 0.0)
			{
				int ret = QMessageBox::warning(this, tr("No Selection"),
					tr("No Normalize Window Selected"),
					QMessageBox::Ok);
				return;

			}
#ifdef _DEBUG
			printf("get value %f from normalize window\n", m_normValue);
#endif

			ui.lineEdit_OpenProjectionFile->setText(ProjectionImage);

			// load image to cv::Mat
			QByteArray bStr = ProjectionImage.toUtf8();
			std::string projectionNameStr = bStr.data();
			cv::Mat tmp = cv::imread(projectionNameStr, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
			// convert to float if necessary
			bool doConv = false; //-ju-20-Feb-2018
			if (type2str(tmp.type()) != "32FC1")
			{
				tmp.convertTo(tmp, CV_32F);
				doConv = true; //-ju-20-Feb-2018
			}
			//normalize data holding orig. image
			tmp /= m_normValue;

			//-ju-20-Feb-2018 load Qt Image
			// if float tif use Mat2QImage() to create a image
			//////////////////////////////////////////////////
			//QImage scImage;
			if (doConv)
			{
				m_projectionImage.load(ProjectionImage);
			}
			else
			{
				XRA::Helper tool;
				m_projectionImage = tool.Mat2QImage(tmp);
			}

			if (m_param.useBHC)
			{
				cv::Mat tmpInterm = cv::Mat::zeros(m_param.imgHeight, m_param.imgWidth, CV_32F);
				cv::Mat tmpBHCConst = cv::Mat::zeros(m_param.imgHeight, m_param.imgWidth, CV_32F);
				//-ju-18-Apr-2017 if BHC on apply log an BHC
				/////////////////////////////////////////////
				//-ju-27-Aug-2016 mask zero values --> avoid log(0)
				// all values should be below 1.0, but depending on 
				// normalisation factor (mean value) could be more 
				// then 1.0 --> lead to neg values log*-1
				///////////////////////////////////////////////////
				cv::Mat temp_NULL(tmp.size(), CV_32F);
				// find all 0 values and mask them
				cv::Mat temp_NULL_255 = tmp <= 0.0f;
				// all assigned 0-values will have values > 17 after taken log(5.0*10e7)
				// should be sufficient high to discriminate from image real values
				temp_NULL_255.convertTo(temp_NULL, CV_32F, 5.0f*10e7f / 255.0f);
				tmp = tmp + temp_NULL;
				cv::log(tmp, tmpInterm);

				//////////////////////////////////////////////////////
				// avoid neg. values due to pow() function
				///////////////////////////////////////////
				tmp = tmpInterm * (-1.0f);
				// make sure having no negative values
				cv::threshold(tmp, tmp, 0.0f, 0.0f, cv::THRESH_TOZERO);
				tmp += 1.0;
				tmp.copyTo(tmpBHCConst);
				// muss groesser 0 sein!!!
				cv::pow(tmp, m_param.coeffBHC, tmpInterm);
				tmpBHCConst = m_param.constCoeffBHC_A*tmpBHCConst;
				tmp = tmpBHCConst + m_param.constCoeffBHC_B*tmpInterm;
				//-ju-18-Apr-2017 if BHC on apply log an BHC
			}


			// copy data to member variable
			m_origImageData.clear();
			m_origImageData.resize(tmp.cols*tmp.rows);
			memcpy(&m_origImageData[0], tmp.ptr(0), tmp.cols*tmp.rows * sizeof(float));

			//-ju-18-Apr-2017
			//-ju-20-Feb-2018 QPixmap ipix = Raw2Pixmap(m_origImageData.data(), m_projectionImage.width(), m_projectionImage.height());
			QPixmap ipix = QPixmap::fromImage(m_projectionImage);
				QPixmap imgPix = ipix.scaled(
				ipix.width() / m_ZoomFacLeft,
				ipix.height() / m_ZoomFacLeft);
			//-ju-18-Apr-2017

			// ajust profile (slider and spin box)
			ui.spinBox_profile->setValue((m_projectionImage.height() - 1) / 2);
			ui.verticalSlider_profile->setMaximum(m_projectionImage.height() - 1);
			ui.verticalSlider_profile->setSliderPosition((m_projectionImage.height() - 1) / 2);

			// draw cross section line
			///////////////////////////

			// get pixmap
			//-ju-18-Apr-2017 QPixmap imgPix = QPixmap::fromImage(scImage);
			uint32_t x0 = 0;
			uint32_t x1 = (uint32_t)((float)m_projectionImage.width() / m_ZoomFacLeft);
			uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacLeft);
			QPoint pntStart(x0,y-1);
			QPoint pntEnd(x1,y-1);
			QLine crossSectionLine(pntStart, pntEnd);
			QPixmap pix(imgPix);
			QPainter paint(&pix);
			QPen pen(Qt::red, 1);
			paint.setPen(pen);
			paint.drawLine(crossSectionLine);
			ui.label_OrigImageLeft->setPixmap(pix);
			ui.label_OrigImageLeft->show();
			m_ImageVisLeft = true;

			// fill line space x for plotting
			//////////////////////////////////
			m_crossLineSpaceX.clear();
			for (int i = 0; i < m_projectionImage.width(); i++)
			{
				m_crossLineSpaceX.push_back(static_cast<float>(i));
			}
		}
	}

}

void LorentzFilterDialog::OpenAlphaEstimatorDialog()
{
	if (GetNormMeanValue() < 0.0)
	{
		int ret = QMessageBox::warning(this, tr("Incorrect Image Normalization Value"),
			tr("Normalization value is not correct.\n"
				"Please redo normalization!"),
			QMessageBox::Ok);
		return;

	}
	AlphaEstimationDialog alphaDLG(m_projectionImage, 
		ui.lineEdit_OpenProjectionFile->text(), m_normValue, m_param, m_origImageData, this);
	if (QDialog::Accepted == alphaDLG.exec())
	{
		 m_alpha = alphaDLG.GetAlphaValue();
		 if (m_alpha <= 0)
		 {
			 int ret = QMessageBox::warning(this, tr("Incorrect Alpha"),
				 tr("Alpha must be greater zero"),
				 QMessageBox::Ok);
			 return;
		 }
		 ui.doubleSpinBox_alphaProp->setValue(m_alpha);
		 // open projection & apply normalization, lorentz filtering
		 // visualize filtered image
		 ////////////////////////////////////////////////////////////
		 ProcessLorentzFilter();
	}
}

void LorentzFilterDialog::ApplyLorentzFilterByStep()
{
	m_alpha = ui.doubleSpinBox_alphaProp->value();
	if (m_alpha <= 0)
	{
		int ret = QMessageBox::warning(this, tr("Incorrect Alpha"),
			tr("Alpha must be greater zero"),
			QMessageBox::Ok);
		return;
	}
	ProcessLorentzFilter();
	m_detAlpha = ui.doubleSpinBox_alphaProp->value();
	double stepSize = ui.doubleSpinBox_alphaStepSize->value();
	disconnect(ui.doubleSpinBox_alphaProp, 0, 0, 0);
	ui.doubleSpinBox_alphaProp->setValue(m_alpha+stepSize);
	connect(ui.doubleSpinBox_alphaProp,
		static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this,
		&LorentzFilterDialog::ChangeAlpha);
	QString txt = tr("%1").arg(m_detAlpha);
	ui.label_AlphaReturn->setText(txt);
}

void LorentzFilterDialog::ChangeAlpha()
{
	m_detAlpha = ui.doubleSpinBox_alphaProp->value();
	double stepSize = ui.doubleSpinBox_alphaStepSize->value();
	QString txt = tr("%1").arg(m_detAlpha);
	ui.label_AlphaReturn->setText(txt);
}

void LorentzFilterDialog::ValidateFile()
{
	if (ui.lineEdit_OpenProjectionFile->text().length() > 0 &&
		QFile::exists(ui.lineEdit_OpenProjectionFile->text()))
	{
		m_validProjFile = true;
		ui.groupBox_alphaComponents->setEnabled(true);
		m_imageName = ui.lineEdit_OpenProjectionFile->text();
	}
	else
	{
		m_validProjFile = false;
		ui.groupBox_alphaComponents->setEnabled(false);
	}
}

void LorentzFilterDialog::ProcessLorentzFilter()
{
	// check if valid alpha
	m_alpha = ui.doubleSpinBox_alphaProp->value();
	if (m_alpha <= 0)
	{
		int ret = QMessageBox::warning(this, tr("Incorrect Alpha"),
			tr("Alpha must be greater zero"),
			QMessageBox::Ok);
		return;
	}
	QByteArray bStr = m_imageName.toUtf8();
	std::string filenameStr = bStr.data();


	af::array  img = af::loadImage(filenameStr.c_str());
	// normalize image
#ifdef _DEBUG
	printf("NormValue: %f\n", m_normValue);
#endif
	img = img / m_normValue;
	// get image size
	af::dim4 dim = img.dims();


	// c- memory layout
	int32_t imSzY = dim[0];
	int32_t imSzX = dim[1];
	size_t sizeData = imSzX*imSzY;

	//-ju-18-Apr-2017
	af::array imgFormMem(imSzX, imSzY, &m_origImageData[0]);
	img = imgFormMem.T();
	//-ju-18-Apr-2017

	// create filter kernel first step
	///////////////////////////////////
	float *filterKernelRaw = new float[imSzX*imSzY];
	LorentzFilterKernel(filterKernelRaw, imSzX, imSzY);
	// create 
	af::array arrayLorentzKernel(imSzX, imSzY, filterKernelRaw);
	// transform to column major mem. layout
	arrayLorentzKernel = arrayLorentzKernel.T();

	// fft of input image
	// output image is complex !!!
	//////////////////////////////
	af::array imgFFT = fft2(img);

	double factor = 1.0e-6*m_alpha;
	af::array filterKernel = arrayLorentzKernel*factor + 1.0;
	filterKernel = 1.0 / filterKernel;

	// shift fft image
	af::array filterKernel_shift = fftshift(filterKernel);

	// create complex filter kernel 
	af::array filterKernel_cmplx = af::complex(filterKernel_shift);
	// apply lorentz filter
	af::array FFT_filt_img = imgFFT*filterKernel_cmplx;
	// take real inverse FFT image
	af::array filt_img_real = real(ifft2(FFT_filt_img));
	filt_img_real = filt_img_real.T();

	//af::saveImageNative("LorentzFilterG.tif", filt_img_real);

	float *data = filt_img_real.host<float>();

	// copy data to variable
	m_lorentzImageData.clear();
	m_lorentzImageData.resize(imSzX*imSzY);
	memcpy(&m_lorentzImageData[0], data, imSzX*imSzY*sizeof(float));

	// do visualization
	////////////////////
	m_pixLorentzFilter = Raw2Pixmap(data, imSzX, imSzY);

	// scale pixmap according zoom
	QPixmap pixmap = m_pixLorentzFilter.scaled(
		(int)((float)m_pixLorentzFilter.width() / m_ZoomFacRight),
		(int)((float)m_pixLorentzFilter.height() / m_ZoomFacRight)
	);

	uint32_t x0 = 0;
	uint32_t x1 = (uint32_t)((float)pixmap.width());
	uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacRight);
	QPoint pntStart(x0, y - 1);
	QPoint pntEnd(x1, y - 1);
	QLine crossSectionLine(pntStart, pntEnd);
	QPixmap pix(pixmap);
	QPainter paint(&pix);
	QPen pen(Qt::red, 1);
	paint.setPen(pen);
	// draw cross section line
	paint.drawLine(crossSectionLine);
	ui.label_FilteredImageRight->setPixmap(pix);
	ui.label_FilteredImageRight->show();

	m_ImageVisRight = true;

	//////////////////////////////////////////////////////////////////////////////
	// plot crosssection (m_origImageData & m_lorentzImageData should be available
	//////////////////////////////////////////////////////////////////////////////
	PlotCrossSection();

#ifdef NDEBUG 
	delete[] data;
#endif
}

void LorentzFilterDialog::ChangeCrossSection()
{
	if (m_ImageVisLeft)
	{
		//-ju-18-Apr-2017
		QPixmap ipix = Raw2Pixmap(m_origImageData.data(), m_projectionImage.width(), m_projectionImage.height());
		QPixmap imgPix = ipix.scaled(
			ipix.width() / m_ZoomFacLeft,
			ipix.height() / m_ZoomFacLeft);
		//-ju-18-Apr-2017
		uint32_t x0 = 0;
		uint32_t x1 = (uint32_t)((float)m_projectionImage.width() / m_ZoomFacLeft);
		uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacLeft);
		QPoint pntStart(x0, y - 1);
		QPoint pntEnd(x1, y - 1);
		QLine crossSectionLine(pntStart, pntEnd);
		QPixmap pix(imgPix);
		QPainter paint(&pix);
		QPen pen(Qt::red, 1);
		paint.setPen(pen);
		paint.drawLine(crossSectionLine);
		ui.label_OrigImageLeft->setPixmap(pix);
		ui.label_OrigImageLeft->show();
	}

	if (m_ImageVisRight)
	{
		// scale pixmap according zoom
		QPixmap pixmap = m_pixLorentzFilter.scaled(
			(int)((float)m_pixLorentzFilter.width() / m_ZoomFacRight),
			(int)((float)m_pixLorentzFilter.height() / m_ZoomFacRight)
		);
		uint32_t x0 = 0;
		uint32_t x1 = (uint32_t)((float)pixmap.width());
		uint32_t y = (uint32_t)((float)ui.verticalSlider_profile->sliderPosition() / m_ZoomFacRight);
		QPoint pntStart(x0, y - 1);
		QPoint pntEnd(x1, y - 1);
		QLine crossSectionLine(pntStart, pntEnd);
		QPixmap pix(pixmap);
		QPainter paint(&pix);
		QPen pen(Qt::red, 1);
		paint.setPen(pen);
		// draw cross section line
		paint.drawLine(crossSectionLine);
		ui.label_FilteredImageRight->setPixmap(pix);
		ui.label_FilteredImageRight->show();
		if (m_plotEnabled == true)
		{
			PlotCrossSection();
		}
	}

}


// general functions
////////////////////////////////////////////////

// memory of pFilterArray must be alloc/dealloc out side of function
void LorentzFilterDialog::LorentzFilterKernel(float *pFilterArray, int32_t szX, int32_t szY)
{
	for (int iy = 0; iy < szY; iy++)
	{
		for (int ix = 0; ix < szX; ix++)
		{
			pFilterArray[szX*iy + ix] = (ix - (szX / 2 - 1))*(ix - (szX / 2 - 1)) 
				+ (iy - (szY / 2 - 1))*(iy - (szY / 2 - 1));
		}
	}
}


QPixmap LorentzFilterDialog::Raw2Pixmap(float *rawData,
	uint32_t width, uint32_t height)
{
	cv::Mat imgMat = cv::Mat::zeros(height, width, CV_32F);
	assert(rawData);
	memcpy(imgMat.data, rawData, height*width * sizeof(float));

	double minVal, maxVal;
	cv::minMaxLoc(imgMat, &minVal, &maxVal); //find minimum and maximum intensities
											   // scale image to uchar
	cv::Mat imgU8(imgMat.rows, imgMat.cols, CV_8U, cv::Scalar::all(0));
	imgMat.convertTo(imgMat, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));


	if (m_ColorTable.isEmpty())
	{
		for (int i = 0; i < 256; ++i)
			m_ColorTable.push_back(qRgb(i, i, i));
	}

	QImage image(imgMat.data, imgMat.cols, imgMat.rows, imgMat.step, QImage::Format_Indexed8);

	image.setColorTable(m_ColorTable);

	return QPixmap::fromImage(image);
}

void LorentzFilterDialog::GetCrossSectionPlotData(std::vector<float> imageData, 
	std::vector<float> &crossSectionLine)
{
	// calculate offset
	int32_t w = m_projectionImage.width();
	int32_t h = m_projectionImage.height();
	// current profile position
	int32_t pos = ui.spinBox_profile->value();
	int32_t off = w*pos;
	crossSectionLine.clear();
	crossSectionLine.resize(w);
	//-ju-Feb-2018 check why is invalid
	memcpy(&crossSectionLine[0], &imageData[off], w * sizeof(float));
}

void LorentzFilterDialog::PlotCrossSection()
{

	// get profile from orig. image data
	GetCrossSectionPlotData(m_origImageData, m_origLineData);
	// get profile from lorentz image data
	GetCrossSectionPlotData(m_lorentzImageData, m_lorentzLineData);

	// first data set
	std::vector<double> x, y;
	int32_t crossSecLength = m_projectionImage.width();
	for(int32_t i = 0; i < crossSecLength; i++)
	{
		x.push_back((double)i);
		y.push_back((double)m_origLineData[i]);
	}

	// second data set
	std::vector<double> x_LF, y_LF;
	for (int32_t i = 0; i < crossSecLength; i++)
	{
		x_LF.push_back((double)i);
		y_LF.push_back((double)m_lorentzLineData[i]);
	}


	// determine dimensions of plot
	////////////////////////////////
	double max_val_y = *std::max_element(y.begin(), y.end());
	double min_val_y = *std::min_element(y.begin(), y.end());
	double max_val_x = *std::max_element(x.begin(), x.end());
	double min_val_x = *std::min_element(x.begin(), x.end());
#ifdef _DEBUG
	printf("min_x: %f min_y: %f max_x: %f max_y: %f\n", min_val_x, min_val_y, max_val_x, max_val_y);
#endif

	// clear curve from previous plot
	//////////////////////////////////
	ui.qwtPlot_CrossSection->detachItems(QwtPlotItem::Rtti_PlotCurve);

	ui.qwtPlot_CrossSection->setTitle("Cross-Section");
	ui.qwtPlot_CrossSection->setCanvasBackground(Qt::white);

	// set dimension of plot
	/////////////////////////
	QPolygonF points_SW;
	if (m_fullSelection)
	{
		ui.qwtPlot_CrossSection->setAxisScale(QwtPlot::yLeft, min_val_y, max_val_y);
		ui.qwtPlot_CrossSection->setAxisScale(QwtPlot::xBottom, min_val_x, max_val_x);
		// selection window rectangle
		QPointF p1(m_xLeft, m_yTop);
		points_SW += p1;
		QPointF p2((double)m_xRight, (double)m_yTop);
		points_SW += p2;
		QPointF p3((double)m_xRight, (double)m_yBottom);
		points_SW += p3;
		QPointF p4((double)m_xLeft, (double)m_yBottom);
		points_SW += p4;
		QPointF p5(m_xLeft, m_yTop);
		points_SW += p5;

	}
	else
	{
		ui.qwtPlot_CrossSection->setAxisScale(QwtPlot::yLeft, m_yBottom, m_yTop);
		ui.qwtPlot_CrossSection->setAxisScale(QwtPlot::xBottom, m_xLeft, m_xRight);
	}

	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->enableXMin(true);
	grid->enableYMin(true);
	grid->setMajorPen(QPen(Qt::black, 1, Qt::SolidLine));
	grid->setMinorPen(QPen(Qt::white, 1, Qt::DotLine));
	grid->attach(ui.qwtPlot_CrossSection);

	QwtPlotCurve *curve_orig = new QwtPlotCurve();
	QwtPlotCurve *curve_LF = new QwtPlotCurve();
	QwtPlotCurve *curve_SW = new QwtPlotCurve();


	// first curve original
	curve_orig->setTitle("without Lorentz Filter");
	curve_orig->setPen(Qt::blue, 3),
		curve_orig->setRenderHint(QwtPlotItem::RenderAntialiased, true);

	QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse,
		QBrush(Qt::yellow), QPen(Qt::darkYellow, 1), QSize(5, 5));
	curve_orig->setSymbol(symbol);
	curve_orig->setPen(Qt::darkGreen, 2);
	curve_orig->setStyle(QwtPlotCurve::Lines);


	// second curve
	curve_LF->setTitle("with Lorentz Filter");
	curve_LF->setPen(Qt::darkCyan, 3),
		curve_LF->setRenderHint(QwtPlotItem::RenderAntialiased, true);

	QwtSymbol *symbol_LF = new QwtSymbol(QwtSymbol::Diamond,
		QBrush(Qt::red), QPen(Qt::darkRed, 1), QSize(5, 5));
	curve_LF->setSymbol(symbol_LF);
	curve_LF->setPen(Qt::darkMagenta, 2);
	curve_LF->setStyle(QwtPlotCurve::Lines);

	ui.qwtPlot_CrossSection->setAxisMaxMajor(QwtPlot::xBottom, 20);
	ui.qwtPlot_CrossSection->setAxisMaxMinor(QwtPlot::xBottom, 5);
	ui.qwtPlot_CrossSection->setAxisMaxMajor(QwtPlot::yLeft, 10);
	ui.qwtPlot_CrossSection->setAxisMaxMinor(QwtPlot::yLeft, 10);

	m_pPicker = new CrossPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
									QwtPlotPicker::CrossRubberBand,
									QwtPicker::AlwaysOn,
									(QwtPlotCanvas *)ui.qwtPlot_CrossSection->canvas());
	m_pPicker->setStateMachine(new QwtPickerClickPointMachine());
	m_pPicker->setRubberBandPen(QColor(Qt::green));
	m_pPicker->setRubberBand(QwtPicker::CrossRubberBand);
	m_pPicker->setTrackerPen(QColor(Qt::black));


	if (m_fullSelection)
	{
		curve_SW->setPen(Qt::darkBlue, 2);
		curve_SW->setStyle(QwtPlotCurve::Lines);
	}


	QPolygonF points;
	const int numSamples = x.size();
	for (int i = 0; i < numSamples; i++)
	{
		points += QPointF((double)x[i], (double)y[i]);
	}

	// second curve lorentz filtered image
	QPolygonF points_LF;
	const int numSamples_LF = x_LF.size();
	for (int i = 0; i < numSamples_LF; i++)
	{
		points_LF += QPointF((double)x_LF[i], (double)y_LF[i]);
	}


	curve_orig->setSamples(points);
	curve_LF->setSamples(points_LF);
	if (m_fullSelection)
	{
		curve_SW->setSamples(points_SW);
	}

	curve_orig->attach(ui.qwtPlot_CrossSection);
	curve_LF->attach(ui.qwtPlot_CrossSection);
	if (m_fullSelection)
	{
		curve_SW->attach(ui.qwtPlot_CrossSection);
	}
	ui.qwtPlot_CrossSection->replot();
	ui.qwtPlot_CrossSection->show();
	m_plotEnabled = true;
	ui.groupBox_WindowsZoomSelection->setEnabled(true);
}
