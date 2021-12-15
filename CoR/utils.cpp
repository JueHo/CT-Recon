/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>

#define PRINT_BUILD 1
#define PRINT_COPYRIGHT 1

struct LANGUAGE_AND_CODE_PAGE {
  WORD language;
  WORD codePage;
} *translation;

using namespace std;

void PrintVersion(char* executable[])
{
    LPDWORD lpdwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSizeA(executable[0], lpdwHandle);
	cout << "--------------------------------------------------------------------------------------------------------------\n-\n";
	if(!dwSize)
	{
		cout << "-  No Version Information for >> " << executable[0] << " << available\n";
		cout << "-\n--------------------------------------------------------------------------------------------------------------\n";
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
		cout << "-\n--------------------------------------------------------------------------------------------------------------\n";
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

	cout << "-\n--------------------------------------------------------------------------------------------------------------\n";
	cout.flush();
}
