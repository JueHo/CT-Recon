/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef _DEFINITION_PUBLIC_H
#define _DEFINITION_PUBLIC_H

#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>
#include <cstdint>

//-12-Oct-2015
extern uint32_t g_cntCurrentTile;

enum ParamDataTypes
{
	_NULLTYPE = 0,
	_UCHAR8 = 101,
	_USHORT16 = 102,
	_UINT32 = 104,
	_REAL32 = 114,
};

enum FileType
{
	UNKNOWN = 0,
	TIFF = 1,
	TIF = 2,
	PNG = 3,
	JPG = 4,
	RAW = 5,
};


struct PRect
{
	uint64_t x;
	uint64_t y;
	uint64_t w;
	uint64_t h;
};

struct HelperFunctions
{
	static bool CreateDir(QString dir);
	static bool DirExist(QString dir);
	static double log2(double x);
};

//-todo- code to string translator
enum MSG_CODE
{
	// 1 - 99 is INFO
	///////////////
	INF_FILE_EXISTS = 10,
	INF_NOT_ENOUGH_MEMORY = 11,
	// 100 - 199 is WARNING
	WARN_CNT_STACK_INCONST = 100,
	// = 0 is OK
	//////////////
	IS_OK = 0,
	// < 0 is ERROR
	////////////////
	ERR_UNSPEC = -99,
	ERR_EMPTY_LIST = -100,
	ERR_FILE_TYPE_NOT_SUPP = -101,
	ERR_UNKNOWN = -1,
	ERR_CREATE_PARAM_FILE = -10,
	ERR_CREATE_DIR = -11,
	ERR_WRITE_PARAM_FILE = -12,
	ERR_READ_PARAM_FILE = -13,
	ERR_PARAM_FILE_NOT_EXISTS = -14,
	ERR_PARAM_ITEM = -15,
	ERR_MEM_ALLOC = -16,
	ERR_OPEN_SINOFILE = -17,
	// param errors -500 -> -600
	ERR_WRONG_IMG_HEIGHT = -500,
	ERR_WRONG_IMG_WIDTH = -501,
};

struct PreprocParam
{
	QString projectName;
	QString ownerName;
	QString creationDate;
	QString modificationDate;
	QString inputDir;
	QString outputDir;
	int32_t inDataType;
	int32_t outDataType;
	QString inFilePattern;
	QString outFilePattern;
	int32_t inFileType;
	int32_t outFileType;
	QString flatFile;
	QString darkFile;
	int32_t doMedian;
	int32_t doFFT;
	int32_t doBeamHard;
	int32_t doNormalisation;
	int32_t normWinWidth;
	int32_t normWinHeight;
	int32_t normWinPosX;
	int32_t normWinPosY;
	uint32_t paddMulti; // padding multiplicator of FFT image
	float sigmaOutlier;
	float beamHardeningCoeff;
	uint64_t imgX;
	uint64_t imgY;
	uint64_t projectionCnt;
	uint64_t tileHeight;
	uint64_t tileCnt;
	uint64_t numberOfThreads;
};

#endif // _DEFINITION_PUBLIC_H