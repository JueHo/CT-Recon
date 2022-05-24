/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _RECON_FDK_KERNEL_H
#define _RECON_FDK_KERNEL_H

#include "cuda.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <ctime>

using namespace std;

#define PIX_MIDTH 0.5f
#define PI 3.1415927f
#define CORR_TERM 0.5f


/* use texure objects; texture refrences have been declared deprecated starting from Cuda 11.0
texture<float, cudaTextureType3D>  texSino;
texture<float,cudaTextureType2DLayered> texSinoLay;
//-ju-15-Mar-2011 texture for cos and sin
texture<float,1,cudaReadModeElementType> sinusTexRef;
texture<float,1,cudaReadModeElementType> cosinusTexRef;
*/

typedef struct
{
	float x;
	float y;
}Point;

typedef struct
{
	int x;
	int y;
	int z;
}VolType;

typedef struct
{
	int   imgWidth;
	int   imgHeight;
	int   numProj;
	int	  projProcSize;
	float angleIncr;
	float voxSize;
	float distSrcObj;
	float offsetX;
	float offsetY;

} FDK_Constants;

__constant__ FDK_Constants fdkConst;

////////////////////////////////////////////////////////
// Calculate interpolation point on projection and
// weighting in voxel volume regarding its position
////////////////////////////////////////////////////////
__forceinline__  __device__ void GetInterpolationPoint(const VolType &voxel, Point &ptInterpol, 
	const float &phi, float &weight, float &winOrigX, float &winOrigY, float &winOrigZ)
{
	float x, ry, z, dso, voxSz;
	dso   = fdkConst.distSrcObj;
	voxSz = fdkConst.voxSize;

	// translate co-ordinates from origin left upper edge to centre of image
	/////////////////////////////////////////////////////////////////////////
	x  = voxel.x - fdkConst.offsetX + winOrigX;	
	ry = fdkConst.offsetY - voxel.y - winOrigY;	
	z  = voxel.z - fdkConst.offsetX + winOrigZ;

	float co, si;
	__sincosf(phi,&si,&co);
	float rx = __fmaf_rn(x,co,z*si);
	float rz = __fmaf_rn(-x,si,z*co);


	float denominator =  __fmaf_rn(-rz,voxSz,dso);

	// pixel coordinates
	float px = __fmul_rn(dso,rx)/denominator;
	float py = __fmul_rn(dso,ry)/denominator;

	//-ju-07-Jan-2013 add corr. term to be consistent with CUDA tex. interpolation 
	ptInterpol.x=fdkConst.offsetX + CORR_TERM - px;
	ptInterpol.y=fdkConst.offsetY + CORR_TERM - py;

	weight = (dso*dso)/(denominator*denominator);
}


// Reconstruction of a 3D-window
// Standard backprojection kernel
__global__ void fdk_kernel_3DW(float *d_backProj,    // accumulated back projected slice
							   int    y_c,           // current y-slice
							   int    cuProjBlockIdx, // current projection block index to use
							   int    volWidth,
							   int	  volDepth,
							   float  xOffset,
							   float  yOffset,
							   float  winOrigX, 
							   float  winOrigY, 
							   float  winOrigZ,
			      			   cudaTextureObject_t tex3DLayObj) //-ju-24-May-2022 add texture object
{
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;


	float phi;

	vox.x = x; vox.y = y_c; vox.z = z;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
	if(x < volWidth_loc && z < volDepth_loc)
	{
		float l_back   = 0.0f;
		float l_weight = 0.0f;
		for(int i=0; i<fdkConst.projProcSize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);

			float _winOrigX = winOrigX - xOffset_loc;
			float _winOrigY = winOrigY - yOffset_loc;
			GetInterpolationPoint(vox, interpolPoint, phi, l_weight, _winOrigX, _winOrigY, winOrigZ);

			//-ju-24-May-2022 replace texture reference by texture object
			l_back += tex2DLayered<float>(tex3DLayObj, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i)*l_weight;


		}
		d_backProj[x + z*volWidth] += l_back;
	}
}

// reconstruction with 3D-window and none equal sized projection blocks (with remainder)
//////////////////////////////////////////////////////////////////////////////////////////
__global__ void fdk_kernel_3DW_R(float *d_backProj,    // accumulated back projected slice
							     int    y_c,           // current y-slice
							     int    cuProjBlockIdx, // current projection block index to use
							     int	cuProjBlocksize,
							     int    volWidth,
							     int	volDepth,
							     float  xOffset,
							     float  yOffset,
							     float  winOrigX, 
							     float  winOrigY, 
							     float  winOrigZ,
			      				 cudaTextureObject_t tex3DLayObj) //-ju-24-May-2022 add texture object) 
{
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;

	float phi;

	vox.x = x; vox.y = y_c; vox.z = z;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
	if(x < volWidth_loc && z < volDepth_loc)
	{
		//-ju- local variable
		float l_back   = 0.0f;
		float l_weight = 0.0f;
		for(int i=0; i<cuProjBlocksize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);
			GetInterpolationPoint(vox, interpolPoint, phi, l_weight, winOrigX, winOrigY, winOrigZ);

			//-ju-24-May-2022 replace texture reference by texture object
			l_back += tex2DLayered<float>(tex3DLayObj, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i)*l_weight;

		}
		d_backProj[x + z*volWidth] += l_back;
	}
}


#endif // _RECON_FDK_KERNEL_H
