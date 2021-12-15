/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "fdk_gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSplashScreen *splash = new QSplashScreen(QPixmap("Images/FDKSPLASH-V2.0.1Win10.png"),Qt::WindowStaysOnTopHint);
	//splash->setPixmap(QPixmap(":/Images/FDKSPLASH.png"));
	splash->show();
	Qt::Alignment bottomLeft = Qt::AlignLeft | Qt::AlignBottom;
	splash->showMessage(QObject::tr("GUI Version 2.0.1 Win10"),bottomLeft, Qt::white);
	Qt::Alignment bottomRight = Qt::AlignRight | Qt::AlignBottom;
	splash->showMessage(QObject::tr("GUI Version 2.0.q Win10   October 2021   Copyright (c) EMPA Duebendorf"),bottomRight, Qt::white);
	Sleep(2000);
	a.processEvents();
	splash->showMessage(QObject::tr("Author: Juergen Hofmann        Center for X-ray Analytics"),bottomRight, Qt::white);
	a.processEvents();
	Sleep(2000);

	FDK_GUI w;
	w.show();
	splash->finish(&w);
	delete splash;

	return a.exec();
}
