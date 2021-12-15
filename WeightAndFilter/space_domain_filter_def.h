/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _SPACE_DOMAIN_FILTER_FUNCTIONS_H
#define _SPACE_DOMAIN_FILTER_FUNCTIONS_H

#include <cmath>
#include <vector>

using namespace std;

typedef void (*SpaceDomainFilterFunction)(const int&, vector<float>&);

//-ju-	Ramp filter in space domain
//		Data range 2xN-1: [-len+1, len-1]
extern void Ramp(const int &len, vector<float>& outData);

//-ju-	Shepp-Logan filter in space domain (incl. ramp filter)
//		Data range 2xN-1: [-len+1, len-1]
extern void SheppLogan(const int &len, vector<float>& outData); 


struct FilterFuncName
{
    SpaceDomainFilterFunction filterFunc;
    char*					  filterName;
};

extern FilterFuncName filterFunctionList[];

#endif // _SPACE_DOMAIN_FILTER_FUNCTIONS_H