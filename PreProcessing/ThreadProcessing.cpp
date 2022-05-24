/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "threadprocessing.h"
#include "projectionpreprocessor.h"
//-ju-19-08-2015 add OpenMP
///////////////////////////
#ifndef _DEBUG
#include <omp.h>
#endif
#include <algorithm>
#include <boost/sort/spreadsort/float_sort.hpp>
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <thread>

#include <arrayfire.h>

bool flag = true;

//-12-Oct-2015
extern uint32_t g_cntCurrentTile;


ThreadProcessing::ThreadProcessing(QObject *parent, bool intrp, bool thsp)
	: QThread(parent), m_interrupt(intrp), m_thread_stopped(thsp)
{
	m_parentObject = dynamic_cast<ProjectionPreProcessor*>(parent);
}

ThreadProcessing::~ThreadProcessing()
{

}

void ThreadProcessing::run()
{
	m_procPara = m_parentObject->GetprocessingParam();
	//-ju-09-Oct-2015-implement tiling
	///////////////////////////////////
	if (m_procPara.applyMemTiling)
	{
		QMutexLocker locker(&m_mutex);
		emit threadStart();
		if (this->m_interrupt)
		{
			this->m_interrupt = false;
			emit threadStopped();
		}
		locker.unlock();

		for (int i = 0; i < m_procPara.numOfTiles; i++)
		{
			QString msg;
			msg.sprintf("Proc> Processing tile >> %d << of %d tiles.", i + 1, m_procPara.numOfTiles);
			emit valueChanged(msg);
			float *stackMem = m_parentObject->GetTileMemoryStackPtr();
			// mem is allocated
			if (stackMem)
			{
				m_projSumImage.deallocate(); // deallocate before using member variable
				m_projSumImage = Mat::zeros(m_procPara.tilesSegmentProperties[i].height, m_procPara.imgWidth, CV_32F);
				uint64_t tileHeight = m_procPara.tilesSegmentProperties[i].height;
				uint64_t tileWidth = m_procPara.imgWidth;
				// this is called from ThreadProcessing
				// for runningTileNo == 2 (if windows selection is active)
				// ==> get windows normalisation values
				// get normalization window of image
				if (g_cntCurrentTile == 1 && m_procPara.useWinNormalisation)
				{
					QString msg;
					msg.sprintf("Proc> Re-reading projections for normalisation.");
					emit valueChanged(msg);
					msg.sprintf("Proc>   reading ...");
					emit valueChanged(msg);
					for (int i = 0; i < m_procPara.selectedImages.count(); i++)
					{
						QString filename = m_procPara.selectedImages[i];
						QByteArray bStr = filename.toUtf8();
						string projectionNameStr = bStr.data();
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
						Mat roi = tmp(Rect(m_procPara.xWinPos, m_procPara.yWinPos,
							m_procPara.widthWin, m_procPara.heightWin));
						// for every projection cal. mean of normalization window
						m_procPara.winNormValueVector.push_back(mean(roi).val[0]);
					}// end re-read images
					msg.sprintf("Proc>   end.");
					emit valueChanged(msg);
				}
				//-1- do pre-processing
				///////////////////////
				if (m_procPara.useOutlierSupRAC && m_procPara.useOutlierSup)
				{
					QString msg;
					msg.sprintf("Proc> Start tile calculation projection sum.");
					emit valueChanged(msg);
					GetProjectionsSumTileImage(stackMem, i);
					msg.sprintf("Proc> Finished calculation projection sum.");
					emit valueChanged(msg);
					////////////////////////
					msg.sprintf("Proc> Start outlier reduction filter.");
					emit valueChanged(msg);
					//-ju-16-Oct-2015 cv::Mat outlierImage = cv::Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
					cv::Mat outlierImage = cv::Mat::zeros(tileHeight, tileWidth, CV_32F);
					SegmentForOutliers(outlierImage);
					vector<cv::Vec2i> outlierPixelList;
					FindOutliers(outlierImage, outlierPixelList);
					ApplyOutlierReductionFilter(stackMem, outlierPixelList, tileHeight, tileWidth);
					msg.sprintf("Proc> Finished outlier reduction filter.");
					emit valueChanged(msg);
					////////////////////////
				}
				// do normalization, new ring artefact correction and BHC
				if (m_procPara.useNormalisation && !m_procPara.saveOnly)
				{
					QString msg;
					msg.sprintf("Proc> Start normalisation.");
					emit valueChanged(msg);
					NormalizeImages(stackMem, tileHeight, tileWidth);
					msg.sprintf("Proc> Finished normalisation.");
					emit valueChanged(msg);
				}
				//-ju-16-Oct-2015 do savings for tiles
				//////////////////////////////////////
				QString msg;
				msg.sprintf("Proc> Start writing projections [Segment %d] of %d Segments.", i + 1, m_procPara.numOfTiles);
				emit valueChanged(msg);
				SaveProjections(stackMem, i);
				msg.sprintf("Proc> Finished writing projections.");
				emit valueChanged(msg);
				////////////////////////////////////////////////////////////////////////
				//-2- if runningTileNo == 1 create file else append
				//-3- write to file
				//-4- increment runningTileNo
				//-12-Oct-2015 m_procPara.runningTileNo = i+1;
				g_cntCurrentTile = i + 2;
				//-5- read new tile if runningTileNo <= numOfTiles
				///////////////////////////////////////////////////////////////////////
				if (g_cntCurrentTile <= m_procPara.numOfTiles)
				{
					m_parentObject->m_pLoadFileThread->start();
					QString msg;
					msg.sprintf("Proc> Re-loading projections for tile >> %d <<", g_cntCurrentTile);
					emit valueChanged(msg);
					m_parentObject->m_pLoadFileThread->wait();
				}
			}
		} // end for tiles
		//-ju-16-Oct-2015 tiles
		emit threadEnd();
	}
	else
	{
		m_projSumImage = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
		float *stackMem = m_parentObject->GetMemoryStackPtr();

		// mem is allocated
		if (stackMem)
		{
			QMutexLocker locker(&m_mutex);
			emit threadStart();
			if (this->m_interrupt)
			{
				this->m_interrupt = false;
				emit threadStopped();
			}
			locker.unlock();

			if (m_procPara.useOutlierSupRAC && m_procPara.useOutlierSup && !m_procPara.saveOnly)
			{
				QString msg;
				msg.sprintf("Proc> Start calculation projection sum.");
				emit valueChanged(msg);
				GetProjectionsSumImage(stackMem);
				msg.sprintf("Proc> Finished calculation projection sum.");
				emit valueChanged(msg);
				msg.sprintf("Proc> Start outlier reduction filter.");
				emit valueChanged(msg);
				cv::Mat outlierImage = cv::Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
				SegmentForOutliers(outlierImage);
				vector<cv::Vec2i> outlierPixelList;
				FindOutliers(outlierImage, outlierPixelList);
				ApplyOutlierReductionFilter(stackMem, outlierPixelList);
				msg.sprintf("Proc> Finished outlier reduction filter.");
				emit valueChanged(msg);
			}
			// apply normalization an BHC together due to performance
			if (m_procPara.useNormalisation && !m_procPara.saveOnly)
			{
				QString msg;
				msg.sprintf("Proc> Start normalisation.");
				emit valueChanged(msg);
				NormalizeImages(stackMem);
				msg.sprintf("Proc> Finished normalisation.");
				emit valueChanged(msg);
			}
			QString msg;
			msg.sprintf("Proc> Start writing projections.");
			emit valueChanged(msg);
			SaveProjections(stackMem);
			msg.sprintf("Proc> Finished writing projections.");
			emit valueChanged(msg);

			emit threadEnd();
		}
	}
}

void ThreadProcessing::GetProjectionsSumImage(float *VolMem)
{
	// handle only 32 bit float images
	///////////////////////////////////
	// create/allocate matrix
	Mat tmp = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);

	// one projection
	uint64_t imgSz = m_procPara.imgHeight * m_procPara.imgWidth;

	for (uint64_t i = 0; i < m_procPara.cntProj; i++)
	{
		uint64_t offset = imgSz*i;
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		m_projSumImage = m_projSumImage + tmp;
	}
#ifdef _DEBUG
	cv::Mat a = m_projSumImage;
	m_projSumImage;
#endif
}

//-ju-13-Oct-2015 implementation for tile [0 ... i]
void ThreadProcessing::GetProjectionsSumTileImage(float *VolMem, uint32_t tileNo)
{
	// handle only 32 bit float images
	///////////////////////////////////
	// create/allocate matrix
	Mat tmp = Mat::zeros(m_procPara.tilesSegmentProperties[tileNo].height, m_procPara.imgWidth, CV_32F);

	// one projection
	uint64_t imgSz = m_procPara.tilesSegmentProperties[tileNo].height * m_procPara.imgWidth;

	for (uint64_t i = 0; i < m_procPara.cntProj; i++)
	{
		uint64_t offset = imgSz*i;
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		m_projSumImage = m_projSumImage + tmp;
	}
#ifdef _DEBUG
	cv::Mat a = m_projSumImage;
	m_projSumImage;
#endif
}


void ThreadProcessing::GetMeanFromFlatField(QString filename, float &meanVal)
{
	QByteArray bStr = filename.toUtf8();
	string filenameStr = bStr.data();
	// read one projection and check parameters
	////////////////////////////////////////////
	cv::Mat temp = imread(filenameStr, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
	bool conv2float = false;
	if (temp.type() != CV_32F)
	{
		temp.convertTo(temp, CV_32F);
	}
	if (temp.rows != m_procPara.imgHeight)
	{
		QString msg;
		msg.sprintf("Proc Error!> temp.rows (%d) != projection image height (%d)",
			temp.rows, m_procPara.imgHeight);
		emit valueChanged(msg);
		msg.sprintf("Proc Info!> load data again!");
		emit valueChanged(msg);
		return;
	}
	if (temp.cols != m_procPara.imgWidth)
	{
		QString msg;
		msg.sprintf("Proc Error!> temp.cols (%d) != projection image width (%d)",
			temp.cols, m_procPara.imgWidth);
		emit valueChanged(msg);
		msg.sprintf("Proc Info!> load data again!");
		emit valueChanged(msg);
		return;
	}
	meanVal = mean(temp).val[0];
}


void ThreadProcessing::NormalizeImages(float *VolMem)
{
	cv::Mat tmp = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
	cv::Mat tmpInterm = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
	cv::Mat tmpBHCConst = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
	// get size of one projection
	uint64_t imgSz = m_procPara.imgHeight * m_procPara.imgWidth;
	// check if single image normalization should be applied
	if (m_procPara.useWinNormalisation || m_procPara.isDarkFlatCorrected == 1)
	{
		if (m_procPara.widthWin * m_procPara.heightWin == 0 && m_procPara.isDarkFlatCorrected == 0)
		{
			QString msg;
			msg.sprintf("Proc Error!> normalisation window size is zero!");
			emit valueChanged(msg);
			msg.sprintf("Proc Info!> load data again!");
			emit valueChanged(msg);
		}
		// do normalisation
		/////////////////////
		QString msg;
		if (m_procPara.isDarkFlatCorrected == 0)
		{
			msg.sprintf("Run!> normalisation is running!");
			emit valueChanged(msg);
		}
		//-ju-11-Apr-2017 Lorentz Filter
		float *pImage;
		float *filterKernelRaw;
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			pImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			filterKernelRaw = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			LorentzFilterKernel(filterKernelRaw, m_procPara.imgWidth, m_procPara.imgHeight);
		}
		//-ju-11-Apr-2017 Lorentz Filter
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			// get normalization window; part of image
			Mat roi = tmp(Rect(m_procPara.xWinPos, m_procPara.yWinPos,
				m_procPara.widthWin, m_procPara.heightWin));
			// for every projection cal. mean of normalization window
			Scalar meanVal = mean(roi);

			if (m_procPara.isDarkFlatCorrected == 1)
			{
				tmp = tmp / static_cast<float>(m_procPara.maxGreyInStack);
			}
			else
			{
				////////-ju-24-Aug-2016 replacement by threshold
				/////////////////////////////////////////////////
				tmp = tmp / (meanVal.val[0]); // --> num. problem
			}

			//-ju-10-Apr-2017 add Lorentz Filter
			/////////////////////////////////////
			if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
			{
				if (i == 0)
				{
					//msg.sprintf("Run!> apply Lorentz filter!");
					msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
					emit valueChanged(msg);
				}
				ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
			}

			//-ju-26-Aug-2016 replacement by threshold
			// values should be <= 1.0 after norm.
			// depending on norm-factor can be > 1.0
			// this will be corrected by thresholding
			///////////////////////////////////////////
			cv::threshold(tmp, tmp, 1.0, 1.0, cv::THRESH_TRUNC);
#ifdef _DEBUG_OUT
			if (i == 0) printf("Raw --> File: %s, line %d: threshold to zero\n", __FILE__, __LINE__ + 1);
#endif
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-11-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-11-Apr-2017 Lorentz Filter

		cv::Mat medianRatioMap = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
		if (m_procPara.useRAC)
		{
			//////////////////////////////////////////////
			//-ju-19-08-2015 new ring artefact correction

			// create copy of the volume
			/////////////////////////////
			long long w = m_procPara.imgWidth;
			long long h = m_procPara.imgHeight;
			long long n = m_procPara.cntProj;
			uint64_t memSzClone = w*h*n*sizeof(float);
			float *VolMemClone = new float[w*h*n];
			if (0 == VolMemClone)
			{
				QString msg;
				msg.sprintf("Proc Error!> Can not allocating memory for ring artefact correction failed!");
				emit valueChanged(msg);
				return;
			}

			// copy data
			//////////////
			memcpy(VolMemClone, VolMem, memSzClone);

			// calculate ratio
			///////////////////
			long long isc;
			msg.sprintf("Run!> calculating ratio values!");
			emit valueChanged(msg);
#ifndef _DEBUG
			unsigned int ncores = std::thread::hardware_concurrency();
			msg.sprintf("Run!> Have %2d cores. Use %d", ncores, ncores - 1);
			emit valueChanged(msg);
			omp_set_num_threads(ncores - 1);
#pragma omp parallel for shared(VolMemClone)
#endif
			for (isc = 0; isc < n; isc++)
			{
				uint64_t offset = imgSz*isc;
				// copy data
				for (int iy = 0; iy < h; iy++)
				{
					for (int ix = 0; ix < w - 1; ix++)
					{
						uint64_t idx = isc*w*h + iy*w + ix;
						VolMemClone[idx] = VolMemClone[idx + 1] / VolMemClone[idx];
					}
				}
				//memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float)); //-ju- temp have to be local
			}
			// calculate ratio map
			///////////////////////
			//-ju-31-08-2015 cv::Mat medianRatioMap = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
			msg.sprintf("Run!> calculating ratio map!");
			emit valueChanged(msg);
			long long height = m_procPara.imgHeight;
			for (int iy = 0; iy < m_procPara.imgHeight; iy++)
			{
#ifdef _DEBUG_OUT
				if (iy % 10 == 0)
				{
					msg.sprintf("Line> %04d w=%d", iy, m_procPara.imgWidth);
					emit valueChanged(msg);
				}
#endif // _DEBUG_OUT
				int ix;
				unsigned int width = m_procPara.imgWidth;
				unsigned int proj = m_procPara.cntProj;

#ifndef _DEBUG
#pragma omp parallel for shared(VolMemClone, medianRatioMap, width)
#endif
				for (ix = 0; ix < width - 1; ix++)
				{
					std::vector<float> sinoVec;
					for (int k = 0; k < m_procPara.cntProj; k++)
					{
						uint64_t idx = k*width*height + iy*width + ix;
						sinoVec.push_back(VolMemClone[idx]);
					}
					boost::sort::spreadsort::float_sort(sinoVec.begin(), sinoVec.end());
					medianRatioMap.at<float>(iy, ix) = sinoVec[(int)(sinoVec.size()/ 2.0f)];
				}
			}
			///////////////////////
			delete[] VolMemClone;
			///////////////////////

#ifdef _DEBUG_OUT
			std::ofstream fMedianRatio;
			char medianRatioName[260];
			sprintf(medianRatioName, "MedianRatioMap_%04dx%04d.raw", m_procPara.imgWidth, m_procPara.imgHeight);
			fMedianRatio.open(medianRatioName, std::ios::binary);
			fMedianRatio.write((char*)medianRatioMap.ptr(0), m_procPara.imgWidth*m_procPara.imgHeight*sizeof(float));
			fMedianRatio.close();
			printf("RAC 1 write %s \n", medianRatioName);
#endif // _DEBUG_OUT
			// calculate correction matrix
			///////////////////////////////
			msg.sprintf("Run!> calculating correction matrix!");
			emit valueChanged(msg);
			for (int iy = 0; iy < medianRatioMap.rows; iy++)
			{
				float corr = 1.0f;
				// just fill border values with 1.0
				medianRatioMap.at<float>(iy, medianRatioMap.cols - 1) = corr;
			}
		} // useRac end
#ifdef _DEBUG_OUT
		std::ofstream fCorrRatio;
		char CorrRatioName[260];
		sprintf(CorrRatioName, "CorrectionMap_%04dx%04d.raw", m_procPara.imgWidth, m_procPara.imgHeight);
		fCorrRatio.open(CorrRatioName, std::ios::binary);
		fCorrRatio.write((char*)medianRatioMap.ptr(0), m_procPara.imgWidth*m_procPara.imgHeight*sizeof(float));
		fCorrRatio.close();
#endif //_DEBUG_OUT

		//-ju-13-July-2016 add convolution --> high pass filter
		//-ju-29-Aug-2016 used to smooth medianRatioMap
		////////////////////////////////////////////////////////
		// define filter kernel of size 31
		float smoothKernel31[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		const int KSZ31 = 31;
		af::array SK31(KSZ31, 1, smoothKernel31);
		//normalize kernel
		SK31 /= KSZ31;
		// do data preparation
		float *pSignalImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
		memcpy(&pSignalImage[0], medianRatioMap.data, medianRatioMap.cols*medianRatioMap.rows*sizeof(float));
		af::array SignalImage(m_procPara.imgWidth, m_procPara.imgHeight,  &pSignalImage[0]);
		//-ju-20-12-2016
		af::array ConvSignalImage = af::convolve1(SignalImage, SK31, AF_CONV_DEFAULT);
		// do correction of medianRatioMap image
		SignalImage = SignalImage / ConvSignalImage;

		std::vector<float> mem;
		mem.resize(m_procPara.imgWidth*m_procPara.imgHeight);
		SignalImage.host(&mem[0]);
		memcpy(medianRatioMap.data, &mem[0], medianRatioMap.cols*medianRatioMap.rows * sizeof(float));

		delete[] pSignalImage;

#define _DEBUG_OUT_STOP
#ifdef _DEBUG_OUT
		std::ofstream fMedianCorrRatioFilter;
		char medianCorrRatioNameFilter[260];
		sprintf(medianCorrRatioNameFilter, "FilterCorrectionMap_%04lldx%04lld.raw", m_procPara.imgWidth, m_procPara.imgHeight);
		fMedianCorrRatioFilter.open(medianCorrRatioNameFilter, std::ios::binary);
		fMedianCorrRatioFilter.write((char*)medianRatioMap.ptr(0), m_procPara.imgWidth*m_procPara.imgHeight*sizeof(float));
		fMedianCorrRatioFilter.close();
#endif // _DEBUG_OUT
#undef _DEBUG_OUT
		// do correction
		/////////////////
		msg.sprintf("Run!> do projection correction!");
		emit valueChanged(msg);
		//-ju-12-Apr-2017 apply Lorentz Filter with BHC
		///////////////////////////////////////////////
		if (m_procPara.useLorentzFilter && m_procPara.useBHC)
		{
			pImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			filterKernelRaw = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			LorentzFilterKernel(filterKernelRaw, m_procPara.imgWidth, m_procPara.imgHeight);
		}
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
#ifdef _DEBUG_OUT
			if (i % 100 == 0)
			{
				msg.sprintf("Image> I=%04d", i+1);
				emit valueChanged(msg);
			}
#endif // _DEBUG_OUT
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
			if (m_procPara.useRAC)
			{
				// apply correction
				tmp = tmp.mul(medianRatioMap);
			}
#ifdef _DEBUG_OUT
			if (i == 0)
			{
				std::ofstream fMul;
				char mulName[260];
				sprintf(mulName, "Mul.raw");
				fMul.open(mulName, std::ios::binary);
				fMul.write((char*)tmp.ptr(0), m_procPara.imgWidth*m_procPara.imgHeight*sizeof(float));
				fMul.close();
			}
#endif // _DEBUG_OUT
			//-ju-21-Oct-2015 implementing taking no logarithm (phase contrast)
			///////////////////////////////////////////////////////////////////
			if (m_procPara.noLog)
			{
				// no negativ values -> set to zero
				cv::threshold(tmp, tmp, 0.0, 0.0, cv::THRESH_TOZERO);
			}
			else
			{
				//-ju-27-Aug-2016 mask zero values --> avoid log(0)
				// all values should be below 1.0, but depending on 
				// normalisation factor (mean value) could be more 
				// then 1.0 --> lead to neg values log*-1
				///////////////////////////////////////////////////
				//-ju-26-Sept-2016 cv::Mat temp_NULL(tmp.size(), CV_32F);
				cv::Mat temp_NULL = cv::Mat::zeros(tmp.size(), CV_32F);
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
#ifdef _DEBUG_OUT
				if (i == m_procPara.cntProj - 1) printf("After log() --> File: %s, line %d: threshold to zero\n", __FILE__, __LINE__ + 1);
#endif

				//-ju-26-Aug-2016 threshold to zero
				// make sure having no negative values
				cv::threshold(tmp, tmp, 0.0f, 0.0f, cv::THRESH_TOZERO);
			}
#ifdef _DEBUG_OUT
			if (i == 0)
			{
				std::ofstream fLog;
				char logName[260];
				sprintf(logName, "Log.raw");
				fLog.open(logName, std::ios::binary);
				fLog.write((char*)tmp.ptr(0), m_procPara.imgWidth*m_procPara.imgHeight*sizeof(float));
				fLog.close();

			}
#endif // _DEBUG_OUT
			if (m_procPara.useBHC)
			{
				//-ju-24-07-2015 see above
				tmp += 1.0;
				tmp.copyTo(tmpBHCConst);
				// muss groesser 0 sein!!!
				cv::pow(tmp, m_procPara.coeffBHC, tmpInterm);
				tmpBHCConst = m_procPara.constCoeffBHC_A*tmpBHCConst;
				tmp = tmpBHCConst + m_procPara.constCoeffBHC_B*tmpInterm;

				//-ju-12-Apr-2017 apply Lorentz Filter with BHC
				///////////////////////////////////////////////
				if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
				{
					if (i == 0)
					{
						msg.sprintf("Run!> apply Lorentz filter! (val=%f)",m_procPara.alphaValue);
						emit valueChanged(msg);
					}
					ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
					printf("Apply Lorentz Filter projection : %04lld\n", i);
					printf("Lorentz mit BHC\n");
				}

			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-11-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
			printf("Apply Delete\n");
		}
		//-ju-11-Apr-2017 Lorentz Filter

	}
	else
	{
		// load flat image -> mean of flat -> done once
		// check directory path and add  >> / << if necessary
		///////////////////////////////////////////////
		QString projectionPath = m_procPara.flatFieldImageFile;
		if (projectionPath.isEmpty())
		{
			QString msg;
			msg.sprintf("No valid flat field image specified.");
			emit valueChanged(msg);
			msg.sprintf("Proc Info!> load data again!");
			emit valueChanged(msg);
			return;
		}
		// do normalisation
		/////////////////////
		float mea;
		GetMeanFromFlatField(projectionPath, mea);
		QString msg;
		msg.sprintf("Run!> normalisation is running!");
		emit valueChanged(msg);
		//-ju-11-Apr-2017 Lorentz Filter
		float *pImage;
		float *filterKernelRaw;
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			pImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			filterKernelRaw = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			LorentzFilterKernel(filterKernelRaw, m_procPara.imgWidth, m_procPara.imgHeight);
		}
		//-ju-11-Apr-2017 Lorentz Filter

		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
			tmp = tmp / mea;

			//-ju-10-Apr-2017 add Lorentz Filter
			/////////////////////////////////////
			if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
			{
				if (i == 0)
				{
					//msg.sprintf("Run!> apply Lorentz filter!");
					msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
					emit valueChanged(msg);
				}
				ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
			}

			//-ju-29-Aug-2016 trunc values to <= 1
			// to void neg. values after -log(value)
			///////////////////////////////////////////
			cv::threshold(tmp, tmp, 1.0, 1.0, cv::THRESH_TRUNC);
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-11-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-11-Apr-2017 Lorentz Filter

		//-ju-31-08-2015
		cv::Mat medianRatioMap = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
		if (m_procPara.useRAC)
		{
			//////////////////////////////////////////////
			//-ju-19-08-2015 new ring artefact correction

			// create copy of the volume
			/////////////////////////////
			long long w = m_procPara.imgWidth;
			long long h = m_procPara.imgHeight;
			long long n = m_procPara.cntProj;
			uint64_t memSzClone = w*h*n*sizeof(float);
			float *VolMemClone = new float[w*h*n];
			if (0 == VolMemClone)
			{
				QString msg;
				msg.sprintf("Proc Error!> Can not allocating memory for ring artefact correction failed!");
				emit valueChanged(msg);
				return;
			}

			// copy data
			//////////////
			memcpy(VolMemClone, VolMem, memSzClone);

			// calculate ratio
			///////////////////
			long long isc;
			msg.sprintf("Run!> calculating ratio values!");
			emit valueChanged(msg);
#ifndef _DEBUG
			unsigned int ncores = std::thread::hardware_concurrency();
			msg.sprintf("Run!> Have %2d cores. Use %d", ncores, ncores-1);
			emit valueChanged(msg);
			omp_set_num_threads(ncores - 1);
#pragma omp parallel for shared(VolMemClone)
#endif
			for (isc = 0; isc < n; isc++)
			{
				uint64_t offset = imgSz*isc;
				// copy data
				for (int iy = 0; iy < h; iy++)
				{
					for (int ix = 0; ix < w - 1; ix++)
					{
						uint64_t idx = isc*w*h + iy*w + ix;
						VolMemClone[idx] = VolMemClone[idx + 1] / VolMemClone[idx];
					}
				}
			}
			// calculate ratio map
			///////////////////////
			msg.sprintf("Run!> Calculating of ratio map!");
			emit valueChanged(msg);
			long long height = m_procPara.imgHeight;
			for (int iy = 0; iy < m_procPara.imgHeight; iy++)
			{
				int ix;
				unsigned int width = m_procPara.imgWidth;
				unsigned int proj = m_procPara.cntProj;

#ifndef _DEBUG
#pragma omp parallel for shared(VolMemClone, medianRatioMap, width)
#endif
				for (ix = 0; ix < width - 1; ix++)
				{
					std::vector<float> sinoVec;
					for (int k = 0; k < m_procPara.cntProj; k++)
					{
						uint64_t idx = k*width*height + iy*width + ix;
						sinoVec.push_back(VolMemClone[idx]);
					}
					boost::sort::spreadsort::float_sort(sinoVec.begin(), sinoVec.end());
					medianRatioMap.at<float>(iy, ix) = sinoVec[sinoVec.size() / 2];
				}
			}
			///////////////////////
			delete[] VolMemClone;
			///////////////////////

			// calculate correction matrix
			///////////////////////////////
			msg.sprintf("Run!> Calculating of correction matrix!");
			emit valueChanged(msg);
			for (int iy = 0; iy < medianRatioMap.rows; iy++)
			{
				float corr = 1.0f;
				medianRatioMap.at<float>(iy, medianRatioMap.cols - 1) = corr;
			}
		} // useRAC
		//-ju-29-Aug-2016 add convolution --> high pass filter
		// used to smooth medianRatioMap
		////////////////////////////////////////////////////////
		// define filter kernel of size 31
		float smoothKernel31[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		af::array SK31(31, 1, smoothKernel31);
		//normalize kernel
		SK31 /= 31;
		// do data preparation
		float *pSignalImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
		memcpy(&pSignalImage[0], medianRatioMap.data, medianRatioMap.cols*medianRatioMap.rows*sizeof(float));
		af::array SignalImage(m_procPara.imgWidth, m_procPara.imgHeight, &pSignalImage[0]);
		printf("Smoothing medianRatioMap by applying convolution using Kernel SK31\n");
		af::array ConvSignalImage = af::convolve1(SignalImage, SK31, AF_CONV_DEFAULT);

		// do correction of medianRatioMap image
		SignalImage = SignalImage / ConvSignalImage;

		//-ju-27-Nov-2017 fix error at pSignalImage -->
		std::vector<float> mem;
		mem.resize(m_procPara.imgWidth*m_procPara.imgHeight);
		SignalImage.host(&mem[0]);
		memcpy(medianRatioMap.data, &mem[0], medianRatioMap.cols*medianRatioMap.rows * sizeof(float));

		delete[] pSignalImage;

		////////////////////////////////
		// do correction
		/////////////////
		msg.sprintf("Run!> Do projection correction!");
		emit valueChanged(msg);
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			pImage = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			filterKernelRaw = new float[m_procPara.imgWidth*m_procPara.imgHeight];
			LorentzFilterKernel(filterKernelRaw, m_procPara.imgWidth, m_procPara.imgHeight);
		}

		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			if (m_procPara.useRAC)
			{
				tmp = tmp.mul(medianRatioMap);
			}

			//}
			//-ju-21-Oct-2015 implementing taking no logarithm (phase contrast)
			///////////////////////////////////////////////////////////////////
			if (m_procPara.noLog)
			{
				// no negativ values -> set to zero
				cv::threshold(tmp, tmp, 0.0, 0.0, cv::THRESH_TOZERO);
			}
			else
			{
				//-ju-29-Aug-2016 mask zero values --> avoid log(0)
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
				tmp = tmpInterm * (-1.0f);
				//-ju-29-Aug-2016 threshold to zero
				// make sure having no negative values
				cv::threshold(tmp, tmp, 0.0f, 0.0f, cv::THRESH_TOZERO);
			}
			if (m_procPara.useBHC)
			{
				//-ju-24-07-2015 see above
				tmp += 1.0;
				tmp.copyTo(tmpBHCConst);
				// muss groesser 0 sein!!!
				cv::pow(tmp, m_procPara.coeffBHC, tmpInterm);
				tmpBHCConst = m_procPara.constCoeffBHC_A*tmpBHCConst;
				tmp = tmpBHCConst + m_procPara.constCoeffBHC_B*tmpInterm;
				//-ju-12-Apr-2017 apply Lorentz Filter with BHC
				///////////////////////////////////////////////
				if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
				{
					if (i == 0)
					{
						msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
						emit valueChanged(msg);
					}
					ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
				}

			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-11-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-11-Apr-2017 Lorentz Filter

	}
}

//-ju-16-Oct-2015 apply tiling to normalize
////////////////////////////////////////////
void ThreadProcessing::NormalizeImages(float *VolMem, uint64_t tileHeight, uint64_t tileWidth)
{
	cv::Mat tmp = Mat::zeros(tileHeight, tileWidth, CV_32F);
	cv::Mat tmpInterm = Mat::zeros(tileHeight, tileWidth, CV_32F);
	cv::Mat tmpBHCConst = Mat::zeros(tileHeight, tileWidth, CV_32F);
	// get size of one projection
	uint64_t imgSz = tileHeight * tileWidth;
	// check if single image normalization should be applied
	//-ju-11-Apr-2017 Lorentz Filter
	float *pImage;
	float *filterKernelRaw;
	if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
	{
		pImage = new float[tileWidth*tileHeight];
		filterKernelRaw = new float[tileWidth*tileHeight];
		LorentzFilterKernel(filterKernelRaw, tileWidth, tileHeight);
	}
	//-ju-11-Apr-2017 Lorentz Filter

	//-ju-23-Feb-2018 no dark/flat correction
	/////////////////////////////////////////
	if (m_procPara.useWinNormalisation || m_procPara.isDarkFlatCorrected == 1)
	{
		if (m_procPara.widthWin * m_procPara.heightWin == 0 && m_procPara.isDarkFlatCorrected == 0)
		{
			QString msg;
			msg.sprintf("Proc Error!> normalisation window size is zero!");
			emit valueChanged(msg);
			msg.sprintf("Proc Info!> load data again!");
			emit valueChanged(msg);
		}
		// do normalisation
		/////////////////////
		QString msg;
		if (m_procPara.isDarkFlatCorrected == 0)
		{
			msg.sprintf("Run!> normalisation is running!");
			emit valueChanged(msg);
		}
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			if (m_procPara.isDarkFlatCorrected == 1)
			{
				tmp = tmp / static_cast<float>(m_procPara.maxGreyInStack);
			}
			else
			{
				tmp = tmp / m_procPara.winNormValueVector[i];
			}

			//-ju-12-Apr-2017 add Lorentz Filter
			/////////////////////////////////////
			if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
			{
				if (i == 0)
				{
					//msg.sprintf("Run!> apply Lorentz filter!");
					msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
					emit valueChanged(msg);
				}
				ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
			}

			//-ju-27-Aug-2016 threshold see none tile version
			//////////////////////////////////////////////////
			cv::threshold(tmp, tmp, 1.0, 1.0, cv::THRESH_TRUNC);
#ifdef _DEBUG_OUT
			if (i == 0) printf("Tiled Raw --> File: %s, line %d: threshold to zero\n", __FILE__, __LINE__ + 1);
#endif
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-12-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-12-Apr-2017 Lorentz Filter


		cv::Mat medianRatioMap = Mat::zeros(tileHeight, tileWidth, CV_32F);
		if (m_procPara.useRAC)
		{
			//////////////////////////////////////////////
			//-ju-19-08-2015 new ring artefact correction

			// create copy of the volume
			/////////////////////////////
			long long w = tileWidth;
			long long h = tileHeight;
			long long n = m_procPara.cntProj;
			uint64_t memSzClone = w*h*n*sizeof(float);
			float *VolMemClone = new float[w*h*n];
			if (0 == VolMemClone)
			{
				QString msg;
				msg.sprintf("Proc Error!> Can not allocating memory for ring artefact correction failed!");
				emit valueChanged(msg);
				return;
			}

			// copy data
			//////////////
			memcpy(VolMemClone, VolMem, memSzClone);

			// calculate ratio
			///////////////////
			long long isc;
			msg.sprintf("Run!> calculating ratio values!");
			emit valueChanged(msg);
#ifndef _DEBUG
			unsigned int ncores = std::thread::hardware_concurrency();
			msg.sprintf("Run!> Have %2d cores. Use %d", ncores, ncores - 1);
			emit valueChanged(msg);
			omp_set_num_threads(ncores - 1);
#pragma omp parallel for shared(VolMemClone)
#endif
			for (isc = 0; isc < n; isc++)
			{
				uint64_t offset = imgSz*isc;
				// copy data
				for (int iy = 0; iy < h; iy++)
				{
					for (int ix = 0; ix < w - 1; ix++)
					{
						uint64_t idx = isc*w*h + iy*w + ix;
						VolMemClone[idx] = VolMemClone[idx + 1] / VolMemClone[idx];
					}
				}
			}
			// calculate ratio map
			///////////////////////
			msg.sprintf("Run!> calculating tiled ratio map!");
			emit valueChanged(msg);
			// using tile height
			long long height = tileHeight;
			for (int iy = 0; iy < tileHeight; iy++)
			{
#ifdef _DEBUG_OUT
				if (iy % 10 == 0)
				{
					msg.sprintf("Line> %04d w=%d", iy, tileWidth);
					emit valueChanged(msg);
				}
#endif // _DEBUG_OUT
				int ix;
				// using tile width
				unsigned int width = tileWidth;
				unsigned int proj = m_procPara.cntProj;

#ifndef _DEBUG
#pragma omp parallel for shared(VolMemClone, medianRatioMap, width)
#endif
				for (ix = 0; ix < width - 1; ix++)
				{
					std::vector<float> sinoVec;
					for (int k = 0; k < m_procPara.cntProj; k++)
					{
						uint64_t idx = k*width*height + iy*width + ix;
						sinoVec.push_back(VolMemClone[idx]);
					}
					boost::sort::spreadsort::float_sort(sinoVec.begin(), sinoVec.end());
					// median value 
					medianRatioMap.at<float>(iy, ix) = sinoVec[(int)sinoVec.size() / 2];
				}
			}
			///////////////////////
			delete[] VolMemClone;
			///////////////////////

#ifdef _DEBUG_OUT
			std::ofstream fMedianRatio;
			char medianRatioName[260];
			sprintf(medianRatioName, "MedianRatioMap_%04dx%04d.raw", tileWidth, tileHeight);
			fMedianRatio.open(medianRatioName, std::ios::binary);
			fMedianRatio.write((char*)medianRatioMap.ptr(0), tileWidth*tileHeight*sizeof(float));
			fMedianRatio.close();
#endif // _DEBUG_OUT
			// calculate correction matrix
			///////////////////////////////
			msg.sprintf("Run!> calculating correction matrix!");
			emit valueChanged(msg);
			for (int iy = 0; iy < medianRatioMap.rows; iy++)
			{
				float corr = 1.0f;
				medianRatioMap.at<float>(iy, medianRatioMap.cols - 1) = corr;
			}
		} // useRac end
#ifdef _DEBUG_OUT
		std::ofstream fMedianCorrRatio;
		char medianCorrRatioName[260];
		sprintf(medianCorrRatioName, "CorrectionMap_%04dx%04d.raw", tileWidth, tileHeight);
		fMedianCorrRatio.open(medianCorrRatioName, std::ios::binary);
		fMedianCorrRatio.write((char*)medianRatioMap.ptr(0), tileWidth*tileHeight*sizeof(float));
		fMedianCorrRatio.close();
#endif // _DEBUG_OUT
		//-ju-29-Aug-2016 add convolution --> high pass filter
		// used to smooth medianRatioMap
		////////////////////////////////////////////////////////
		// define filter kernel of size 31
		float smoothKernel31[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		af::array SK31(31, 1, smoothKernel31);
		//normalize kernel
		SK31 /= 31;
		// do data preparation for smoothing (convolution)
		float *pSignalImage = new float[tileWidth*tileHeight];
		memcpy(&pSignalImage[0], medianRatioMap.data, medianRatioMap.cols*medianRatioMap.rows*sizeof(float));
		af::array SignalImage(tileWidth, tileHeight, &pSignalImage[0]);
		printf("Smoothing medianRatioMap by applying convolution using Kernel SK31\n");
		af::array ConvSignalImage = af::convolve1(SignalImage, SK31, AF_CONV_DEFAULT);
		// do correction of medianRatioMap image
		SignalImage = SignalImage / ConvSignalImage;

		//-ju-27-Nov-2017 fix error at pSignalImage -->
		std::vector<float> mem;
		mem.resize(m_procPara.imgWidth*m_procPara.imgHeight);
		SignalImage.host(&mem[0]);
		memcpy(medianRatioMap.data, &mem[0], medianRatioMap.cols*medianRatioMap.rows * sizeof(float));

		delete[] pSignalImage;

		////////////////////////////////
		// do correction
		/////////////////
		msg.sprintf("Run!> do projection correction!");
		emit valueChanged(msg);
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			pImage = new float[tileWidth*tileHeight];
			filterKernelRaw = new float[tileWidth*tileHeight];
			LorentzFilterKernel(filterKernelRaw, tileWidth, tileHeight);
		}

		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
#ifdef _DEBUG_OUT
			if (i % 100 == 0)
			{
				msg.sprintf("Image> I=%04d", i + 1);
				emit valueChanged(msg);
			}
#endif // _DEBUG_OUT
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
			if (m_procPara.useRAC)
			{
				// apply correction
				tmp = tmp.mul(medianRatioMap);
			}
#ifdef _DEBUG_OUT
			if (i == 0)
			{
				std::ofstream fMul;
				char mulName[260];
				sprintf(mulName, "Mul.raw");
				fMul.open(mulName, std::ios::binary);
				fMul.write((char*)tmp.ptr(0), tileWidth*tileHeight*sizeof(float));
				fMul.close();
			}
#endif // _DEBUG_OUT
			//-ju-21-Oct-2015 implementing taking no logarithm (phase contrast)
			///////////////////////////////////////////////////////////////////
			if (m_procPara.noLog)
			{
				// no negativ values -> set to zero
				cv::threshold(tmp, tmp, 0.0, 0.0, cv::THRESH_TOZERO);
			}
			else
			{
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
#ifdef _DEBUG_OUT
				if (i == m_procPara.cntProj - 1) printf("Tiled after log() --> File: %s, line %d: threshold to zero\n", __FILE__, __LINE__ + 1);
#endif
				//-ju-26-Aug-2016 threshold to zero
				// make sure having no negative values
				cv::threshold(tmp, tmp, 0.0f, 0.0f, cv::THRESH_TOZERO);
			}
#ifdef _DEBUG_OUT
			if (i == 0)
			{
				std::ofstream fLog;
				char logName[260];
				sprintf(logName, "Log.raw");
				fLog.open(logName, std::ios::binary);
				fLog.write((char*)tmp.ptr(0), tileWidth*tileHeight*sizeof(float));
				fLog.close();

			}
#endif // _DEBUG_OUT
			if (m_procPara.useBHC)
			{
				//-ju-24-07-2015 see above
				tmp += 1.0;
				tmp.copyTo(tmpBHCConst);
				// muss groesser 0 sein!!!
				cv::pow(tmp, m_procPara.coeffBHC, tmpInterm);
				tmpBHCConst = m_procPara.constCoeffBHC_A*tmpBHCConst;
				tmp = tmpBHCConst + m_procPara.constCoeffBHC_B*tmpInterm;
				//-ju-12-Apr-2017 apply Lorentz Filter with BHC
				///////////////////////////////////////////////
				if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
				{
					if (i == 0)
					{
						msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
						emit valueChanged(msg);
					}
					ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
				}

			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-12-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-12-Apr-2017 Lorentz Filter


	}
	else
	{
		// load flat image -> mean of flat -> done once
		// check directory path and add  >> / << if necessary
		///////////////////////////////////////////////
		QString projectionPath = m_procPara.flatFieldImageFile;
		if (projectionPath.isEmpty())
		{
			QString msg;
			msg.sprintf("No valid flat field image specified.");
			emit valueChanged(msg);
			msg.sprintf("Proc Info!> load data again!");
			emit valueChanged(msg);
			return;
		}
		// do normalisation
		/////////////////////
		float mea;
		GetMeanFromFlatField(projectionPath, mea);
		QString msg;
		msg.sprintf("Run!> normalisation is running!");
		emit valueChanged(msg);
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			pImage = new float[tileHeight*tileHeight];
			filterKernelRaw = new float[tileHeight*tileHeight];
			LorentzFilterKernel(filterKernelRaw, tileHeight, tileHeight);
		}

		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
			tmp = tmp / mea;
			//-ju-10-Apr-2017 add Lorentz Filter
			/////////////////////////////////////
			if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
			{
				if (i == 0)
				{
					//msg.sprintf("Run!> apply Lorentz filter!");
					msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
					emit valueChanged(msg);
				}
				ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
			}

			//-ju-29-Aug-2016 trunc values to <= 1
			// to void neg. values after -log(value)
			///////////////////////////////////////////
			cv::threshold(tmp, tmp, 1.0, 1.0, cv::THRESH_TRUNC);
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-12-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && !m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-12-Apr-2017 Lorentz Filter


		//-ju-31-08-2015
		cv::Mat medianRatioMap = Mat::zeros(tileHeight, tileWidth, CV_32F);
		if (m_procPara.useRAC)
		{
			//////////////////////////////////////////////
			//-ju-19-08-2015 new ring artefact correction

			// create copy of the volume
			/////////////////////////////
			long long w = tileWidth;
			long long h = tileHeight;
			long long n = m_procPara.cntProj;
			uint64_t memSzClone = w*h*n*sizeof(float);
			float *VolMemClone = new float[w*h*n];
			if (0 == VolMemClone)
			{
				QString msg;
				msg.sprintf("Proc Error!> Can not allocating memory for ring artefact correction failed!");
				emit valueChanged(msg);
				return;
			}

			// copy data
			//////////////
			memcpy(VolMemClone, VolMem, memSzClone);

			// calculate ratio
			///////////////////
			long long isc;
			msg.sprintf("Run!> calculating ratio values!");
			emit valueChanged(msg);
#ifndef _DEBUG
			unsigned int ncores = std::thread::hardware_concurrency();
			msg.sprintf("Run!> Have %2d cores. Use %d", ncores, ncores - 1);
			emit valueChanged(msg);
			omp_set_num_threads(ncores - 1);
#pragma omp parallel for shared(VolMemClone)
#endif
			for (isc = 0; isc < n; isc++)
			{
				uint64_t offset = imgSz*isc;
				// copy data
				for (int iy = 0; iy < h; iy++)
				{
					for (int ix = 0; ix < w - 1; ix++)
					{
						uint64_t idx = isc*w*h + iy*w + ix;
						VolMemClone[idx] = VolMemClone[idx + 1] / VolMemClone[idx];
					}
				}
			}
			// calculate ratio map
			///////////////////////
			msg.sprintf("Run!> Calculating of ratio map!");
			emit valueChanged(msg);
			long long height = tileHeight;
			for (int iy = 0; iy < tileHeight; iy++)
			{
				int ix;
				unsigned int width = tileWidth;
				unsigned int proj = m_procPara.cntProj;

#ifndef _DEBUG
#pragma omp parallel for shared(VolMemClone, medianRatioMap, width)
#endif
				for (ix = 0; ix < width - 1; ix++)
				{
					std::vector<float> sinoVec;
					for (int k = 0; k < m_procPara.cntProj; k++)
					{
						uint64_t idx = k*width*height + iy*width + ix;
						sinoVec.push_back(VolMemClone[idx]);
					}
					boost::sort::spreadsort::float_sort(sinoVec.begin(), sinoVec.end());
					medianRatioMap.at<float>(iy, ix) = sinoVec[sinoVec.size() / 2];
				}
			}
			///////////////////////
			delete[] VolMemClone;
			///////////////////////

			// calculate correction matrix
			///////////////////////////////
			msg.sprintf("Run!> Calculating of correction matrix!");
			emit valueChanged(msg);
			for (int iy = 0; iy < medianRatioMap.rows; iy++)
			{
				float corr = 1.0f;
				medianRatioMap.at<float>(iy, medianRatioMap.cols - 1) = corr;
			}
		} // end useRAC
		//-ju-29-Aug-2016 add convolution --> high pass filter
		// used to smooth medianRatioMap
		////////////////////////////////////////////////////////
		// define filter kernel of size 31
		float smoothKernel31[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		af::array SK31(31, 1, smoothKernel31);
		//normalize kernel
		SK31 /= 31;
		// do data preparation
		float *pSignalImage = new float[tileWidth*tileHeight];
		printf("Tile flat: w=%lld h=%lld\n", tileWidth, tileHeight);
		memcpy(&pSignalImage[0], medianRatioMap.data, medianRatioMap.cols*medianRatioMap.rows*sizeof(float));
		printf("af::array SignalImage\n");
		af::array SignalImage(tileWidth, tileHeight, &pSignalImage[0]);
		printf("Smoothing medianRatioMap by applying convolution using Kernel SK31\n");
		af::array ConvSignalImage = af::convolve1(SignalImage, SK31, AF_CONV_DEFAULT);

		// do correction of medianRatioMap image
		printf("divide\n");
		SignalImage = SignalImage / ConvSignalImage;

		//-ju-27-Nov-2017 fix error at pSignalImage -->
		std::vector<float> mem;
		mem.resize(m_procPara.imgWidth*m_procPara.imgHeight);
		SignalImage.host(&mem[0]);
		memcpy(medianRatioMap.data, &mem[0], medianRatioMap.cols*medianRatioMap.rows * sizeof(float));

		delete[] pSignalImage;

		////////////////////////////////
		// do correction
		/////////////////
		msg.sprintf("Run!> Do projection correction!");
		emit valueChanged(msg);
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			if (m_procPara.useRAC)
			{
				tmp = tmp.mul(medianRatioMap);
			}

			//}
			//-ju-21-Oct-2015 implementing taking no logarithm (phase contrast)
			///////////////////////////////////////////////////////////////////
			if (m_procPara.noLog)
			{
				// no negativ values -> set to zero
				cv::threshold(tmp, tmp, 0.0, 0.0, cv::THRESH_TOZERO);
			}
			else
			{
				//-ju-29-Aug-2016 mask zero values --> avoid log(0)
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
				tmp = tmpInterm * (-1.0f);
				//-ju-29-Aug-2016 threshold to zero
				// make sure having no negative values
				cv::threshold(tmp, tmp, 0.0f, 0.0f, cv::THRESH_TOZERO);
			}
			if (m_procPara.useBHC)
			{
				//-ju-24-07-2015 see above
				tmp += 1.0;
				tmp.copyTo(tmpBHCConst);
				// muss groesser 0 sein!!!
				cv::pow(tmp, m_procPara.coeffBHC, tmpInterm);
				tmpBHCConst = m_procPara.constCoeffBHC_A*tmpBHCConst;
				tmp = tmpBHCConst + m_procPara.constCoeffBHC_B*tmpInterm;
				//-ju-12-Apr-2017 apply Lorentz Filter with BHC
				///////////////////////////////////////////////
				if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
				{
					if (i == 0)
					{
						//msg.sprintf("Run!> apply Lorentz filter!");
						msg.sprintf("Run!> apply Lorentz filter! (val=%f)", m_procPara.alphaValue);
						emit valueChanged(msg);
					}
					ApplyLorentzFilter(tmp, filterKernelRaw, pImage);
					printf("Apply Lorentz Filter projection : %04lld\n", i);
					printf("Lorentz mit BHC\n");
				}

			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//-ju-11-Apr-2017 Lorentz Filter
		if (m_procPara.useLorentzFilter && m_procPara.useBHC == 1)
		{
			delete[] pImage;
			delete[] filterKernelRaw;
		}
		//-ju-11-Apr-2017 Lorentz Filter
	}
}


void ThreadProcessing::SegmentForOutliers(cv::Mat &binOutlierImage)
{
	//-ju-16-Oct-2015
	// adapt to tiled images
	/////////////////////////
	Mat medianImage = Mat::zeros(binOutlierImage.rows, binOutlierImage.cols, CV_32F);
#undef DO_WRITE
#ifdef DO_WRITE
	cv::imwrite("m_projSumImage.tif", m_projSumImage);
#endif

	medianBlur(m_projSumImage, medianImage, m_medianMaskSize);
#ifdef DO_WRITE
	cv::imwrite("MedianBlur_m_projSumImage.tif", medianImage);
#endif
	absdiff(m_projSumImage, medianImage, binOutlierImage);
#ifdef DO_WRITE
	cv::imwrite("AbsDiff_MedianBlur-Minus_m_projSumImage.tif", binOutlierImage);
#endif

	// calculate z-score
	/////////////////////
	Scalar meanVal;
	Scalar stddevVal;
	meanStdDev(binOutlierImage, meanVal, stddevVal);
	double mean_s = meanVal.val[0];
	double stddev_s = stddevVal.val[0];
	binOutlierImage = (binOutlierImage - mean_s) / stddev_s;
#ifdef DO_WRITE
	cv::imwrite("z-score-m_projSumImage.tif", binOutlierImage);
#endif
	double sigma;
	if (m_procPara.correctAlgo)
	{
		sigma = m_procPara.outlierSigmaMedian9;
	}
	else
	{
		sigma = m_procPara.outlierSigmaMean9;
	}
	// do binary segmentation
	cv::threshold(binOutlierImage, binOutlierImage, sigma, 1.0, THRESH_BINARY);
#ifdef DO_WRITE
	cv::imwrite("threshold-z-score-m_projSumImage.tif", binOutlierImage);
#endif
}

void ThreadProcessing::FindOutliers(cv::Mat binOutlierImage, vector<cv::Vec2i> &outlierPixelList)
{
	int nr_rows = binOutlierImage.rows;
	int nr_cols = binOutlierImage.cols;
	cv::Vec2i coor;

	for (int row = 0; row < nr_rows; row++)
	{
		// start pointer of date in row
		float *data = binOutlierImage.ptr<float>(row);
		for (int col = 0; col < nr_cols; col++)
		{
			if (*data > 0.0f)
			{
				coor.val[0] = row;
				coor.val[1] = col;
				outlierPixelList.push_back(coor);
			}
			*data++;
		}
	}
}

void ThreadProcessing::ApplyOutlierReductionFilter(float *VolMem, vector<cv::Vec2i> &outlierPixelList)
{
	Mat tmp = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);

	// size of one projection
	uint64_t imgSz = m_procPara.imgHeight * m_procPara.imgWidth;

	for (uint64_t i = 0; i < m_procPara.cntProj; i++)
	{
		uint64_t offset = imgSz*i;
		// copy data
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		if (m_procPara.correctAlgo)
		{
			for (int k = 0; k < outlierPixelList.size(); k++)
			{
				RingArtefactReplaceByMedian9(tmp, outlierPixelList[k]);
			}
		}
		else
		{
			for (int k = 0; k < outlierPixelList.size(); k++)
			{
				RingArtefactReplaceByMean9(tmp, outlierPixelList[k]);
			}
		}
		// copy data back
		memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
	}
}

//-ju-16-Oct-2015 overloaded function used for tiled images
void ThreadProcessing::ApplyOutlierReductionFilter(float *VolMem, vector<cv::Vec2i> &outlierPixelList, uint64_t rows, uint64_t cols)
{
	Mat tmp = Mat::zeros(rows, cols, CV_32F);

	// size of one projection
	uint64_t imgSz = rows * cols;

	for (uint64_t i = 0; i < m_procPara.cntProj; i++)
	{
		uint64_t offset = imgSz*i;
		// copy data
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		if (m_procPara.correctAlgo)
		{
			for (int k = 0; k < outlierPixelList.size(); k++)
			{
				RingArtefactReplaceByMedian9(tmp, outlierPixelList[k]);
			}
		}
		else
		{
			for (int k = 0; k < outlierPixelList.size(); k++)
			{
				RingArtefactReplaceByMean9(tmp, outlierPixelList[k]);
			}
		}
		// copy data back
		memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
	}
}

void ThreadProcessing::RingArtefactReplaceByMean9(cv::Mat &projection, cv::Vec2i &pixCoord)
{
	cv::Mat filterVec(1, 8, CV_32F);
	Vec2i imageDim(projection.rows, projection.cols);
	float val, val0;
	if (pixCoord.val[0] > 0 && pixCoord.val[0] < imageDim.val[0] - 2 &&
		pixCoord.val[1] > 0 && pixCoord.val[1] < imageDim.val[1] - 2)
	{
		val0 = projection.at<float>(pixCoord.val[0], pixCoord.val[1]);
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] - 1); // (-1,-1) (y,x)
		filterVec.at<float>(0) = val;
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1]); // (-1, 0)
		filterVec.at<float>(1) = val;
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] + 1); // (-1, 1)
		filterVec.at<float>(2) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] - 1); // ( 0,-1)
		filterVec.at<float>(3) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] + 1); // ( 0, 1)
		filterVec.at<float>(4) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] - 1); // ( 1,-1)
		filterVec.at<float>(5) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1]); // ( 1, 0)
		filterVec.at<float>(6) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] + 1); // ( 1, 1)
		filterVec.at<float>(7) = val;
		cv::sort(filterVec, filterVec, cv::SORT_ASCENDING);
		cv::Mat mat = filterVec.colRange(0, 7);
		float meanVal = cv::mean(mat).val[0];
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = meanVal;
	}
}

void ThreadProcessing::RingArtefactReplaceByMedian9(cv::Mat &projection, cv::Vec2i &pixCoord)
{
	cv::Mat filterVec(1, 8, CV_32F);
	Vec2i imageDim(projection.rows, projection.cols);
	float val, val0;
	if (pixCoord.val[0] > 0 && pixCoord.val[0] < imageDim.val[0] - 2 &&
		pixCoord.val[1] > 0 && pixCoord.val[1] < imageDim.val[1] - 2)
	{
		val0 = projection.at<float>(pixCoord.val[0], pixCoord.val[1]);
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] - 1); // (-1,-1) (y,x)
		filterVec.at<float>(0) = val;
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1]); // (-1, 0)
		filterVec.at<float>(1) = val;
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] + 1); // (-1, 1)
		filterVec.at<float>(2) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] - 1); // ( 0,-1)
		filterVec.at<float>(3) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] + 1); // ( 0, 1)
		filterVec.at<float>(4) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] - 1); // ( 1,-1)
		filterVec.at<float>(5) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1]); // ( 1, 0)
		filterVec.at<float>(6) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] + 1); // ( 1, 1)
		filterVec.at<float>(7) = val;
		cv::sort(filterVec, filterVec, cv::SORT_ASCENDING);
		// take value 4 and 5 to calc. median from mean of both, because of even value list (len=8)
		float medianVal = (filterVec.at<float>(3) + filterVec.at<float>(4)) / 2.0f;
		// replace central pixel
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = medianVal;
	}
}

void ThreadProcessing::SaveProjections(float *VolMem)
{
	OutTypes convertToType;
	uint64_t dataTypeSize;
	m_procPara.saveOnly = false; // reset
	if (m_procPara.dataTypeOut == OutTypes::REAL32)
	{
		dataTypeSize = 4;
	}
	if (m_procPara.dataTypeOut == OutTypes::USHORT16)
	{
		dataTypeSize = 2;
	}
	// check directory path and add  >> / << if necessary
	///////////////////////////////////////////////
	QString projectionPath = m_procPara.outputDirectory;
	QDir directoryOut(projectionPath);
	if (!directoryOut.exists())
	{
		// create complete path
		directoryOut.mkpath(projectionPath);
	}
	QChar end = projectionPath[projectionPath.size() - 1];
	if (end != QChar('/') || end != QChar('\\'))
	{
		projectionPath += QChar('/');
	}
	QByteArray bStr = projectionPath.toUtf8();
	string projectionPathStr = bStr.data();
	// read one projection and check parameters
	////////////////////////////////////////////
	QString pattern = m_procPara.outputFilepattern;
	pattern.chop(8); // remove ####.raw from end of file
	QByteArray outNamePattern = pattern.toUtf8();
	string outFileNamePatternStr = outNamePattern.data();
	projectionPathStr = projectionPathStr + outFileNamePatternStr;
	char fileNameBuffer[260];
	ofstream projectionFile;
	uint64_t sz = m_procPara.imgHeight * m_procPara.imgWidth;
	emit updateProgressBar(0);
	if (m_procPara.dataTypeOut == OutTypes::REAL32)
	{
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = sz * i;
			sprintf_s(fileNameBuffer, "%s%04lld.raw",
				projectionPathStr.c_str(), i + 1);
			projectionFile.open(fileNameBuffer, ios::binary);
			if (!projectionFile.is_open())
			{
				QString msg;
				msg.sprintf("Proc Error!> write file: %s", fileNameBuffer);
				emit valueChanged(msg);
				msg.sprintf("Proc Info!> load data again!");
				emit valueChanged(msg);
				return;
			}
			projectionFile.write((char*)&VolMem[offset], sz*dataTypeSize);
			projectionFile.close();
			emit updateProgressBar(i + 1);
		}
	}
	if (m_procPara.dataTypeOut == OutTypes::USHORT16)
	{
		cv::Mat tmp = Mat::zeros(m_procPara.imgHeight, m_procPara.imgWidth, CV_32F);
		// get size of one projection
		uint64_t imgSz = m_procPara.imgHeight * m_procPara.imgWidth;
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data buffer
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			// do conversion to 16 Bit unsigned
			////////////////////////////////////
			double minVal, maxVal;
			cv::minMaxLoc(tmp, &minVal, &maxVal); //find minimum and maximum intensities
			// scale image to uchar
			Mat convMat(tmp.rows, tmp.cols, CV_16U, Scalar::all(0));
			tmp.convertTo(convMat, CV_16U, 65535.0 / (maxVal - minVal), -minVal * 65535.0 / (maxVal - minVal));

			sprintf_s(fileNameBuffer, "%s%04lldx%04lld_16U_%04lld.raw",
				projectionPathStr.c_str(), m_procPara.imgWidth, m_procPara.imgHeight, i + 1);
			projectionFile.open(fileNameBuffer, ios::binary);
			if (!projectionFile.is_open())
			{
				QString msg;
				msg.sprintf("Proc Error!> write file: %s", fileNameBuffer);
				emit valueChanged(msg);
				msg.sprintf("Proc Info!> load data again!");
				return;
			}
			projectionFile.write((char*)convMat.data, sz*dataTypeSize);
			projectionFile.close();
			emit updateProgressBar(i + 1);
		}
	}
	emit updateProgressBar(0);
}

void ThreadProcessing::SaveProjections(float *VolMem, uint32_t tileNum)
{
	OutTypes convertToType;
	uint64_t dataTypeSize;
	m_procPara.saveOnly = false; // reset
	if (m_procPara.dataTypeOut == OutTypes::REAL32)
	{
		dataTypeSize = 4;
	}
	if (m_procPara.dataTypeOut == OutTypes::USHORT16)
	{
		dataTypeSize = 2;
	}
	// check directory path and add  >> / << if necessary
	///////////////////////////////////////////////
	QString projectionPath = m_procPara.outputDirectory;
	QDir directoryOut(projectionPath);
	if (!directoryOut.exists())
	{
		// create complete path
		directoryOut.mkpath(projectionPath);
	}
	QChar end = projectionPath[projectionPath.size() - 1];
	if (end != QChar('/') || end != QChar('\\'))
	{
		projectionPath += QChar('/');
	}
	QByteArray bStr = projectionPath.toUtf8();
	string projectionPathStr = bStr.data();
	// read one projection and check parameters
	////////////////////////////////////////////
	QString pattern = m_procPara.outputFilepattern;
	pattern.chop(8); // remove ####.raw from end of file
	QByteArray outNamePattern = pattern.toUtf8();
	string outFileNamePatternStr = outNamePattern.data();
	projectionPathStr = projectionPathStr + outFileNamePatternStr;
	char fileNameBuffer[260];
	ofstream projectionFile;
	//-ju-16-Oct-2015 add tiling
	////////////////////////////
	uint64_t tileHeight = m_procPara.tilesSegmentProperties[tileNum].height;
	uint64_t tileWidth = m_procPara.imgWidth;

	uint64_t sz = tileHeight * tileWidth;
	emit updateProgressBar(0);
	if (m_procPara.dataTypeOut == OutTypes::REAL32)
	{
		for (uint64_t i = 0; i < m_procPara.cntProj; i++)
		{
			uint64_t offset = sz * i;
			sprintf_s(fileNameBuffer, "%s%04lld.raw",
				projectionPathStr.c_str(), i + 1);
			if (tileNum == 0)
			{
				projectionFile.open(fileNameBuffer, ios::binary);
			}
			else
			{
				projectionFile.open(fileNameBuffer, ios::binary|ios::app);
			}
			if (!projectionFile.is_open())
			{
				QString msg;
				msg.sprintf("Proc Error!> write file: %s", fileNameBuffer);
				emit valueChanged(msg);
				msg.sprintf("Proc Info!> load data again!");
				emit valueChanged(msg);
				return;
			}
			///-tiling
			Mat splitMat = Mat::zeros(m_procPara.tilesSegmentProperties[tileNum].height, tileWidth, CV_32F);

			int pto = 0;
			if (tileNum > 0)
			{
				pto = 1; // compensate row - 1 overlap
			}
			memcpy(splitMat.data, &VolMem[offset], sz*sizeof(float));
			projectionFile.write((char*)splitMat.ptr(pto), m_procPara.tilesSegmentProperties[tileNum].length * dataTypeSize); // write segment without overlap
			/////////////////////////////////

			projectionFile.close();
			emit updateProgressBar(i + 1);
		}
	}

	emit updateProgressBar(0);
}

// memory of pFilterArray must be alloc/dealloc out side of function
void ThreadProcessing::LorentzFilterKernel(float *pFilterArray, int32_t szX, int32_t szY)
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

void ThreadProcessing::ApplyLorentzFilter(cv::Mat &image, float *filterKernelRaw, float *pTemp)
{
	af::array img(m_procPara.imgWidth, m_procPara.imgHeight, image.ptr<float>(0));

	// filter kernel
	af::array arrayLorentzKernel(m_procPara.imgWidth, m_procPara.imgHeight, filterKernelRaw);

	// fft of input image
	// output image is complex !!!
	//////////////////////////////
	af::array imgFFT = fft2(img);

	double factor = 1.0e-6*m_procPara.alphaValue;
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

	std::vector<float> mem;
	mem.resize(m_procPara.imgWidth*m_procPara.imgHeight);
	filt_img_real.host(&mem[0]);
	memcpy(image.data, &mem[0], m_procPara.imgWidth*m_procPara.imgHeight * sizeof(float));
}
