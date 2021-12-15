/**
*  Copyright © [2014], Empa, Juergen Hofmann
*/

#include "autorotcenterestimation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoRotCenterEstimation w;
	w.show();
	return a.exec();
}
