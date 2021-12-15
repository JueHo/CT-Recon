#include "io_memory_handler.h"

using namespace std;
using namespace cv;
using namespace blitz;

MSG_CODE IOMemoryHandler::AllocProjectionStack(QString &msgStr)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	uint64_t memAvail = status.ullAvailPhys;

	//-ju- calulate memory usage for projection stack data type float
	uint64_t arraySize = m_parameter.imgX * m_parameter.imgY * m_parameter.projectionCnt;
	// add 20% memory usage for ongoing calculations
	uint64_t memSize = (arraySize + arraySize / 5) * sizeof(float);

	if (memSize >= memAvail)
	{
		msgStr = QString("Not enough physical memory available");
		return INF_NOT_ENOUGH_MEMORY;
	}
	//-ju- alloc memory
	m_memoryStack = new float[arraySize];

	msgStr = QString("OK");
	return IS_OK;
}

void IOMemoryHandler::DeAllocProjectionStack()
{
	if (m_memoryStack != 0)
	{
		delete[] m_memoryStack;
		m_memoryStack = 0;
	}
}

IOMemoryHandler::~IOMemoryHandler()
{
	DeAllocProjectionStack();
}

// public member functions
///////////////////////////
//void IOMemoryHandler::LoadProjectionsToMemory(QMutex mtx, Ui::ProjectionPreProcessorClass ui)
//{
//	//for (int i = 0; i < 200; i++)
//	//{
//	//	QString msg;
//	//	msg.sprintf("Loop Nr.: %3d", i);
//	//	ui.plainTextEdit_MessagesOutput->appendPlainText(msg);
//	//	Sleep(500);
//	//	QMutexLocker locker(&mtx);
//	//}
//}

MSG_CODE IOMemoryHandler::LoadProjectionsToMemory(QString &msgStr)
{
	MSG_CODE code;
	if ((code = CreateProjectionFilesList()) != IS_OK)
	{
		return code;
	}
	// read files
	//////////////

	// check for file type
	// current: for input only tiff is supported
	//////////////////////////////////////////////
	if (m_parameter.inFileType != TIFF && m_parameter.inFileType != TIF)
	{
		msgStr = QString("File type current not supported");
		return ERR_FILE_TYPE_NOT_SUPP;
	}

	// check directory path and add  >> / << if necessary
	///////////////////////////////////////////////
	QString projectionPath = m_parameter.inputDir;
	QChar end = projectionPath[projectionPath.size() - 1];
	if (end != QChar('/') || end != QChar('\\'))
	{
		projectionPath += QChar('/');
	}
	QByteArray bStr =  projectionPath.toUtf8();
	string projectionPathStr = bStr.data();
	// read one projection and check parameters
	////////////////////////////////////////////
	bStr = m_projectionFileList[0].toUtf8();
	string projectionNameStr = bStr.data();
	string filePath = projectionPathStr + projectionNameStr;
	cv::Mat temp = imread(filePath, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
	bool conv2float = false;
	if (temp.type() != CV_32F)
	{
		conv2float = true;
	}
	if (temp.rows != m_parameter.imgY)
	{
		msgStr = QString("wrong projection height");
		return ERR_WRONG_IMG_HEIGHT;
	}
	if (temp.cols != m_parameter.imgX)
	{
		msgStr = QString("wrong projection width");
		return ERR_WRONG_IMG_WIDTH;
	}

	// read all files to memory
	////////////////////////////
#define _PRINT
#ifdef _PRINT
	printf("Load projections\n"
		"----------------\n");
#endif // _PRINT
	int i;
	for (i = 0; i < m_projectionFileList.count(); i++)
	{
		bStr = m_projectionFileList[i].toUtf8();
		string projectionNameStr = bStr.data();
		string filePath = projectionPathStr + projectionNameStr;
		cv::Mat tmp = imread(filePath, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_GRAYSCALE);
		// convert to float if necessary
		if (conv2float)
		{
			tmp.convertTo(tmp, CV_32F);
		}
		// make phys. copy
		Mat mat(tmp.rows, tmp.cols, tmp.type(), Scalar::all(0));
		tmp.copyTo(mat);
		uint64_t imgSz = tmp.rows*tmp.cols;
		uint64_t imgOffs = i*imgSz;
		// regard tiling -> not done yet !
		//////////////////////////////////
		memcpy(&m_memoryStack[imgOffs], tmp.ptr(0), imgSz*sizeof(float));
#ifdef _PRINT
		if (i % 10 == 0)
		{
			std::printf("\tload %4d projection of %4d\r", i+1, m_projectionFileList.count());
		}
#endif // _PRINT
	}
#ifdef _PRINT
	printf("\ndone\n");
#endif // _PRINT

	return IS_OK;
}

MSG_CODE IOMemoryHandler::SaveProjections(float *vol)
{
	// check for file type
	// current: for input only tiff is supported
	//////////////////////////////////////////////
	if (m_parameter.outFileType != RAW)
	{
		return ERR_FILE_TYPE_NOT_SUPP;
	}
	// check directory path and add  >> / << if necessary
	///////////////////////////////////////////////
	QString projectionPath = m_parameter.outputDir;
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
	QByteArray outNamePattern = m_parameter.outFilePattern.toUtf8();
	string outFileNamePatternStr = outNamePattern.data();
	projectionPathStr = projectionPathStr + outFileNamePatternStr;
	char fileNameBuffer[260];
	ofstream sinogramFile;
	uint64_t sz = m_parameter.imgX * m_parameter.imgY;
	printf(" ==> write sinograms ...");
	for (uint64_t i = 0; i < m_parameter.projectionCnt; i++)
	{
		uint64_t offset = sz * i;
		sprintf_s(fileNameBuffer, "%s%04dx%04d_32F_%04d.raw", 
			projectionPathStr.c_str(), m_parameter.imgX, m_parameter.imgY, i+1);
		//printf("%s\n", fileNameBuffer);
		sinogramFile.open(fileNameBuffer, ios::binary);
		if (!sinogramFile.is_open())
		{
			return ERR_OPEN_SINOFILE;
		}
		sinogramFile.write((char*)&vol[offset], sz*sizeof(float));
		sinogramFile.close();
	}
	printf(" done\n");
	return IS_OK;
}

// private member functions
////////////////////////////
MSG_CODE IOMemoryHandler::CreateProjectionFilesList()
{
	QDir projections;
	projections.setPath(m_parameter.inputDir);
	QString filePattern = m_parameter.inFilePattern;
	filePattern += QString("*.");
	filePattern += GetFileExtension();
	projections.setNameFilters(QStringList() << filePattern);

	// check validity of projection stack
	//////////////////////////////////////
	if (projections.entryList().empty()) return ERR_EMPTY_LIST;
	if (projections.entryList().size() != m_parameter.projectionCnt)return WARN_CNT_STACK_INCONST;

	m_projectionFileList = projections.entryList();

	return IS_OK;
}

QString IOMemoryHandler::GetFileExtension()
{
	QString ext;
	switch (m_parameter.inFileType)
	{
	case TIFF:
		ext = QString("tiff");
		break;
	case TIF:
		ext = QString("tif");
		break;
	case PNG:
		ext = QString("png");
		break;
	case JPG:
		ext = QString("jpg");
		break;
	case RAW:
		ext = QString("raw");
		break;
	default:
		ext = QString("UNKNOWN");
		break;
	}
	return ext;
}