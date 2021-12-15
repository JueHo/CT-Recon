/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "threadload.h"
#include "projectionpreprocessor.h"

//-12-Oct-2015
extern uint32_t g_cntCurrentTile;

ThreadLoad::ThreadLoad(QObject *parent, bool intrp, bool thsp)
	: QThread(parent), m_interrupt(intrp), m_thread_stopped(thsp)
{
	m_parentObject = dynamic_cast<ProjectionPreProcessor*>(parent);
}

ThreadLoad::~ThreadLoad()
{

}

void ThreadLoad::run()
{
	ProcessParameter procParam = m_parentObject->GetprocessingParam();

	//-ju-08-Oct-2015 select between full or tile image stack
	//////////////////////////////////////////////////////////
	if (procParam.applyMemTiling && procParam.numOfTiles > 1)
	{
		float *stackTileMem = m_parentObject->GetTileMemoryStackPtr();
		// mem allocated
		if (stackTileMem)
		{
			int i;
			QString msg;
			msg.sprintf("> Load image files.");
			emit valueChanged(msg);

			//-ju-08-Oct-2015 calulate scale factor
			//				  for sc. images
			///////////////////////////////////////
			uint64_t row = procParam.imgHeight;
			uint64_t col = procParam.imgWidth;
			uint64_t cnt = procParam.cntProj;
			// create buffer
			Mat visImage = Mat::zeros(row, col, CV_32F);
			uint64_t imageSize = col * row;
			uint32_t scFac;

			//-ju-08-Oct-2015 storage for scale images
			QVector<Mat> imgStoreVec;
			for (i = 0; i < procParam.selectedImages.count(); i++)
			{
				QMutexLocker locker(&m_mutex);
				emit threadStart();
				if (this->m_interrupt)
				{
					this->m_interrupt = false;
					emit threadStopped();
					break;
				}
				locker.unlock();


				//-ju-15-Feb-2018 reverse order in case of anti clockwise direction of rotation
				///////////////////////////////////////////////////////////////////////////////
				QString filename;
				if (procParam.antiClockWise == 1)
				{
					filename = procParam.selectedImages[procParam.selectedImages.count() - i - 1];
				}
				else
				{
					filename = procParam.selectedImages[i];
				}
				
				QByteArray bStr = filename.toUtf8();
				string projectionNameStr = bStr.data();
				//-ju-15-Feb-2018
#ifdef _DEBUG
				msg.sprintf("> Image %s loaded.", projectionNameStr.c_str());
				emit valueChanged(msg);
#endif

				cv::Mat tmp = imread(projectionNameStr, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
				if (tmp.datastart == 0)
				{
					this->m_interrupt = false;
					emit threadStopped();
					break;
				}
				// convert to float if necessary
				if (m_parentObject->type2str(tmp.type()) != "32FC1")
				{
					tmp.convertTo(tmp, CV_32F);
				}

				// make phys. copy
				Mat mat(tmp.rows, tmp.cols, tmp.type(), Scalar::all(0));
				tmp.copyTo(mat);



				//-ju-08-Oct-2015 do scaling only for the first tile
				////////////////////////////////////////////////////
				//-12-Oct-2015 if (procParam.runningTileNo == 1) //-ju-> wird in diesem thread nicht hochgezählt
				if (g_cntCurrentTile == 1)
				{
					///////////////////////////////////////////////////////////
					//-ju-08-Oct-2015 scaling down image and store it in vector
					///////////////////////////////////////////////////////////
					uint64_t offset = imageSize*i;
					// create visualization image
					double minVal, maxVal;
					cv::minMaxLoc(mat, &minVal, &maxVal); //find minimum and maximum intensities
					//-ju-23-Feb-2018 no dark/flat correction
					/////////////////////////////////////////
					// calculate always max value of whole stack to map it in the range of 0.0 .. 1.0
					// independent if checkBox_useDarkFlatCorrected is checked or not
					m_maxGreyInStack = cv::max(procParam.maxGreyInStack, maxVal);

					// scale image and convert it to uchar
					Mat visMat(visImage.rows, visImage.cols, CV_8U, Scalar::all(0));
					mat.convertTo(visMat, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
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
					imgStoreVec.push_back(visMat);
					//-ju-08-Oct-2015 scaling end
					/////////////////////////////
				}

				//-ju-08-Oct-2015 copy tile from image
				//////////////////////////////////////
				//-12-Oct-2015 uint32_t segId = procParam.runningTileNo - 1;
				uint32_t segId = g_cntCurrentTile-1;
				// using privious cal. tile height and image width
				Mat tileMat = Mat::zeros(procParam.tilesSegmentProperties[segId].height, tmp.cols, CV_32F);
				tmp.rowRange(procParam.tilesSegmentProperties[segId].from, 
					procParam.tilesSegmentProperties[segId].to).copyTo(tileMat);

				// tile size
				uint64_t imgSz = tileMat.rows*tileMat.cols;
				uint64_t imgOffs = i*imgSz;
				// copy to tile memory
				memcpy(&stackTileMem[imgOffs], tileMat.ptr(0), imgSz*sizeof(float));
				emit updateProgressBar(i + 1);

				if (i == procParam.selectedImages.count() - 1)
				{
					QString msg;
					msg.sprintf("> Last File loaded is: %s", filename.toUtf8().toStdString().c_str());
					emit valueChanged(msg);
				}
			}
			// only for first tile
			if (g_cntCurrentTile == 1)
			{
				//-ju- save scaled images
				m_parentObject->SetVisImageVector(imgStoreVec);
				m_parentObject->SetScaleFactor(scFac);
				if (procParam.isDarkFlatCorrected == 1)
				{
					m_parentObject->SetMaxGreyValue(m_maxGreyInStack);
				}
				emit threadEnd();
			}
		}

	}
	else
	{
		float *stackMem = m_parentObject->GetMemoryStackPtr();
		// mem allocated
		if (stackMem)
		{
			int i;
			QString msg;
			msg.sprintf("> Load image files.");
			emit valueChanged(msg);
			for (i = 0; i < procParam.selectedImages.count(); i++)
			{
				QMutexLocker locker(&m_mutex);
				emit threadStart();
				if (this->m_interrupt)
				{
					this->m_interrupt = false;
					emit threadStopped();
					break;
				}
				locker.unlock();

				//-ju-15-Feb-2018 reverse order in case of anti clockwise direction of rotation
				///////////////////////////////////////////////////////////////////////////////
				QString filename;
				if (procParam.antiClockWise == 1)
				{
					filename = procParam.selectedImages[procParam.selectedImages.count() - i - 1];
				}
				else
				{
					filename = procParam.selectedImages[i];
				}
				QByteArray bStr = filename.toUtf8();
				string projectionNameStr = bStr.data();
#ifdef _DEBUG
				msg.sprintf("> Image %s loaded.", projectionNameStr.c_str());
				emit valueChanged(msg);
#endif

				cv::Mat tmp = imread(projectionNameStr, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
				if (tmp.datastart == 0)
				{
					this->m_interrupt = false;
					emit threadStopped();
					break;
				}
				// convert to float if necessary
				if (m_parentObject->type2str(tmp.type()) != "32FC1")
				{
					tmp.convertTo(tmp, CV_32F);
				}
				// make phys. copy
				Mat mat(tmp.rows, tmp.cols, tmp.type(), Scalar::all(0));
				tmp.copyTo(mat);

				//-ju-23-Feb-2018 no dark/flat correction
				/////////////////////////////////////////
				// calculate always max value of whole stack to map it in the range of 0.0 .. 1.0
				// independent if checkBox_useDarkFlatCorrected is checked or not
				double minVal, maxVal;
				cv::minMaxLoc(mat, &minVal, &maxVal);
				m_maxGreyInStack = cv::max(procParam.maxGreyInStack, maxVal);


				uint64_t imgSz = tmp.rows*tmp.cols;
				uint64_t imgOffs = i*imgSz;
				// regard tiling -> not done yet !
				//////////////////////////////////
				memcpy(&stackMem[imgOffs], tmp.ptr(0), imgSz*sizeof(float));
				emit updateProgressBar(i + 1);
				if (i == procParam.selectedImages.count() - 1)
				{
					QString msg;
					msg.sprintf("> Last File loaded is: %s", filename.toUtf8().toStdString().c_str());
					emit valueChanged(msg);
				}
			}
			if (procParam.isDarkFlatCorrected == 1)
			{
				m_parentObject->SetMaxGreyValue(m_maxGreyInStack);
			}
			emit threadEnd();
		}
	} // apply tiling memory
}
