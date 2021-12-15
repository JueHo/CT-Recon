/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "projectionpreprocessor.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressDialog>
#include <arrayfire.h>
#include <Windows.h>

#define _ACTIVATE_LORENTZ

int main(int argc, char *argv[])
{
#ifdef _ACTIVATE_LORENTZ
	MessageBox(0, 
		(LPCWSTR)L"The following initialization can takes some time.\nPlease be patient!", 
		(LPCWSTR)L"Information",
		MB_OK|MB_ICONINFORMATION);
#endif // _ACTIVATE_LORENTZ

	QApplication a(argc, argv);
	ProjectionPreProcessor w;
	w.show();
	// init ArrayFire
#ifdef _ACTIVATE_LORENTZ
	int devCnt = af::getDeviceCount();
	if (devCnt > 1)
	{
		af::setDevice(1);
	}
	else
	{
		af::setDevice(0);
	}
	af::info();
#endif // _ACTIVATE_LORENTZ
	return a.exec();
}
