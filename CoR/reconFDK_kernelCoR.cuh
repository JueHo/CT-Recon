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



texture<float, cudaTextureType3D>  texSino;
texture<float,cudaTextureType2DLayered> texSinoLay;
//-ju-15-Mar-2011 texture for cos and sin
texture<float,1,cudaReadModeElementType> sinusTexRef;
texture<float,1,cudaReadModeElementType> cosinusTexRef;

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

// max. number of projections
#define MAX_PROJ_NUM 2000
__constant__ float radsConst[MAX_PROJ_NUM];

//-ju-14-Apr-2016 Higher precision bi-linear interpolation
/////////////////////////////////////////////////////////
__forceinline__  __device__ float tex2DLayeredHighPrec(texture<float, cudaTextureType2DLayered> tex,
	const float &x_in, const float &y_in, const int layer)
{
	const int    ix = floor(x_in);
	const int    iy = floor(y_in);
	const float x = x_in - ix;
	const float y = y_in - iy;

	const float v00 = tex2DLayered(tex, ix, iy, layer);
	const float v10 = tex2DLayered(tex, ix + 1, iy, layer);
	const float v11 = tex2DLayered(tex, ix + 1, iy + 1, layer);
	const float v01 = tex2DLayered(tex, ix, iy + 1, layer);

	//r1 = x * v10 + (-v00 * x + v00); // --> __fmaf_rn(a,d10.x,__fmaf_rn(-d00.x,a,d00.x)) ju  
	//r2 = x * v11 + (-v01 * x + v01);
	const float r1 = __fmaf_rn(x, v10, __fmaf_rn(-v00, x, v00));
	const float r2 = __fmaf_rn(x, v11, __fmaf_rn(-v01, x, v01));

	//return (y * r2 + (-r1 * y + r1));
	return __fmaf_rn(y, r2, __fmaf_rn(-r1, y, r1));
}




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

////// Get interpolation point
////
////__forceinline__  __device__ void GetInterpolationPoint(const VolType &voxel, Point &ptInterpol, const float &phi, float &weight)
////{
////	// Voraussetzung: Voxelgroesse = Pixelgroesse/Vergroesserung
////	// ==> 
////	float x, ry, z, dso, voxSz;
////	dso   = fdkConst.distSrcObj;
////	voxSz = fdkConst.voxSize;
////	// translate co-ordinates from origin left upper edge to centre of image
////	/////////////////////////////////////////////////////////////////////////
////
////
////	x = __fsub_rn(voxel.x,fdkConst.offsetX);
////	ry = fdkConst.offsetY - voxel.y;
////	z = __fsub_rn(voxel.z,fdkConst.offsetX);
////
////	float sptr, cptr;
////	__sincosf(phi,&sptr,&cptr);
////	float rx =  __fadd_rn(__fmul_rn(x,cptr),__fmul_rn(z,sptr));
////	float rz =  __fsub_rn(__fmul_rn(z,cptr),__fmul_rn(x,sptr));
////
////
////	float denominator = __fsub_rn(dso,rz*voxSz);
////
////
////	// in Projektionsebene vergroessern ==> bereits in Pixel-Koord.
////	float px = dso*rx/denominator;
////	float py = dso*ry/denominator;
////	// Pixel-Koordinaten (0,0) linke obere Ecke
////	//-ju-07-Jan-2013 add corr. term to be consistens with CUDA tex. interpolation
////	ptInterpol.x=fdkConst.offsetX + CORR_TERM - px;
////	ptInterpol.y=fdkConst.offsetY + CORR_TERM - py;
////
////	weight = dso*dso/(denominator*denominator);
////}
////
////__forceinline__  __device__ void GetInterpolationPoint(const VolType &voxel, Point &ptInterpol, const float &phi, const int &bin, float &weight)
////{
////	// Voraussetzung: Voxelgroesse = Pixelgroesse/Vergroesserung
////	// ==> 
////	float x, ry, z, dso, voxSz;
////	dso   = fdkConst.distSrcObj;
////	voxSz = fdkConst.voxSize;
////	// translate co-ordinates from origin left upper edge to centre of image
////	/////////////////////////////////////////////////////////////////////////
////	//-ju-23-Sep-2011 replacement fdkConst.volOffsetX by fdkConst.offsetX
////	//				  devide by bin
////	x  = voxel.x - fdkConst.offsetX/bin;
////	//x  = voxel.x - fdkConst.volOffsetX;
////	//-ju-23-Sep-2011 replacement fdkConst.volOffsetY by fdkConst.offsetY
////	//				  devide by bin
////	ry = fdkConst.offsetY/bin - voxel.y;
////	//ry = fdkConst.volOffsetY - voxel.y;
////	//-ju-23-Sep-2011 replacement fdkConst.volOffsetZ by fdkConst.offsetX
////	//				  devide by bin
////	//				  width = depth !
////	z  = voxel.z - fdkConst.offsetX/bin;
////	//z  = voxel.z - fdkConst.volOffsetZ;
////	//-ju-15-Mar-2011-->
////
////	float rx =  x * cosf(phi) + z * sinf(phi);
////	float rz = -x * sinf(phi) + z * cosf(phi);
////
////	//-ju-15-Mar-2011<--
////	float denominator =  dso - rz*voxSz;
////	// in Projektionsebene vergroessern ==> bereits in Pixel-Koord.
////
////	float px = bin*dso*rx/denominator;
////	float py = bin*dso*ry/denominator;
////	// Pixel-Koordinaten (0,0) linke obere Ecke
////	//-ju-07-Jan-2013 add corr. term to be consistens with CUDA tex. interpolation
////	ptInterpol.x=fdkConst.offsetX + CORR_TERM - px;
////	ptInterpol.y=fdkConst.offsetY + CORR_TERM - py;
////
////	weight = dso*dso/(denominator*denominator);
////}

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
							   float  winOrigZ) 
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

			l_back += (tex2DLayeredHighPrec(texSinoLay, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i))*l_weight;


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
							     float  winOrigZ) 
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

			l_back += (tex2DLayeredHighPrec(texSinoLay, interpolPoint.x + xOffset_loc, interpolPoint.y + yOffset_loc, i))*l_weight;

		}
		d_backProj[x + z*volWidth] += l_back;
	}
}


#endif // _RECON_FDK_KERNEL_H