/**
*  Copyright © [2012], Empa, Juergen Hofmann
*/

#include "histogramremap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HistogramRemap w;
	w.show();
	return a.exec();
}
