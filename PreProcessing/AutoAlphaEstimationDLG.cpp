/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "AutoAlphaEstimationDLG.h"
#include <QtGui>
#include <QMessageBox> 
#include <QProgressDialog>
#include <arrayfire.h>
#include <string>
#include <algorithm>
#include <utility>
// plotting
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "LorentzFilterDLG.h"



extern void CalculateSkew(float *data, size_t sizeData, float &skewness);


AlphaEstimationDialog::AlphaEstimationDialog(QImage image, 
	QString imageName, 
	double meanValue, 
	ProcessParameter param,
	std::vector<float> origImageData,
	QWidget *parent)
:m_origImage(image), 
m_imageName(imageName), 
m_normMeanValue(meanValue),
m_param(param),
m_origImageData(origImageData)
{
	// setup GUI
	/////////////
	ui_alpha.setupUi(this);
	// install event handler
	/////////////////////////
	ui_alpha.label_imageWinSelection->installEventFilter(this);

	// hide debug button
#ifndef _DEBUG
	ui_alpha.pushButton_saveSelection->hide();
#endif
	// get window normalize mean value


	m_alphaFrom = ui_alpha.doubleSpinBox_AlphaFrom->value();
	m_alphaTo = ui_alpha.doubleSpinBox_AlphaTo->value();
	m_alphaStepSize = ui_alpha.doubleSpinBox_AlphaStepSize->value();
	CalcNoSlices();

	m_imageZoomFactor = 4.0; // default zoom factor 25%

	InitCon4Vec();

	m_imageW = m_origImage.width();
	m_imageH = m_origImage.height();

	// adapt image label size
	ui_alpha.label_imageWinSelection->setFixedWidth(m_imageW / m_imageZoomFactor);
	ui_alpha.label_imageWinSelection->setFixedHeight(m_imageH / m_imageZoomFactor);

	m_scaledImage = m_origImage.scaled((int)((float)m_imageW / m_imageZoomFactor),
									  (int)((float)m_imageH / m_imageZoomFactor));

	//-ju-18-Apr-2017
	QPixmap ipix = 
		dynamic_cast<LorentzFilterDialog*>(parent)->Raw2Pixmap(m_origImageData.data(), 
															   m_origImage.width(), 
															   m_origImage.height());
	m_origImage = ipix.toImage();
	QPixmap imgPix = ipix.scaled(
		ipix.width() / m_imageZoomFactor,
		ipix.height() / m_imageZoomFactor);
	ui_alpha.label_imageWinSelection->setPixmap(imgPix);
	m_scaledImage = imgPix.toImage();
	//-ju-18-Apr-2017

	ui_alpha.label_imageWinSelection->show();



	// signal slot connect
	//////////////////////////////////////////////////////
	//-ju- need a pointer to a function, because currentIndexChanged is overloaded and we have to decide 
	//     between int and string argument of the signal
	void (QComboBox::*signalChange)(int) = &QComboBox::currentIndexChanged;
	connect(ui_alpha.comboBox_ImageZoom, signalChange, this, &AlphaEstimationDialog::ImageZoom);
	// windows selection by sin box
	void (QSpinBox::*valueSet)(int) = &QSpinBox::valueChanged;
	connect(ui_alpha.spinBox_PointP1_x, valueSet, this, &AlphaEstimationDialog::DrawRectangleP1X);
	connect(ui_alpha.spinBox_PointP1_y, valueSet, this, &AlphaEstimationDialog::DrawRectangleP1Y);
	connect(ui_alpha.spinBox_PointP2_x, valueSet, this, &AlphaEstimationDialog::DrawRectangleP2X);
	connect(ui_alpha.spinBox_PointP2_y, valueSet, this, &AlphaEstimationDialog::DrawRectangleP2Y);

	// control of alpha estimation process
	void (QDoubleSpinBox::*signalValChanged)(double) = &QDoubleSpinBox::valueChanged;
	connect(ui_alpha.doubleSpinBox_AlphaFrom, signalValChanged, this, &AlphaEstimationDialog::ChangeAlpha);
	connect(ui_alpha.doubleSpinBox_AlphaTo, signalValChanged, this, &AlphaEstimationDialog::ChangeAlpha);
	connect(ui_alpha.doubleSpinBox_AlphaStepSize, signalValChanged, this, &AlphaEstimationDialog::ChangeAlpha);

	// start automatic alpha estimation
	connect(ui_alpha.pushButton_StartAlphaEstimation, &QPushButton::clicked, this, &AlphaEstimationDialog::StartAlphaEstimationProc);

	// only for test
	connect(ui_alpha.pushButton_saveSelection, &QPushButton::clicked, this, &AlphaEstimationDialog::SaveSelection);
}

AlphaEstimationDialog::~AlphaEstimationDialog()
{

}

// custom event handler
////////////////////////
bool AlphaEstimationDialog::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if (targetCtrl == ui_alpha.label_imageWinSelection)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if (mEvt->button() == Qt::LeftButton)
			{
				//-reset- image --> delete rect
				ui_alpha.label_imageWinSelection->setPixmap(QPixmap::fromImage(m_scaledImage));
				ui_alpha.label_imageWinSelection->show();

				m_x = mEvt->x();
				m_y = mEvt->y();
#ifdef _DEBUG
				printf("x1=%d\ty1=%d\n", m_x, m_y);
#endif
				QPixmap pix((*ui_alpha.label_imageWinSelection->pixmap()));
				m_pix = pix;
			}
		}
		if (targetCtrl == ui_alpha.label_imageWinSelection && event->type() == QEvent::MouseMove)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);

			QPoint ptnStart(m_x, m_y);
			QPoint ptnMove = mEvt->pos();
			// check if valid rectangle --> width, height wird negativ
			int32_t xs_n = m_x;
			int32_t ys_n = m_y;
			int32_t xe_n = ptnMove.x();
			int32_t ye_n = ptnMove.y();
			if (xe_n > m_scaledImage.width())
			{
				xe_n = m_scaledImage.width() - 1;
			}
			if (xe_n < 0)
			{
				xe_n = 0;
			}
			if (ye_n > m_scaledImage.height())
			{
				ye_n = m_scaledImage.height() - 1;
			}
			if (ye_n < 0)
			{
				ye_n = 0;
			}

			QPoint pntMv(xe_n, ye_n);
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue, 1);
			paint.setPen(pen);
			QRect drawRect(ptnStart, pntMv);
			paint.drawRect(drawRect);
			ui_alpha.label_imageWinSelection->setPixmap(pix);
		}
		if (event->type() == QEvent::MouseButtonRelease)
		{
			InitCon4Vec();

			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			QPoint ptnStart(m_x, m_y);
			QPoint ptnEnd = mEvt->pos();
			// check if valid rectangle --> width, height wird negativ
			int32_t xs_n = m_x;
			int32_t ys_n = m_y;
			int32_t xe_n = ptnEnd.x();
			int32_t ye_n = ptnEnd.y();
			if (xe_n > m_scaledImage.width())
			{
				xe_n = m_scaledImage.width() - 1;
			}
			if (xe_n < 0)
			{
				xe_n = 0;
			}
			if (ye_n > m_scaledImage.height())
			{
				ye_n = m_scaledImage.height() - 1;
			}
			if (ye_n < 0)
			{
				ye_n = 0;
			}

			if (xs_n > xe_n)
			{
				std::swap(xs_n, xe_n);
			}
			if (ys_n > ye_n)
			{
				std::swap(ys_n, ye_n);
			}
			QPoint p1(xs_n, ys_n);
			QPoint p2(xe_n, ye_n);

			// upscale selection depending on zoom factor
			QPoint p1N = p1*m_imageZoomFactor;
			QPoint p2N = p2*m_imageZoomFactor;
#ifdef _DEBUG
			printf("x1=%d --> x1N=%d  y1=%d --> y1=%d\n", p1.x(), p1N.x(), p1.y(), p1N.y());
			printf("x2=%d --> x2N=%d  y2=%d --> y2=%d\n", p2.x(), p2N.x(), p2.y(), p2N.y());
#endif

			// store selected rectangle
			m_rectSelection.setTopLeft(p1*m_imageZoomFactor);
			m_rectSelection.setBottomRight(p2*m_imageZoomFactor);
			ui_alpha.spinBox_PointP1_x->setValue(p1N.x());
			ui_alpha.spinBox_PointP1_y->setValue(p1N.y());
			ui_alpha.spinBox_PointP2_x->setValue(p2N.x());
			ui_alpha.spinBox_PointP2_y->setValue(p2N.y());
		}
	}
	this->update();
	return QDialog::eventFilter(targetCtrl, event);

}
// end custom event handler
///////////////////////////


//--> slots 
////////////

void AlphaEstimationDialog::ImageZoom()
{
	uint32_t idx = ui_alpha.comboBox_ImageZoom->currentIndex();
	switch (idx)
	{
	case 0:
		m_imageZoomFactor = 4.0;
		break;
	case 1:
		m_imageZoomFactor = 2.0;
		break;
	case 2:
		m_imageZoomFactor = 1.25;
		break;
	case 3:
		m_imageZoomFactor = 1.0;
		break;
	case 4:
		m_imageZoomFactor = 0.5;
		break;
	default:
		m_imageZoomFactor = 4.0;
		break;
	}

	// adapt image label size
	ui_alpha.label_imageWinSelection->setFixedWidth(m_imageW / m_imageZoomFactor);
	ui_alpha.label_imageWinSelection->setFixedHeight(m_imageH / m_imageZoomFactor);

	m_scaledImage = m_origImage.scaled((int)((float)m_imageW / m_imageZoomFactor),
									   (int)((float)m_imageH / m_imageZoomFactor));
	ui_alpha.label_imageWinSelection->setPixmap(QPixmap::fromImage(m_scaledImage));
	ui_alpha.label_imageWinSelection->show();

	QPixmap pix(QPixmap::fromImage(m_scaledImage));
	ui_alpha.label_imageWinSelection->setPixmap(pix);
	ui_alpha.label_imageWinSelection->show();


	QPainter paint(&pix);
	QPen pen(Qt::blue, 1);
	paint.setPen(pen);
	QRect scaledRect(m_rectSelection.topLeft() / m_imageZoomFactor,
		m_rectSelection.bottomRight() / m_imageZoomFactor);

	paint.drawRect(scaledRect);
	ui_alpha.label_imageWinSelection->setPixmap(pix);
}



void AlphaEstimationDialog::DrawRectangleP1X()
{
	if (IfCon4VecIsTrue())
	{
		DrawRectangle();
	}
	else
	{
		m_con1 = true;
	}
}

void AlphaEstimationDialog::DrawRectangleP1Y()
{
	if (IfCon4VecIsTrue())
	{
		DrawRectangle();
	}
	else
	{
		m_con2 = true;
	}

}

void AlphaEstimationDialog::DrawRectangleP2X()
{
	if (IfCon4VecIsTrue())
	{
		DrawRectangle();
	}
	else
	{
		m_con3 = true;
	}

}

void AlphaEstimationDialog::DrawRectangleP2Y()
{
	if (IfCon4VecIsTrue())
	{
		DrawRectangle();
	}
	else
	{
		m_con4 = true;
	}
}

void AlphaEstimationDialog::ChangeAlpha()
{
	m_alphaFrom = ui_alpha.doubleSpinBox_AlphaFrom->value();
	m_alphaTo = ui_alpha.doubleSpinBox_AlphaTo->value();
	m_alphaStepSize = ui_alpha.doubleSpinBox_AlphaStepSize->value();
	CalcNoSlices();
}

void AlphaEstimationDialog::StartAlphaEstimationProc()
{
	using namespace af;
	int32_t colStart = ui_alpha.spinBox_PointP1_x->value();
	int32_t colEnd = ui_alpha.spinBox_PointP2_x->value();
	int32_t rowStart = ui_alpha.spinBox_PointP1_y->value();
	int32_t rowEnd = ui_alpha.spinBox_PointP2_y->value();

	// check if valid area A > 0
	int32_t area = (colEnd - colStart)*(rowEnd - rowStart);
	if (area <= 0)
	{
		int ret = QMessageBox::warning(this, tr("Window Selection Invalid"),
			tr("The selected window is not valid.\n"
				"Please specify new window"),
			QMessageBox::Ok);
		return;
	}
	QApplication::setOverrideCursor(Qt::WaitCursor);

	QByteArray bStr = m_imageName.toUtf8();
	std::string filenameStr = bStr.data();

	//af::setDevice(0);
	//af::info();


	array  img = loadImage(filenameStr.c_str());
	// normalize image
	img = img / m_normMeanValue;
	array subWinIn = img.cols(colStart, colEnd).rows(rowStart, rowEnd);

	// get subwindow size
	dim4 dim = subWinIn.dims();

	// c- memory layout
	int32_t imSzY = dim[0];
	int32_t imSzX = dim[1];
	size_t sizeData = imSzX*imSzY;

	// create filter kernel first step
	///////////////////////////////////
	float *filterKernel = new float[imSzX*imSzY];
	LorentzFilterKernel(filterKernel, imSzX, imSzY);
	// create 
	array arrayLorentzKernel(imSzX, imSzY, filterKernel);
	// transform to column major mem. layout
	arrayLorentzKernel = arrayLorentzKernel.T();

	QProgressDialog progress("Determine Alpha", "Abort", 0, m_noSlices, this);
	progress.setWindowModality(Qt::WindowModal);

	// create edge image from original image
	array img_sobel_orig = sobel(subWinIn);	

	// fft of input image
	// output image is complex !!!
	//////////////////////////////
	array orig_img_fft = fft2(subWinIn);

	// init
	uint32_t idx = 0;
	double alpha = 0.0; 

	// skew vector
	std::vector<double> skewArray;
	// x range vector
	std::vector<double> alphaValues;
	while(idx < m_noSlices)
	{
		progress.setValue(idx);
		alpha = m_alphaFrom + m_alphaStepSize*idx;
		alphaValues.push_back(alpha);
#ifdef _DEBUG
		printf_s("(%0d) Run alpha=%e\n",idx+1, alpha);
#endif
		double factor = 1.0e-6*alpha;
		array filterKernel = arrayLorentzKernel*factor + 1.0;
		filterKernel = 1.0 / filterKernel;

		// shift fft image
		array filterKernel_shift = fftshift(filterKernel);

		// create complex filter kernel 
		array filterKernel_cmplx = af::complex(filterKernel_shift);
		array FFT_filt_img = orig_img_fft*filterKernel_cmplx;
		array filt_img_real = real(ifft2(FFT_filt_img)); // take real image

		// process image with sobel (edges)
		array img_sobel = sobel(filt_img_real);

		array diffImg = img_sobel - img_sobel_orig;
		float skewness;
		float *data = diffImg.host<float>();
		CalculateSkew(data, sizeData, skewness);
		skewArray.push_back(skewness);

		// raise an acception in debug mode
		// --> disable in debug mode --> get mem. leak
#ifdef NDEBUG 
		delete[] data;
#endif

#ifdef _DEBUG
		printf("Skew = %f\n", skewness);
#endif
		idx++;
	}
	progress.setValue(m_noSlices);

	//std::vector<double>::iterator maxVal;
	auto  maxVal = std::max_element(skewArray.begin(), skewArray.end());
	auto maxAlpha = std::distance(skewArray.begin(), maxVal);

#ifdef _DEBUG
	//printf("Max Skew: %f\n", alphaValues[maxAlpha]);
#endif
	double foundAlpha = -1.0;
	if (maxAlpha >= 0 && maxAlpha < alphaValues.size())
	{
		foundAlpha = alphaValues[maxAlpha];
	}
	ui_alpha.doubleSpinBox_AlphaResult->setValue(foundAlpha);
	m_AlphaResult = foundAlpha;

	delete[] filterKernel;
	QApplication::restoreOverrideCursor();

	PlotSkewness(skewArray, alphaValues);
}
//<-- slots 
////////////

// class functions
/////////////////////////////////////////
void AlphaEstimationDialog::DrawRectangle()
{
	QPoint p1(ui_alpha.spinBox_PointP1_x->value(),
		ui_alpha.spinBox_PointP1_y->value());
	QPoint p2(ui_alpha.spinBox_PointP2_x->value(),
		ui_alpha.spinBox_PointP2_y->value());


	p1 = p1 / m_imageZoomFactor;
	p2 = p2 / m_imageZoomFactor;
#ifdef _DEBUG
	printf("\nDrawRec: x1=%d y1=%d x2=%d y2=%d\n\n", p1.x(), p1.y(), p2.x(), p2.y());
#endif

	if (p1.x() <= p2.x() &&
		p1.y() <= p2.y() &&
		p2.x() < m_imageW / m_imageZoomFactor &&
		p2.y() < m_imageH / m_imageZoomFactor)
	{
		QPixmap pix(QPixmap::fromImage(m_scaledImage));
		ui_alpha.label_imageWinSelection->setPixmap(pix);
		ui_alpha.label_imageWinSelection->show();

		//		QPixmap pix(m_pix);
		QPainter paint(&pix);
		QPen pen(Qt::blue, 1);
		paint.setPen(pen);
		QRect drawRect(p1, p2);
		paint.drawRect(drawRect);
		ui_alpha.label_imageWinSelection->setPixmap(pix);

		// store selected rectangle
		m_rectSelection.setTopLeft(p1*m_imageZoomFactor);
		m_rectSelection.setBottomRight(p2*m_imageZoomFactor);
	}
	else
	{
		QPixmap pix(QPixmap::fromImage(m_scaledImage));
		ui_alpha.label_imageWinSelection->setPixmap(pix);
		ui_alpha.label_imageWinSelection->show();

		//		QPixmap pix(m_pix);
		QPainter paint(&pix);
		QPen pen(Qt::blue, 1);
		paint.setPen(pen);
		paint.drawRect(m_rectSelection);
		ui_alpha.label_imageWinSelection->setPixmap(pix);
		ui_alpha.spinBox_PointP1_x->setValue(m_rectSelection.topLeft().rx());
		ui_alpha.spinBox_PointP1_y->setValue(m_rectSelection.topLeft().ry());
		ui_alpha.spinBox_PointP2_x->setValue(m_rectSelection.bottomRight().rx());
		ui_alpha.spinBox_PointP2_y->setValue(m_rectSelection.bottomRight().ry());
	}
}

void AlphaEstimationDialog::CalcNoSlices()
{
	m_noSlices = 
		static_cast<int32_t>((m_alphaTo / m_alphaStepSize) - (m_alphaFrom / m_alphaStepSize) + 1);
	ui_alpha.lcdNumber_NoSlice->display(m_noSlices);
}

// memory of pFilterArray must be alloc/dealloc out side of function
void AlphaEstimationDialog::LorentzFilterKernel(float *pFilterArray, int32_t szX, int32_t szY)
{
	for (int iy = 0; iy < szY; iy++)
	{
		for (int ix = 0; ix < szX; ix++)
		{
			pFilterArray[szX*iy + ix] = (ix - (szX / 2 - 1))*(ix - (szX / 2 - 1)) + (iy - (szY / 2 - 1))*(iy - (szY / 2 - 1));
		}
	}
}

// plotting function
void AlphaEstimationDialog::PlotSkewness(std::vector<double> skewVal, std::vector<double> alphaVal)
{
	// determine dimensions of plot
	////////////////////////////////
	double max_val_y = *std::max_element(skewVal.begin(), skewVal.end());
	double min_val_y = *std::min_element(skewVal.begin(), skewVal.end());
	double max_val_x = *std::max_element(alphaVal.begin(), alphaVal.end());
	double min_val_x = *std::min_element(alphaVal.begin(), alphaVal.end());

	// clear curve from previous plot
	//////////////////////////////////
	ui_alpha.qwtPlot_Skew->detachItems(QwtPlotItem::Rtti_PlotCurve);

	ui_alpha.qwtPlot_Skew->setTitle("Find best alpha");
	ui_alpha.qwtPlot_Skew->setCanvasBackground(Qt::white);

	// set dimension of plot
	/////////////////////////
	ui_alpha.qwtPlot_Skew->setAxisScale(QwtPlot::yLeft, min_val_y, max_val_y);
	ui_alpha.qwtPlot_Skew->setAxisScale(QwtPlot::xBottom, min_val_x, max_val_x);

	ui_alpha.qwtPlot_Skew->insertLegend(new QwtLegend());


	QwtPlotGrid *grid = new QwtPlotGrid();
	grid->attach(ui_alpha.qwtPlot_Skew);

	QwtPlotCurve *curve = new QwtPlotCurve();

	QwtPlotZoomer* zoomer = new QwtPlotZoomer(ui_alpha.qwtPlot_Skew->canvas());
	zoomer->setRubberBandPen(QColor(Qt::black));
	zoomer->setTrackerPen(QColor(Qt::black));
	zoomer->setMousePattern(QwtEventPattern::MouseSelect2,
		Qt::RightButton, Qt::ControlModifier);
	zoomer->setMousePattern(QwtEventPattern::MouseSelect3,
		Qt::RightButton);

	QwtPlotPanner *panner = new QwtPlotPanner(ui_alpha.qwtPlot_Skew->canvas());
	panner->setMouseButton(Qt::MidButton);


	// first curve original
	curve->setTitle("Alpha Maximation Curve");
	curve->setPen(Qt::blue, 3),
		curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

	QwtSymbol *symbol = new QwtSymbol(QwtSymbol::Ellipse,
		QBrush(Qt::red), QPen(Qt::darkYellow, 1), QSize(5, 5));
	curve->setSymbol(symbol);
	curve->setPen(Qt::darkGreen, 2);
	curve->setStyle(QwtPlotCurve::Lines);

	QPolygonF points;
	const int numSamples = alphaVal.size();
	for (int i = 0; i < numSamples; i++)
	{
		points += QPointF(alphaVal[i], skewVal[i]);
	}
	curve->itemChanged();
	curve->setSamples(points);
	curve->attach(ui_alpha.qwtPlot_Skew);
	ui_alpha.qwtPlot_Skew->replot();
	ui_alpha.qwtPlot_Skew->show();
}

// only for test
/////////////////
void AlphaEstimationDialog::SaveSelection()
{
	int32_t colStart = ui_alpha.spinBox_PointP1_x->value();
	int32_t colEnd = ui_alpha.spinBox_PointP2_x->value();
	int32_t rowStart = ui_alpha.spinBox_PointP1_y->value();
	int32_t rowEnd = ui_alpha.spinBox_PointP2_y->value();

	QByteArray bStr = m_imageName.toUtf8();
	std::string filenameStr = bStr.data();

	af::array  img = af::loadImage(filenameStr.c_str());
	af::array subWin = img.cols(colStart, colEnd).rows(rowStart, rowEnd);
	saveImageNative("SubWindow.tif", subWin);
}