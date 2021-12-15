/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _FDK_PARAMETER_H
#define _FDK_PARAMETER_H

#pragma warning(disable : 4996)

#include <string>
#include <fstream>
#include <vector>
using namespace std;

static char* Default_Parameter_File 	= ".\\parameters.desc";

static const char* CNT_PROJ				= "count_projections";
static const char* START_IDX			= "start_index";
static const char* IMG_WIDTH			= "image_width";
static const char* IMG_HEIGHT			= "image_height";
static const char* PIXEL_SIZE			= "pixel_size";
static const char* PREVIEW_SCALE		= "preview_scale";

static const char* GPU_MEM_USE  		= "gpu_mem_usage";
static const char* CPU_MEM_USE  		= "cpu_mem_usage";
static const char* THREADS_X    		= "threads_x";
static const char* THREADS_Y    		= "threads_y";

static const char* W_ORIG_X				= "vol_win_orig_x";
static const char* W_ORIG_Y				= "vol_win_orig_y";
static const char* W_ORIG_Z				= "vol_win_orig_z";

static const char* VOL_X				= "vol_x";
static const char* VOL_Y				= "vol_y";
static const char* VOL_Z				= "vol_z";
static const char* HORIZ_SHIFT			= "horiz_shift";
static const char* VERT_SHIFT			= "vert_shift";
static const char* DSD					= "source_detector";
static const char* DSO					= "source_rotcenter";
static const char* IN_DATATYPE			= "in_datatype";
static const char* OUT_DATATYPE			= "out_datatype";
static const char* SINO_NAME			= "sinogram_name";
static const char* TOMO_NAME			= "tomogram_name";
static const char* SINO32_DIR			= "sino32_dir";
static const char* SINO32_DIR_LIM		= "sino32_dir_lim"; //1
static const char* SINO_DIR				= "sino_dir";
static const char* TOMO_DIR				= "tomo_dir";
static const char* APPLY_FILTER			= "apply_filter";
static const char* FLIP_IMAGE			= "flip_image";
static const char* START_ANGLE  		= "starts_with_angle";
static const char* LIM_ANG_BPROJ		= "limited_angle_backproj";
static const char* USE_FILE_LIST		= "use_file_list"; //1
static const char* ANGLE_LFILE			= "angle_list_file";//not used
static const char* ANGLE_INCR			= "angle_increment"; //1
//ju-25-July-2014 phase contrast
static const char* USE_DCP				= "use_phase_contrast_filter"; // 0 (not used)
//-ju-17-June-2021 tilted axis correction
// selection
static const char* APPLY_TILT_CORR		= "apply_tilted_axis_correction"; // 0 --> do not apply
// slope value
static const char* TILT_CORR_SLOPE_M	= "slope_value_m_tilted_axis_correction";
// offset
static const char* TILT_CORR_CONST_C	= "const_offset_value_tilted_axis_correction";

//-ju-08-Nov-2011 add number threads
static const char* NUM_THREADS			= "number_threads";
//-ju-10-Nov-2011 add switches for blockfiles
static const char* SINO32_BLOCK_WRITE	= "sino32_block_write";
static const char* SINO32_BlOCK_USE		= "sino32_block_use";
static const char* TOMO_BLOCK_WRITE		= "tomo_block_write";
static const char* CONV_Block_INTERNAL	= "convert_block_internal";

namespace FDK {
	struct FDK_Parameters
	{
		int numThreads;				//-ju-08-Nov-2011 number of threads to use
		int cntProjection;			// number of projections (e.q. 600)
		int startIndex;				// projection numbering starts with index
		int imageWidth;				// image width
		int imageHeight;			// image height
		float pixelSize;			// pixel size
		int previewScale;			// scaling factor if reconstructing with binning
		int threadsX;				// number of threads on gpu in x-direction
		int threadsY;				// number of threads on gpu in y-direction
		float gpuMemoryUsage;		// how much of available graphic card memory will be used (%)
		float cpuMemoryUsage;		// how much of available cpu memory will be used (%)
		int winVolOrigX;			// x component of start point of reconstr. volume
		int winVolOrigY;			// y component of start point of reconstr. volume
		int winVolOrigZ;			// z component of start point of reconstr. volume
		int volumeX;				// x-size of reconst. volume
		int volumeY;				// y-size of reconst. volume
		int volumeZ;				// z-size of reconst. volume
		float horizShift;			// shift of rotation axis
		float vertShift;			// vertical shift of image (only DETECT)
		float dsd;					// distance source detector
		float dso;					// distance source rotation centre
		string inDataType;			// data type of sinograms
		string outDataType;			// data type of tomograms
		string sinoName;			// name of sinograms (with whitespaces)
		string tomoName;			// name of tomograms
		string sinoDir;				// directory of sinograms
		string sinoDir32;			// directory of pre-processed sinograms
		string sinoDirLim32;
		string tomoDir;				// directory of tomograms
		string applyFilter;			// name of filter which should be used
		int	useDCPFilter;			// use phase contrast filter (0, 1) (off/on)
		int flipImageFlag;			// flip image (values: -1, 0, 1)
		float startAngle;			// angle at which projections starts
		int limAngleBProj;			// set to 0/1 -> don't/do limited angle backprojection
		int useSinoFileList;		// set to 0/1 -> don't use/use file list
		vector<float> angleList;	// list of limited angles (in degree)
		vector<string> fileList;	// list of limited angles (in degree)
		string parameterFile;		// holds name of parameter file
		//-ju-10-Nov-2011
		int sino32BlockWrite;		// write to block file pre-proc sinograms
		int sino32BlockUse;			// use pre-proc sinograms block file
		int tomoBlockWrite;			// write tomograms to block files
		int convertBlockInternal;	// write converted tomograms back in block file
		string sino32BlockFile;		// file name incl. path for sino32 block file
									// get from env. variable PRE_PROC_BLOCKFILE
		string tomoBlockFile;		// file name incl. path for tomo block file
									// get from env. variable TOMO_BLOCKFILE
		//-ju-17-June-2021 add paramters for axis tilt correction
		int applyTiltCorr;			// switch on/off tilt correction
									// if off horiz. shift is used in reconstruction
		double slopeTiltCorr;		// slope value for tilt correction
		double constTiltCorr;		// const offset value used in tilt correction
	};

class Parameter
{
public:
	Parameter(char *parameterFile)
	:m_parameterFile(parameterFile)
	{//-ju-09-Aug-2012 fallbacks to handle migration of parameter files (parameters are missing)
		m_param.sino32BlockUse       = 0;
		m_param.sino32BlockWrite     = 0;
		m_param.tomoBlockWrite		 = 0;
		m_param.convertBlockInternal = 0;
		m_param.numThreads			 = 8;
	}
	FDK_Parameters GetParameters()
	{
		if(!isRead)
		{
			CheckParameters();
			ReadParameters();
			isRead = true;
		}
		return m_param;
	}
	void ReadParameters();
private:
	void CheckParameters()
	{
		// check if values are in range
	}
	static bool isRead;
	FDK_Parameters m_param;
	char *m_parameterFile;
};

}
#endif //_FDK_PARAMETER_H