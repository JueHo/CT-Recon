/**
*  Copyright © [2014], Empa, Juergen Hofmann
*/

#include "autorotcenterestimation.h"
#include <cstdlib>
#include <iostream>

AutoRotCenterEstimation::AutoRotCenterEstimation(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	int mulRowStepCnt = ui.spinBox_multiRowStepSize->value();
	int supportCnt = ui.spinBox_supportPointSize->value();

	// connections
	///////////////
	connect(ui.pushButton_Close, &QPushButton::clicked, this, &AutoRotCenterEstimation::CloseWin);
	connect(ui.pushButton_Start, &QPushButton::clicked, this, &AutoRotCenterEstimation::StartAutoRot);
	connect(ui.pushButton_LoadPFDK, &QPushButton::clicked, this, &AutoRotCenterEstimation::LoadPFDKFile);
	connect(ui.checkBox_tilted, &QCheckBox::clicked, this, &AutoRotCenterEstimation::CheckTiltStatus);
	connect(ui.spinBox_multiRowStepSize, QOverload<int>::of(&QSpinBox::valueChanged), this, 
		&AutoRotCenterEstimation::ChangeMultiRowStepSize);
	connect(ui.spinBox_startSlice, QOverload<int>::of(&QSpinBox::valueChanged), this, 
		&AutoRotCenterEstimation::ChangeFromSlice);
	connect(ui.spinBox_supportPointSize, QOverload<int>::of(&QSpinBox::valueChanged), this,
		&AutoRotCenterEstimation::ChangeCntSupportPoint);

	this->setWindowTitle(tr("Center of Rotation Determination"));
}

AutoRotCenterEstimation::~AutoRotCenterEstimation()
{

}

void AutoRotCenterEstimation::StartAutoRot()
{
	// check parameters
	if (ui.lineEdit_PFDK_File->text().isEmpty())
	{
		QMessageBox::warning(0, tr("Missing Parameter"), tr("FDK Parameter File is missing."));
		ui.lineEdit_PFDK_File->setFocus();
		return;
	}
	double lBoundVal = ui.doubleSpinBox_LBound->value();
	double rBoundVal = ui.doubleSpinBox_RBound->value();
	if (lBoundVal > rBoundVal)
	{
		QMessageBox::warning(0, tr("Parameter Error"), tr("left bound of interval is greater than right bound."));
		ui.doubleSpinBox_LBound->setFocus();
		return;
	}
	// create a command string
	QString cmd;
	QByteArray parFile = ui.lineEdit_PFDK_File->text().toUtf8();
	std::string parFileStr = parFile.data();
	if (ui.checkBox_tilted->isChecked())
	{
		cmd.sprintf("RotationAxisDetermination.exe %s %d %f %f %f %d %d",
			parFileStr.c_str(),
			ui.spinBox_startSlice->value(),
			ui.doubleSpinBox_LBound->value(),
			ui.doubleSpinBox_RBound->value(),
			ui.doubleSpinBox_StepWidth->value(),
			ui.spinBox_supportPointSize->value(),
			ui.spinBox_multiRowStepSize->value());
	}
	else
	{
		cmd.sprintf("RotationAxisDetermination.exe %s %d %f %f %f",
			parFileStr.c_str(),
			ui.spinBox_SliceNumber->value(),
			ui.doubleSpinBox_LBound->value(),
			ui.doubleSpinBox_RBound->value(),
			ui.doubleSpinBox_StepWidth->value());
	}
	QByteArray bStr = cmd.toUtf8();
	std::string str = bStr.data();
	// start executable with system()
	//QMessageBox::information(0, tr("Info"), cmd);
	std::cout << str.c_str() << std::endl;
	system(str.c_str());
}

void AutoRotCenterEstimation::CloseWin()
{
	close();
}

void AutoRotCenterEstimation::LoadPFDKFile()
{
	QString pfdkFile = QFileDialog::getOpenFileName(this,
		tr("Open FDK Project Parameter File"),
		tr(""),
		tr("pfdk File (*.pfdk)"));
	if (!pfdkFile.isEmpty())
	{
		ui.lineEdit_PFDK_File->setText(pfdkFile);
	}
}

void AutoRotCenterEstimation::CheckTiltStatus()
{
	if (ui.checkBox_tilted->isChecked())
	{
		ui.spinBox_SliceNumber->setEnabled(false);
		ui.spinBox_multiRowStepSize->setEnabled(true);
		ui.spinBox_startSlice->setEnabled(true);
		ui.spinBox_supportPointSize->setEnabled(true);
	}
	else
	{
		ui.spinBox_SliceNumber->setEnabled(true);
		ui.spinBox_multiRowStepSize->setEnabled(false);
		ui.spinBox_startSlice->setEnabled(false);
		ui.spinBox_supportPointSize->setEnabled(false);
	}
}

void AutoRotCenterEstimation::ChangeMultiRowStepSize()
{
	SetValuesChange();
}

void AutoRotCenterEstimation::ChangeFromSlice()
{
	SetValuesChange();
}

void AutoRotCenterEstimation::ChangeCntSupportPoint()
{
	SetValuesChange();
}

void AutoRotCenterEstimation::SetValuesChange()
{
	int numRows = ui.spinBox_multiRowStepSize->value();
	int supPnt = ui.spinBox_supportPointSize->value();
	int endSlice = numRows * (supPnt - 1) + ui.spinBox_startSlice->value();
	QString str;
	str.sprintf("%d", endSlice);
	ui.label_endSlice->setText(str);
}