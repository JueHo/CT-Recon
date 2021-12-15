/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "definitions_public.h"

bool HelperFunctions::DirExist(QString dirPath)
{
	QDir dir(dirPath);
	return dir.exists();
}
bool HelperFunctions::CreateDir(QString dirPath)
{
	QDir dir;
	return dir.mkpath(dirPath);
}

double HelperFunctions::log2(double x)
{
	return log(x) / log(2.0);
}
