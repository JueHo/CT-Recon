/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "ScaleImageDownThread.h"
#include "projectionpreprocessor.h"

//-12-Oct-2015
extern uint32_t g_cntCurrentTile;

ThreadScImage::ThreadScImage(QObject *parent)
	: QThread(parent)
{
	m_parentObject = dynamic_cast<ProjectionPreProcessor*>(parent);
}

ThreadScImage::~ThreadScImage()
{

}

void ThreadScImage::run()
{
	ProcessParameter procParam = m_parentObject->GetprocessingParam();
	// applying stack tiling. 
	// Only for the first loaded tile
	//////////////////////////////////
	if (procParam.applyMemTiling && g_cntCurrentTile == 1)
	{
		uchar *scaledStackMem = m_parentObject->GetScaledImageStackPtr();
		float *stackMem = m_parentObject->GetTileMemoryStackPtr();
		QVector<cv::Mat> visVec = m_parentObject->GetVisImageVector();
		// check if mem is allocated
		if (stackMem && scaledStackMem)
		{
			int i;
			QString msg;
			msg.sprintf("> Down scaling of images started.");
			emit valueChanged(msg);
			emit threadStart();
			// scaled image stack is priviously stored in a vector of images
			// --> ThreadLoad::run()

			// get size
			uint64_t imgSz = visVec[0].rows*visVec[0].cols;
			for (i = 0; i < visVec.size(); i++)
			{			
				uint64_t imgOffs = i*imgSz;
				memcpy(&scaledStackMem[imgOffs], visVec[i].ptr(0), imgSz*sizeof(uchar));
				emit updateProgressBar(i + 1);
			}
			emit threadEnd();
		}
	}
	else // whole image stack fits in memory
	{
		uchar *scaledStackMem = m_parentObject->GetScaledImageStackPtr();
		float *stackMem = m_parentObject->GetMemoryStackPtr();
		// check if mem is allocated
		if (stackMem && scaledStackMem)
		{
			int i;
			QString msg;
			msg.sprintf("> Down scaling of images started.");
			emit valueChanged(msg);
			emit threadStart();

			// calulate scale factor
			uint64_t row = procParam.imgHeight;
			uint64_t col = procParam.imgWidth;
			uint64_t cnt = procParam.cntProj;
			// create buffer
			Mat visImage = Mat::zeros(row, col, CV_32F);
			uint64_t imageSize = col * row;
			uint32_t scFac;
			for (i = 0; i < cnt; i++)
			{
				uint64_t offset = imageSize*i;
				memcpy(visImage.data, &stackMem[offset], imageSize*sizeof(float));
				// create visualization image
				///////////////////////////////
				double minVal, maxVal;
				cv::minMaxLoc(visImage, &minVal, &maxVal); //find minimum and maximum intensities
				// scale image to uchar
				Mat visMat(visImage.rows, visImage.cols, CV_8U, Scalar::all(0));
				visImage.convertTo(visMat, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
				int r = row;
				int c = col;
				Mat pyrMat;
				scFac = 1;
				while (max(r, c) > MAX_IMAGE_SIZE)
				{
					c /= 2;
					r /= 2;
					pyrDown(visMat, pyrMat, Size(c, r));
					visMat = pyrMat;
					scFac *= 2;
				}

				uint64_t imgSz = r*c;
				uint64_t imgOffs = i*imgSz;
				memcpy(&scaledStackMem[imgOffs], visMat.ptr(0), imgSz*sizeof(uchar));

				emit updateProgressBar(i + 1);
			}
			m_parentObject->SetScaleFactor(scFac);
			emit threadEnd();
		}
	}
}
