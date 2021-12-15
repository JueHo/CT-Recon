/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _FDK_SYMBOLS_H
#define _FDK_SYMBOLS_H

static const char* CNT_PROJ			= "count_projections"; //1
static const char* START_IDX		= "start_index"; //1
static const char* IMG_WIDTH		= "image_width"; //1
static const char* IMG_HEIGHT		= "image_height"; //1
static const char* PIXEL_SIZE		= "pixel_size"; //1
static const char* PREVIEW_SCALE	= "preview_scale";

static const char* GPU_MEM_USE		= "gpu_mem_usage"; //1
static const char* CPU_MEM_USE		= "cpu_mem_usage"; //1
static const char* THREADS_X		= "threads_x"; //1
static const char* THREADS_Y		= "threads_y"; //1
//-ju-03-Nov-2016 high accurate bi-lin.
static const char* HI_ACC			= "high_acc";
//-ju-17-Jun-2011 new reconstruction key words
static const char* NUM_GPUS_USE		= "number_gpus_used"; //1
static const char* CT_SYSTEM		= "ct_system"; //1
//-ju-17-Jun-2011

static const char* W_ORIG_X			= "vol_win_orig_x"; //1
static const char* W_ORIG_Y			= "vol_win_orig_y"; //1
static const char* W_ORIG_Z			= "vol_win_orig_z"; //1

static const char* VOL_X			= "vol_x"; //1
static const char* VOL_Y			= "vol_y"; //1
static const char* VOL_Z			= "vol_z"; //1
static const char* HORIZ_SHIFT		= "horiz_shift"; //1
static const char* VERT_SHIFT		= "vert_shift"; //1
static const char* DSD				= "source_detector"; //1
static const char* DSO				= "source_rotcenter"; //1
static const char* IN_DATATYPE		= "in_datatype"; //1
static const char* OUT_DATATYPE		= "out_datatype"; //1
static const char* SINO_NAME		= "sinogram_name"; //1
static const char* TOMO_NAME		= "tomogram_name"; //1
static const char* SINO32_DIR		= "sino32_dir"; //1
static const char* SINO32_DIR_LIM	= "sino32_dir_lim"; //1
static const char* SINO_DIR			= "sino_dir"; //1
static const char* TOMO_DIR			= "tomo_dir"; //1
static const char* APPLY_FILTER		= "apply_filter"; //1
static const char* VIEW_DIRECTION	= "view_direction";
static const char* USE_DCP			= "use_phase_contrast_filter";
static const char* FLIP_IMAGE		= "flip_image"; //1
static const char* START_ANGLE		= "starts_with_angle"; //1
static const char* ANGLE_INCR		= "angle_increment"; //1

// switches
static const char* LIM_ANG_BPROJ	= "limited_angle_backproj";
static const char* USE_FILE_LIST	= "use_file_list"; //1

// data types
static const char* SERIAL_BYTE		= "byte";
static const char* SERIAL_SHORT		= "short16";
static const char* SERIAL_USHORT	= "ushort16";
static const char* SERIAL_INT		= "int32";
static const char* SERIAL_REAL		= "real32";
static const char* SERIAL_UNDEF		= "undef";

//-ju- project saving settings (not reconstruction relevant)
//static const char* USE_MPI			= "use_mpi";
//static const char* MPI_VERSION		= "mpi_version";
//static const char* GPU_COMP_VERS	= "gpu_compa_version";
//static const char* NUM_MPI_PROC		= "number_threads";
static const char* NUM_THREADS		= "number_threads";
static const char* DO_WEIGHT_FILTER	= "do_weight_filter";
static const char* DO_BACK_PROJECT	= "do_back_projection";

//-ju-10-Nov-2011 add switches for blockfiles
static const char* SINO32_BLOCK_WRITE	= "sino32_block_write";
static const char* SINO32_BlOCK_USE		= "sino32_block_use";
static const char* TOMO_BLOCK_WRITE		= "tomo_block_write";
static const char* CONV_Block_INTERNAL	= "convert_block_internal";

//-ju-17-June-2021 tilted axis correction
static const char* APPLY_TILT_CORR = "apply_tilted_axis_correction"; 
static const char* TILT_CORR_SLOPE_M = "slope_value_m_tilted_axis_correction";
static const char* TILT_CORR_CONST_C = "const_offset_value_tilted_axis_correction";

#endif