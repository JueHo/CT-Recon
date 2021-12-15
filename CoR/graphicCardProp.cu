/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

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
  		gpuProp.globalMem		= prop.totalGlobalMem/MB;
		gpuProp.maxThrPerBlk	= prop.maxThreadsPerBlock;
		gpuProp.majorRev		= prop.major;
		gpuProp.minorRev		= prop.minor;
		gpuProp.multProcCnt		= prop.multiProcessorCount ;
		gpuPropV.push_back(gpuProp);
	}
}