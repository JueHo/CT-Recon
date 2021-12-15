/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/
/**********************************************************
*
* $Log: graphicCardProp.cu $
* Revision 1.2  2010/12/21 06:47:32  Hofmann
* remove not used keywords
*
* Revision 1.1  2010/12/15 09:52:49  Hofmann
* Initial revision
*
**********************************************************/
#include "typesFDK.h"
#include "recon.h"
#include <vector>
#include <iostream>

using namespace std;

extern "C"
void GetGraphicCardProp(vector<GraphicCardProp> &gpuPropV)
{
	// get graphic card property
	////////////////////////////
	// get number of available graphic devices
	const unsigned MB = 1024*1024;
	int cnt;
	cudaDeviceProp prop;
	HANDLE_ERROR(cudaGetDeviceCount(&cnt));
	for(int i = 0; i < cnt; i++)
	{
		HANDLE_ERROR(cudaGetDeviceProperties(&prop,i));
		GraphicCardProp gpuProp;
        /*
        gpuProp.name = prop.name;

        //cout << "\n\n ---->>>> " << prop.name << "\n\n";

        basic_string <char>::size_type indexCh;
        const char *cstr = "Tesla";
        indexCh = gpuProp.name.find(cstr,0);
        if (indexCh != string::npos)

        if(prop.tccDriver) gpuProp.tccDriver = true;
        */
		gpuProp.globalMem		= prop.totalGlobalMem/MB;
		gpuProp.maxThrPerBlk	= prop.maxThreadsPerBlock;
		gpuProp.majorRev		= prop.major;
		gpuProp.minorRev		= prop.minor;
		gpuProp.multProcCnt		= prop.multiProcessorCount ;
		gpuPropV.push_back(gpuProp);
	}
}