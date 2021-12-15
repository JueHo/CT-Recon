/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

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
