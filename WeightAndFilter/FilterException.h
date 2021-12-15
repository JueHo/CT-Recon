/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _FILTEREXCEPTION_H
#define _FILTEREXCEPTION_H

#include "errormessages.h"

#include <string>
using namespace std;

class FilterException
{
public:
	FilterException(const FILTER_ERROR &errNo)
		:m_errNo(errNo)
	{
	}

	FilterException(const FILTER_ERROR &errNo, string text)
		:m_errNo(errNo), m_text(text)
	{
	}

	string GetErrorMessage()
	{
		int n = 0;
		string msg = "";
		while(message_table[n].err != err_list_end)
		{
			if(message_table[n].err == m_errNo)
			{
				msg = message_table[n].msg;
				break;
			}
			n++;
		}
		msg += ": ";
		msg += m_text;
		return msg;
	}
private:
	int    m_errNo;
	string m_text;
};
#endif