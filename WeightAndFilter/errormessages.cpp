/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "errormessages.h"

ErrorMessage
message_table[]=
 {
	"error open sinogram for reading",				err_open_r_sinogram,
	"error reading sinogram",						err_read_sinogram,
	"error open preprocessed sinogram for reading", err_open_r_pre_sino,
	"error reading preprocessed sinogram",			err_read_pre_sino,
	"error open sinogram for writing",				err_open_w_pre_sino,
	"error writing preprocessed sinogram",			err_write_pre_sino,
	"error unknown data type",						err_unknown_data_type,
	"error file size",								err_file_size,
	"error filter type",							err_filter_type,
	"",												err_list_end
};
