/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _IMPORT_DLG_H
#define _IMPORT_DLG_H

#include <QtWidgets/QDialog>
#include "ui_ImportDetectData.h"

class ImportDLG : public QDialog
{
	Q_OBJECT

public:
	ImportDLG(QWidget *parent = 0);

protected:
	bool ImportDLG::eventFilter(QObject *targetCtrl, QEvent *event);

public:
	Ui::Dialog m_ui;

private:
	QString m_completeBaseInputName;
	QString m_outputDir;
	QString m_temDir;

private slots:
	void GetVolumeFile();
	void GetSinoOutDir();
	void ImportConvert();
};

#endif