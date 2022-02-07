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
//#include <cutil_inline.h>
#include <ctime>

using namespace std;

// reconstruction stack height must be a multiple of MAP
////////////////////////////////////////////////////////
#define MAP 8
#define STREAM_SIZE 4
#define PI 3.1415927f
#define CORR_TERM 0.5f

/*-ju-02-02-2022 migration from texture references to texture objects
texture<float, cudaTextureType3D>  texSino;
texture<float,cudaTextureType2DLayered> texSinoLay;
*/

typedef struct
{
	float x;
	float y;
}Point;

typedef struct
{
	float x;
	float y;
	float z;
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

// max. number of projections
#define MAX_PROJ_NUM 2000
__constant__ float radsConst[MAX_PROJ_NUM];


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
	float px = __fdividef((dso*rx),denominator);
	float py = __fdividef((dso*ry),denominator);

	// Shift to pixel coordinates (0,0) upper left corner.
	// Cuda texture using middle of pixel => + CORR_TERM  
	ptInterpol.x=fdkConst.offsetX + CORR_TERM - px;
	ptInterpol.y=fdkConst.offsetY + CORR_TERM - py;

    // calculate weight of voxel
	weight = __fdividef((dso*dso),(denominator*denominator));
}

/////////////////////////////////////////////////////////////////////////////
//-ju-03-Nov-2016 more accurate (not hardware based) bi-linear interpolation
/////////////////////////////////////////////////////////////////////////////
__forceinline__  __device__ float tex2DLayeredHighPrec(cudaTextureObject_t tex,
	const float &x_in, const float &y_in, const int layer)
{
	const int    ix = floor(x_in);
	const int    iy = floor(y_in);
	const float x = x_in - ix;
	const float y = y_in - iy;

	const float v00 = tex2DLayered<float>(tex, ix, iy, layer);
	const float v10 = tex2DLayered<float>(tex, ix + 1, iy, layer);
	const float v11 = tex2DLayered<float>(tex, ix + 1, iy + 1, layer);
	const float v01 = tex2DLayered<float>(tex, ix, iy + 1, layer);

	//r1 = x * v10 + (-v00 * x + v00); // --> __fmaf_rn(a,d10.x,__fmaf_rn(-d00.x,a,d00.x)) ju  
	//r2 = x * v11 + (-v01 * x + v01);
	const float r1 = __fmaf_rn(x, v10, __fmaf_rn(-v00, x, v00));
	const float r2 = __fmaf_rn(x, v11, __fmaf_rn(-v01, x, v01));

	//return (y * r2 + (-r1 * y + r1));
	return __fmaf_rn(y, r2, __fmaf_rn(-r1, y, r1));
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////
// Reconstruction of a 3D-window
// Standard backprojection kernel
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
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
							   cudaTextureObject_t tex3DLayObj) //-ju-0202-2022 texture object
{
	//-ju-09-Dec-2015
	float vst[MAP];
	for (int i = 0; i < MAP; i++)
	{
		vst[i] = 0.0f;
	}
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;

	float phi;
	vox.x = (float)x + 0.5f; vox.y = (float)y_c  + 0.5f; vox.z = (float)z + 0.5f;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
    float discr = sqrtf((x-volWidth_loc/2.0f)*(x-volWidth_loc/2.0f) + (z-volWidth_loc/2.0f)*(z-volWidth_loc/2.0f)); 
	if(x < volWidth_loc && z < volDepth_loc && discr < volWidth_loc/2.0f )
	{
		float l_weight = 0.0f;
		for(int i=0; i<fdkConst.projProcSize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);

			//-ju-08-Dec-2015
			for (int k = 0; k < MAP; k++)
			{
				GetInterpolationPoint(vox, interpolPoint, phi, l_weight, winOrigX, winOrigY, winOrigZ);
				vst[k] += tex2DLayered<float>(tex3DLayObj,interpolPoint.x+xOffset_loc,interpolPoint.y+yOffset_loc,i)*l_weight;
				vox.y = vox.y + 1.0f;
			}
			vox.y = (float)y_c + 0.5f;
		}
		for (int k = 0; k < MAP; k++)
		{
			d_backProj[x + z*volWidth + k*volWidth*volDepth] += vst[k];
		};
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// reconstruction with 3D-window and none equal sized projection blocks (with remainder)
// kernel 1.2
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
								 cudaTextureObject_t tex3DLayObj) //-ju-0202-2022 texture object
{
	//-ju-09-Dec-2015
	float vst[MAP];
	for (int i = 0; i < MAP; i++)
	{
		vst[i] = 0.0f;
	}
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;

	float phi;
	vox.x = (float)x + 0.5f; vox.y = (float)y_c + 0.5f; vox.z = (float)z + 0.5f;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
	// effective true reconstruction circle
	float discr = sqrtf((x - volWidth_loc / 2.0f)*(x - volWidth_loc / 2.0f) + (z - volWidth_loc / 2.0f)*(z - volWidth_loc / 2.0f));
	if (x < volWidth_loc && z < volDepth_loc && discr < volWidth_loc / 2.0f)
	{
		float l_weight = 0.0f;
		for (int i = 0; i<cuProjBlocksize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);

			//-ju-08-Dec-2015
			for (int k = 0; k < MAP; k++)
			{
				GetInterpolationPoint(vox, interpolPoint, phi, l_weight, winOrigX, winOrigY, winOrigZ);
				vst[k] += tex2DLayered<float>(tex3DLayObj, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i)*l_weight;
				vox.y = vox.y + 1.0f;
			}
			vox.y = (float)y_c + 0.5f;

		}
		for (int k = 0; k < MAP; k++)
		{
			d_backProj[x + z*volWidth + k*volWidth*volDepth] += vst[k];
		};
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// reconstruction of a 3D-window
// -ju-03-Nov-2016 kernel for accurate bi-linear interpolation
///////////////////////////////////////////////////////////////////////////////////////////////
__global__ void fdk_kernel_3DW_HA(float *d_backProj, 
	int    y_c,           // current y-slice
	int    cuProjBlockIdx, // current projection block index to use
	int    volWidth,
	int	  volDepth,
	float  xOffset,
	float  yOffset,
	float  winOrigX,
	float  winOrigY,
	float  winOrigZ,
	cudaTextureObject_t tex3DLayObj) //-ju-0202-2022 texture object
{
	//-ju-09-Dec-2015
	float vst[MAP];
	for (int i = 0; i < MAP; i++)
	{
		vst[i] = 0.0f;
	}
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;

	float phi;
	vox.x = (float)x + 0.5f; vox.y = (float)y_c + 0.5f; vox.z = (float)z + 0.5f;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
	float discr = sqrtf((x - volWidth_loc / 2.0f)*(x - volWidth_loc / 2.0f) + (z - volWidth_loc / 2.0f)*(z - volWidth_loc / 2.0f));
	if (x < volWidth_loc && z < volDepth_loc && discr < volWidth_loc / 2.0f)
	{
		float l_weight = 0.0f;
		for (int i = 0; i<fdkConst.projProcSize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);

			//-ju-08-Dec-2015
			for (int k = 0; k < MAP; k++)
			{
				GetInterpolationPoint(vox, interpolPoint, phi, l_weight, winOrigX, winOrigY, winOrigZ);
				vst[k] += tex2DLayeredHighPrec(tex3DLayObj, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i)*l_weight;
				vox.y = vox.y + 1.0f;
			}
			vox.y = (float)y_c + 0.5f;
		}
		for (int k = 0; k < MAP; k++)
		{
			d_backProj[x + z*volWidth + k*volWidth*volDepth] += vst[k];
		};
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// reconstruction with 3D-window and none equal sized projection blocks (with remainder)
// -ju-03-Nov-2016 kernel for more accurate bi-linear interpolation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void fdk_kernel_3DW_R_HA(float *d_backProj,    // accumulated back projected slice
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
	cudaTextureObject_t tex3DLayObj) //-ju-02-02-2022 texture object
{
	//-ju-09-Dec-2015
	float vst[MAP];
	for (int i = 0; i < MAP; i++)
	{
		vst[i] = 0.0f;
	}
	// map from threadIdx/BlockIdx to pixel position
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int z = threadIdx.y + blockIdx.y * blockDim.y;

	Point interpolPoint;
	VolType vox;

	float phi;
	vox.x = (float)x + 0.5f; vox.y = (float)y_c + 0.5f; vox.z = (float)z + 0.5f;

	int volWidth_loc = volWidth;
	int volDepth_loc = volDepth;
	float xOffset_loc = xOffset;
	float yOffset_loc = yOffset;
	float discr = sqrtf((x - volWidth_loc / 2.0f)*(x - volWidth_loc / 2.0f) + (z - volWidth_loc / 2.0f)*(z - volWidth_loc / 2.0f));
	if (x < volWidth_loc && z < volDepth_loc && discr < volWidth_loc / 2.0f)
	{
		float l_weight = 0.0f;
		for (int i = 0; i<cuProjBlocksize; i++)
		{
			phi = fdkConst.angleIncr*(cuProjBlockIdx*fdkConst.projProcSize + i);

			//-ju-08-Dec-2015
			for (int k = 0; k < MAP; k++)
			{
				GetInterpolationPoint(vox, interpolPoint, phi, l_weight, winOrigX, winOrigY, winOrigZ);
				vst[k] += tex2DLayeredHighPrec(tex3DLayObj, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i)*l_weight;
				vox.y = vox.y + 1.0f;
			}
			vox.y = (float)y_c + 0.5f;

		}
		for (int k = 0; k < MAP; k++)
		{
			d_backProj[x + z*volWidth + k*volWidth*volDepth] += vst[k];
		};
	}
}

#endif // _RECON_FDK_KERNEL_H
