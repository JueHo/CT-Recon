#include "preprocessor.h"

#define _RUN_TESTS
#undef _RUN_TESTS

ProjectionPreprocessor::ProjectionPreprocessor(QString parameterFile, bool createNew)
	:m_parameterFile(parameterFile), m_createNewParam(createNew)
{};

MSG_CODE ProjectionPreprocessor::InitParametersNew()
{
	MSG_CODE ret;
	QString retMsg;
	m_preHnd.CreateParameterFile(QString(m_parameterFile), ret, retMsg);
	m_preHnd.LoadParameter(QString(m_parameterFile), ret, retMsg);
	if (ret != IS_OK)
	{
#ifdef _RUN_TESTS
		char buffer[256];
		QByteArray bStr = retMsg.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Parameter error >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
#endif
		return ret;
	}
	m_paramObj = m_preHnd.GetParameters();
	m_projSumImage = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::InitParameters()
{
	MSG_CODE ret;
	QString retMsg;
	m_preHnd.LoadParameter(QString(m_parameterFile), ret, retMsg);
	if (ret != IS_OK)
	{
#ifdef _RUN_TESTS
		char buffer[256];
		QByteArray bStr = retMsg.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Parameter error >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
#endif
		return ret;
	}
	m_paramObj = m_preHnd.GetParameters();
	m_projSumImage = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);
	return IS_OK;
}


void ProjectionPreprocessor::ShiftFFT(Mat &image)
{
	Mat tmp, rec1, rec2, rec3, rec4;
	/////////////////////////////////////////////////////////////////////////////////
	// first crop the image, if it has an odd number of rows or columns
	// should and must always be an even number, 
	// because of padding to 256, 512, 1024, 2048, 4096 ... !!!!
	/////////////////////////////////////////////////////////////////////////////////
	image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
	int hW  = image.cols / 2;
	int hH = image.rows / 2;

	// rearrange the quadrants 1 -> 4 of Fourier image
	// so that the origin is at the image center

	rec1 = image(Rect(0, 0, hW, hH));
	rec2 = image(Rect(hW, 0, hW, hH));
	rec3 = image(Rect(0, hH, hW, hH));
	rec4 = image(Rect(hW, hH, hW, hH));

	rec1.copyTo(tmp);
	rec4.copyTo(rec1);
	tmp.copyTo(rec4);

	rec2.copyTo(tmp);
	rec3.copyTo(rec2);
	tmp.copyTo(rec3);
}

void ProjectionPreprocessor::CreateFFTFilterKernel(Mat &FFTFilterKernel,
	int32_t maskWidtHalf, int32_t maskHeight)
{
	// create mask filled with 1.0
	///////////////////////////////
	Mat tmp = Mat(FFTFilterKernel.rows, FFTFilterKernel.cols, CV_32F, Scalar::all(1.0));

	Point centre = Point(FFTFilterKernel.cols / 2, FFTFilterKernel.rows / 2);

	int twoLines = 1;	// filter mask (=2): centre line + next line
						// filter mask (=1): only centre line --> better
	for (int32_t i = centre.y; i < centre.y + twoLines; i++)
	{
		for (int32_t j = 0; j < FFTFilterKernel.cols; j++)
		{
			if (j < centre.x - maskWidtHalf || j >= centre.x + maskWidtHalf)
			{
				// set mask to zero
				tmp.at<float>(i, j) = 0.0;
			}
		}
	}
	Mat toMerge[] = { tmp, tmp };
	merge(toMerge, 2, FFTFilterKernel);
}

uint64_t ProjectionPreprocessor::CalcFFTMinSize(uint64_t imgWidth, uint64_t imgHeight)
{
	uint64_t imgMaxExt = std::max(imgWidth, imgWidth);
	double expo = ceil(log2(static_cast<double>(imgMaxExt)));
	double length = pow(2, expo);
	return static_cast<uint64_t>(length + 0.5);
}

MSG_CODE ProjectionPreprocessor::FFTSinoStripeReductionFilter(float *VolMem)
{
	// create volume array from projection stack
	/////////////////////////////////////////////
	Array<float, 3> volume(VolMem, 
		shape(m_paramObj.projectionCnt, m_paramObj.imgY, m_paramObj.imgX), 
		neverDeleteData);

#ifdef _OPENMP
	omp_set_num_threads(m_paramObj.numberOfThreads);
#endif

	// create array which holds minimum values of every sinogram
	// is used to determine shift values is min. value in volume is < 0 (log)
	std::vector<double> minValArray(volume.extent(secondDim), 0.0);

	int i;
	PreprocParam paramObj(m_paramObj);
#ifdef _OPENMP
#pragma omp parallel for private(i) firstprivate(paramObj) shared(volume)
#endif
	for (i = 0; i <volume.extent(secondDim); i++)
	{
		// create array holding sinogram
		/////////////////////////////////
		const int32_t imgRows = volume.extent(firstRank);
		const int32_t imgCols = volume.extent(thirdDim);
		Array<float, 2> SinoSlice(imgRows, imgCols);

		// determine size of FFT image
		///////////////////////////////
		uint64_t SL_ROWS_OPT, SL_COLS_OPT;
		uint64_t SL_OPT = CalcFFTMinSize(imgRows, imgCols);
		SL_ROWS_OPT = SL_COLS_OPT = SL_OPT * paramObj.paddMulti;

		// fourier image
		//////////////////
		Mat paddImg;		
		Mat complexImg, dft_Filter, filterOutput;
		Mat imgPlanes[2];

		// create sinograms by reslicing projection stack
		//////////////////////////////////////////////////
		SinoSlice = volume(blitz::Range::all(), i, blitz::Range::all());


		// setup Mat FFT sinogram using array data
		///////////////////////////////////////////
		Mat sinoImg(imgRows, imgCols, CV_32F, SinoSlice.data());
		// create complex padded image for FFT
		copyMakeBorder(sinoImg, paddImg, 
			0, SL_ROWS_OPT - sinoImg.rows, 
			0, SL_COLS_OPT - sinoImg.cols, 
			BORDER_CONSTANT, Scalar::all(0));
		imgPlanes[0] = Mat::zeros(paddImg.size(), CV_32F);
		imgPlanes[0] = paddImg;
		imgPlanes[1] = Mat::zeros(paddImg.size(), CV_32F);
		merge(imgPlanes, 2, complexImg);

		// do DFT
		//////////
		dft(complexImg, complexImg);

		// create filter kernel with same size as complex image
		////////////////////////////////////////////////////////
		dft_Filter = complexImg.clone();
		// filter kernel is shifted to center
		CreateFFTFilterKernel(dft_Filter);

		// center spectrum
		ShiftFFT(complexImg);
		// apply filter by spectrum multiplication
		///////////////////////////////////////////
		mulSpectrums(complexImg, dft_Filter, complexImg, 0);
		ShiftFFT(complexImg);

		// do inverse FFT
		//////////////////
		idft(complexImg, complexImg);
		split(complexImg, imgPlanes);

		// phys. copy
		//////////////
		Mat imgIFFT(paramObj.projectionCnt, paramObj.imgX, CV_32F, Scalar::all(0));
		imgPlanes[0].copyTo(imgIFFT);

		// scale image (FFT) by array size
		///////////////////////////////////
		float sz = imgIFFT.cols * imgIFFT.rows;
		imgIFFT = imgIFFT / sz;

		// crop image to original size (not padded)
		////////////////////////////////////////////
		Mat cropSinoImg(imgIFFT, Rect(0, 0, paramObj.imgX, paramObj.projectionCnt));
		//Mat resultImg(paramObj.projectionCnt, paramObj.imgX, CV_32F, Scalar::all(0.0));
		cropSinoImg.copyTo(sinoImg);

		// determine minmal value in sinogram
		//////////////////////////////////////
		double minVal;
		minMaxLoc(sinoImg, &minVal);
		minValArray[i] = minVal;

		// copy back corrected sinograms to array data
		///////////////////////////////////////////////
		memcpy((char*)SinoSlice.data(), (char*)sinoImg.data, paramObj.projectionCnt*paramObj.imgX*sizeof(float));
		volume(blitz::Range::all(), i, blitz::Range::all()) = SinoSlice;

		int num;
#ifdef _OPENMP
		if ((num = omp_get_thread_num()) == 0)
		{
			std::printf("==> %4d slices of %4d processed\r", i*omp_get_num_threads(), volume.extent(secondDim));
		}
#endif
	}
	std::printf("\n");
	std::printf("Determine minimal value ... ");
	double minimal_value = *min_element(minValArray.begin(), minValArray.end());
	std::printf("done\n");
	printf("Minimal value in array is: %f\n", minimal_value);
	if (minimal_value <= 0)
	{
		minimal_value = minimal_value + minimal_value / 1000.0; // increase min val by 0.1%
		printf("Increase volume values by: %f ...  ", std::fabs((float)minimal_value));
		volume = volume + std::fabs((float)minimal_value);
	}
	else
	{
		printf("Nothing to do ... ");
	}
	printf(" done. \n\n");

	// copy data back
	//////////////////
	uint64_t memSize = paramObj.imgX * paramObj.imgY * paramObj.projectionCnt * sizeof(float);
	memcpy(&VolMem[0], volume.data(), memSize);

	return IS_OK;
}

Mat ProjectionPreprocessor::GetProjectionsSumImage(float *VolMem)
{
	// handle only 32 bit float images
	///////////////////////////////////
	// create/allocate matrix
	Mat tmp = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);

	// one projection
	uint64_t imgSz = m_paramObj.imgY * m_paramObj.imgX;

	for (uint64_t i = 0; i < m_paramObj.projectionCnt; i++)
	{
		uint64_t offset = imgSz*i;
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		m_projSumImage = m_projSumImage + tmp;
	}
#ifdef _RUN_TESTS
	ofstream fSum("sum_1024x1024.raw", ios::binary);
	fSum.write((char*)m_projSumImage.data, imgSz*sizeof(float));
	fSum.close();
#endif
	return m_projSumImage;
}

MSG_CODE ProjectionPreprocessor::SegmentForOutliers(Mat &binOutlierImage)
{
	Mat medianImage = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);

	medianBlur(m_projSumImage, medianImage, m_medianMaskSize);
	absdiff(m_projSumImage, medianImage, binOutlierImage);

	// calculate z-score
	/////////////////////
	Scalar meanVal;
	Scalar stddevVal;
	meanStdDev(binOutlierImage, meanVal, stddevVal);
	double mean_s = meanVal.val[0];
	double stddev_s = stddevVal.val[0];
	binOutlierImage = (binOutlierImage - mean_s) / stddev_s;

	// to catch only outliers sigma should be > 5*Z-score
	///////////////////////////////////////////////////////
	double sigma = m_paramObj.sigmaOutlier;
	// do binary segmentation
	threshold(binOutlierImage, binOutlierImage, sigma, 1.0, THRESH_BINARY);

	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::FindOutliers(Mat binOutlierImage, vector<Vec2i> &outlierPixelList)
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
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::RingArtefactReplaceByMedian9(Mat &projection, Vec2i &pixCoord)
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
		cv::sort(filterVec, filterVec, CV_SORT_ASCENDING);
		// take value 4 and 5 to calc. median from mean of both, because of even value list (len=8)
		float medianVal = (filterVec.at<float>(3) + filterVec.at<float>(4)) / 2.0f;
		// replace central pixel
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = medianVal;
	}
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::RingArtefactReplaceByMean9(Mat &projection, Vec2i &pixCoord)
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
		cv::sort(filterVec, filterVec, CV_SORT_ASCENDING);
		cv::Mat mat = filterVec.colRange(0, 7);
		float meanVal = cv::mean(mat).val[0];
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = meanVal;
	}
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::RingArtefactReplaceByMean13(Mat &projection, Vec2i &pixCoord)
{
	cv::Mat filterVec(1, 13, CV_32F);
	float val, val0;
	Vec2i imageDim(projection.rows, projection.cols);
	if (pixCoord.val[0] > 1 && pixCoord.val[0] < imageDim.val[0] - 3 &&
		pixCoord.val[1] > 1 && pixCoord.val[1] < imageDim.val[1] - 3)
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

		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1]); // (-2, 0)
		filterVec.at<float>(8) = val;
		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1]); // ( 2, 0)
		filterVec.at<float>(9) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] + 2); // ( 0, 2)
		filterVec.at<float>(10) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] - 2); // ( 0, -2)
		filterVec.at<float>(11) = val;

		cv::sort(filterVec, filterVec, CV_SORT_ASCENDING);
		cv::Mat mat = filterVec.colRange(0, 12);
		//float medianVal = (filterVec.at<float>(5) + filterVec.at<float>(6)) / 2.0f;
		//projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = medianVal;
		float meanVal = cv::mean(filterVec).val[0];
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = meanVal;
	}
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::RingArtefactReplaceByMean24(Mat &projection, Vec2i &pixCoord)
{
	cv::Mat filterVec(1, 24, CV_32F);
	float val, val0;
	Vec2i imageDim(projection.rows, projection.cols);
	if (pixCoord.val[0] > 1 && pixCoord.val[0] < imageDim.val[0] - 3 &&
		pixCoord.val[1] > 1 && pixCoord.val[1] < imageDim.val[1] - 3)
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

		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1] - 2); // (-2, -2)
		filterVec.at<float>(8) = val;
		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1] - 1); // (-2, -1)
		filterVec.at<float>(9) = val;
		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1]); // (-2, 0)
		filterVec.at<float>(10) = val;
		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1] + 1); // (-2, 1)
		filterVec.at<float>(11) = val;
		val = projection.at<float>(pixCoord.val[0] - 2, pixCoord.val[1] + 2); // (-2, 2)
		filterVec.at<float>(12) = val;
		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] - 2); // (-1, -2)
		filterVec.at<float>(13) = val;
		val = projection.at<float>(pixCoord.val[0] - 0, pixCoord.val[1] - 2); // (0, -2)
		filterVec.at<float>(14) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] - 2); // (1, -2)
		filterVec.at<float>(15) = val;
		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1] - 2); // (2, -2)
		filterVec.at<float>(16) = val;

		val = projection.at<float>(pixCoord.val[0] - 1, pixCoord.val[1] + 2); // (-1, 2)
		filterVec.at<float>(17) = val;
		val = projection.at<float>(pixCoord.val[0], pixCoord.val[1] + 2); // (0, 2)
		filterVec.at<float>(18) = val;
		val = projection.at<float>(pixCoord.val[0] + 1, pixCoord.val[1] + 2); // (1, 2)
		filterVec.at<float>(19) = val;
		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1] + 2); // (2, 2)
		filterVec.at<float>(20) = val;

		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1] - 2); // (2, -1)
		filterVec.at<float>(20) = val;
		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1]); // (2, 0)
		filterVec.at<float>(20) = val;
		val = projection.at<float>(pixCoord.val[0] + 2, pixCoord.val[1] + 1); // (2, 1)
		filterVec.at<float>(20) = val;

		cv::sort(filterVec, filterVec, CV_SORT_ASCENDING);
		cv::Mat mat = filterVec.colRange(0, 23);
		float meanVal = cv::mean(filterVec).val[0];
		projection.at<float>(pixCoord.val[0], pixCoord.val[1]) = meanVal;
	}
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::ApplyOutlierReductionFilter(float *VolMem,
	vector<Vec2i> &outlierPixelList)
{
	Mat tmp = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);

	// one projection
	uint64_t imgSz = m_paramObj.imgY * m_paramObj.imgX;
#ifdef _RUN_TESTS
	//uint64_t sz = m_paramObj.imgY * m_paramObj.imgX * sizeof(float) * m_paramObj.projectionCnt;
	//ofstream fbefore("before_1024x1024x721.raw", ios::binary);
	//fbefore.write((char*)&VolMem[0], sz);
	//fbefore.close();
#endif

	for (uint64_t i = 0; i < m_paramObj.projectionCnt; i++)
	{
		uint64_t offset = imgSz*i;
		// copy data
		memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
		for (int k = 0; k < outlierPixelList.size(); k++)
		{
			RingArtefactReplaceByMean9(tmp, outlierPixelList[k]);
		}
		// copy data back
		memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
	}
#ifdef _RUN_TESTS
	//ofstream fafter("after_1024x1024x721.raw", ios::binary);
	//fafter.write((char*)&VolMem[0], sz);
	//fafter.close();
#endif

	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::GetMeanFromFlatField(QString filename, float &meanVal)
{
	QByteArray bStr = filename.toUtf8();
	string filenameStr = bStr.data();
	// read one projection and check parameters
	////////////////////////////////////////////
	cv::Mat temp = imread(filenameStr, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	bool conv2float = false;
	if (temp.type() != CV_32F)
	{
		temp.convertTo(temp, CV_32F);
	}
	if (temp.rows != m_paramObj.imgY)
	{
		return ERR_WRONG_IMG_HEIGHT;
	}
	if (temp.cols != m_paramObj.imgX)
	{
		return ERR_WRONG_IMG_WIDTH;
	}
	meanVal = mean(temp).val[0];
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::NormalizeImages(float *VolMem)
{
	Mat tmp = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);
	Mat tmpInterm = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);
	// one projection
	uint64_t imgSz = m_paramObj.imgY * m_paramObj.imgX;
	// check if single image normalization should be applied
	if (m_paramObj.doNormalisation)
	{
		for (uint64_t i = 0; i < m_paramObj.projectionCnt; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));

			// get normalization window part of image
			Mat roi = tmp(Rect(m_paramObj.normWinPosX, m_paramObj.normWinPosY, 
				m_paramObj.normWinWidth, m_paramObj.normWinHeight));
			// for every projection cal. mean of normalization window
			Scalar meanVal = mean(roi);
			tmp = tmp + 0.01; // due to numerical errors --> rec. data min. val huge --> max. =0
#define _CHECK_VALUES
#undef _CHECK_VALUES
			tmp = tmp / (meanVal.val[0]); // --> num. problem
			log(tmp, tmpInterm);
			// avoid neg. values due to pow() function
			///////////////////////////////////////////
			//-ju-24-07-2015 do it only for beam hardening
			tmp = tmpInterm * (-1.0f);
			if (m_paramObj.doBeamHard)
			{
				tmp = tmpInterm * (-1.0f) + 1.; //-ju-24-07-2015 correction see above
				// muss groesser 0 sein!!!
				pow(tmp, m_paramObj.beamHardeningCoeff, tmpInterm);
#ifdef _CHECK_VALUES
				double minv, maxv;
				minMaxLoc(tmpInterm, &minv, &maxv);
				printf("tmpI-> i:%3d min value=%f max value=%f\n", i + 1, minv, maxv);
				double minv_, maxv_;
				minMaxLoc(tmp, &minv_, &maxv_);
				printf("tmp -> i:%3d min value=%f max value=%f\n", i + 1, minv_, maxv_);
#endif // _CHECK_VALUES
				tmp = tmp + tmpInterm;
			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}

	}
	else
	{
		// load flat image -> mean of flat -> done once
		// check directory path and add  >> / << if necessary
		///////////////////////////////////////////////
		QString projectionPath = m_paramObj.inputDir;
		QChar end = projectionPath[projectionPath.size() - 1];
		if (end != QChar('/') || end != QChar('\\'))
		{
			projectionPath += QChar('/');
		}
		projectionPath += m_paramObj.flatFile;
		float mea;
		GetMeanFromFlatField(projectionPath, mea);
		for (uint64_t i = 0; i < m_paramObj.projectionCnt; i++)
		{
			uint64_t offset = imgSz*i;
			// copy data
			memcpy(tmp.data, &VolMem[offset], imgSz*sizeof(float));
			tmp = tmp + 0.01; // due to numerical errors --> rec. data min. val huge --> max. =0
			tmp = tmp / mea;
			log(tmp, tmpInterm);
			// avoid neg. values due to pow() function
			///////////////////////////////////////////
			tmp = tmpInterm * (-1.0f) + 1.;
			if (m_paramObj.doBeamHard)
			{
				pow(tmp, m_paramObj.beamHardeningCoeff, tmpInterm);
#ifdef _CHECK_VALUES
				double minv, maxv;
				minMaxLoc(tmpInterm, &minv, &maxv);
				printf("tmpI-> i:%3d min value=%f max value=%f\n", i + 1, minv, maxv);
				double minv_, maxv_;
				minMaxLoc(tmp, &minv_, &maxv_);
				printf("tmp -> i:%3d min value=%f max value=%f\n", i + 1, minv_, maxv_);
#endif // _CHECK_VALUES
				tmp = tmp + tmpInterm;
			}
			// copy data back
			memcpy(&VolMem[offset], tmp.data, imgSz*sizeof(float));
		}
		//printf("\n");
	}
	return IS_OK;
}

MSG_CODE ProjectionPreprocessor::RunPrepocessor()
{
	MSG_CODE ret;
	QString retMsg;

	// do memory allocation
	////////////////////////
	IOMemoryHandler ioHNDObj(m_paramObj);
	ret = ioHNDObj.AllocProjectionStack(retMsg);
	if (ret != IS_OK)
	{
#ifdef _RUN_TESTS
		char buffer[256];
		QByteArray bStr = retMsg.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Error! message: >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
#endif
		return ret;
	}

	// load projections
	////////////////////
	ret = ioHNDObj.LoadProjectionsToMemory(retMsg);
	if (ret != IS_OK)return ret;

	clock_t t;
	t = clock();
	// process filters
	///////////////////
	if (m_paramObj.doFFT)
	{
		FFTSinoStripeReductionFilter(ioHNDObj.GetStackPTR());
	}
	if (m_paramObj.doMedian)
	{
		printf("\n ==> calculate projection Sum ...");
		GetProjectionsSumImage(ioHNDObj.GetStackPTR());
		printf(" done\n\n");

		Mat outlierImage = Mat::zeros(m_paramObj.imgY, m_paramObj.imgX, CV_32F);
		SegmentForOutliers(outlierImage);
#ifdef _RUN_TESTS
		uint64_t sz = m_paramObj.imgY * m_paramObj.imgX * sizeof(float);
		ofstream fOutL("outlier_1024x1024.raw", ios::binary);
		fOutL.write((char*)outlierImage.data, sz);
		fOutL.close();
#endif
		vector<Vec2i> outlierPixelList;
		FindOutliers(outlierImage, outlierPixelList);
		printf(" ==> apply outlier filter ...");
		ApplyOutlierReductionFilter(ioHNDObj.GetStackPTR(), outlierPixelList);
		printf(" done\n\n");
	}
	printf(" ==> normalize projections ...");
	NormalizeImages(ioHNDObj.GetStackPTR());
	t = clock() - t;
	std::printf(" finished.\n\n");
	std::printf("\n==> Correction process time %f seconds\n\n", ((float)t) / CLOCKS_PER_SEC);

	// save sinograms
	//////////////////
	ioHNDObj.SaveProjections(ioHNDObj.GetStackPTR());
#ifdef _RUN_TESTS
	//uint64_t sz = m_paramObj.imgY * m_paramObj.imgX * sizeof(float) * m_paramObj.projectionCnt;
	//printf("Write final image stack ...");
	//ofstream fafter("F:/Data/test/finished_1024x1024x721.raw", ios::binary);
	//fafter.write((char*)ioHNDObj.GetStackPTR(), sz);
	//fafter.close();
	//printf("\n");
#endif

	ioHNDObj.DeAllocProjectionStack();
	return IS_OK;
}