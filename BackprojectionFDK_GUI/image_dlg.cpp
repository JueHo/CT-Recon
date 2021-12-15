/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "image_dlg.h"
//#include <QtGui/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include "fdk_gui.h"

ImageDLG::ImageDLG(QWidget *parent)
:QDialog(parent),
 m_imageNo(-1),
 m_doDrawing(false),
 m_move(false),
 m_zoom(2),
 m_rectSelection(0,0,0,0)
{
	ui.setupUi(this);
	//-ju- event filter registration
	ui.DLG_ImageArea->installEventFilter(this);

	connect(ui.checkBox_keepSelection,SIGNAL(toggled(bool)),this,SLOT(ReDraw()));

	// rectangle size
	connect(ui.spinBox_x0,SIGNAL(valueChanged(int)),this,SLOT(ChangeRectX0()));
	connect(ui.spinBox_y0,SIGNAL(valueChanged(int)),this,SLOT(ChangeRectY0()));
	connect(ui.spinBox_width,SIGNAL(valueChanged(int)),this,SLOT(ChangeRectWidth()));
	connect(ui.spinBox_height,SIGNAL(valueChanged(int)),this,SLOT(ChangeRectHeight()));
	connect(ui.comboBox_imageScale,SIGNAL(currentIndexChanged(QString)),this,SLOT(ChangeImageSize()));
}

ImageDLG::~ImageDLG()
{
}

////////////////////
//-ju- Event filter
////////////////////////////////////////////////////////////////////////////////////
bool ImageDLG::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if(targetCtrl == ui.DLG_ImageArea && ui.checkBox_keepSelection->isChecked() && GetImageNumber() != m_imageNo)
	{
		m_imageNo = GetImageNumber();
		QPixmap pix((*(ui.DLG_ImageArea->pixmap())));
		m_pix = pix;
		QPainter paint(&pix);
		QPen pen(Qt::blue,1);
		paint.setPen(pen);
		paint.drawRect(m_rectSelection);
		ui.DLG_ImageArea->setPixmap(pix);
	}
	if(targetCtrl == ui.DLG_ImageArea && ui.checkBox_keepSelection->isChecked())
	{
		if(event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if(mEvt->button() == Qt::LeftButton)
			{
				m_startMove = mEvt->pos();
				m_move = true;
			}
		}
		if(event->type() == QEvent::MouseMove && m_move)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			QPoint curPos = mEvt->pos();
			QPoint diffPos = curPos - m_startMove;
			QPoint newPos = QPoint(m_rectSelection.x(),m_rectSelection.y()) + diffPos;

			m_rectSelection.moveTo(newPos);

			m_startMove = curPos;

			ui.spinBox_x0->setValue(m_rectSelection.x()*GetZoom());
			ui.spinBox_y0->setValue(m_rectSelection.y()*GetZoom());
			ui.spinBox_width->setValue(m_rectSelection.width()*GetZoom());
			ui.spinBox_height->setValue(m_rectSelection.height()*GetZoom());

			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue,1);
			paint.setPen(pen);
			paint.drawRect(m_rectSelection);
			ui.DLG_ImageArea->setPixmap(pix);
		}
		if(event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			m_move = false;
		}
	}
	if(targetCtrl == ui.DLG_ImageArea && !ui.checkBox_keepSelection->isChecked())
	{
		if(event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if(mEvt->button() == Qt::LeftButton)
			{
				m_doDrawing = true;
				m_x = mEvt->x();
				m_y = mEvt->y();
				ui.spinBox_x0->setValue(m_x*GetZoom());
				ui.spinBox_y0->setValue(m_y*GetZoom());
				ui.spinBox_width->setValue(m_w*GetZoom());
				ui.spinBox_height->setValue(m_h*GetZoom());
				if(GetImageNumber() != m_imageNo || m_zoomModified)
				{
					m_imageNo = GetImageNumber();
					QPixmap pix((*(ui.DLG_ImageArea->pixmap())));
					m_pix = pix;
					m_zoomModified = false;
				}
			}
		}
		if(event->type() == QEvent::MouseMove && !ui.checkBox_keepSelection->isChecked())
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if(m_doDrawing)
			{
				QPoint ptnStart(m_x,m_y);
				QPoint ptnMove = mEvt->pos();
				m_w = abs(m_x-ptnMove.x());
				m_h = abs(m_y-ptnMove.y());
				ui.spinBox_x0->setValue(m_x*GetZoom());
				ui.spinBox_y0->setValue(m_y*GetZoom());
				ui.spinBox_width->setValue(m_w*GetZoom());
				ui.spinBox_height->setValue(m_h*GetZoom());
				if(GetImageNumber() == m_imageNo)
				{
					QPixmap pix(m_pix);
					QPainter paint(&pix);
					QPen pen(Qt::blue,1);
					paint.setPen(pen);
					QRect drawRect(ptnStart,ptnMove);
					paint.drawRect(drawRect);
					ui.DLG_ImageArea->setPixmap(pix);
				}
			}
		}
		if(event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if(m_doDrawing)
			{
				m_doDrawing = false;
				QPoint ptnStart(m_x,m_y);
				QPoint ptnEnd = mEvt->pos();
				m_rectSelection.setTopLeft(ptnStart);
				m_rectSelection.setBottomRight(ptnEnd);
			}
		}
	}
	return QDialog::eventFilter(targetCtrl,event);
}

int ImageDLG::GetImageNumber()
{
	QString title = this->windowTitle();
	QStringList titlePart = title.split(tr("#"));
	return titlePart[1].toInt();
}

// Slots
void ImageDLG::ReDraw()
{
	if(!ui.checkBox_keepSelection->isChecked())
	{
		m_x = m_y = m_w = m_h = 0;
		m_rectSelection = QRect(0,0,0,0);
	}
	if(GetImageNumber() == m_imageNo)
	{
		QPixmap pix(m_pix);
		QPainter paint(&pix);
		QPen pen(Qt::blue,1);
		paint.setPen(pen);
		paint.drawRect(m_rectSelection);
		ui.DLG_ImageArea->setPixmap(pix);
	}
	this->update();
}

void ImageDLG::ChangeRectX0()
{
	if(ui.checkBox_keepSelection->isChecked())
	{
		m_rectSelection.moveLeft(ui.spinBox_x0->value()/GetZoom());
		if(GetImageNumber() == m_imageNo)
		{
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue,1);
			paint.setPen(pen);
			paint.drawRect(m_rectSelection);
			ui.DLG_ImageArea->setPixmap(pix);
		}
		this->update();
	}
}

void ImageDLG::ChangeRectY0()
{
	if(ui.checkBox_keepSelection->isChecked())
	{
		m_rectSelection.moveTop(ui.spinBox_y0->value()/GetZoom());
		if(GetImageNumber() == m_imageNo)
		{
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue,1);
			paint.setPen(pen);
			paint.drawRect(m_rectSelection);
			ui.DLG_ImageArea->setPixmap(pix);
		}
		this->update();
	}
}

void ImageDLG::ChangeRectWidth()
{
	if(ui.checkBox_keepSelection->isChecked())
	{
		m_rectSelection.setWidth(ui.spinBox_width->value()/GetZoom());
		if(GetImageNumber() == m_imageNo)
		{
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue,1);
			paint.setPen(pen);
			paint.drawRect(m_rectSelection);
			ui.DLG_ImageArea->setPixmap(pix);
		}
		this->update();
	}
}

void ImageDLG::ChangeRectHeight()
{
	if(ui.checkBox_keepSelection->isChecked())
	{
		m_rectSelection.setHeight(ui.spinBox_height->value()/GetZoom());
		if(GetImageNumber() == m_imageNo)
		{
			QPixmap pix(m_pix);
			QPainter paint(&pix);
			QPen pen(Qt::blue,1);
			paint.setPen(pen);
			paint.drawRect(m_rectSelection);
			ui.DLG_ImageArea->setPixmap(pix);
		}
		this->update();
	}
}

void ImageDLG::ChangeImageSize()
{
	int entry = ui.comboBox_imageScale->currentIndex();
	switch(entry)
	{
	case 0: //50%
		m_zoom = 2;
		break;
	case 1: //10%
		m_zoom = 10;
		break;
	case 2: //20%
		m_zoom = 5;
		break;
	case 3: //25%
		m_zoom = 4;
		break;
	case 4:	//33%
		m_zoom = 3;
		break;
	case 5:	//100%
		m_zoom = 1;
		break;
	}
	m_zoomModified = true;
	FDK_GUI *pW = (FDK_GUI*)parentWidget();
	pW->ShowSinogram();
}