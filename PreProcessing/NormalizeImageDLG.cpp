/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "NormalizeImageDLG.h"
#include <QtWidgets/QMessageBox>
#include <QtGui/qevent.h>
#include <windows.h>
#include "XRA_HelperFunc.h"

using namespace cv;


NormalizeImageDLG::NormalizeImageDLG(QString name, QWidget *parent)
: m_rectSelection(0,0,0,0)
{
	m_parentWidget = static_cast<LorentzFilterDialog*>(parent);

	ui_norm.setupUi(this);
	ui_norm.label_origImage->installEventFilter(this);

	//m_parentWidget->SetNormValue(4.5);

	m_normValue = -1.0;
	ui_norm.doubleSpinBox_meanValue->setValue(m_normValue);

	m_imageName = name;

	// load image to cv::Mat
	QString filename = name;
	QByteArray bStr = filename.toUtf8();
	std::string projectionNameStr = bStr.data();
	cv::Mat tmp = cv::imread(projectionNameStr, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
	// convert to float if necessary
	bool doConv = false; //-ju-16-Feb-2018
	if (type2str(tmp.type()) != "32FC1")
	{
		tmp.convertTo(tmp, CV_32F);
		doConv = true;
	}

	// make phys. copy
	m_ProjectionMat = cv::Mat::zeros(tmp.rows, tmp.cols, tmp.type());
	tmp.copyTo(m_ProjectionMat);

	//-ju-16-Feb-2018 load Qt Image
	// if float tif use Mat2QImage() to create a image
	//////////////////////////////////////////////////
	if (doConv)
	{
		m_image.load(m_imageName);
	}
	else
	{
		XRA::Helper tool;
		m_image = tool.Mat2QImage(m_ProjectionMat);
	}

	printf("Load: %s\n", m_imageName.toStdString().c_str());
	if (m_image.isNull())
	{
		printf("Can not load %s\n", m_imageName.toStdString().c_str());
	}
	m_img_width = m_image.width();
	m_img_height = m_image.height();
	ui_norm.label_origImage->setPixmap(QPixmap::fromImage(m_image));
	ui_norm.label_origImage->show();
}

bool NormalizeImageDLG::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if (targetCtrl == ui_norm.label_origImage)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if (mEvt->button() == Qt::LeftButton)
			{
				//-reset- image --> delete rect
				ui_norm.label_origImage->setPixmap(QPixmap::fromImage(m_image));
				ui_norm.label_origImage->show();

				m_x = mEvt->x();
				m_y = mEvt->y();
				printf("x1=%d\ty1=%d\n", mEvt->x(), mEvt->y());
				QPixmap pix((*ui_norm.label_origImage->pixmap()));
				m_pix = pix;
			}
		}
		if (targetCtrl == ui_norm.label_origImage && event->type() == QEvent::MouseMove)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);

			QPoint ptnStart(m_x, m_y);
			QPoint ptnMove = mEvt->pos();
			int32_t xs_n = m_x;
			int32_t ys_n = m_y;
			int32_t xe_n = ptnMove.x();
			int32_t ye_n = ptnMove.y();

			xe_n = cv::min(xe_n, m_ProjectionMat.cols - 2);
			ye_n = cv::min(ye_n, m_ProjectionMat.rows - 2);
			xe_n = cv::max(xe_n, -1);
			ye_n = cv::max(ye_n, -1);
			QPoint pntMv(xe_n, ye_n);
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue, 1);
			paint.setPen(pen);
			QRect drawRect(ptnStart, pntMv);
			paint.drawRect(drawRect);
			ui_norm.label_origImage->setPixmap(pix);
			// re-use in ImageViewShowImage()
			//////////////////////////////////
			//m_rectSelectionRedraw = drawRect;

		}
		if (event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			QPoint ptnStart(m_x, m_y);
			QPoint ptnEnd = mEvt->pos();

			// check if valid rectangle --> width, height wird negativ
			int32_t xs_n = m_x;
			int32_t ys_n = m_y;
			int32_t xe_n = ptnEnd.x();
			int32_t ye_n = ptnEnd.y();
			if (xs_n > xe_n)
			{
				std::swap(xs_n, xe_n);
			}
			if (ys_n > ye_n)
			{
				std::swap(ys_n, ye_n);
			}
			m_ProjectionMat;
			xe_n = cv::min(xe_n, m_ProjectionMat.cols - 1);
			ye_n = cv::min(ye_n, m_ProjectionMat.rows - 1);
			xe_n = cv::max(xe_n, 0);
			ye_n = cv::max(ye_n, 0);
			QPoint p1(xs_n, ys_n);
			QPoint p2(xe_n, ye_n);

			// store selected rectangle
			m_rectSelection.setTopLeft(p1);
			m_rectSelection.setBottomRight(p2);

			// create cv::Mat rectangle used for normalization
			///////////////////////////////////////////////////
			// check if roi is inside of image
			if (p1.x() < 0 ||
				p1.x() > m_ProjectionMat.cols - 1 ||
				p2.x() < 0 ||
				p2.x() > m_ProjectionMat.cols - 1 ||
				p1.y() < 0 ||
				p1.y() > m_ProjectionMat.rows - 1 ||
				p2.y() < 0 ||
				p2.y() > m_ProjectionMat.rows - 1)
			{
				int ret = QMessageBox::warning(this, tr("Warning"),
					tr("Selection out of range!"),
					QMessageBox::Ok);

				//-reset- image --> delete rect
				ui_norm.label_origImage->setPixmap(QPixmap::fromImage(m_image));
				ui_norm.label_origImage->show();
				this->update();
				return QDialog::eventFilter(targetCtrl, event);
			}
			cv::Mat roi = 
				m_ProjectionMat(Rect(p1.x(), p1.y(), p2.x()-p1.x(),p2.y()-p1.y()));
			cv::Scalar meanVal = mean(roi);
			double mval = meanVal[0];
			ui_norm.doubleSpinBox_meanValue->setValue(mval);
			// send value to LorentzFilterDialog
			m_parentWidget->SetNormValue(mval);
			m_normValue = mval;
		}
	}
	this->update();
	return QDialog::eventFilter(targetCtrl, event);

}

std::string NormalizeImageDLG::type2str(int type)
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


NormalizeImageDLG::~NormalizeImageDLG()
{

}