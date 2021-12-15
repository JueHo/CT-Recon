/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _RECON_H
#define _RECON_H

#include "plot_struct.h"

#include "typesFDK.h"
#include "cuda.h"
#include <cuda_runtime_api.h>
#include <vector>

extern "C" 
int runFDK(BackProjParam param, int devNo, float *minGray, float *maxGray, FILE *fpVol, PlotData *plData);

extern "C"
void GetGraphicCardProp(std::vector<GraphicCardProp> &gpuPropV);

extern "C"
void HandleError( cudaError_t err,const char *file,int line );

#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__ ))


#endif // _RECON_H