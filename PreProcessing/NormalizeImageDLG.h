/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#pragma once
#include <ui_NormalizeImageDLG.h>
#include "LorentzFilterDLG.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cstdint>


class NormalizeImageDLG :public QDialog
{
	Q_OBJECT

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);


public:
	NormalizeImageDLG(QString name, QWidget *parent = 0);
	~NormalizeImageDLG();

public:
	QString m_imageName;
	QImage m_image;
	double m_normValue;

private:
	Ui::DialogNormalize ui_norm;

	int32_t m_x, m_y;
	QPixmap m_pix;

	uint32_t m_img_width;
	uint32_t m_img_height;


	// member variables
	///////////////////
	LorentzFilterDialog *m_parentWidget;
	cv::Mat m_ProjectionMat;
	QRect m_rectSelection;

private:
	std::string type2str(int type);

private slots:

};
