/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

/**********************************************************
*
* $Log: typesFDK.h $
* Revision 1.2  2010/12/21 06:47:32  Hofmann
* remove not used keywords
*
* Revision 1.1  2010/12/15 09:52:49  Hofmann
* Initial revision
*
**********************************************************/
#ifndef _TYPES_FDK_H
#define _TYPES_FDK_H

#include <string>
#include <vector>

#define FILE_NUMBER_LEN 5

using namespace std;

struct BackProjParam
{
	string projectName;
	int   numProj;
	int   imgWidth;
	int   imgHeight;
	float shiftX;
	float shiftY;
	float pixSize;
	float wVolOrigX;
	float wVolOrigY;
	float wVolOrigZ;
	int	  volX;
	int	  volY;
	int	  volZ;
	float magnification;
	float dso;
	float dsd;
	int   binFac;
	bool  useVolWin;
	int   startIndex;
	float startAngle;
	string tomoDir;
	string sinoPreProcDir;
	string sinoLimPreProcDir;
	string fileList;
	string limFileList;
	string sinoName;
	string tomoName;
	string outDataType;
	int threadX;
	int threadY;
	int highAcc;
	size_t projectionChunkSize;
	size_t sliceChunkSize;
	int useFileList;
	int useLimAngle;
    int viewDirection; //-ju-15-Apr-2015 add
	vector<float> angleList;
	vector<string> sinoList;
	string sino32BlockFile;
	string tomoBlockFile;
	int sino32BlockUse;			
	int tomoBlockWrite;
	int convertBlockInternal;
	//-ju-17-June-2021 add tilt correction
	int applyTiltCorr;			
	double slopeTiltCorr;		
	double constTiltCorr;		
};

struct GraphicCardProp
{
	size_t globalMem;
	int majorRev;
	int minorRev;
	int maxThrPerBlk;
	int multProcCnt;
    //-ju-18-Nov-2013
    string name;
    bool tccDriver;
};

#endif // _TYPES_FDK_H