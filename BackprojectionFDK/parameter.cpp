/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "parameter.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::algorithm;
using namespace boost;

bool FDK::Parameter::isRead = false;

void FDK::Parameter::ReadParameters()
{
	ifstream paramStream;
	paramStream.open(m_parameterFile);
	if(!paramStream.is_open())
	{
		char buffer[300];
		sprintf_s(buffer, 300, 
				  "Can not open parameter file: %s!", 
			      m_parameterFile);
		MessageBoxA(NULL, buffer, "Error Open File",MB_ICONERROR);
		exit(-1);
	}
	// store filename
	m_param.parameterFile = m_parameterFile;
	// read parameter file
    string buffer;
    string buf;
	bool token_found = false;
    while(getline(paramStream,buffer,'\n'))
    {
        // remove left white space
		trim_left(buffer);
		//-ju-09-Aug-2012 skip empty line
		if(buffer.empty()) continue;
        // 1. skip lines starting with #
        if(buffer[0] == '#') continue;
        // 2. comment (#) is not at the binning of line
        vector<string> token;
        split(token,buffer,is_any_of("#"));
        // check first token most left part of token
        buf = token[0];
        token.clear();
        // split parameter string by key/value
        split(token,buf,is_any_of("="));
        // skip if no value exists
        if(token.size() < 2) continue;
        trim_left(token[1]);
        trim_right(token[1]);
        if(token[1].size() == 0) continue;

		// number of projections
		/////////////////////////
        if(find_first(token[0],CNT_PROJ))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
                m_param.cntProjection = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					CNT_PROJ, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
        if(find_first(token[0],START_IDX))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.startIndex = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					START_IDX, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// image width
		///////////////
        if(find_first(token[0],IMG_WIDTH))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.imageWidth = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					IMG_WIDTH, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// image height
		////////////////
        if(find_first(token[0],IMG_HEIGHT))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.imageHeight = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					IMG_HEIGHT, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// pixel size
		//////////////
        if(find_first(token[0],PIXEL_SIZE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.pixelSize = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					PIXEL_SIZE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// prieview scale
		//////////////////
        if(find_first(token[0],PREVIEW_SCALE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.previewScale = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					PREVIEW_SCALE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// memory usage of gpu in %
		///////////////////////////
        if(find_first(token[0],GPU_MEM_USE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.gpuMemoryUsage = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					GPU_MEM_USE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// memory usage of cpu in %
		///////////////////////////
        if(find_first(token[0],CPU_MEM_USE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.cpuMemoryUsage = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					CPU_MEM_USE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// threads per block in x-direction
		///////////////////////////////////
        if(find_first(token[0],THREADS_X))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.threadsX = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					THREADS_X, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// threads per block in y-direction
		///////////////////////////////////
        if(find_first(token[0],THREADS_Y))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.threadsY = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					THREADS_Y, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		//-ju-03-Nov-2016 add high acc
		///////////////////////////////
		if (find_first(token[0], HI_ACC))
		{
			token_found = true;
			// check sign of number
			trim_if(token[1], !(is_digit() || is_any_of("+-")));
			try
			{
				m_param.highAcc = lexical_cast<int>(token[1]);
			}
			catch (bad_lexical_cast & blc)
			{
				char buf[500];
				sprintf_s(buf, 500,
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!",
					THREADS_Y, blc.what());
				MessageBoxA(NULL, buf,
					"Error Parsing Parameter File"
					, MB_ICONERROR);
				exit(-2);
			}
		}


		// x component of recon. volume window
		//////////////////////////////////////
        if(find_first(token[0],W_ORIG_X))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.winVolOrigX = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					W_ORIG_X, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// y component of recon. volume window
		//////////////////////////////////////
        if(find_first(token[0],W_ORIG_Y))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.winVolOrigY = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					W_ORIG_Y, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// z component of recon. volume window
		//////////////////////////////////////
        if(find_first(token[0],W_ORIG_Z))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.winVolOrigZ = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					W_ORIG_Z, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// recon. volume x
		///////////////////
        if(find_first(token[0],VOL_X))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.volumeX = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					VOL_X, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// recon. volume y
		///////////////////
        if(find_first(token[0],VOL_Y))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.volumeY = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					VOL_Y, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// recon. volume z
		///////////////////
        if(find_first(token[0],VOL_Z))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.volumeZ = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					VOL_Z, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// vertical shift
		//////////////////
        if(find_first(token[0],VERT_SHIFT))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.vertShift = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					VERT_SHIFT, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// horizontal shift
		////////////////////
        if(find_first(token[0],HORIZ_SHIFT))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.horizShift = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					HORIZ_SHIFT, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		//-ju-17-June-2021 tilt correction
//////////////////////////////////
// switch tilt correction
/////////////////////////
		if (find_first(token[0], APPLY_TILT_CORR))
		{
			token_found = true;
			// check sign of number
			trim_if(token[1], !(is_digit() || is_any_of("+-")));
			try
			{
				m_param.applyTiltCorr = lexical_cast<int>(token[1]);
			}
			catch (bad_lexical_cast & blc)
			{
				char buf[500];
				sprintf_s(buf, 500,
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!",
					TOMO_BLOCK_WRITE, blc.what());
				MessageBoxA(NULL, buf,
					"Error Parsing Parameter File"
					, MB_ICONERROR);
				exit(-2);
			}
		}
		// slope of tilt correction
		////////////////////////////
		if (find_first(token[0], TILT_CORR_SLOPE_M))
		{
			token_found = true;
			// check sign of number
			trim_if(token[1], !(is_digit() || is_any_of("+-")));
			try
			{
				m_param.slopeTiltCorr = lexical_cast<float>(token[1]);
			}
			catch (bad_lexical_cast & blc)
			{
				char buf[500];
				sprintf_s(buf, 500,
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!",
					PIXEL_SIZE, blc.what());
				MessageBoxA(NULL, buf,
					"Error Parsing Parameter File"
					, MB_ICONERROR);
				exit(-2);
			}
		}
		// offset of tilt correction
		////////////////////////////
		if (find_first(token[0], TILT_CORR_CONST_C))
		{
			token_found = true;
			// check sign of number
			trim_if(token[1], !(is_digit() || is_any_of("+-")));
			try
			{
				m_param.constTiltCorr = lexical_cast<float>(token[1]);
			}
			catch (bad_lexical_cast & blc)
			{
				char buf[500];
				sprintf_s(buf, 500,
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!",
					PIXEL_SIZE, blc.what());
				MessageBoxA(NULL, buf,
					"Error Parsing Parameter File"
					, MB_ICONERROR);
				exit(-2);
			}
		}
		// flip image
		//////////////
        if(find_first(token[0],FLIP_IMAGE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				//-ju-11-Feb-2011 cast to int instead of cast to float
				m_param.flipImageFlag = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					FLIP_IMAGE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// source detector distance 
		////////////////////////////
        if(find_first(token[0],DSD))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.dsd = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					DSD, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// source rotation centre distance 
		///////////////////////////////////
        if(find_first(token[0],DSO))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.dso = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					DSO, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		// data type input data
		////////////////////////
        if(find_first(token[0],IN_DATATYPE))
        {
			token_found = true;
            m_param.inDataType = token[1];
        }
		// data type output data
		/////////////////////////
        if(find_first(token[0],OUT_DATATYPE))
        {
			token_found = true;
            m_param.outDataType = token[1];
        }
		// name of sinogram
		/////////////////////
        if(find_first(token[0],SINO_NAME))
        {
			token_found = true;
            m_param.sinoName = token[1];
			if (CheckForWhiteSpace(token[1]))
			{
				exit(-3);
			}
		}
		// name of tomogram
		/////////////////////
        if(find_first(token[0],TOMO_NAME))
        {
			token_found = true;
            m_param.tomoName = token[1];
			if (CheckForWhiteSpace(token[1]))
			{
				exit(-3);
			}
		}
		// sinogram directory
		//////////////////////
        if(find_first(token[0],SINO_DIR))
        {
			token_found = true;
            m_param.sinoDir = token[1];
			if (CheckForWhiteSpace(token[1]))
			{
				exit(-3);
			}
        }
		// tomgram directory
		/////////////////////
        if(find_first(token[0],TOMO_DIR))
        {
            m_param.tomoDir = token[1];
			token_found = true;
			if (CheckForWhiteSpace(token[1]))
			{
				exit(-3);
			}
		}
		// filter which should be applied
		//////////////////////////////////
        if(find_first(token[0],APPLY_FILTER))
        {
			token_found = true;
            m_param.applyFilter = token[1];
        }
		// pre-processed sinogram directory
		////////////////////////////////////
        if(find_first(token[0],SINO32_DIR))
        {
			token_found = true;
            m_param.sinoDir32 = token[1];
			if (CheckForWhiteSpace(token[1]))
			{
				exit(-3);
			}
		}
		// pre-processed sinogram directory
		////////////////////////////////////
        if(find_first(token[0],SINO32_DIR_LIM))
        {
			token_found = true;
            m_param.sinoDirLim32 = token[1];
        }
		// write pre-processed sinograms to block file
		///////////////////////////////////////////////
        if(find_first(token[0],SINO32_BLOCK_WRITE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.sino32BlockWrite = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					SINO32_BLOCK_WRITE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
        }
		//use pre-processed sinograms to block file for recon.
		///////////////////////////////////////////////////////
        if(find_first(token[0],SINO32_BlOCK_USE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.sino32BlockUse = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					SINO32_BlOCK_USE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
        }
		// write tomogram block files (not possible for batch)
		///////////////////////////////////////////////////////
        if(find_first(token[0],TOMO_BLOCK_WRITE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.tomoBlockWrite = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					TOMO_BLOCK_WRITE, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
        }
		// write converted tomograms back to block file
		////////////////////////////////////////////////
        if(find_first(token[0],CONV_Block_INTERNAL))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.convertBlockInternal = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					CONV_Block_INTERNAL, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
        }
		// use file list
		////////////////////////////////
		if(find_first(token[0],USE_FILE_LIST))
		{
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.useSinoFileList = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					USE_FILE_LIST, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
		}
		if(find_first(token[0],NUM_THREADS))
		{
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.numThreads = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					NUM_THREADS, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
		}
		// limited angle backprocessing
		////////////////////////////////
		if(find_first(token[0],LIM_ANG_BPROJ))
		{
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.limAngleBProj = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					LIM_ANG_BPROJ, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
			}
		}
		if(find_first(token[0],ANGLE_LFILE))
		{
			token_found = true;
			// read angle file
			if(m_param.limAngleBProj == 1)
			{
				std::ifstream angleFile;
				angleFile.open(token[1].c_str());
				if(!angleFile.is_open())
				{
					char buf[500];
					sprintf_s(buf, 500, 
						"Can not open angle list file >> %s << !"
						"\n\n EXIT Application!", 
						token[1].c_str());
					MessageBoxA(NULL, buf, 
						"Error Parsing Parameter File"
						,MB_ICONERROR);
					exit(-2);
				}
				float value = 0.0;
				int idx = 1;
				while(!angleFile.eof() && idx <= m_param.cntProjection)
				{
					angleFile >> value;
					m_param.angleList.push_back(value);
					idx++;
				}
				if(idx <= m_param.cntProjection)
				{
					cerr << "Too few entries in >> " << token[1].c_str() << " <<\n";
					exit(-2);
				}
			}
		}
		// projections starts with angle
		///////////////////////////////////
        if(find_first(token[0],START_ANGLE))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				//std::cout << "----------->" << token[1] << "\n";
				m_param.startAngle = lexical_cast<float>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type float."
					"\n\nMessage: %s\n\n EXIT Application!", 
					DSO, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }
		//ju-25-July-2014 phase contrast
		// use phase contrast filter
		/////////////////////////////
        if(find_first(token[0],USE_DCP))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.useDCPFilter = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					USE_DCP, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }

        //ju-15-Apr-2015 specify view direction
		// view in diretion to x-ray source or detector
		////////////////////////////////////////////////
        if(find_first(token[0],VIEW_DIRECTION))
        {
			token_found = true;
			// check sign of number
            trim_if(token[1],!(is_digit()||is_any_of("+-")));
            try 
            {
				m_param.viewDirection = lexical_cast<int>(token[1]);
            }
            catch(bad_lexical_cast & blc) 
            {
				char buf[500];
				sprintf_s(buf, 500, 
					"Value of parameter >> %s << is not of type integer."
					"\n\nMessage: %s\n\n EXIT Application!", 
					VIEW_DIRECTION, blc.what());
				MessageBoxA(NULL, buf, 
					"Error Parsing Parameter File"
					,MB_ICONERROR);
				exit(-2);
            }
        }

		//if(token_found == false)
		//{
		//			char buf[500];
		//			sprintf_s(buf, 500, 
		//				"Token >> %s << in paramter file not defined!"
		//				"\n\n EXIT Application!", 
		//				token[0].c_str());
		//			MessageBoxA(NULL, buf, 
		//				"Error Parsing Parameter File"
		//				,MB_ICONERROR);
		//			exit(-2);
		//}
		//else
		//{
		//	token_found = false;
		//}
	}
	// close file
	paramStream.close();
}

bool FDK::Parameter::CheckForWhiteSpace(string name)
{
	if (contains(name, " "))
	{
		char buf[500];
		sprintf_s(buf, 500,
			"Error: >> %s << contains white spaces!", name.c_str());
		fprintf(stderr, "%s\n", buf);
		MessageBoxA(NULL, buf,
			"Error: White Spaces in Path Names are Not Supported"
			, MB_ICONERROR);
		return true;
	}
	return false;
}