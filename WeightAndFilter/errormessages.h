/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _ERROR_MESSAGES_H
#define _ERROR_MESSAGES_H

enum FILTER_ERROR
{
	err_open_r_sinogram   = 1000,
	err_read_sinogram     = 1005,
	err_open_r_pre_sino   = 1010,
	err_read_pre_sino     = 1015,
	err_open_w_pre_sino   = 1020,
	err_write_pre_sino    = 1025,
	err_unknown_data_type = 1030,
	err_file_size	      = 1035,
	err_filter_type       = 1040,
	err_list_end		  = -1,
};

struct ErrorMessage
{
	char *msg;
	FILTER_ERROR err;
};

extern ErrorMessage message_table[]; 

#endif //_ERROR_MESSAGES_H