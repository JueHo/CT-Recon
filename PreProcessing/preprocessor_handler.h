#ifndef _PRE_PROCESSOR_HANDLER_H
#define _PRE_PROCESSOR_HANDLER_H

#include <windows.h> 
#include <fstream>
#include <cstdio>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>
#include <blitz/array.h>
#include <cstdint>
#include <ctime> 
#ifdef _OPENMP
#include <omp.h>
#endif


#include "definitions_public.h"

using namespace cv;
using namespace std;
using namespace blitz;


class PreprocParamHandler
{
public:
	PreprocParamHandler()
	{
		m_parameter.creationDate = "-nn-";
		m_parameter.darkFile = "-nn-";
		m_parameter.flatFile = "-nn-";
		m_parameter.doBeamHard = -1;
		m_parameter.doFFT = -1;
		m_parameter.doMedian = -1;
		m_parameter.doNormalisation = -1;
		m_parameter.imgX = 0;
		m_parameter.imgY = 0;
		m_parameter.inDataType = _NULLTYPE;
		m_parameter.inFilePattern = "-nn-";
		m_parameter.inFileType = UNKNOWN;
		m_parameter.inputDir = "-nn-";
		m_parameter.modificationDate = "-nn-";
		m_parameter.normWinHeight = -1;
		m_parameter.normWinWidth = -1;
		m_parameter.normWinPosX = -1;
		m_parameter.normWinPosY = -1;
		m_parameter.numberOfThreads = 0;
		m_parameter.outDataType = _NULLTYPE;
		m_parameter.outFilePattern = "-nn-";
		m_parameter.outFileType = UNKNOWN;
		m_parameter.outputDir = "-nn-";
		m_parameter.ownerName = "-nn-";
		m_parameter.paddMulti = 0;
		m_parameter.projectionCnt = 0;
		m_parameter.tileCnt = 0; //-ju->memory splitting
		m_parameter.tileHeight = 0;
		m_parameter.projectName = "-nn-";
		m_parameter.sigmaOutlier = -1.0f;
		m_parameter.beamHardeningCoeff = -1.0f;
	}
	// create default parameter file
	/////////////////////////////////
	void CreateParameterFile(QString filename, MSG_CODE &retCode, QString &msgStr);

	void SaveParameter(QString filename, MSG_CODE &retCode, QString &msgStr);
	void LoadParameter(QString filename, MSG_CODE &retCode, QString &msgStr);

	PreprocParam GetParameters()
	{
		return m_parameter;
	}

	QString GetInputDir();
	void SetInputDir(QString dir);
	QString GetOutputDir();
	void SetOutputDir(QString dir);
	ParamDataTypes GetInDataType();
	void SetInType(ParamDataTypes type);
	ParamDataTypes GetOutDataType();
	void SetOutType(ParamDataTypes type);
	QString GetInFilePattern();
	void SetInFilePattern(QString pattern);
	QString GetOutFilePattern();
	void SetOutFilePattern(QString pattern);

private:
	PreprocParam m_parameter;
	QString m_parameterFilename;
	MSG_CODE  m_msg;
};

#endif // _PRE_PROCESSOR_HANDLER_H