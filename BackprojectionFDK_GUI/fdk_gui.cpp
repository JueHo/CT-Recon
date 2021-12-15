/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "fdk_gui.h"
#include "image_dlg.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <climits>
#include "rawFile2Image.h"
#include <windows.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolTip>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>

#include <QtGui/QHelpEvent>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include <QtCore/QTextStream>
//-ju-22-Jan-2019 debug
#include <iostream>


struct LANGUAGE_AND_CODE_PAGE 
{
  WORD language;
  WORD codePage;
} *translation;

////////////////////////////////
//-ju- constructors/destructors
///////////////////////////////////////////////////////////////////////////////

FDK_GUI::FDK_GUI(QWidget *parent)
: QMainWindow(parent)
{
	// pre-set member variables
	//////////////////////////
	m_importDlg = 0;
	m_dataPath = tr("C:\\");
	m_mpiPath  = tr("C:\\Program Files");

	ui.setupUi(this);
	SetAddtionalControlProperties();
	SetAdditionalConnections();

	//read settings
	QSettings settings("EMPA_CT_Group", "FDK_GUI");

	settings.beginGroup("mainWindow");
		restoreGeometry(settings.value("geometry").toByteArray());
		restoreState(settings.value("state").toByteArray());
	settings.endGroup();

	if(!ui.dockWidget_ImageView->isHidden())
	{
		ui.actionImage_View->setChecked(true);
	}
	else
	{
		ui.actionImage_View->setChecked(false);
	}

	if(ui.actionToolbar->isVisible())
	{
		ui.actionToolbar->setChecked(true);
	}
	else
	{
		ui.actionToolbar->setChecked(false);
	}

	// overwrite stored settings
	/////////////////////////////

	// hide option-dock-window after geometry/state restore
	ui.dockWidget_ProjectOptions->hide();

	ui.TreeWidget_LimAngleSeg->header()->setDefaultSectionSize(180);

	m_imgDlg = 0;

	m_stopBatch = false;
	m_batchIndex = 0;
	//-ju-22-Jan-2019 initialize batch count
	m_batchCnt = 0;

	// volume selection size flag
	m_volSelecTooBig = false;

	projSerialize.Init(GetUI());

	// load path settings
	LoadPathSetting();
	ui.lineEdit_MPIPath->hide();
	ui.Btn_MPIPath->hide();

	//-ju-28-July-2014 make invisible
	ui.ListWidget_SinogramList->hide();
	ui.Btn_SelectSinograms->hide();
	ui.Btn_RemoveSelection->hide();
	ui.GrBox_LimitAngleSinograms->hide();

	ui.GrBox_CTSystemSelection->hide();
	ui.groupBox_6->hide();
	ui.groupBox_7->hide();
	ui.CkBox_WriteBlockFile->hide();
	ui.label_WriteToBlockFile->hide();
}

FDK_GUI::~FDK_GUI()
{
	if(m_imgDlg != 0)
	{
		delete m_imgDlg;
	}
}

void FDK_GUI::closeEvent(QCloseEvent *event)
{
	QSettings settings("EMPA_CT_Group", "FDK_GUI");

	settings.beginGroup("mainWindow");
		settings.setValue("geometry", saveGeometry());
		settings.setValue("state",saveState());
	settings.endGroup();

	QWidget::closeEvent(event);
}

void FDK_GUI::SetAddtionalControlProperties()
{
	ui.ListWidget_SinogramList->setAlternatingRowColors(true);
	ui.ListWidget_SinogramList->setAutoScroll(true);
	ui.ListWidget_SinogramList->setWindowTitle("Sinograms");

	//-ju- event filter registration
	ui.LEd_SinoNamePattern->installEventFilter(this);
	ui.ListWidget_SinogramList->installEventFilter(this);
	ui.LEd_TomoOutDir->installEventFilter(this);
	ui.LEd_LimAnglePreProcDir->installEventFilter(this);
	ui.LEd_PreprocSinoDirectory->installEventFilter(this);
	ui.LEd_SinogramDirectory->installEventFilter(this);

	//-ju- add control to toolbar
	QHBoxLayout *layout = new QHBoxLayout(ui.toolBar);

	QLabel *projectLabel = new QLabel(tr("Project:  "));
	projectLabel->setStyleSheet("color: black;font: bold 14px;");

	m_toolLabel = new QLabel(tr("*"));
	m_toolLabel->setFixedHeight(20);
	m_toolLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	m_toolLabel->setFrameStyle(QFrame::Plain | QFrame::WinPanel);
	m_toolLabel->setStyleSheet("color: darkgray; background: gold; font: bold 14px;");

	ui.toolBar->addSeparator();
	layout->addWidget(projectLabel);
	layout->addWidget(m_toolLabel);
	layout->insertSpacing(0,20);
	ui.toolBar->addWidget(layout->widget());
	ui.toolBar->addWidget(projectLabel);
	ui.toolBar->addWidget(m_toolLabel);

	ui.GrBox_LimitAngleSinograms->setEnabled(false);


	//-ju-10-Nov-2011 ui.GrBox_MPI->hide();


	//-ju-hide dowck window at start
	//ui.dockWidget_ImageView->hide();
	ui.dockWidget_Database->hide();

	//ui.pw_SinogramGroupBox->setStyleSheet("QGroupBox{background-color: slategray; color: yellow}");
	//ui.pw_filePattern->setStyleSheet("background-color: tomato; font: 75 8pt Consolas");
	//ui.pw_LimAngleSino->setVisible(false);
	/*
	QColor col;
	QFile file("out.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	return;

	QTextStream out(&file);
	QStringList sl = col.colorNames();
	foreach(QString color, sl)
	{
	out << color << "\n";
	}
	file.close();
	*/
}

void FDK_GUI::SetAdditionalConnections()
{
	connect(ui.Btn_SelectSinograms,SIGNAL(clicked()),this,SLOT(SinoFileSelections()));
	connect(ui.Btn_RemoveSelection,SIGNAL(clicked()),this,SLOT(RemSelSinoFromList()));
	//connect(ui.Btn_EditFilePattern,SIGNAL(toggled(bool)),this,SLOT(EditFilePattern()));
	connect(ui.ListWidget_SinogramList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(ShowSinogram()));
	connect(ui.Btn_LimAnglePreProcDir,SIGNAL(clicked()),this,SLOT(LimAnglePreProcDirSel()));
	connect(ui.Btn_LimAngleAddSeg,SIGNAL(clicked()),this,SLOT(LimAngleAddSegment()));
	connect(ui.Btn_LimAngleRemSeg,SIGNAL(clicked()),this,SLOT(LimAngleRemoveSegment()));
	connect(ui.Btn_RunReconstruction,SIGNAL(clicked()),this,SLOT(RunReconstruction()));
	// process handling
	connect(&m_filterProc,SIGNAL(readyRead()),this,SLOT(UpdateFromFilterProc()));
	connect(&m_filterProc,SIGNAL(started()),this,SLOT(ProcStarted()));
	connect(&m_filterProc,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(ProcFinished())); 
	//connect(&m_reconProc,SIGNAL(readyReadStandardOutput()),this,SLOT(UpdateFromRecProc()));
	connect(&m_reconProc,SIGNAL(readyRead()),this,SLOT(UpdateFromRecProc()));
	connect(&m_reconProc,SIGNAL(started()),this,SLOT(ProcStartedRec()));
	connect(&m_reconProc,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(ProcFinishedRec()));

	connect(ui.Btn_StopWeightFilterProc,SIGNAL(clicked()),this,SLOT(StopWFProcess()));
	connect(ui.Btn_StopReconstructionProc,SIGNAL(clicked()),this,SLOT(StopRecProcess()));

	connect(ui.Btn_SelectSinogramDirectory,SIGNAL(clicked()),this,SLOT(SinogramDir()));
	connect(ui.Btn_SelectPreprocSinoDir,SIGNAL(clicked()),this,SLOT(SinogramPreProcDir()));
	connect(ui.Btn_MPIPath,SIGNAL(clicked()),this,SLOT(SetupMPIPath()));
	connect(ui.Btn_DataTopDir,SIGNAL(clicked()),this,SLOT(SetupDataTopPath()));

	
	connect(ui.checkBox_useFileList,SIGNAL(toggled(bool)),this,SLOT(SetVolumeSelectionButton()));
	connect(ui.radioButton_limitedAngleRecon,SIGNAL(toggled(bool)),this,SLOT(SetVolumeSelectionButton()));

	//-ju- actions
	connect(ui.actionSave,SIGNAL(triggered()),this,SLOT(ActionSaveProject()));
	connect(ui.actionSave_as,SIGNAL(triggered()),this,SLOT(ActionSaveProjectAs()));
	connect(ui.actionOptions,SIGNAL(triggered()),this,SLOT(ActionSwitchView()));
	connect(ui.actionOpen,SIGNAL(triggered()),this,SLOT(ActionOpenProject()));
	connect(ui.actionCheck_Parameters,SIGNAL(triggered()),this,SLOT(ActionCheckParameters()));
	//connect(ui.actionNew,SIGNAL(triggered()),this,SLOT(ActionNewProject()));

	//-ju- basic parameters
	connect(ui.SBox_ImgWidth,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_ImgHeight,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_NumberOfProjections,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_AngleIncr,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBOX_PixelSize,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_HorizontalShift,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_VerticalShift,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_DistSrcDetector,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_DistSrcRotCentre,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_InDataFormat,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_NumStartIndex,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_SinoStartAtAngle,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_FilterType,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_ViewDirection,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_FlipSinogramImage,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetGuiModified()));
	//-ju-17-June-2021 new
	connect(ui.checkBox_applyTiltAxCorr, SIGNAL(stateChanged(int)), this, SLOT(SetTiltCorr()));
	//connect(ui.checkBox_applyTiltAxCorr, SIGNAL(stateChanged(int)), this, SLOT(SetGuiModified()));
	//connect(ui.doubleSpinBox_corrSlope_m, SIGNAL(stateChanged(int)), this, SLOT(SetGuiModified()));
	//connect(ui.doubleSpinBox_corrSlope_m, SIGNAL(valueChanged(double)), this, SLOT(SlopeTiltValueChanged()));
	connect(ui.doubleSpinBox_corrSlope_m, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, &FDK_GUI::SlopeTiltValueChanged);
	connect(ui.doubleSpinBox_corrOffset_c, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, &FDK_GUI::ConstTiltValueChanged);
	//connect(ui.doubleSpinBox_corrOffset_c, SIGNAL(valueChanged(double)), this, SLOT(SetGuiModified()));
	//connect(ui.doubleSpinBox_corrOffset_c, SIGNAL(valueChanged(double)), this, SLOT(ConstTiltValueChanged()));
	// reconstruction parameters
	connect(ui.SBox_BinningFactor,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeWidth,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeHeight,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeDepth,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeOriginX,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeOriginY,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_VolumeOriginZ,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_TomoOutDataFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.LEd_TomoName,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.LEd_TomoOutDir,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.Btn_SelTomoOutDir,SIGNAL(clicked()),this,SLOT(SetupTomoDir()));
	connect(ui.Btn_GetVolumeFromSelection,SIGNAL(clicked()),this,SLOT(SetVolumeCoord()));
	//check binning
	connect(ui.SBox_BinningFactor,SIGNAL(valueChanged(int)),this,SLOT(SetBinningSettings()));
	// advanced settings
	connect(ui.DSBox_CPUMemUsage,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.DSBox_GPUMemUsage,SIGNAL(valueChanged(double)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_GPUThreadsX,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.SBox_GPUThreadsY,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	//-ju-04-Nov-2016 add interpolation type
	connect(ui.radioButton_fast, SIGNAL(toggled(bool)), this, SLOT(SetGuiModified()));
	connect(ui.radioButton_accurate, SIGNAL(toggled(bool)), this, SLOT(SetGuiModified()));

	connect(ui.CBox_GPUCompaVers,SIGNAL(currentIndexChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_GPUCompaVers,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeGPUThreads()));
	connect(ui.radioButton_fullAngleRecon, SIGNAL(toggled(bool)), this, SLOT(SetGuiModified()));
	connect(ui.checkBox_useFileList, SIGNAL(toggled(bool)), this, SLOT(SetGuiModified()));
	connect(ui.SBox_UseNumGPUs,SIGNAL(valueChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.CBox_CT_SystemSelection,SIGNAL(currentIndexChanged(QString)),this,SLOT(SetGuiModified()));
	//-ju-10-Nov-2011 connect(ui.CkBox_UseMPI,SIGNAL(stateChanged(int)),this,SLOT(SetGuiModified()));
	//-ju-10-Nov-2011 connect(ui.CBox_MPIVersion,SIGNAL(currentIndexChanged(int)),this,SLOT(SetGuiModified()));
	connect(ui.CkBox_WeightFilter,SIGNAL(toggled(bool)),this,SLOT(SetGuiModified()));
	connect(ui.CkBox_Backprojection,SIGNAL(toggled(bool)),this,SLOT(SetGuiModified()));
	// sinogram selection
	connect(ui.ListWidget_SinogramList,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(SetGuiModified()));
	connect(ui.LEd_SinoNamePattern,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.LEd_SinoNamePattern,SIGNAL(textEdited(QString)),this,SLOT(DeleteALLItemFromList()));
	connect(ui.LEd_SinogramDirectory,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	connect(ui.LEd_PreprocSinoDirectory,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	// sinograms limited angle
	connect(ui.LEd_LimAnglePreProcDir,SIGNAL(textChanged(QString)),this,SLOT(SetGuiModified()));
	// file list
	connect(ui.checkBox_useFileList, SIGNAL(toggled(bool)), this, SLOT(SetupControls()));
	// dock widgets program options
	connect(ui.radioButton_fullAngleRecon,SIGNAL(toggled(bool)),this,SLOT(SetOptionModified()));
	//connect(ui.radioButton_fullAngleRecon,SIGNAL(toggled(bool)),this,SLOT(SetBinaryFileOption()));
    connect(ui.radioButton_limitedAngleRecon,SIGNAL(toggled(bool)),this,SLOT(SetOptionModified()));
    connect(ui.checkBox_useFileList,SIGNAL(toggled(bool)),this,SLOT(SetOptionModified()));
    connect(ui.lineEdit_MPIPath,SIGNAL(textChanged(QString)),this,SLOT(SetOptionModified()));
    connect(ui.lineEdit_DataTopDir,SIGNAL(textChanged(QString)),this,SLOT(SetOptionModified()));
	connect(ui.Btn_SaveOptions,SIGNAL(clicked(bool)),this,SLOT(SavePathSetting()));
	connect(ui.radioButton_limitedAngleRecon,SIGNAL(toggled(bool)),this,SLOT(SetUseFileList()));

	// autom. setters for image width and height --> Volume width, height and depth
	connect(ui.SBox_ImgWidth,SIGNAL(valueChanged(int)),ui.SBox_VolumeWidth,SLOT(setValue(int)));
	connect(ui.SBox_ImgWidth,SIGNAL(valueChanged(int)),ui.SBox_VolumeDepth,SLOT(setValue(int)));
	connect(ui.SBox_ImgHeight,SIGNAL(valueChanged(int)),ui.SBox_VolumeHeight,SLOT(setValue(int)));

	// batch
	connect(ui.Btn_AddProjectToBatch,SIGNAL(clicked()),this,SLOT(AddProjectToBatch()));
	connect(ui.Btn_RemProjectToBatch,SIGNAL(clicked()),this,SLOT(RemoveProjectFromBatch()));
	connect(ui.Btn_RunBatch,SIGNAL(clicked()),this,SLOT(RunBatch()));
	connect(ui.Btn_StopBatch,SIGNAL(clicked()),this,SLOT(StopBatch()));
	connect(ui.pushButton_SaveProcessOutput,SIGNAL(clicked()),this,SLOT(SaveProcessOutput()));

	// timer and LCD connects
	connect(&m_timer,SIGNAL(timeout()),this,SLOT(updateProcTime()));

	// start import dialog
	connect(ui.actionImport_convert_DETECT_data,SIGNAL(triggered()),this,SLOT(ActionImportDetectData()));

	//-ju-10-Nov-2011 add
	//-ju-22-Jan-2019 signal triggred() is unknown connect(ui.CkBox_StoreConvTomoBlockFile,SIGNAL(triggered()),this,SLOT(CkeckBlockStatus()));
	/*-ju-13-Aug-2012 disable blockfile handling for pre-processed sinograms (bugs to fix)
    connect(ui.CkBox_WriteToPreProcBlockFile,SIGNAL(toggled(bool)),this, SLOT(SetGuiModified()));
    connect(ui.CkBox_UsePreProcBlockFile,SIGNAL(toggled(bool)),this, SLOT(SetGuiModified()));
	*/
    connect(ui.CkBox_StoreConvTomoBlockFile,SIGNAL(toggled(bool)),this, SLOT(SetGuiModified()));
    connect(ui.CkBox_WriteBlockFile,SIGNAL(toggled(bool)),this, SLOT(SetGuiModified()));
	
	//-ju-22-Jan-2019 signal stateChanged() is unknown connect(ui.radioButton_limitedAngleRecon,SIGNAL(stateChanged(int)),this,SLOT(ResetBlockFileSettings(int)));
	connect(ui.radioButton_fullAngleRecon,SIGNAL(toggled(bool)),this,SLOT(ResetDisplaySettings(bool)));
	connect(ui.checkBox_useFileList,SIGNAL(stateChanged(int)),this,SLOT(ResetBlockFileSettings(int)));
	connect(ui.checkBox_useFileList,SIGNAL(stateChanged(int)),this,SLOT(ResetDisplaySettingsFS(int)));

	//-ju-16-Nov-2011 add
	connect(ui.SBox_NumberOfMPIProcesses, SIGNAL(valueChanged(int)), this, SLOT(SetGuiModified()));
}

////////////////////
//-ju- Event filter
////////////////////////////////////////////////////////////////////////////////////
//bool KSWBoneGeometry::eventFilter(QObject *targetCtrl, QEvent *event)
//{
//	if (targetCtrl == ui.label_patientImage)
//	{
//		// calibration points
//		if (ui.checkBox_calibrationAddPoints->isChecked()
//			&& !ui.checkBox_acceptCalibration->isChecked())
//		{
//			if (event->type() == QEvent::MouseButtonPress)
//			{
//				QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
//				if (mEvt->button() == Qt::LeftButton)
//				{
//					QPoint curPos = mEvt->pos();
//					if (!m_imagePix.isNull())
//					{
//						// add point to calibration point list
//						DrawCrossList(curPos, m_imagePix, m_calibrationPointsVIS, 1);
//						// fitting points to a circle and draw it
//						CalcAndDrawCalibrationCircle(curPos, m_imagePix, 1);
//					}
//				}
//				if (mEvt->button() == Qt::RightButton)
//				{
//					if (!m_imagePix.isNull())

bool FDK_GUI::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if(targetCtrl == ui.LEd_TomoOutDir)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(ui.LEd_TomoOutDir->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("< empty >"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),ui.LEd_TomoOutDir->text());				
			}
		}
	}
	if(targetCtrl == ui.LEd_SinogramDirectory)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(ui.LEd_SinogramDirectory->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("< empty >"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),ui.LEd_SinogramDirectory->text());				
			}
		}
	}
	if(targetCtrl == ui.LEd_PreprocSinoDirectory)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(ui.LEd_PreprocSinoDirectory->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("< empty >"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),ui.LEd_PreprocSinoDirectory->text());				
			}
		}
	}
	if(targetCtrl == ui.LEd_LimAnglePreProcDir)
	{
		if(event->type() == QEvent::ToolTip)
		{
           QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
			if(ui.LEd_LimAnglePreProcDir->text().isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(),tr("< empty >"));
			}
			else
			{
				QToolTip::showText(helpEvent->globalPos(),ui.LEd_LimAnglePreProcDir->text());				
			}
		}
	}

	if(targetCtrl == ui.LEd_SinoNamePattern && ui.LEd_SinoNamePattern->isEnabled())
	{
		if(event->type() == QEvent::MouseButtonDblClick)
		{
			QMouseEvent *mouseButton = static_cast<QMouseEvent*>(event);
			if(mouseButton->button() == Qt::LeftButton)
			{
				QString path = ui.LEd_SinogramDirectory->text();
				SetFilePattern(path);
			}
		}
	}
	if(targetCtrl == ui.ListWidget_SinogramList)
	{
		if(event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			if(keyEvent->key() == Qt::Key_Delete)
			{
				DeleteItemSelectionFromList();
				return true;
			}
		}
		if(event->type() == QEvent::KeyPress)
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
			Qt::KeyboardModifiers keyMod = keyEvent->modifiers();
			if((keyEvent->key() == Qt::Key_Up || 
				keyEvent->key() == Qt::Key_Down ||
				keyEvent->key() == Qt::Key_PageUp ||
				keyEvent->key() == Qt::Key_PageDown)
				&& keyMod == Qt::ALT)
			{
				if(ui.CBox_InDataFormat->currentText().trimmed() == "byte")
				{
					DisplaySinograms<uchar>(255);
				}
				else
				if(ui.CBox_InDataFormat->currentText().trimmed() == "short16")
				{
					DisplaySinograms<short>(SHRT_MAX);
				}
				else
				if(ui.CBox_InDataFormat->currentText().trimmed() == "ushort16")
				{
					DisplaySinograms<ushort>(USHRT_MAX);
				}
				else
				if(ui.CBox_InDataFormat->currentText().trimmed() == "integer32")
				{
					DisplaySinograms<int>(INT_MAX);
				}
				else
				if(ui.CBox_InDataFormat->currentText().trimmed() == "real32")
				{
					DisplaySinograms<float>(FLT_MAX);
				}
			}

		}
	}
	return QMainWindow::eventFilter(targetCtrl,event);
}


////////////////////////////
// private member functions
///////////////////////////////////////////////////////////////////////////////

void FDK_GUI::DeleteItemSelectionFromList()
{
	QList<QListWidgetItem*> wList = ui.ListWidget_SinogramList->selectedItems();
	foreach(QListWidgetItem* item, wList)
	{
		QString itemTxt = item->text();
		int idx = 0;
		foreach(QString filename, m_fileList)
		{
			if(filename == itemTxt)
			{
				m_fileList.removeAt(idx);
				//-ju-25-July-2011 delete item
				delete item;
			}
			idx++;
		}
	}
	if(wList.count() > 0)
	{
		ui.ListWidget_SinogramList->clear();
		SetGuiModified();

		m_fileList.sort();
		int i = 0;
		foreach(QString file, m_fileList)
		{
			QListWidgetItem *pLWI = new QListWidgetItem(m_fileList[i], ui.ListWidget_SinogramList);
			pLWI->setTextAlignment(Qt::AlignLeft);
			i++;
		}
	}
}

void FDK_GUI::EditFilePattern()
{
	//if(ui.Btn_EditFilePattern->isChecked())
	//{
	//	//ui.Btn_EditFilePattern->setStyleSheet(
	//	//	"QPushButton{background-color: tomato; color: darkblue; font: bold}");
	//	ui.LEd_SinoNamePattern->setEnabled(true);
	//	//ui.LEd_SinoNamePattern->setStyleSheet(
	//	//	"background-color: chartreuse; font: 75 8pt Consolas");
	//	ui.Btn_EditFilePattern->setText(tr("Lock"));
	//}
	//else
	//{
	//	//ui.Btn_EditFilePattern->setStyleSheet(
	//	//	"QPushButton{background-color: chartreuse; color: darkblue; font: bold}");
	//	ui.LEd_SinoNamePattern->setEnabled(false);
	//	//ui.LEd_SinoNamePattern->setStyleSheet(
	//	//	"background-color: light grey");
	//	ui.Btn_EditFilePattern->setText(tr("Edit"));
	//}
}

void FDK_GUI::DelFromLimAngleSinoFileList(int topIndex)
{
	QVector<QMap<QString,double> >::iterator iter = m_LimAngleSinoFileList.begin();
	iter += topIndex;
	m_LimAngleSinoFileList.erase(iter);
}

void FDK_GUI::ReListLimAngleSinoFileList()
{
	ui.TreeWidget_LimAngleSeg->clear();
	for(int i = 0; i < m_LimAngleSinoFileList.size(); i++)
	{
		QMap<QString,double> keyVal = m_LimAngleSinoFileList[i];
		AddChildsToTree(i,keyVal,ui.TreeWidget_LimAngleSeg);
	}
}

void FDK_GUI::AddChildsToTree(int node, const QMap<QString,double> &fileDegree, QTreeWidget *toplevel)
{
	QString root;
	root.sprintf("Segment-%02d:", node);
	QStringList list;


	QMap<QString,double>::const_iterator iter = fileDegree.constBegin();
	if(iter != fileDegree.constEnd())
	{
		QFileInfo dir(iter.key());
		QString path  = dir.path();
		root = root + tr(" ") + path;
	}
	list.append(root);

	QTreeWidgetItem *parent = new QTreeWidgetItem(toplevel,list);
	QTreeWidgetItem *child;

	while(iter != fileDegree.constEnd()) 
	{
		QStringList keyVal;
		QString key = iter.key();

		QFileInfo file(iter.key());
		QString filename  = file.fileName();
		keyVal.append(filename);

		QString val;
		val.sprintf("%6.2f°", iter.value());
		keyVal.append(val);

		child = new QTreeWidgetItem(keyVal);
		parent->addChild(child);
		++iter;
	}
}

void FDK_GUI::SetFilePattern(QString sinogramDir)
{
	//if(sinogramDir.isEmpty())
	//{
	//	return;
	//}
	//QFileInfo sinoDir(sinogramDir);
	//if(!sinoDir.exists())
	//{
	//	QString txt;
	//	txt.sprintf("Sinogram Directory: %s does not exist. Specify another!", sinoDir);
	//	ui.statusBar->showMessage(txt);
	//	return;
	//}

	QString dirPath = sinogramDir;
	if(sinogramDir.isEmpty())
	{
		dirPath = m_dataPath;
	}
	QString file =
		QFileDialog::getOpenFileName(this,
		tr("Select Sinogram Files"),
		dirPath,
		tr("Sinograms (*.sin *.raw);; All Files (*.*)"));

	if(file.isEmpty())
	{
		return;
	}
	// sinogram access mask
	QFileInfo dir(file);
	QString filename = dir.fileName();
	QStringList part = filename.split(".");
	if(part[0].size() == 0)
	{
		QString msg(tr("Filenames with >> . << in front of numbers are not supported"));
		QMessageBox::warning(this, tr("Unsupported Filename"), msg);
		return;
	}
	if(!part[0][part[0].size()-1].isDigit())
	{
		QString msg(tr("Filename Format is not Supported - Missing at least one digit"));
		QMessageBox::warning(this, tr("Unsupported Filename"), msg);
		return;
	}
	//ju- match and replace last 4 integer number in first part string
	QString pattern = part[0].replace(QRegExp("[0-9]{4,4}$"), "****");
	for(int i = 1; i < part.size(); i++)
	{
		pattern += ".";
		pattern += part[i];
	}
	ui.LEd_SinoNamePattern->clear();
	ui.LEd_SinoNamePattern->insert(pattern);
	ui.LEd_SinoNamePattern->setAlignment(Qt::AlignRight);
	ui.LEd_SinogramDirectory->clear();
	ui.LEd_PreprocSinoDirectory->clear();
	ui.LEd_SinogramDirectory->setText(dir.absolutePath()+tr("/"));
	QStringList pathList = dir.absolutePath().split("/");
	pathList[pathList.count()-1] = tr("sino32/");
	QString preDir = pathList.join("/");
	ui.LEd_PreprocSinoDirectory->setText(preDir);
	pathList[pathList.count()-1] = tr("tomo/");
	QString tomoDir = pathList.join("/");
	ui.LEd_TomoOutDir->setText(tomoDir);
}

void FDK_GUI::SetGUIOnSave(bool enable)
{
	// enable/disable execute block
	ui.Btn_RunReconstruction->setEnabled(enable);
	// enable/disable save button
	ui.actionSave->setDisabled(enable);
}

void FDK_GUI::SaveProjectAs(QString &filename)
{
	QString sinoDir		  = ui.LEd_SinogramDirectory->text();
	QString sinoPreDir	  = ui.LEd_PreprocSinoDirectory->text();
	QString sinoLimPreDir = ui.LEd_LimAnglePreProcDir->text();
	QString projectPath = sinoDir;
	if(projectPath.isEmpty())
	{
		projectPath = sinoPreDir;
		if(projectPath.isEmpty())
		{
			projectPath = sinoLimPreDir;
		}
	}
	if(!projectPath.isEmpty())
	{
		projectPath.chop(1);
		QStringList pathList = projectPath.split("\\");
		pathList.pop_back();
		projectPath = pathList.join("\\");
	}
	else
	{
		projectPath = m_dataPath;
	}
	QString fileName = 
		QFileDialog::getSaveFileName(this, 
		tr("Save Project File"),
		projectPath,
		tr("Project (*.pfdk)"));
	if(fileName.isEmpty())
	{
		return;
	}
	m_projectName = fileName;

	if(!projSerialize.WriteToFile(fileName))
	{
		//reset project name in save as
		//m_projectName.clear();
		QDir fileHandler;
		fileHandler.remove(fileName);
		return;
	}

	// set label project
	QFileInfo projFile(fileName);
	m_toolLabel->clear();
	m_toolLabel->setText(projFile.completeBaseName());
	//-ju- check if all necessary parameters are set 
	// and enable execute panel
	SetGUIOnSave(true);

	//parse Main Wintow Title -no-Project and replace by project name
	QString projectText = projFile.completeBaseName();
	QString winTitle = "-no - Project"; //-ju-20-Nov-2017 windowTitle();
	//QString winTitle = windowTitle();
	QStringList winTitleArray = winTitle.split(tr("-"));
	winTitleArray[1] = projectText;
	QString title = winTitleArray.join(tr("- "));
	setWindowTitle(title);

}

void FDK_GUI::SaveProject(/*QString filename*/)
{
	QString txt = m_toolLabel->text();
	if(m_projectName.isEmpty())
	{
		SaveProjectAs(m_projectName);
		if(m_projectName.isEmpty())
			return;
	}
	if(txt.endsWith(tr("*")))
	{
		if(!projSerialize.WriteToFile(m_projectName))
		{
			return;
		}

		// set label project
		QFileInfo projFile(m_projectName);
		m_toolLabel->clear();
		m_toolLabel->setText(projFile.completeBaseName());
		//-ju- check if all necessary parameters are set 
		// and enable execute panel
		SetGUIOnSave(true);

		//parse Main Wintow Title -no-Project and replace by project name
		QString projectText = projFile.completeBaseName();
		QString winTitle = "-no - Project"; //-ju-20-Nov-2017 windowTitle();
		//QString winTitle = windowTitle();
		QStringList winTitleArray = winTitle.split(tr("-"));
		winTitleArray[1] = projectText;
		QString title = winTitleArray.join(tr("- "));
		setWindowTitle(title);
		// reset * at end
		txt.chop(1);
		m_toolLabel->clear();
		m_toolLabel->setText(txt);
		SetGUIOnSave(true);
		return;
	}
}

void FDK_GUI::OpenProjectFile(QString &filename)
{
	filename = 
		QFileDialog::getOpenFileName(this, 
									 tr("Open Project File"),
									 m_dataPath,
                                     tr("Project File (*.pfdk)"));

	if(filename.isEmpty())
	{
		return;
	}
	m_projectName = filename;

	CtrlSerialize guiElements;
	projSerialize.ReadFromFile(filename,guiElements,m_fileList,m_LimAngleSinoFileList);

	// set controls read from files
	//SetupGuiControls(guiElements);

	// set label project
	QFileInfo projFile(filename);
	m_toolLabel->clear();
	m_toolLabel->setText(projFile.completeBaseName());
}

void FDK_GUI::GetMPIVersion()
{
	QString str = tr("mpich2\\bin");
	if(m_mpiPath.contains(str,Qt::CaseInsensitive))
	{
		//-ju-10-Nov-2011 int idx = ui.CBox_MPIVersion->findText(tr("mpich2"),Qt::MatchContains);
		//-ju-10-Nov-2011 ui.CBox_MPIVersion->setCurrentIndex(idx);
	}
	else
	if(m_mpiPath.contains(tr("deino"),Qt::CaseInsensitive))
	{
		// get version
		int major    = 0;
		int minor    = 0;
		int subMajor = 0;
		int subMinor = 0;
		//VersionNumbers(major,subMajor,minor,subMinor);
#ifdef _DEBUG_TEST
		QString message;
		message.sprintf("Version: %d.%d.%d.%d\n",major,subMajor,minor,subMinor);
		QMessageBox::information(0, "Version MPI", message);
#endif
		if(major == 1)
		{
			//-ju-10-Nov-2011 int idx = ui.CBox_MPIVersion->findText(tr("DeinoMPI1"),Qt::MatchContains);
			//-ju-10-Nov-2011 ui.CBox_MPIVersion->setCurrentIndex(idx);
		}
		else
			if(major == 2)
			{
				//-ju-10-Nov-2011 int idx = ui.CBox_MPIVersion->findText(tr("DeinoMPI2"),Qt::MatchContains);
				//-ju-10-Nov-2011 ui.CBox_MPIVersion->setCurrentIndex(idx);
			}
			else // unkown DeinoMPI version
			{
				//-ju-10-Nov-2011 int idx = ui.CBox_MPIVersion->findText(tr("unknown"),Qt::MatchContains);
				//-ju-10-Nov-2011 ui.CBox_MPIVersion->setCurrentIndex(idx);
				//-ju-25-Nov-2011 QMessageBox::warning(0,
					//-ju-25-Nov-2011 tr("Warning: Unknown DeinoMPI version"),
					//-ju-25-Nov-2011 tr("No known DeinoMPI version found; check path or installation"));
			}
	}
	else // not kown version detected
	{
		//-ju-10-Nov-2011 int idx = ui.CBox_MPIVersion->findText(tr("unknown"),Qt::MatchContains);
		//-ju-10-Nov-2011 ui.CBox_MPIVersion->setCurrentIndex(idx);
		//-ju-25-Nov-2011 QMessageBox::warning(0,
			//-ju-25-Nov-2011 tr("Warning: No MPI version found"),
			//-ju-25-Nov-2011 tr("No known MPI version found; check path or installation"));
	}
}

/*bool FDK_GUI::VersionNumbers(int &major,int &submajor,int &minor,int &subminor)
{

	QString executable = m_mpiPath + tr("\\mpiexec.exe");
	wchar_t totalPath[500];
	int n = executable.toWCharArray(totalPath);
	totalPath[n] = L'\0';
    LPDWORD lpdwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSize(totalPath, lpdwHandle);

	if(!dwSize)
	{
		return false;
	}

	BYTE *pVersionInfo = new BYTE[dwSize];
	
	BOOL r = GetFileVersionInfo(totalPath,
								 0,	// ignore parameter
								 dwSize, 
								 pVersionInfo);
	if(!r)
	{
		delete [] pVersionInfo;
		return false;
	}

    UINT     len;
 
	VS_FIXEDFILEINFO *pFfi;
	r = VerQueryValue(pVersionInfo , L"\\" , (LPVOID *)&pFfi , &len );
	
	if(r)
	{
		DWORD dwBuildNumMS = pFfi->dwFileVersionMS;
		DWORD dwBuildNumLS = pFfi->dwFileVersionLS;

		major	 = HIWORD(dwBuildNumMS);
		submajor = LOWORD(dwBuildNumMS);
		minor	 = HIWORD(dwBuildNumLS);
		subminor = LOWORD(dwBuildNumLS);
		
	}
	delete [] pVersionInfo;

	return true;
}
*/

/////////////
//-ju- slots
///////////////////////////////////////////////////////////////////////////////

// delete all entries from sinogram file list
void FDK_GUI::DeleteALLItemFromList()
{
	if(ui.LEd_SinoNamePattern->isEnabled())
	{
		ui.ListWidget_SinogramList->selectAll();
		QList<QListWidgetItem*> wList = ui.ListWidget_SinogramList->selectedItems();
		foreach(QListWidgetItem* item, wList)
		{
			QString itemTxt = item->text();
			int idx = 0;
			foreach(QString filename, m_fileList)
			{
				if(filename == itemTxt)
				{
					m_fileList.removeAt(idx);
				}
				idx++;
			}
		}
		ui.ListWidget_SinogramList->clear();
	}
}

// batch processing
////////////////////
void FDK_GUI::AddProjectToBatch()
{
	QString filename = 
		QFileDialog::getOpenFileName(this, 
									 tr("Add Project File"),
									 m_dataPath,
                                     tr("Project File (*.pfdk)"));

	if(filename.isEmpty())
	{
		return;
	}
	ui.ListWidget_ReconProjectList->addItem(filename);
}

void FDK_GUI::RemoveProjectFromBatch()
{
	int i = ui.ListWidget_ReconProjectList->currentRow();
	delete ui.ListWidget_ReconProjectList->takeItem(i);
}

void FDK_GUI::RunBatch()
{
	ui.Btn_StopBatch->setEnabled(true);
	ui.Txt_ProcessOutput->clear();
	m_batchCnt = ui.ListWidget_ReconProjectList->count();

	if(m_batchCnt > 0)
	{
		m_batchIndex = 0;
		ui.ListWidget_ReconProjectList->setCurrentRow(m_batchIndex);
		QString fileEntry = ui.ListWidget_ReconProjectList->currentItem()->text();
		CtrlSerialize guiElements;
		projSerialize.ReadFromFile(fileEntry,guiElements,m_fileList,m_LimAngleSinoFileList);
		QFileInfo projFile(fileEntry);
		m_toolLabel->clear();
		m_toolLabel->setText(projFile.completeBaseName());
		QString txtOut(tr("\n\n####################################################################################################"));
		ui.Txt_ProcessOutput->append(txtOut);
		txtOut = tr(">> Project:  ") + fileEntry + " <<";
		ui.Txt_ProcessOutput->append(txtOut);
		txtOut = tr("####################################################################################################");
		ui.Txt_ProcessOutput->append(txtOut);
		m_projectName = fileEntry;
		ui.Btn_RunBatch->setEnabled(false);
		RunReconstruction();
	}
}

void FDK_GUI::SaveProcessOutput()
{
	QString fileName = 
		QFileDialog::getSaveFileName(this, 
		tr("Save Project File"),
		m_dataPath,
		tr("Process Log File (*.plog);; All Files (*.*)"));
	if(fileName.isEmpty())
	{
		return;
	}
	QFile procOut(fileName);
	if(!procOut.open(QIODevice::WriteOnly))
	{
		QString msg;
		msg.sprintf("Can not create/write to File: %s", procOut.fileName().toStdString().c_str());
		QMessageBox::warning(0, tr("Error creating/writing File"), msg);
		return;
	}
	QTextStream procOutStream(&procOut);
	procOutStream << ui.Txt_ProcessOutput->toPlainText();
}

void FDK_GUI::StopBatch()
{
	m_stopBatch = true;
	ui.Btn_StopBatch->setEnabled(false);
	QString txt = ui.statusBar->windowTitle();
	txt +=  tr("Process is running - Stop flag is set - Batch is stopped after process finished!");
	ui.statusBar->showMessage(txt);
	ui.Btn_RunBatch->setEnabled(true);
}

// process update function
void FDK_GUI::UpdateFromFilterProc()
{
	QByteArray line;
	while (!(line = m_filterProc.readLine()).isEmpty())
	{
		QString txt = QString::fromLocal8Bit(line);
		txt.chop(2);
		ui.Txt_ProcessOutput->append(txt);
	}
}

void FDK_GUI::ProcStarted()
{
	QProcess::ProcessState state =  m_filterProc.state();
	if(state == QProcess::Running)
	{
		QString msg(("Weighting and filtering is running ..."));
		ui.statusBar->showMessage(msg);
		ui.Btn_StopWeightFilterProc->setEnabled(true);
		m_timer.start(1000);
	}
}

void FDK_GUI::ProcFinished()
{
	QProcess::ExitStatus exStat = m_filterProc.exitStatus();
	ui.Btn_StopWeightFilterProc->setEnabled(false);
	QString msg;
	switch(exStat)
	{
		case QProcess::NormalExit:
			m_timer.stop();
			msg = tr("Weighting and filtering exited normally.");
			ui.statusBar->showMessage(msg);
			if(ui.CkBox_Backprojection->isChecked())
			{
				// start reconstruction
				QString executeFDKStr;
				int idx = ui.CBox_CT_SystemSelection->currentIndex();
				if(idx == 0) // micro CT
				{
					//-ju-26-July-2011
					ui.tabWidget->setEnabled(false);
					ui.TabWidget_SinogramSettings->setEnabled(false);

					executeFDKStr.sprintf("./FDKRecon.exe \"%s\"",
										  m_projectName.toStdString().c_str());
					m_reconProc.setProcessChannelMode(QProcess::MergedChannels);
					m_reconProc.start(executeFDKStr);
				}
				if(idx == 1) //DETECT CT
				{
					//-ju-26-July-2011
					ui.tabWidget->setEnabled(false);
					ui.TabWidget_SinogramSettings->setEnabled(false);

					executeFDKStr.sprintf("./FDKRecon.exe \"%s\"",
										  m_projectName.toStdString().c_str());
					m_reconProc.setProcessChannelMode(QProcess::MergedChannels);
					m_reconProc.start(executeFDKStr);
				}
			}
			else
			{
				//-ju-26-July-2011
				ui.tabWidget->setEnabled(true);
				ui.TabWidget_SinogramSettings->setEnabled(true);
				ui.Btn_RunReconstruction->setEnabled(true);
			}
			break;
		case QProcess::CrashExit:
			//-ju-26-July-2011
			ui.tabWidget->setEnabled(true);
			ui.TabWidget_SinogramSettings->setEnabled(true);
			ui.Btn_RunReconstruction->setEnabled(true);
			m_timer.stop();
			msg = tr("Weighting and filtering process crashed!");
			ui.statusBar->showMessage(msg);
			//-ju-26-July-2011 -->
			m_batchIndex++;
			if(m_batchIndex < m_batchCnt && !m_stopBatch)
			{
				ui.Btn_StopBatch->setEnabled(true);
				ui.Btn_RunBatch->setEnabled(false);
				ui.ListWidget_ReconProjectList->setCurrentRow(m_batchIndex);
				QString fileEntry = ui.ListWidget_ReconProjectList->currentItem()->text();
				CtrlSerialize guiElements;
				projSerialize.ReadFromFile(fileEntry,guiElements,m_fileList,m_LimAngleSinoFileList);
				QFileInfo projFile(fileEntry);
				m_toolLabel->clear();
				m_toolLabel->setText(projFile.completeBaseName());
				QString txtOut(tr("\n\n####################################################################################################"));
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr(">> Project:  ") + fileEntry + " <<";
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr("####################################################################################################");
				ui.Txt_ProcessOutput->append(txtOut);
				m_projectName = fileEntry;
				RunReconstruction();
			}
			else
			{
				ui.Btn_StopBatch->setEnabled(false);
				ui.Btn_RunBatch->setEnabled(true);
				m_stopBatch = false;
			}
			//-ju-26-July-2011 -->
			break;
	}
}

void FDK_GUI::UpdateFromRecProc()
{
	QByteArray line;
	while (!(line = m_reconProc.readLine()).isEmpty())
	{
		QString txt = QString::fromLocal8Bit(line);
		txt.chop(2);
		if(txt.contains("%"))
		{
		}
		else
		{
			ui.Txt_ProcessOutput->append(txt);
		}
	}
}

void FDK_GUI::ProcStartedRec()
{
	QProcess::ProcessState state =  m_reconProc.state();
	if(state == QProcess::Running)
	{
		QString msg(("Reconstruction is running ..."));
		ui.statusBar->showMessage(msg);
		ui.Btn_StopReconstructionProc->setEnabled(true);
		m_timer.start(1000);
	}
}

void FDK_GUI::ProcFinishedRec()
{
	QProcess::ExitStatus exStat = m_reconProc.exitStatus();
	ui.Btn_StopReconstructionProc->setEnabled(false);
	QString msg;
	switch(exStat)
	{
		case QProcess::NormalExit:
			m_timer.stop();
			msg = tr("Reconstruction exited normally.");
			ui.statusBar->showMessage(msg);
			//-ju-16-Nov-2011 add textfield output
			ui.Txt_ProcessOutput->append(msg);
			//-ju-26-July-2011
			ui.tabWidget->setEnabled(true);
			ui.TabWidget_SinogramSettings->setEnabled(true);
			//-ju-26-July-2011 -->
			m_batchIndex++;
			if(m_batchIndex < m_batchCnt && !m_stopBatch)
			{
				ui.Btn_StopBatch->setEnabled(true);
				ui.Btn_RunBatch->setEnabled(false);
				ui.ListWidget_ReconProjectList->setCurrentRow(m_batchIndex);
				QString fileEntry = ui.ListWidget_ReconProjectList->currentItem()->text();
				CtrlSerialize guiElements;
				projSerialize.ReadFromFile(fileEntry,guiElements,m_fileList,m_LimAngleSinoFileList);
				QFileInfo projFile(fileEntry);
				m_toolLabel->clear();
				m_toolLabel->setText(projFile.completeBaseName());
				QString txtOut(tr("\n\n####################################################################################################"));
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr(">> Project:  ") + fileEntry + " <<";
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr("####################################################################################################");
				ui.Txt_ProcessOutput->append(txtOut);
				m_projectName = fileEntry;
				RunReconstruction();
			}
			else
			{
				ui.Btn_StopBatch->setEnabled(false);
				ui.Btn_RunBatch->setEnabled(true);
				m_stopBatch = false;
			}
			//-ju-26-July-2011 <--

		break;
		case QProcess::CrashExit:
			m_timer.stop();
			msg = tr("Reconstruction process crashed!");
			ui.statusBar->showMessage(msg);
			//-ju-16-Nov-2011 add textfield output
			ui.Txt_ProcessOutput->append(msg);
			//-ju-26-July-2011
			ui.tabWidget->setEnabled(true);
			ui.TabWidget_SinogramSettings->setEnabled(true);
			//-ju-26-July-2011 -->
			m_batchIndex++;
			if(m_batchIndex < m_batchCnt && !m_stopBatch)
			{
				ui.Btn_StopBatch->setEnabled(true);
				ui.Btn_RunBatch->setEnabled(false);
				ui.ListWidget_ReconProjectList->setCurrentRow(m_batchIndex);
				QString fileEntry = ui.ListWidget_ReconProjectList->currentItem()->text();
				CtrlSerialize guiElements;
				projSerialize.ReadFromFile(fileEntry,guiElements,m_fileList,m_LimAngleSinoFileList);
				QFileInfo projFile(fileEntry);
				m_toolLabel->clear();
				m_toolLabel->setText(projFile.completeBaseName());
				QString txtOut(tr("\n\n####################################################################################################"));
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr(">> Project:  ") + fileEntry + " <<";
				ui.Txt_ProcessOutput->append(txtOut);
				txtOut = tr("####################################################################################################");
				ui.Txt_ProcessOutput->append(txtOut);
				m_projectName = fileEntry;
				RunReconstruction();
			}
			else
			{
				ui.Btn_StopBatch->setEnabled(false);
				ui.Btn_RunBatch->setEnabled(true);
				m_stopBatch = false;
			}
			//-ju-26-July-2011 <--
			break;
	}
	ui.Btn_RunReconstruction->setEnabled(true);
}

void FDK_GUI::StopWFProcess()
{
	m_filterProc.kill();
	m_timer.stop();
	QString msg = tr("\n ==> Weight and filter process interrupted manually!");
	ui.statusBar->showMessage(msg);
	ui.Txt_ProcessOutput->append(msg);
	ui.Btn_StopBatch->setEnabled(false);
	ui.Btn_RunBatch->setEnabled(true);
}

void FDK_GUI::StopRecProcess()
{
	m_reconProc.kill();
	m_timer.stop();
	QString msg = tr("\n ==> Reconstruction process interrupted manually!");
	ui.statusBar->showMessage(msg);
	ui.Txt_ProcessOutput->append(msg);
	ui.Btn_StopBatch->setEnabled(false);
	ui.Btn_RunBatch->setEnabled(true);
}

// timer
void FDK_GUI::updateProcTime()
{
	m_procTime += 1.0;
	ui.LCD_timing->display(m_procTime);
}

// starts reconstruction via process interface
void FDK_GUI::RunReconstruction()
{
	m_procTime = 0.0;
	ui.LCD_timing->display(m_procTime);
	// only backprojection
	if(ui.CkBox_Backprojection->isChecked() && !ui.CkBox_WeightFilter->isChecked())
	{
		QString executeFDKStr;
		int idx = ui.CBox_CT_SystemSelection->currentIndex();
		if(idx == 0) // micro CT
		{
			//-05-Sept-2012 check if executable exist
			char *microCTexecutable_str = "./FDKRecon.exe";
			QFile file(microCTexecutable_str);
			if(file.exists())
			{
				//-ju-26-July-2011
				ui.tabWidget->setEnabled(false);
				ui.TabWidget_SinogramSettings->setEnabled(false);
				executeFDKStr.sprintf("%s \"%s\"",
					                  microCTexecutable_str,
									  m_projectName.toStdString().c_str());
				m_reconProc.setProcessChannelMode(QProcess::MergedChannels);
				m_reconProc.start(executeFDKStr);
				ui.Btn_RunReconstruction->setEnabled(false);
			}
			else
			{
				QMessageBox::critical(0,"Can not find executable for MicroCT",microCTexecutable_str);
			}
		}
		if(idx == 1) // DETECT CT
		{
			//-05-Sept-2012 check if executable exist
			char *detectCTexecutable_str = "./FDK_BlockIORec_DETECT_CT.exe";
			QFile file(detectCTexecutable_str);
			if(file.exists())
			{
				//-ju-26-July-2011
				ui.tabWidget->setEnabled(false);
				ui.TabWidget_SinogramSettings->setEnabled(false);
				//-05-Sept-2012 check if executable exist
				executeFDKStr.sprintf("%s \"%s\"",
									  detectCTexecutable_str,
									  m_projectName.toStdString().c_str());
				m_reconProc.setProcessChannelMode(QProcess::MergedChannels);
				m_reconProc.start(executeFDKStr);
				ui.Btn_RunReconstruction->setEnabled(false);
			}
			else
			{
				QMessageBox::critical(0,"Can not find executable for DetectCT",detectCTexecutable_str);
			}
		}
	}
	// filter & yes/no backprojection
	if(ui.CkBox_WeightFilter->isChecked())
	{
		/*-ju-08-Nov-2011 use thread instead
		QString mpi = ui.lineEdit_MPIPath->text();
		if(mpi.isEmpty())
		{
		QMessageBox::warning(0,tr("Error MPI Settings"),tr("Path to mpiexec.exe is not set.\nSet Option in Path Setting."));
		return;
		}
		*/
		//-05-Sept-2012 check if executable exist
		char *filterexecutable_str = "./FDKFilter.exe";
		QFile file(filterexecutable_str);
		if(file.exists())
		{
			//-ju-26-July-2011
			ui.tabWidget->setEnabled(false);
			ui.TabWidget_SinogramSettings->setEnabled(false);
			//QString executeMPIStr;
			QString executeFilterStr;
			//-ju-08-Nov-2011 use thread instead executeMPIStr.sprintf("\"%s\\mpiexec.exe\" -localonly %d WeightFilterFDK.exe \"%s\"",
			//-05-Sept-2012 check if executable exist
			executeFilterStr.sprintf("%s %s",
									 filterexecutable_str,
								     //-ju-08-Nov-2011 mpi.toStdString().c_str(),
								     //-ju-08-Nov-2011 ui.SBox_NumberOfMPIProcesses->value(),
								     m_projectName.toStdString().c_str());
			m_filterProc.setProcessChannelMode(QProcess::MergedChannels);
			m_filterProc.start(executeFilterStr);
			ui.Btn_RunReconstruction->setEnabled(false);
		}
		else
		{
			QMessageBox::critical(0,"Can not find executable for weighting and filtering",filterexecutable_str);
		}
	}
}

// limited angle remove sinograms from file list
void FDK_GUI::LimAngleRemoveSegment()
{
	if(ui.TreeWidget_LimAngleSeg->topLevelItemCount() == 0)
	{
		return;
	}
	QTreeWidgetItem *currentItem = ui.TreeWidget_LimAngleSeg->currentItem();
	if(currentItem == 0)
	{
		return;
	}
	if(currentItem->parent() == 0) // is toplevel item
	{
		int index = ui.TreeWidget_LimAngleSeg->indexOfTopLevelItem(currentItem);
		//QString msg;
		//msg.sprintf("Index: %d",index);
		//QMessageBox::information(0, "Toplevel", msg);
		DelFromLimAngleSinoFileList(index);
		ReListLimAngleSinoFileList();
		SetGuiModified();
	}
	else
	{
		if(!currentItem->parent()->isExpanded())	
			currentItem->parent()->setExpanded(true);
		QMessageBox::information(0, "Child", "Only Segments can be deleted");
	}
}

// limited angle sinogram adding
void FDK_GUI::LimAngleAddSegment()
{
	QStringList fileList =
		QFileDialog::getOpenFileNames(ui.Btn_SelectSinograms,
		tr("Select Sinogram Files"),
		m_dataPath,
		tr("Sinograms (*.sin *.raw);; All Files (*.*)"));
	if(fileList.count() < 1)
	{
		return;
	}


	fileList.sort();
	bool ok;
	double startAngle = QInputDialog::getDouble(this,
		tr("Start Angle"),
		tr("Segment starts with angle in [°]:)"),
		0.0,0.0,360.0,2,&ok);
	if(!ok)
		return;

	double incrAngle = QInputDialog::getDouble(this,
		tr("Increment Angle"),
		tr("Angle Increment in [°]:)"),
		1.0,0.01,180.0,2,&ok);
	if(!ok)
		return;

	double angle = startAngle;
	QMap<QString,double> sino_degree;
	foreach(QString file, fileList)
	{
		sino_degree.insert(file,angle);
		angle += incrAngle;
	}
	m_LimAngleSinoFileList.push_back(sino_degree);
	int node = m_LimAngleSinoFileList.size();
	AddChildsToTree(node,sino_degree,ui.TreeWidget_LimAngleSeg);
	SetGuiModified();
}

// prepocesssed limited angle sinogram directory selection
void FDK_GUI::LimAnglePreProcDirSel()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	m_LimAnglePreProcDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory for preprocessed Files"), 
		m_dataPath,
		QFileDialog::ShowDirsOnly);
	if(m_LimAnglePreProcDir.isEmpty())
	{
		return;
	}
	ui.LEd_LimAnglePreProcDir->setText(m_LimAnglePreProcDir+tr("\\"));
}

// open dialog viewing images
void FDK_GUI::ShowSinogram()
{
	if(ui.CBox_InDataFormat->currentText().trimmed() == "byte")
	{
		DisplaySinograms<uchar>(255);
	}
	else
	if(ui.CBox_InDataFormat->currentText().trimmed() == "short16")
	{
		DisplaySinograms<short>(SHRT_MAX);
	}
	else
	if(ui.CBox_InDataFormat->currentText().trimmed() == "ushort16")
	{
		DisplaySinograms<ushort>(USHRT_MAX);
	}
	else
	if(ui.CBox_InDataFormat->currentText().trimmed() == "int32")
	{
		DisplaySinograms<int>(INT_MAX);
	}
	else
	if(ui.CBox_InDataFormat->currentText().trimmed() == "real32")
	{
		DisplaySinograms<float>(FLT_MAX);
	}
}

void FDK_GUI::RemSelSinoFromList()
{
	DeleteItemSelectionFromList();
}

void FDK_GUI::SinogramPreProcDir()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	QString directory = ui.LEd_SinogramDirectory->text();
	if(directory.isEmpty())
	{
		return;
	}
	QString sinoPreDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory for Prepocessed Sinograms"), 
		m_dataPath,
		QFileDialog::ShowDirsOnly);
	if(sinoPreDir.isEmpty())
	{
		return;
	}
	ui.LEd_PreprocSinoDirectory->clear();

	ui.LEd_PreprocSinoDirectory->setText(sinoPreDir);
}

// file dialog selection of sinograms
void FDK_GUI::SinoFileSelections()
{
	QStringList fileList =
		QFileDialog::getOpenFileNames(ui.Btn_SelectSinograms,
		tr("Select Sinogram Files"),
		m_dataPath,
		tr("Sinograms (*.sin *.raw);; All Files (*.*)"));

	if(fileList.isEmpty())
	{
		return;
	}
	//disable Edit File Pattern Button
	//ui.Btn_EditFilePattern->setChecked(false);
	//-ju- clear input of controls
	ui.ListWidget_SinogramList->clear();
	ui.LEd_SinogramDirectory->clear();
	ui.LEd_SinoNamePattern->clear();
	ui.SBox_NumStartIndex->clear();
	ui.LEd_PreprocSinoDirectory->clear();
	m_fileList.clear();
	m_fileList = fileList;

	m_fileList.sort();
	int i = 0;
	foreach(QString file, m_fileList)
	{
		new QListWidgetItem(m_fileList[i], ui.ListWidget_SinogramList);
		i++;
	}
	ui.SBox_NumberOfProjections->setValue(i);
	ui.DSBox_AngleIncr->setValue(360.0/ui.SBox_NumberOfProjections->value());
	if(m_fileList.size() > 0)
	{
		QFileInfo dir(m_fileList[0]);

		//-ju- sinogram directory
		QString path  = dir.path();
		QStringList preProcPathList = path.split("/");
		preProcPathList[preProcPathList.count()-1] = tr("sino32\\");
		QString preProcPath = preProcPathList.join("\\");
		// set tomo dir
		preProcPathList[preProcPathList.count()-1] = tr("tomo\\");
		ui.LEd_TomoOutDir->clear();
		QString tomoPath = preProcPathList.join("\\");
		ui.LEd_TomoOutDir->insert(tomoPath);
		QString sep("\\");
		path = path.replace("/","\\");
		path = path + sep;
		ui.LEd_SinogramDirectory->insert(path);
		//-ju-07-July-2011
		ui.LEd_PreprocSinoDirectory->insert(preProcPath);
		//ui.LEd_PreprocSinoDirectory->insert(path + tr("sino32\\"));
		ui.LEd_PreprocSinoDirectory->setAlignment(Qt::AlignRight);

		// sinogram access mask
		QString filename = dir.fileName();
		QStringList part = filename.split(".");
		if(part[0].size() == 0)
		{
			QString msg(tr("Filenames with >> . << in front of numbers are not supported"));
			QMessageBox::warning(this, tr("Unsupported Filename"), msg);
			ui.ListWidget_SinogramList->clear();
			ui.LEd_SinogramDirectory->clear();
			ui.LEd_SinoNamePattern->clear();
			ui.LEd_PreprocSinoDirectory->clear();
			return;
		}
		if(!part[0][part[0].size()-1].isDigit())
		{
			QString msg(tr("Filename Format is not Supported - Missing at least one digit"));
			QMessageBox::warning(this, tr("Unsupported Filename"), msg);
			ui.ListWidget_SinogramList->clear();
			ui.LEd_SinogramDirectory->clear();
			ui.LEd_SinoNamePattern->clear();
			ui.LEd_PreprocSinoDirectory->clear();
			return;
		}
		ui.SBox_NumStartIndex->setValue(part[0][part[0].size()-1].digitValue());
		//ju- match and replace last 4 integer number in first part string
		QString pattern = part[0].replace(QRegExp("[0-9]{4,4}$"), "****");
		for(int i = 1; i < part.size(); i++)
		{
			pattern += ".";
			pattern += part[i];
		}
		//-ju-21-Sep-2011 --> Bugfix prevent item from deleting 
		disconnect(ui.LEd_SinoNamePattern,SIGNAL(textEdited(QString)),this,SLOT(DeleteALLItemFromList()));
		//-ju-21-Sep-2011 <--
		ui.LEd_SinoNamePattern->insert(pattern);
		ui.LEd_SinoNamePattern->setAlignment(Qt::AlignRight);
		//-ju-21-Sep-2011 --> Bugfix reset signal connection 
		connect(ui.LEd_SinoNamePattern,SIGNAL(textEdited(QString)),this,SLOT(DeleteALLItemFromList()));
		//-ju-21-Sep-2011 <--
	}
}

// selection of sinogram diretory
void FDK_GUI::SinogramDir()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	QString sinoDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory for Sinograms"), 
		m_dataPath,
		QFileDialog::ShowDirsOnly);
	if(sinoDir.isEmpty())
	{
		return;
	}
	ui.ListWidget_SinogramList->clear();
	ui.LEd_SinogramDirectory->clear();
	ui.LEd_SinoNamePattern->clear();
	ui.LEd_PreprocSinoDirectory->clear();
	ui.LEd_TomoOutDir->clear();
	m_fileList.clear();

	ui.LEd_SinogramDirectory->setEnabled(true);
	ui.LEd_SinogramDirectory->setText(sinoDir+tr("\\"));
	ui.LEd_SinogramDirectory->setEnabled(false);
	QString sinoPreProcDir(sinoDir);
	// set pre-process-sino path
	QStringList parts = sinoPreProcDir.split(tr("\\"));
	parts[parts.count()-1] = tr("sino32\\");
	sinoPreProcDir = parts.join(tr("\\"));
	// set tomo path
	parts[parts.count()-1] = tr("tomo\\");
	QString tomoPath = parts.join("\\");
	ui.LEd_TomoOutDir->insert(tomoPath);

	ui.LEd_PreprocSinoDirectory->setText(sinoPreProcDir);
}

// selection of tomo directory
void FDK_GUI::SetupTomoDir()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	QString tomoDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory for Output Tomograms"), 
		m_dataPath,
		QFileDialog::ShowDirsOnly);
	if(tomoDir.isEmpty())
	{
		return;
	}
	ui.LEd_TomoOutDir->clear();
	ui.LEd_TomoOutDir->setText(tomoDir+tr("\\"));
}

// change number of GPU threads per block accor. to compa. of GPU
void FDK_GUI::ChangeGPUThreads()
{
	int idx = ui.CBox_GPUCompaVers->findText(tr(""),Qt::MatchContains);
	QString entry = ui.CBox_GPUCompaVers->currentText();
	if(entry.contains(tr("1.x"),Qt::CaseInsensitive))
	{
		ui.SBox_GPUThreadsX->setValue(22);
		ui.SBox_GPUThreadsY->setValue(23);
	}
	if(entry.contains(tr("2.x"),Qt::CaseInsensitive))
	{
		ui.SBox_GPUThreadsX->setValue(32);
		ui.SBox_GPUThreadsY->setValue(32);
	}
}

void FDK_GUI::SetGuiModified()
{
	QString txt = m_toolLabel->text();
	// if not flagged at end with *
	if(txt.endsWith(tr("*")))
	{
		return;
	}
	txt += tr("*");
	m_toolLabel->clear();
	m_toolLabel->setText(txt);
	SetGUIOnSave(false);
}

void FDK_GUI::SetOptionModified()
{
	QString txt = ui.dockWidget_ProjectOptions->windowTitle();
	// if not flagged at end with *
	if(txt.endsWith(tr("*")))
	{
		return;
	}
	txt += tr("*");
	ui.dockWidget_ProjectOptions->setWindowTitle(txt);

}

void FDK_GUI::LoadPathSetting()
{
	char *pEnv = getenv("USERPROFILE");
	QString fdkSetting;
	if(pEnv)
	{
		fdkSetting = pEnv;
		fdkSetting += "/FDKGUI.opt";
	}
	else
	{
		fdkSetting = "c:/FDKGUI.opt";
	}
	QFile OptionFile(fdkSetting);
	//QString optFile = tr("FDKGUI.opt");
	//QFile OptionFile(optFile);
	if(!OptionFile.open(QIODevice::ReadOnly))
	{
		/*-ju-28-Nov-2011 do not start option dialog box automatically
		QString msg;
		msg.sprintf("Can not read  path settings file: %s\n Create Settings File.", 
					optFile.toStdString().c_str());
		QMessageBox::warning(0, tr("Error opening File"), msg);
		OptionFile.open(QIODevice::WriteOnly);
		OptionFile.close();
		ui.dockWidget_ProjectOptions->show();
		*/
		ui.statusBar->showMessage(tr("Can not find path settings file"));
		return;
	}
	QTextStream opt(&OptionFile);
	QString textLine;
	while(1)
	{
		textLine = opt.readLine();
		if(textLine.isNull())
			break;
		QStringList keyVal = textLine.split(tr("="));
		QString key = keyVal[0];
		QString val = keyVal[1];
		if(key == tr("MPI_PATH"))
		{
			ui.lineEdit_MPIPath->setText(val);
			m_mpiPath = val;
			if(!m_mpiPath.isEmpty())
			{
				GetMPIVersion();
			}
		}
		if(key == tr("Data_TOP"))
		{
			ui.lineEdit_DataTopDir->setText(val);
			m_dataPath = val;
		}
	}

	QString txt = ui.dockWidget_ProjectOptions->windowTitle();
	txt.chop(1);
	ui.dockWidget_ProjectOptions->setWindowTitle(txt);
}

void FDK_GUI::SavePathSetting()
{
	QString txt = ui.dockWidget_ProjectOptions->windowTitle();
	// if not flagged at end with *
	if(txt.endsWith(tr("*")))
	{
		QFileDialog::getExistingDirectory(0,tr("Directory Selection"),tr("Select Directory for saving Option File FDKGUI.opt (needs write permission!)"));
		char *pEnv = getenv("USERPROFILE");
		QString fdkSetting;
		if(pEnv)
		{
			fdkSetting = pEnv;
			fdkSetting += "/FDKGUI.opt";
		}
		else
		{
			fdkSetting = "c:/FDKGUI.opt";
		}
		QFile OptionFile(fdkSetting);
		if(!OptionFile.open(QIODevice::WriteOnly))
		{
			QString msg;
			msg.sprintf("Can not create/write to File: %s", OptionFile.fileName().toStdString().c_str());
			QMessageBox::warning(0, tr("Error creating/writing File"), msg);
			return;
		}
		QTextStream opt(&OptionFile);
		//QString mpi = ui.lineEdit_MPIPath->text();
		//opt << tr("MPI_PATH=") << mpi << tr("\n");
		QString dataDir = ui.lineEdit_DataTopDir->text();
		opt << tr("Data_TOP=") << dataDir << tr("\n");

		txt.chop(1);
		ui.dockWidget_ProjectOptions->setWindowTitle(txt);
	}
}

void FDK_GUI::SetUseFileList()
{
	if(ui.radioButton_limitedAngleRecon->isChecked())
	{
		ui.checkBox_useFileList->setChecked(true);
		//disconnect(ui.checkBox_useFileList,0,0,SLOT(ResetBlockFileSettings()));
		//connect(ui.checkBox_useFileList,SIGNAL(toggled(bool)),this,SLOT(ResetBlockFileSettings()));
		ui.TabWidget_SinogramSettings->setCurrentWidget(ui.tab_LimAngle);
	}
	else
	{
		ui.TabWidget_SinogramSettings->setCurrentWidget(ui.tab_FullAngle);
	}
}


void FDK_GUI::SetupMPIPath()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	QString mpiDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Directory of MPI executables"), 
		m_mpiPath,
		QFileDialog::ShowDirsOnly);
	if(mpiDir.isEmpty())
	{
		return;
	}
	ui.lineEdit_MPIPath->clear();
	ui.lineEdit_MPIPath->setText(mpiDir);
	m_mpiPath = mpiDir;
	// get mpi version
	GetMPIVersion();
}

void FDK_GUI::SetupDataTopPath()
{
	QFileDialog::Options mode = QFileDialog::Directory;
	QString dataDir = 
		QFileDialog::getExistingDirectory(0, 
		tr("Select Data Top Directory"), 
		m_dataPath,
		QFileDialog::ShowDirsOnly);
	if(dataDir.isEmpty())
	{
		return;
	}
	ui.lineEdit_DataTopDir->clear();
	ui.lineEdit_DataTopDir->setText(dataDir);
	m_dataPath = dataDir;
}

void FDK_GUI::SetBinningSettings()
{
	unsigned short bin = ui.SBox_BinningFactor->value();
	if(bin == 1)
	{
		ui.SBox_VolumeWidth->setEnabled(true);
		ui.SBox_VolumeHeight->setEnabled(true);
		ui.SBox_VolumeDepth->setEnabled(true);
		ui.SBox_VolumeOriginX->setEnabled(true);
		ui.SBox_VolumeOriginY->setEnabled(true);
		ui.SBox_VolumeOriginZ->setEnabled(true);
		int w_max = ui.SBox_ImgWidth->value();
		int h_max = ui.SBox_ImgHeight->value();
		int d_max = w_max;
		ui.SBox_VolumeWidth->setValue(w_max);
		ui.SBox_VolumeHeight->setValue(h_max);
		ui.SBox_VolumeDepth->setValue(d_max);
		ui.SBox_VolumeOriginX->setValue(0);
		ui.SBox_VolumeOriginY->setValue(0);
		ui.SBox_VolumeOriginZ->setValue(0);
	}
	if(bin > 1)
	{
		ui.SBox_VolumeWidth->setEnabled(false);
		ui.SBox_VolumeHeight->setEnabled(false);
		ui.SBox_VolumeDepth->setEnabled(false);
		ui.SBox_VolumeOriginX->setEnabled(false);
		ui.SBox_VolumeOriginY->setEnabled(false);
		ui.SBox_VolumeOriginZ->setEnabled(false);
		int w = ui.SBox_ImgWidth->value();
		int h = ui.SBox_ImgHeight->value();
		int d = w;
		w = w/bin;
		h = h/bin;
		d = d/bin;
		ui.SBox_VolumeWidth->setValue(w);
		ui.SBox_VolumeHeight->setValue(h);
		ui.SBox_VolumeDepth->setValue(d);
		ui.SBox_VolumeOriginX->setValue(0);
		ui.SBox_VolumeOriginY->setValue(0);
		ui.SBox_VolumeOriginZ->setValue(0);
	}
}

void FDK_GUI::CheckMaxVolRecSize()
{
		int w = ui.SBox_VolumeWidth->value();
		int h = ui.SBox_VolumeHeight->value();
		int d = ui.SBox_VolumeDepth->value();
		int x = ui.SBox_VolumeOriginX->value();
		int y = ui.SBox_VolumeOriginY->value();
		int z = ui.SBox_VolumeOriginZ->value();
		int w_max = ui.SBox_ImgWidth->value();
		int h_max = ui.SBox_ImgHeight->value();
		int d_max = w_max;
		m_volSelecTooBig = false;
		if(x+w > w_max)
		{
			int _w = w_max - x;
			if(_w < 0)
			{
				w = w_max;
				x = 0;
			}
			else
			{
				w = _w;
			}
			ui.SBox_VolumeWidth->setValue(w);
			ui.SBox_VolumeOriginX->setValue(x);
			QString msg;
			msg.sprintf("Volume selection (width) to large.\nResize selection.");
			QMessageBox::warning(this,tr("Change Volume Selection"),msg);
			m_volSelecTooBig = true;
		}
		if(y+h > h_max)
		{
			int _h = h_max - y;
			if(_h < 0)
			{
				h = h_max;
				y = 0;
			}
			else
			{
				h = _h;
			}
			ui.SBox_VolumeHeight->setValue(h);
			ui.SBox_VolumeOriginY->setValue(y);
			QString msg;
			msg.sprintf("Volume selection (height) to large.\nResize selection.");
			QMessageBox::warning(this,tr("Change Volume Selection"),msg);
			m_volSelecTooBig = true;
		}
		if(z+d > d_max)
		{
			int _d = d_max - z;
			if(_d < 0)
			{
				d = d_max;
				z = 0;
			}
			else
			{
				d = _d;
			}
			ui.SBox_VolumeDepth->setValue(d);
			ui.SBox_VolumeOriginZ->setValue(z);
			QString msg;
			msg.sprintf("Volume selection (depth) to large.\nResize selection.");
			QMessageBox::warning(this,tr("Change Volume Selection"),msg);
			m_volSelecTooBig = true;
		}
}

//-ju-10-Nov-2011 add
void FDK_GUI::CkeckBlockStatus()
{
}

void FDK_GUI::ResetBlockFileSettings(int val)
{
	if(val)
	{
		int iq = QMessageBox::question(0,tr("Resetting Parameters"),
			tr("Setting Limited Angel Reconstruction or using File List\n"
			"will reset Block-IO settings!"),
			tr("Stop"),tr("Continue"));

		if(iq == 1)
		{
			ui.CkBox_WriteToPreProcBlockFile->setChecked(false);
			ui.CkBox_WriteToPreProcBlockFile->setEnabled(false);

			ui.CkBox_UsePreProcBlockFile->setChecked(false);
			ui.CkBox_UsePreProcBlockFile->setEnabled(false);

			ui.CkBox_WriteBlockFile->setChecked(false);
			ui.CkBox_WriteBlockFile->setEnabled(false);

			ui.CkBox_StoreConvTomoBlockFile->setChecked(false);
			ui.CkBox_StoreConvTomoBlockFile->setEnabled(false);
		}
		else
		{
			//-ju-11-Nov-2011 do explicit switch to full angle rec. button
			ui.radioButton_fullAngleRecon->setChecked(true);
			//-ju-11-Nov-2011 reset state explicit, else stateChanged() SIGNAL is not fired
			ui.checkBox_useFileList->setCheckState(Qt::Unchecked);
			// enable check boxes
			ui.CkBox_WriteToPreProcBlockFile->setEnabled(true);
			ui.CkBox_UsePreProcBlockFile->setEnabled(true);
			ui.CkBox_WriteBlockFile->setEnabled(true);
			ui.CkBox_StoreConvTomoBlockFile->setEnabled(true);
		}
	}
}
void FDK_GUI::ResetDisplaySettings(bool val)
{
	if(val && ui.radioButton_fullAngleRecon->isChecked())
	{
		ui.checkBox_useFileList->setCheckState(Qt::Unchecked);
		ui.CkBox_WriteToPreProcBlockFile->setEnabled(true);
		ui.CkBox_UsePreProcBlockFile->setEnabled(true);
		ui.CkBox_WriteBlockFile->setEnabled(true);
		ui.CkBox_StoreConvTomoBlockFile->setEnabled(true);
	}
}

void FDK_GUI::ResetDisplaySettingsFS(int val)
{
	if(!ui.checkBox_useFileList->isChecked())
	{
		ui.checkBox_useFileList->setCheckState(Qt::Unchecked);
		ui.CkBox_WriteToPreProcBlockFile->setEnabled(true);
		ui.CkBox_UsePreProcBlockFile->setEnabled(true);
		ui.CkBox_WriteBlockFile->setEnabled(true);
		ui.CkBox_StoreConvTomoBlockFile->setEnabled(true);
	}
}

void FDK_GUI::SetVolumeCoord()
{
	if(m_imgDlg != 0)
	{
		QRect volSel = m_imgDlg->GetSelection();
		ui.SBox_VolumeWidth->setValue(volSel.width()*m_imgDlg->GetZoom());
		ui.SBox_VolumeHeight->setValue(volSel.height()*m_imgDlg->GetZoom());
		ui.SBox_VolumeDepth->setValue(volSel.width()*m_imgDlg->GetZoom());
		ui.SBox_VolumeOriginX->setValue(volSel.x()*m_imgDlg->GetZoom());
		ui.SBox_VolumeOriginY->setValue(volSel.y()*m_imgDlg->GetZoom());
		ui.SBox_VolumeOriginZ->setValue(volSel.x()*m_imgDlg->GetZoom());
	}
	else
	{
		QMessageBox::warning(0,tr("No Image Viewer")
			,tr("No Image Viewer Instance available.\n Open Sinogram in Image Viewer"));
	}
}

void FDK_GUI::SetVolumeSelectionButton()
{
	if(ui.checkBox_useFileList->isChecked() && ui.radioButton_fullAngleRecon->isChecked())
	{
		ui.Btn_GetVolumeFromSelection->setEnabled(true);
		//-ju-11-July-2011 m_StyleSheet_DSBox_AngleIncr = ui.DSBox_AngleIncr->styleSheet();
		//-ju-11-July-2011 ui.DSBox_AngleIncr->setStyleSheet("background: greenyellow");
		//-ju-11-July-2011 m_StyleSheet_DSBox_SinoStartAtAngle = ui.DSBox_SinoStartAtAngle->styleSheet();
		//-ju-11-July-2011 ui.DSBox_SinoStartAtAngle->setStyleSheet("background: greenyellow");
	}
	else
	{
		ui.Btn_GetVolumeFromSelection->setEnabled(false);
		//-ju-11-July-2011 ui.DSBox_AngleIncr->setStyleSheet(m_StyleSheet_DSBox_AngleIncr);
	}
}

void FDK_GUI::SetupControls()
{
	if(ui.checkBox_useFileList->isChecked())
	{
		ui.SBox_NumStartIndex->setEnabled(false);
	}
	else
	{
		ui.SBox_NumStartIndex->setEnabled(true);
	}
}

///////////
// actions
///////////////////////////////////////////////////////////////////////////////

// action: save project
void FDK_GUI::ActionSaveProject()
{
	// if no project file is specified select project file
	if(m_toolLabel->text() == tr("*"))
	{
		QString filename;
		SaveProjectAs(filename);
	}
	else
	{
		SaveProject(/*m_toolLabel->text()*/);
	}
}

// action: save project as
void FDK_GUI::ActionSaveProjectAs()
{
	QString filename;
	SaveProjectAs(filename);
}

void FDK_GUI::ActionOpenProject()
{
	QString filename;
	OpenProjectFile(filename);
	if(!filename.isEmpty())
	{
		QFileInfo file(filename);
		QString projectText = file.completeBaseName();
		m_toolLabel->clear();
		m_toolLabel->setText(projectText);
		//parse Main Wintow Title -no-Project and replace by project name
		QString winTitle = "-no - Project"; //-ju-20-Nov-2017 windowTitle();
		QStringList winTitleArray = winTitle.split(tr("-"));
		winTitleArray[1] = projectText;
		QString title = winTitleArray.join(tr("- "));
		setWindowTitle(title);
		ui.actionSave->setEnabled(false);
		ui.Btn_RunReconstruction->setEnabled(true);
	}
}

void FDK_GUI::ActionNewProject()
{
	QString projText = m_toolLabel->text();
	// current project is not saved
	if(projText.endsWith(tr("*")))
	{
		QMessageBox::StandardButton butPressed = 
			QMessageBox::question(this,tr("Save Project"),
				tr("Current project is not saved.\nWill you still continue creating a new project?"),
				QMessageBox::Ok|QMessageBox::No);
		if(butPressed != QMessageBox::StandardButton::Ok)
		{
			return;
		}
	}
	CtrlSerialize guiElements;
	QString filename(tr("defaults\\new.pfdk"));
	QFileInfo file(filename);
	if(file.exists())
	{
		m_fileList.clear();
		m_LimAngleSinoFileList.clear();
		projSerialize.ReadFromFile(filename,guiElements,m_fileList,m_LimAngleSinoFileList);
	}
	else
	{
		QMessageBox::warning(this,tr("Error: missing default template file"),
			tr("Default template file >> defaults\\new.tpl << is missing.\nCheck installation."));
		return;
	}

	m_projectName.clear();
	if(!filename.isEmpty())
	{
		m_toolLabel->clear();
		m_toolLabel->setText(tr("*"));
		ui.actionSave->setEnabled(true);
		setWindowTitle(tr("FDK Reconstruction - no Project"));
	}
}

void FDK_GUI::ActionCheckParameters()
{
	QString txt = m_toolLabel->text();
	// if not flagged at end with *
	if(txt.endsWith(tr("*")))
	{
		QMessageBox::warning(0,
							 tr("Project settings not saved"),
							 tr("Save parameters before proceeding."));
		return;
	}

	// check parameters
	// bool isOk == CheckParamters();
	// if(isOk)
	ui.Btn_RunReconstruction->setEnabled(true);
}

// action: switch option dock window
void FDK_GUI::ActionSwitchView()
{
	if(ui.dockWidget_ProjectOptions->isVisible())
	{
		ui.dockWidget_ProjectOptions->hide();
	}
	else
	{
		ui.dockWidget_ProjectOptions->setFloating(true);
		ui.dockWidget_ProjectOptions->show();
	}
}

void FDK_GUI::ActionImportDetectData()
{
	if(m_importDlg == 0)
	{
		m_importDlg = new ImportDLG(this);
	}
	m_importDlg->show();
	m_importDlg->raise();
	m_importDlg->m_ui.progressBar->setValue(1);

}

//-ju-17-June-2021 new slots
void FDK_GUI::SetTiltCorr()
{
	bool tiltCorrIsCheck = ui.checkBox_applyTiltAxCorr->isChecked();
	if (tiltCorrIsCheck)
	{
		ui.groupBox_ParamShiftCorrCurve->setEnabled(true);
	}
	else
	{
		ui.groupBox_ParamShiftCorrCurve->setEnabled(false);
	}
	SetGuiModified();
}

void FDK_GUI::SlopeTiltValueChanged()
{
	QString beHere = "...";
	SetGuiModified();
}

void FDK_GUI::ConstTiltValueChanged()
{
	QString beHere = "...";
	SetGuiModified();
}