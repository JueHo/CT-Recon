/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _IMAGE_DLG_H
#define _IMAGE_DLG_H

#include <QtWidgets/QDialog>
#include "ui_ShowImageDLG.h"

//-ju- temp hardcode image zoom
#define ZOOM 2

class ImageDLG : public QDialog
{
	Q_OBJECT

public:
	ImageDLG(QWidget *parent = 0);
	~ImageDLG();
	ImageDLG *m_imgDlg;
	QLabel *GetImageArea()
	{
		return ui.DLG_ImageArea;
	}
	int GetImageNumber();
	QRect GetSelection()
	{
		return m_rectSelection;
	}
	void SetSelection(const QRect &rect)
	{
		m_rectSelection = rect;
	}
	void SetZoom(const int &zoom)
	{
		m_zoom = zoom;
	}
	int GetZoom()
	{
		return m_zoom;
	}

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);

public:
	Ui::dlg_ShowImage ui;
private:
	QLabel *m_imageArea;
	QWidget *m_parent;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_imageNo;
	bool m_doDrawing;
	QPixmap m_pix;
	QRect m_rectSelection;
	QPoint m_startMove;
	bool m_move;
	int m_zoom;
	bool m_zoomModified;

private:

private slots:
	void ReDraw();
	void ChangeRectX0();
	void ChangeRectY0();
	void ChangeRectWidth();
	void ChangeRectHeight();
	void ChangeImageSize();
};

#endif