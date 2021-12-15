/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "space_domain_filter_def.h"

// filter definitions
//////////////////////////////////

//-ju-	Ramp filter in space domain
//		Data range 2xN-1: [-len+1, len-1]
void Ramp(const int &len, vector<float>& outData)
{
	// convolution kernel is 1/2 for fan (cone) beam
	// see Buzug, Einführung in die Computertomographie 
	// page 330 (7.199). 
	// Size of detector element = 1 pixel
	//=================================================
	double term = -1/(2*M_PI*M_PI);
	outData.resize(2*len-1);
	unsigned int idx = 0;
	for(int i = -len+1; i < len; i++)
	{
		if(i == 0)
		{
			outData[idx] = static_cast<float>(1.0/8.0);
			idx++;
		}
		else
		if(abs(i%2) == 1)
		{
			outData[idx] = static_cast<float>(term/(i*i));
			idx++;
		}
		else
		{
			outData[idx] = 0.0f;
			idx++;
		}
	}
}

//-ju-	Shepp-Logan filter in space domain (incl. ramp filter)
//		Data range 2xN-1: [-len+1, len-1]
void SheppLogan(const int &len, vector<float>& outData) 
{
	// convolution kernel is 1/2 for fan (cone) beam
	// see Buzug, Einführung in die Computertomographie 
	// page 330 (7.199)
	// Size of detector element = 1 pixel
	//=================================================
	double term = -1/(M_PI*M_PI);
	outData.resize(2*len-1);
	unsigned int idx = 0;
	for(int i = -len+1; i < len; i++)
	{
		outData[idx] = static_cast<float>(term/(4*i*i - 1));
		idx++;
	}
}


// register available functions
/////////////////////////////////////
 
// name in quotation marks must be identical
// the name in the parameter file (case sensitiv).
// Name behind keyword apply_filter.
FilterFuncName filterFunctionList[] =
{
// Specify:
//   func-name : filter name
//  |---------| |-----------|
    {Ramp,       "Ramp"      },
    {SheppLogan, "SheppLogan"},
    {0,           "0"        }
};
