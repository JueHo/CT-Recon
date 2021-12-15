/**
*  Copyright © [2014], Empa, Juergen Hofmann
*/

#ifndef AUTOROTCENTERESTIMATION_H
#define AUTOROTCENTERESTIMATION_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "ui_autorotcenterestimation.h"

class AutoRotCenterEstimation : public QMainWindow
{
	Q_OBJECT

public:
	AutoRotCenterEstimation(QWidget *parent = 0);
	~AutoRotCenterEstimation();

private:
	void SetValuesChange();

public slots:
	void CloseWin();
	void StartAutoRot();
	void LoadPFDKFile();
	void CheckTiltStatus();
	void ChangeMultiRowStepSize();
	void ChangeFromSlice();
	void ChangeCntSupportPoint();

private:
	Ui::AutoRotCenterEstimationClass ui;
};

#endif // AUTOROTCENTERESTIMATION_H
