/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>
#include "typesFDK.h"
#include <vector>
#include <map>
#include <cmath>

#define MBYTE(bytes) bytes/(1024*1024) 
#define KBYTE(bytes) bytes/(1024)


#define PRINT_BUILD 1
#define PRINT_COPYRIGHT 1

struct LANGUAGE_AND_CODE_PAGE {
  WORD language;
  WORD codePage;
} *translation;

using namespace std;

// local helper functions
//////////////////////////////////////////////////////////////////
inline size_t GetAvailablePhysMemory()
{
	size_t availPhysMem;
#if defined(_WIN64)
	MEMORYSTATUSEX memStatEx;
	memStatEx.dwLength = sizeof(memStatEx);
	GlobalMemoryStatusEx(&memStatEx);
	availPhysMem = memStatEx.ullAvailPhys;
#else
	MEMORYSTATUS memStat;
	memStat.dwLength = sizeof(memStat);
	GlobalMemoryStatus(&memStat);
	availPhysMem = memStat.dwAvailPhys;
#endif
	return availPhysMem;
}



// global functions
//////////////////////////////////////////////////////////////////

void CalcParallelProcParam(const BackProjParam &backProjParam)
{
	size_t mem = GetAvailablePhysMemory();

	// equations 
	//
	// y = cz			; ratio between z (diagonal) and y dimension of voxel volume
	//					; straight line with neg. slope through origin
	//
	// y = az + b		; straight line from x-Ray source to detector with slope a, 
	//					; b axis intercept, axis centre in rotation centre
	//
	// z = b / (c - a)
	// and
	// y = cb/(c-a)

	// calc. constants a,b and c
	float yp = backProjParam.volY/2.0f;
	float zp = sqrt(2.0f)*backProjParam.volZ/2.0f;
	// ratio between y and z-diagonal
	float c = -yp/zp; // zp in neg. z direction
	// slope of straight line is image height on detector divided 
	// through distance source-detector in mm
	float imgHeightDet = backProjParam.imgHeight/2.0f*backProjParam.pixSize;
	float a = imgHeightDet/backProjParam.dsd;
	// axis intercept; use theorem on intersecting lines to calc.
	float b = backProjParam.imgHeight/2.0f*backProjParam.pixSize*backProjParam.dso/backProjParam.dsd;
	float z = b/(c-a);
	float y = c*b/(c-a);
	// magnification for voxel
	float m = backProjParam.imgHeight/2.0f*backProjParam.pixSize/y;
	float zz = backProjParam.dso+fabs(z);
	float py = y*backProjParam.dsd/zz;
	py /= backProjParam.pixSize;
}

void PrintVersion(char* executable[])
{
    LPDWORD lpdwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSizeA(executable[0], lpdwHandle);
	cout << "----------------------------------------------------------------------------------------------------\n-\n";
	if(!dwSize)
	{
		cout << "-  No Version Information for >> " << executable[0] << " << available\n";
		cout << "-\n----------------------------------------------------------------------------------------------------\n";
		cout.flush();
		return;
	}

	BYTE *pVersionInfo = new BYTE[dwSize];
	
	BOOL r = GetFileVersionInfoA(executable[0],
								 0,	// ignore parameter
								 dwSize, 
								 pVersionInfo);
	if(!r)
	{
		cout << "-  Error getting version information!\n";
		cout << "-\n----------------------------------------------------------------------------------------------------\n";
		cout.flush();
		delete [] pVersionInfo;
		return;
	}

	// read language and code page info
    UINT     len;
    r = VerQueryValueA(pVersionInfo, 
					   "\\VarFileInfo\\Translation",
					   (LPVOID*)&translation,
					   &len);

	// comments
    char stringInfo[256];
    sprintf_s(stringInfo,255,
		      "\\StringFileInfo\\%04x%04x\\Comments", 
			  translation->language, translation->codePage);
    char *comment;
    r = VerQueryValueA(pVersionInfo, stringInfo, (LPVOID *)&comment ,&len);
	if(r)
	{
		string comment_str = reinterpret_cast<char*>(comment);
		cout << "-  " << comment_str << endl;
		cout.flush();
	}

	// copyright
    sprintf_s(stringInfo,255,
		      "\\StringFileInfo\\%04x%04x\\LegalCopyright", 
			  translation->language, translation->codePage);
    char *copyright;
    r = VerQueryValueA(pVersionInfo, stringInfo, (LPVOID *)&copyright ,&len);
	if(r)
	{
		string copyright_str = reinterpret_cast<char*>(copyright);
	#if PRINT_COPYRIGHT == 1
		cout << "-  " << copyright_str << endl;
		cout.flush();
	#endif
	}

	// version key/values
	VS_FIXEDFILEINFO *pFfi;
	r = VerQueryValueA(pVersionInfo , "\\" , (LPVOID *)&pFfi , &len );
	
	if(r)
	{
		DWORD dwBuildNumMS = pFfi->dwFileVersionMS;
		DWORD dwBuildNumLS = pFfi->dwFileVersionLS;

		DWORD dwLeftMost    = HIWORD(dwBuildNumMS);
		DWORD dwSecondLeft  = LOWORD(dwBuildNumMS);
		DWORD dwSecondRight = HIWORD(dwBuildNumLS);
		DWORD dwRightMost   = LOWORD(dwBuildNumLS);
		
	#if PRINT_BUILD == 1
		printf("-  Build: %d.%d.%d.%d\n", dwLeftMost, dwSecondLeft,
										 dwSecondRight, dwRightMost);
		cout.flush();
	#endif
	}
	delete [] pVersionInfo;

	cout << "-\n----------------------------------------------------------------------------------------------------\n";
	cout.flush();
}

