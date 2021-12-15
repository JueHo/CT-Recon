/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#pragma once
#include <QtGui>
#include <QMessageBox> 
#include <QProgressDialog>
#include <opencv2\opencv.hpp>

namespace XRA
{
	class Helper
	{
	public:
		QImage Mat2QImage(const cv::Mat_<float> &src)
		{
			//-ju-20-Feb-2018 map it between 0.0 and 1.0

			double max_val, min_val;
			cv::minMaxLoc(src, &min_val, &max_val);
			printf("min=%f   max=%f\n", min_val, max_val);
			src.convertTo(src, CV_32F, 1.0 / (max_val - min_val));
			double scale = 255.0;
			QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
			for (int y = 0; y < src.rows; ++y) {
				const float *srcrow = src[y];
				QRgb *destrow = (QRgb*)dest.scanLine(y);
				for (int x = 0; x < src.cols; ++x) {
					unsigned int color = srcrow[x] * scale;
					destrow[x] = qRgba(color, color, color, 255);
				}
			}
			return dest;
		}

		QPixmap Raw2Pixmap(float *rawData,
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

			QVector<QRgb> colorTable;
			if (colorTable.isEmpty())
			{
				for (int i = 0; i < 256; ++i)
					colorTable.push_back(qRgb(i, i, i));
			}

			QImage image(imgMat.data, imgMat.cols, imgMat.rows, imgMat.step, QImage::Format_Indexed8);

			image.setColorTable(colorTable);

			return QPixmap::fromImage(image);
		}

	};
}