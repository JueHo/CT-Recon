/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _UTILITY_FDK_H
#define _UTILITY_FDK_H

#include <cmath>

namespace FDK
{
class Utility
{
public:
	static unsigned int ZeroPadBase2Len(unsigned int n)
	{
		if(n == 0)
		{
			return 0;
		}
		double expo = ceil(log2(static_cast<double>(n)));
		double length = pow(2,expo);
		return static_cast<unsigned int>(length + 0.5);
	}

	static double log2(double x)
	{
	   return log(x)/log(2.0);
	}


};
}
#endif // _UTILITY_FDK_H