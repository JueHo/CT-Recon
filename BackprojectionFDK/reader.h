#ifndef _READER_H
#define _READER_H

#include "typesFDK.h"

bool CreateTomoDir(const char *tomoDir);


int ReadChunkOfSinograms(const int &start_value, 
						 const int &end_value,
						 const BackProjParam &param,
						 float *h_sinoData);

//-ju-10-10-2011 add block file reading
int ReadBlockChunkOfSinograms(const int &start_value, 
							  const int &end_value,
							  const BackProjParam &param,
							  float *h_sinoData);

int ReadChunkOfSinogramsFromFileList(const int &start_value, 
						 			 const int &end_value,
						 			 const BackProjParam &param,
						 			 float *h_sinoData);

#endif
