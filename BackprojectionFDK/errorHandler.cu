/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/
/**********************************************************

*
* $Log: errorHandler.cu $
* Revision 1.1  2010/12/15 09:52:49  Hofmann
* Initial revision
*
*
**********************************************************/
#include <cstdio>
#include <cstdlib>
#include <cuda_runtime_api.h>

extern "C"
void HandleError(cudaError_t err,const char *file,int line) 
{
    if (err != cudaSuccess) 
	{
        printf( "%s in %s at line %d\n",cudaGetErrorString(err),file, line );
        exit(EXIT_FAILURE);
    }
}
