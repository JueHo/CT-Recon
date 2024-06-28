/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "projectionpreprocessor.h"
#include "LorentzFilterDLG.h"

//-12-Oct-2015
uint32_t g_cntCurrentTile = 0;

ProjectionPreProcessor::ProjectionPreProcessor(QWidget *parent)
	: QMainWindow(parent),
	m_rectSelection(0, 0, 0, 0),
	m_doDrawing(false),
	m_scalFactor(1)
{
	// memory stack ptr is 0 in the beginning
	//////////////////////////////////////////
	m_pMemImageStack = 0;
	m_pMemTileImageStack = 0;
	m_pMemScaledImageStack = 0;


	//-ju-05-Oct-2015-new initialize tile size
	///////////////////////////////////////////
	m_processingParam.numOfTiles = 1; //--> all files fit in memory
	// initialize current running tile segment
	m_processingParam.runningTileNo = 0;

	//-ju-21-Oct-2015 no log
	m_processingParam.noLog = false;

	m_processingParam.useLorentzFilter = false;

	//-ju-12-Feb-2018 default is clockwise
	m_processingParam.antiClockWise = 0;

	m_processingParam.maxGreyInStack = 0.0;

	//-ju-25-June-2024
	m_processingParam.useROIPadding = 0;



	// setup gui elements
	ui.setupUi(this);

	// disable export function
	ui.actionExport_PFDK->setEnabled(false);

	//-ju-28-Feb-2018 disable Lorentz filter at start of GUI 
	//--> enable when stack is loaded
	//--> disable after processing filter
	ui.actionLorentz_Filter->setEnabled(false);

	// install event handler
	/////////////////////////
	ui.label_ImageView->installEventFilter(this);

	// set GUI initially to not modified
	m_isModified = false;
	m_processingParam.saveOnly = false;

	// disable GUI --> with new/open/edit enabled
	ui.centralWidget->setEnabled(false);

	// disable interrupt button load data
	ui.pushButton_LoadDataInterrupt->setEnabled(false);


	m_stateHandler.InitStateHandler(&ui, this);

	// Method selection
	////////////////////
	connect(ui.checkBox_Normalize, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::SetEnableMethods);
	connect(ui.checkBox_OutlierSuppression, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::SetEnableMethods);
	connect(ui.checkBox_BHC, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::SetEnableMethods);
	connect(ui.checkBox_StripeReduction, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::SetEnableMethods);
	SetEnableMethods();

	// normalize
	ui.radioButton_UseFlatWindowNormalization->setChecked(false);
	ui.groupBox_NormWin->setEnabled(false);

	// actions
	///////////
	connect(ui.actionNew, &QAction::triggered, this, &ProjectionPreProcessor::NewProject);
	connect(ui.actionSave, &QAction::triggered, this, &ProjectionPreProcessor::SaveProject);
	connect(ui.actionSave_Project_as, &QAction::triggered, this, &ProjectionPreProcessor::SaveProjectAs);
	connect(ui.actionOpen_Project, &QAction::triggered, this, &ProjectionPreProcessor::OpenProject);
	connect(ui.actionExport_PFDK, &QAction::triggered, this, &ProjectionPreProcessor::ExportPFDK);
	connect(ui.actionAbout, &QAction::triggered, this, &ProjectionPreProcessor::About);
	connect(ui.actionLorentz_Filter, &QAction::triggered, this, &ProjectionPreProcessor::StartLorentzFilterDialog);

	/////////////////////////
	// threads
	/////////////////////////

	// load thread
	////////////////
	m_pLoadFileThread = new ThreadLoad(this);
	// connect load thread
	connect(m_pLoadFileThread, &ThreadLoad::valueChanged, this, &ProjectionPreProcessor::LoadValueChanged);
	connect(m_pLoadFileThread, &ThreadLoad::updateProgressBar, this, &ProjectionPreProcessor::LoadThreadUpdateProgressBar);
	connect(m_pLoadFileThread, &ThreadLoad::threadStart, this, &ProjectionPreProcessor::LoadThreadStart);
	connect(m_pLoadFileThread, &ThreadLoad::threadStopped, this, &ProjectionPreProcessor::LoadThreadStopped);
	connect(m_pLoadFileThread, &ThreadLoad::threadEnd, this, &ProjectionPreProcessor::LoadThreadEnd);

	// projection settings connection
	//////////////////////////////////
	connect(ui.lineEdit_projectName, &QLineEdit::textChanged, this, &ProjectionPreProcessor::SetModified);
	connect(ui.lineEdit_projectName, &QLineEdit::textChanged, this, &ProjectionPreProcessor::UpdateMainWindow);
	connect(ui.lineEdit_CreatorOwner, &QLineEdit::textChanged, this, &ProjectionPreProcessor::SetModified);
	connect(ui.lineEdit_date, &QLineEdit::textChanged, this, &ProjectionPreProcessor::SetModified);

	// Normalization
	/////////////////
	connect(ui.radioButton_UseFlatWindowNormalization, &QRadioButton::toggled, this, &ProjectionPreProcessor::NormalizeSelect);
	connect(ui.radioButton_UseFlatFieldNormalization, &QRadioButton::toggled, this, &ProjectionPreProcessor::NormalizeSelect);
	//-ju-23-Feb-2018 enable to work with already dark/falt corrected projections
	connect(ui.checkBox_useDarkFlatCorrected, &QCheckBox::toggled, this, &ProjectionPreProcessor::DarkFlatCorrectedStateChanged);

	// Lorentz Filter
	//////////////////
	connect(ui.checkBox_applyLorentzFilter, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::SetupLorentzFilter);
	// take logarithm -ju-21-Oct-2015
	/////////////////////////////////
	connect(ui.checkBox_NoLogarithm, &QCheckBox::toggled, this, &ProjectionPreProcessor::NoLogStateChanged);

	//-ju-15-Feb-2018 add signal handler for rotation direction changed; (anti) clock wise
	void (QComboBox:: *signalChange)(int) = &QComboBox::currentIndexChanged;
	connect(ui.comboBox_ClockWise, signalChange, this, &ProjectionPreProcessor::ChangeDirection);

	// image process view thread
	//////////////////////////////
	m_pScaleImageThread = new ThreadScImage(this);
	connect(m_pScaleImageThread, &ThreadScImage::threadStart, this, &ProjectionPreProcessor::ScImgThreadThreadStart);
	connect(m_pScaleImageThread, &ThreadScImage::threadEnd, this, &ProjectionPreProcessor::ScImgThreadThreadEnd);
	connect(m_pScaleImageThread, &ThreadScImage::updateProgressBar, this, &ProjectionPreProcessor::ScImgThreadThreadUpdateProgressBar);


	// processesing  thread
	//////////////////////////////
	m_pProcessingThread = new ThreadProcessing(this);
	connect(m_pProcessingThread, &ThreadProcessing::threadStart, this, &ProjectionPreProcessor::ProcessingThreadStart);
	connect(m_pProcessingThread, &ThreadProcessing::threadEnd, this, &ProjectionPreProcessor::ProcessingThreadEnd);
	connect(m_pProcessingThread, &ThreadProcessing::valueChanged, this, &ProjectionPreProcessor::ProcessingThreadValueChanged);
	connect(m_pProcessingThread, &ThreadProcessing::updateProgressBar, this, &ProjectionPreProcessor::ProcessingThreadUpdateProgressbar);
	connect(ui.pushButton_Run, &QPushButton::clicked, this, &ProjectionPreProcessor::RunProcessing);

	// connections
	connect(ui.pushButton_SelInputDir, &QPushButton::clicked, this, &ProjectionPreProcessor::I_SelectInputFiles);
	connect(ui.pushButton_LoadInputData, &QPushButton::clicked, this, &ProjectionPreProcessor::I_LoadInputData);
	// interrupt load thread
	connect(ui.pushButton_LoadDataInterrupt, &QPushButton::clicked, this, &ProjectionPreProcessor::I_LoadInputDataInterrupt);
	// load flat field image
	connect(ui.pushButton_SelectFlat, &QPushButton::clicked, this, &ProjectionPreProcessor::LoadFlatFieldImage);
	connect(ui.pushButton_SelectDark, &QPushButton::clicked, this, &ProjectionPreProcessor::LoadDarkFieldImage);
	// save message output
	connect(ui.pushButton_SaveMessageOutput, &QPushButton::clicked, this, &ProjectionPreProcessor::SaveOutputMessage);
	connect(ui.pushButton_SelectOutputDir, &QPushButton::clicked, this, &ProjectionPreProcessor::SaveProcessedData);
	// save settings
	connect(ui.pushButton_SaveSettingsForRun, &QPushButton::clicked, this, &ProjectionPreProcessor::CheckSettingsForRun);
	// if BHC is checked normalization must be checked too
	connect(ui.checkBox_BHC, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::BHCStateChanged);
	connect(ui.checkBox_Normalize, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::NormalizeStateChanged);
	//-ju-21-Oct-2015 add checkbox signal handler for disabling logarithm
	// save data
	connect(ui.pushButton_SaveDataStart, &QPushButton::clicked, this, &ProjectionPreProcessor::RunSaving);

	// local tomography
	/////////////////////
	connect(ui.checkBox_local_tomo, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::LocalTomoEnable);
	void (QSpinBox::* signalSpinLocTomo)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox_roi_percentage, signalSpinLocTomo, this, &ProjectionPreProcessor::LocTomoPercentage);
	void (QSpinBox::* signalSpinAVGRange)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox_roi_percentage, signalSpinAVGRange, this, &ProjectionPreProcessor::AVGRange);

	// image view
	///////////////
	void (QSpinBox:: *signalSpin)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox_SliceNumber, signalSpin, this, &ProjectionPreProcessor::ImageViewShowImage);
	connect(ui.spinBox_SliceNumber, signalSpin, ui.horizontalSlider_imageView, &QSlider::setValue);
	connect(ui.pushButton_UndoImageProcessing, &QPushButton::clicked, this, &ProjectionPreProcessor::UndoImageProcessing);
	connect(ui.pushButton_applyEqualize, &QPushButton::clicked, this, &ProjectionPreProcessor::EqualizeImages);
	void (QDoubleSpinBox::*signalDoubleSpin)(double) = &QDoubleSpinBox::valueChanged;
	connect(ui.doubleSpinBox_ContrastSlope, signalDoubleSpin, this, &ProjectionPreProcessor::ChangeContrastOfCurrentImage);
	connect(ui.doubleSpinBox_ContrastOffset, signalDoubleSpin, this, &ProjectionPreProcessor::ChangeContrastOfCurrentImage);
	connect(ui.pushButton_ContrastApply, &QPushButton::clicked, this, &ProjectionPreProcessor::ContrastApplyToImages);

	connect(ui.checkBox_EnableWindowSelection, &QCheckBox::stateChanged, this, &ProjectionPreProcessor::WindowsSelectionState);

	//-ju- try to read settings
	////////////////////////////
	QDir dir;
	QString settingPath = dir.homePath();
	settingPath += "/empa/pre_proj_settings.txt";
	QFile file(settingPath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream settings(&file);
		// last project directory
		QString line = settings.readLine();
		QStringList paramList = line.split('=');
		m_lastProjectPath = paramList[1];
		// main window width
		line = settings.readLine();
		paramList = line.split('=');
		int mainWinWidth = paramList[1].toInt();
		// main window height
		line = settings.readLine();
		paramList = line.split('=');
		int mainWinHeight = paramList[1].toInt();
		// main window x pos
		line = settings.readLine();
		paramList = line.split('=');
		int mainWinXPos = paramList[1].toInt();
		// main window y pos
		line = settings.readLine();
		paramList = line.split('=');
		int mainWinYPos = paramList[1].toInt();
		file.close();

		this->resize(mainWinWidth, mainWinHeight);
		this->move(mainWinXPos, mainWinYPos);
	}
	else
	{
		m_lastProjectPath = dir.rootPath();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProjectionPreProcessor::~ProjectionPreProcessor()
{
	QDir dir;
	QString settingPath = dir.homePath();
	QString tempPath = settingPath + "/empa";
	QDir setDir(tempPath);
	if (!setDir.exists())
	{
		setDir.mkpath(tempPath);
	}
	settingPath += "/empa/pre_proj_settings.txt";
	QSize sz = this->size();
	QPoint pt = this->pos();
	QFile file(settingPath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream settings(&file);
		if (m_lastProjectPath.isEmpty())m_lastProjectPath = dir.rootPath();
		settings << "LastProjectPath=" << m_lastProjectPath << "\n";
		settings << "Win_Width=" << sz.width() << "\n";
		settings << "Win_Height=" << sz.height() << "\n";
		settings << "Win_X_Pos=" << pt.x() << "\n";
		settings << "Win_Y_POS=" << pt.y() << "\n";
		file.close();
	}
	DeAllocImageStack();
	DeAllocScaledImageStack();
}

bool ProjectionPreProcessor::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if (targetCtrl == ui.label_ImageView && ui.checkBox_EnableWindowSelection->isChecked())
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if (mEvt->button() == Qt::LeftButton)
			{
				Mat m = GetCurrentVizImage();
				ui.label_ImageView->setPixmap(Mat2Pixmap(m));
				ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
				ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
				m_doDrawing = true;
				m_x = mEvt->x();
				m_y = mEvt->y();
				QPixmap pix((*(ui.label_ImageView->pixmap())));
				m_pix = pix;
			}
		}
		if (targetCtrl == ui.label_ImageView && event->type() == QEvent::MouseMove && ui.checkBox_EnableWindowSelection->isChecked())
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if (m_doDrawing)
			{
				Mat m = GetCurrentVizImage();

				QPoint ptnStart(m_x, m_y);
				QPoint ptnMove = mEvt->pos();
				int32_t xs_n = m_x;
				int32_t ys_n = m_y;
				int32_t xe_n = ptnMove.x();
				int32_t ye_n = ptnMove.y();
				xe_n = min(xe_n, m.cols - 2);
				ye_n = min(ye_n, m.rows - 2);
				xe_n = max(xe_n, -1);
				ye_n = max(ye_n, -1);
				QPoint pntMv(xe_n, ye_n);
				QPixmap pix(m_pix);
				QPainter paint(&pix);
				QPen pen(Qt::blue, 1);
				paint.setPen(pen);
				QRect drawRect(ptnStart, pntMv);
				paint.drawRect(drawRect);
				ui.label_ImageView->setPixmap(pix);
				// re-use in ImageViewShowImage()
				//////////////////////////////////
				m_rectSelectionRedraw = drawRect;
			}
		}
		if (event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if (m_doDrawing)
			{
				Mat m = GetCurrentVizImage();
				m_doDrawing = false;
				QPoint ptnStart(m_x, m_y);
				QPoint ptnEnd = mEvt->pos();

				// check if valid rectangle --> width, height wird negativ
				int32_t xs_n = m_x;
				int32_t ys_n = m_y;
				int32_t xe_n = ptnEnd.x();
				int32_t ye_n = ptnEnd.y();
				if (xs_n > xe_n)
				{
					std::swap(xs_n, xe_n);
				}
				if (ys_n > ye_n)
				{
					std::swap(ys_n, ye_n);
				}
				xe_n = min(xe_n, m.cols-1);
				ye_n = min(ye_n, m.rows-1);
				xe_n = max(xe_n, 0);
				ye_n = max(ye_n, 0);
				QPoint p1(xs_n, ys_n);
				QPoint p2(xe_n, ye_n);
				m_rectSelection.setTopLeft(p1);
				m_rectSelection.setBottomRight(p2);
				ui.spinBox_NormWinXPos->setValue(m_rectSelection.x() * m_scalFactor);
				ui.spinBox_xWinPos->setValue(m_rectSelection.x() * m_scalFactor);
				ui.spinBox_NormWinYPos->setValue(m_rectSelection.y() * m_scalFactor);
				ui.spinBox_yWinPos->setValue(m_rectSelection.y() * m_scalFactor);
				ui.spinBox_NormWinWidth->setValue(m_rectSelection.width() * m_scalFactor);
				ui.spinBox_WinWidth->setValue(m_rectSelection.width() * m_scalFactor);
				ui.spinBox_NormWinHeight->setValue(m_rectSelection.height() * m_scalFactor);
				ui.spinBox_WinHeight->setValue(m_rectSelection.height() * m_scalFactor);
			}
		}
	}
	this->update();
	return QMainWindow::eventFilter(targetCtrl, event);
}


float *ProjectionPreProcessor::GetMemoryStackPtr()
{
	return m_pMemImageStack;
}

uchar *ProjectionPreProcessor::GetScaledImageStackPtr()
{
	return m_pMemScaledImageStack;
}

float *ProjectionPreProcessor::GetTileMemoryStackPtr()
{
	return m_pMemTileImageStack;
}


bool ProjectionPreProcessor::AllocMemory()
{
	if (m_processingParam.array3DSize == 0)
	{
		QMessageBox::information(this, tr("Wrong Parameters"), tr("Allocation failed. Image stack size is zero!"), QMessageBox::Ok);
		return false;
	}

	m_pMemImageStack = new float[m_processingParam.array3DSize];
	if (0 == m_pMemImageStack)
	{
		QMessageBox::critical(this, tr("Alloc Error"), tr("Can not alloc memory for image stack!"), QMessageBox::Ok);
		return false;
	}
	return true;
}

bool ProjectionPreProcessor::AllocTileMemory()
{
	DeAllocTileImageStack();
	if (m_processingParam.tileArray3DMaxSize == 0)
	{
		QMessageBox::information(this, tr("Wrong Parameters"), 
			tr("Allocation of tiled image stack failed. Image stack size is zero!"), 
			QMessageBox::Ok);
		return false;
	}
	m_pMemTileImageStack = new float[m_processingParam.tileArray3DMaxSize];
	if (0 == m_pMemTileImageStack)
	{
		QMessageBox::critical(this, tr("Tile Alloc Error"), 
			tr("Can not alloc memory for tile image stack!"), 
			QMessageBox::Ok);
		return false;
	}
	return true;
}

void ProjectionPreProcessor::DeAllocImageStack()
{
	if (m_pMemImageStack)
	{
		delete[] m_pMemImageStack;
		m_pMemImageStack = 0;
	}
}

void ProjectionPreProcessor::DeAllocTileImageStack()
{
	if (m_pMemTileImageStack)
	{
		delete[] m_pMemTileImageStack;
		m_pMemTileImageStack = 0;
	}
}

bool ProjectionPreProcessor::AllocScaledImgStacKMemory(uint64_t arr3DSz)
{
	if (arr3DSz == 0)
	{
		QMessageBox::information(this, tr("Wrong Parameters"), tr("Allocation failed. Scaled Image stack size is zero!"), QMessageBox::Ok);
		return false;
	}

	m_pMemScaledImageStack = new uchar[arr3DSz];
	if (0 == m_pMemScaledImageStack)
	{
		QMessageBox::critical(this, tr("Alloc Error"), tr("Can not alloc memory for scaled image stack!"), QMessageBox::Ok);
		return false;
	}
	return true;
}

void ProjectionPreProcessor::DeAllocScaledImageStack()
{
	if (m_pMemScaledImageStack)
	{
		delete[] m_pMemScaledImageStack;
		m_pMemScaledImageStack = 0;
	}
}

ProcessParameter ProjectionPreProcessor::GetprocessingParam()
{
	return m_processingParam;
}

void ProjectionPreProcessor::SetScaleFactor(uint32_t scFac)
{
	m_scalFactor = scFac;
}

//-ju-23-Feb-2018 
void ProjectionPreProcessor::SetMaxGreyValue(double greyVal)
{
	m_maxGreyVal = greyVal;
}


// --> action slots
////////////////////
void ProjectionPreProcessor::NewProject()
{
	// if memory is allocted --> delete it
	////////////////////////////////////////
	DeAllocImageStack();

	MakeEditable();
	// initialize fields
	/////////////////////
	ClearProjectSettings(); // reset first
	// clear progress bar
	ui.progressBar_LoadData->setMinimum(0);
	ui.progressBar_LoadData->setMaximum(10000);
	ui.progressBar_LoadData->setValue(0);
	//dito image vis
	ui.progressBar_ImageProcessing->setFormat(tr(""));
	ui.progressBar_ImageProcessing->setMaximum(100);
	ui.progressBar_ImageProcessing->setValue(0);


	// project name
	ui.lineEdit_projectName->setText(tr("****"));

	// user/owner name
	QString loginUserName(tr("*****"));
	char acUserName[100];
	DWORD nUserName = sizeof(acUserName);
	if (GetUserNameA(acUserName, &nUserName))
	{
		loginUserName = acUserName;
	}
	ui.lineEdit_CreatorOwner->setText(loginUserName);

	// default date
	ui.lineEdit_date->setText(QDateTime::currentDateTime().toString());

	// enable GUI
	ui.centralWidget->setEnabled(true);

	// disable export function
	ui.actionExport_PFDK->setEnabled(false);
}

void ProjectionPreProcessor::SaveProject()
{
	// ask for file name
	if (m_processingParam.projectFileName.isEmpty())
	{
		SaveFileProccess();
	}
	else // check if file exists
	{
		QFileInfo projectFile(m_processingParam.projectFileName);
		if (projectFile.exists())
		{
			WriteProjectParameterToFile();
			QString title = this->windowTitle();
			if (title[title.size() - 1] == '*')
			{
				title.truncate(title.size() - 1);
				this->setWindowTitle(title);
			}
		}
		else
		{
			SaveFileProccess();
		}
	}

}

void ProjectionPreProcessor::SaveProjectAs()
{
	SaveFileProccess();
}


void ProjectionPreProcessor::OpenProject()
{
	EnableForOpen();
	ClearProjectSettings();
	// vis progress bar
	ui.progressBar_ImageProcessing->setFormat(tr(""));
	ui.progressBar_ImageProcessing->setValue(0);

	// open project setting
	////////////////////////
	QString projectFile = QFileDialog::getOpenFileName(this,
		tr("Open project file"),
		m_lastProjectPath,
		tr("Project File (*.pprx)"));
	if (!projectFile.isEmpty())
	{
		QFileInfo fileInfo(projectFile);
		std::cout << "Path" << fileInfo.absolutePath().toStdString() << std::endl;
		m_lastProjectPath = fileInfo.absolutePath();
		m_processingParam.projectFileName = projectFile;
		WriteProjectParameterToGui();
	}

	// if oppening was sucsessfull -->
	// if memory is allocted --> delete it
	////////////////////////////////////////
	DeAllocImageStack();
}

void ProjectionPreProcessor::About()
{
	QMessageBox::information(this, 
		tr("Version Information"), 
		tr("Pre-processor Version 2.1.0 \n"
			"June 2024\n"
			"Copyright (c) Empa 2015. Center for X-ray Analytics\n"
			"Author: Juergen Hofmann"), 
		QMessageBox::Ok);
}

void ProjectionPreProcessor::ExportPFDK()
{
	// save project before exporting
	/////////////////////////////////
	WriteProjectParameterToFile();

	ProjectSerialize ser;
	QString logFile = QFileDialog::getOpenFileName(this,
		tr("Open log file"),
		m_lastProjectPath,
		tr("Log File (*.log)"));
	if (!logFile.isEmpty())
	{
		QFileInfo fileInfo(logFile);
		m_lastProjectPath = fileInfo.absolutePath();
		CtrlSerialize lgPar;
		ser.ReadLogFile(logFile, lgPar);

		// read all other parameters
		/////////////////////////////
		lgPar.projectName = ui.lineEdit_projectName->text();
		lgPar.imageWidth = ui.spinBox_ProjectionWidth->value();
		lgPar.imageHeight = ui.spinBox_ProjectionHeight->value();
		lgPar.numberOfProjections = ui.spinBox_NumberProjections->value()-1;
		lgPar.horizShift = 0.0;
		lgPar.vertShift = 0.0;
		int32_t idx = ui.comboBox_OutputFileType->currentIndex();
		switch (idx)
		{
		case 0:
			lgPar.inDataFormat = "real32";
			break;
		case 1:
			lgPar.inDataFormat = "uint16";
			break;
		}
		lgPar.startIndex = 1;
		lgPar.filterType = tr("Ramp");
		lgPar.phaseContrastFilter = 0;
		lgPar.flipImage = 2;
		lgPar.binFactor = 1;
		lgPar.volWidth = lgPar.imageWidth;
		lgPar.volHeight = lgPar.imageHeight;
		lgPar.volOrigX = 0;
		lgPar.volOrigY = 0;
		lgPar.volOrigZ = 0;
		QString sd = ui.lineEdit_OutPutDir->text();
		sd += "/";
		lgPar.sinoDir = sd;
		QString sdf = ui.lineEdit_OutPutDir->text();
		QStringList spSdf = sdf.split(tr("/"));
		sdf = sdf.replace(spSdf[spSdf.size() - 1], tr("sino32"));
		sdf += tr("/");
		lgPar.sino32Dir = sdf;
		QString pattern = ui.lineEdit_OutRawPattern->text();
		pattern = pattern.replace('#', '*');
		lgPar.sinoNamePattern = pattern;
		QString tom = ui.lineEdit_OutPutDir->text();
		QStringList spTom = tom.split(tr("/"));
		tom = tom.replace(spTom[spTom.size() - 1], tr("tomo"));
		tom += tr("/");
		lgPar.tomoDir = tom;
		lgPar.outDataFormat = tr("real32");
		lgPar.tomoName = tr("tomo_");
		lgPar.cpuMemUsage = 90.0;
		lgPar.gpuMemUsage = 90.0;
		lgPar.gpuThreadX = 16;
		lgPar.gpuThreadY = 16;
		lgPar.gpuVersion = tr("2.xx +");
		lgPar.numOfGPUThreads = 1;
		lgPar.useFileList = 0;
		lgPar.sino32BlockUse = 0;
		lgPar.sino32BlockWrite = 0;
		lgPar.tomoBlockWrite = 0;
		lgPar.convBlockInternal = 0;
		lgPar.doWeightAndFiltering = 1;
		lgPar.doBackprojection = 0;


		// save pfdk file
		//////////////////
		QString pfdkFile = m_lastProjectPath + "/" + ui.lineEdit_projectName->text();
		QString saveFileName = QFileDialog::getSaveFileName(this, 
			tr("Save Project Reconstruction File"),
			pfdkFile,
			//ui.lineEdit_projectName->text(),
			tr("FDK project file (*.pfdk)"));
		if (!saveFileName.isEmpty())
		{
			ser.WriteASCIIFile(saveFileName, lgPar);
		}
	}

}

// <-- action slots
////////////////////


void ProjectionPreProcessor::SetModified()
{
	m_isModified = true;
	QString modSign(tr("*"));
	QString title = this->windowTitle();
	if (title[title.size() - 1] != '*')
	{
		title = title + modSign;
		this->setWindowTitle(title);
	}
}


void ProjectionPreProcessor::UpdateMainWindow()
{
	// get old title
	QString newTitel = this->windowTitle();
	// get parts of title
	QStringList titleList = newTitel.split(' ');
	// modify last string in list
	titleList[4] = ui.lineEdit_projectName->text();
	// remove white spaces
	titleList[4] = titleList[4].remove(' ');
	// merge it
	newTitel = titleList.join(' ');
	this->setWindowTitle(newTitel);
	ui.lineEdit_projectName->setText(titleList[4]);
	// set to modif
	SetModified();
}

void ProjectionPreProcessor::EnableForOpen()
{
	// enable central window
	ui.centralWidget->setEnabled(true);
	// change running controls
	ui.tabWidget_ParameterSettings->setEnabled(false);
	ui.groupBox_runBatch->setEnabled(false);
	ui.pushButton_Run->setEnabled(false);
	ui.pushButton_SaveSettingsForRun->setEnabled(true);
}

void ProjectionPreProcessor::MakeEditable()
{
	ui.centralWidget->setEnabled(true);
	ui.tabWidget_ParameterSettings->setEnabled(true);
	ui.groupBox_runBatch->setEnabled(true);
	ui.pushButton_Run->setEnabled(false);
}

void ProjectionPreProcessor::MakeOpenEditable()
{
	// enable central window
	ui.centralWidget->setEnabled(true);
	// change running controls
	ui.tabWidget_ParameterSettings->setEnabled(true);
	ui.groupBox_runBatch->setEnabled(true);
	ui.pushButton_Run->setEnabled(false);
	ui.pushButton_SaveSettingsForRun->setEnabled(true);
}


void ProjectionPreProcessor::LoadValueChanged(QString msg)
{
	ui.textEdit_MessagesOutput->append(msg);
	cout << msg.toUtf8().data() << endl;
}

// --> handling signal of load files thread
////////////////////////////////////////////
void ProjectionPreProcessor::LoadThreadStopped()
{
	m_pLoadFileThread->m_thread_stopped = true;
	ui.textEdit_MessagesOutput->append(tr("> Loading Files Stopped by User!"));
	ui.textEdit_MessagesOutput->append(tr("> Clean up resources!"));
	ui.pushButton_LoadInputData->setEnabled(true);
	ui.pushButton_LoadDataInterrupt->setEnabled(false);
	//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
	if (!ui.comboBox_ClockWise->isEnabled())
	{
		ui.comboBox_ClockWise->setEnabled(true);
	}

	// clean up resources
	//////////////////////
	DeAllocImageStack();
	ui.progressBar_LoadData->setValue(0);
}

void ProjectionPreProcessor::LoadThreadStart()
{
	ui.pushButton_LoadInputData->setEnabled(false);
	ui.pushButton_LoadDataInterrupt->setEnabled(true);
	ui.actionNew->setEnabled(false);
	ui.actionOpen_Project->setEnabled(false);
	ui.actionSave->setEnabled(false);
	ui.actionSave_Project_as->setEnabled(false);
	//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
	if (ui.comboBox_ClockWise->isEnabled())
	{
		ui.comboBox_ClockWise->setEnabled(false);
	}

}

void ProjectionPreProcessor::LoadThreadEnd()
{
	if (m_pLoadFileThread->m_thread_stopped == true)
	{
		ui.textEdit_MessagesOutput->append(tr("> No Images to visualize"));
		ui.pushButton_LoadInputData->setEnabled(true);
		ui.pushButton_LoadDataInterrupt->setEnabled(false);
		ui.actionNew->setEnabled(true);
		ui.actionOpen_Project->setEnabled(true);
		ui.actionSave->setEnabled(true);
		ui.actionSave_Project_as->setEnabled(true);
		//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
		if (!ui.comboBox_ClockWise->isEnabled())
		{
			ui.comboBox_ClockWise->setEnabled(true);
		}
	}
	else // create scaled image stack and load first image
	{
		//-ju-23-Feb-2018
		m_processingParam.maxGreyInStack = m_maxGreyVal;
		//-ju-09-Oct-2015 implement tiling
		if (m_processingParam.applyMemTiling)
		{
			//-12-Oct-2015if (m_processingParam.runningTileNo == 1)
			if (g_cntCurrentTile == 1)
			{
				// prepare and run scaling thread
				//////////////////////////////////
				DeAllocScaledImageStack(); // clean memory before loading new scaled images
				uint64_t row = ui.spinBox_ProjectionHeight->value();
				uint64_t col = ui.spinBox_ProjectionWidth->value();
				uint64_t cnt = ui.spinBox_NumberProjections->value();
				while (max(row, col) > MAX_IMAGE_SIZE)
				{
					col /= 2;
					row /= 2;
				}
				m_processingParam.imgHeightScaled = row;
				m_processingParam.imgWidthScaled = col;
				uint64_t arr3DSz = row*col*cnt;
				AllocScaledImgStacKMemory(arr3DSz);

				ui.progressBar_ImageProcessing->setMaximum(cnt);

				ui.actionNew->setEnabled(true);
				ui.actionOpen_Project->setEnabled(true);
				ui.actionSave->setEnabled(true);
				ui.actionSave_Project_as->setEnabled(true);
				//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
				if (!ui.comboBox_ClockWise->isEnabled())
				{
					ui.comboBox_ClockWise->setEnabled(true);
				}


				// starting scaling thread
				///////////////////////////
				m_pScaleImageThread->start();

				// reset progess bar vis
				ui.progressBar_ImageProcessing->setFormat(tr("Process for visualisation"));
				ui.progressBar_ImageProcessing->setValue(0);
			}
		}
		else
		{
			// prepare and run scaling thread
			//////////////////////////////////
			DeAllocScaledImageStack(); // clean memory before loading new scaled images
			uint64_t row = ui.spinBox_ProjectionHeight->value();
			uint64_t col = ui.spinBox_ProjectionWidth->value();
			uint64_t cnt = ui.spinBox_NumberProjections->value();
			while (max(row, col) > MAX_IMAGE_SIZE)
			{
				col /= 2;
				row /= 2;
			}
			m_processingParam.imgHeightScaled = row;
			m_processingParam.imgWidthScaled = col;
			uint64_t arr3DSz = row*col*cnt;
			AllocScaledImgStacKMemory(arr3DSz);

			ui.progressBar_ImageProcessing->setMaximum(cnt);

			ui.actionNew->setEnabled(true);
			ui.actionOpen_Project->setEnabled(true);
			ui.actionSave->setEnabled(true);
			ui.actionSave_Project_as->setEnabled(true);
			//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
			if (!ui.comboBox_ClockWise->isEnabled())
			{
				ui.comboBox_ClockWise->setEnabled(true);
			}


			// starting scaling thread
			///////////////////////////
			m_pScaleImageThread->start();

			// reset progess bar vis
			ui.progressBar_ImageProcessing->setFormat(tr("Process for visualisation"));
			ui.progressBar_ImageProcessing->setValue(0);

		}

	}
	QString msg;
	QString dateTime = QDateTime::currentDateTime().toString();
	ui.textEdit_MessagesOutput->append(tr("> ") + dateTime);
	msg.sprintf("> Loading files finished.\n");
	ui.textEdit_MessagesOutput->append(msg);
	// if load of data finished allow processing
	ui.pushButton_SaveSettingsForRun->setEnabled(true);
}

void ProjectionPreProcessor::ScImgThreadThreadStart()
{
	if (m_processingParam.applyMemTiling)
	{
		//-12-Oct-2015 if (m_processingParam.runningTileNo == 1)
		if (g_cntCurrentTile == 1)
		{
			ui.pushButton_LoadDataInterrupt->setEnabled(false);
			QString msg;
			QString dateTime = QDateTime::currentDateTime().toString();
			ui.textEdit_MessagesOutput->append(tr("> ") + dateTime);
			msg.sprintf("> Scaling images thread started.\n");
			ui.textEdit_MessagesOutput->append(msg);
			ui.actionNew->setEnabled(false);
			ui.actionOpen_Project->setEnabled(false);
			ui.actionSave->setEnabled(false);
			ui.actionSave_Project_as->setEnabled(false);
		}
	}
	else
	{
		ui.pushButton_LoadDataInterrupt->setEnabled(false);
		QString msg;
		QString dateTime = QDateTime::currentDateTime().toString();
		ui.textEdit_MessagesOutput->append(tr("> ") + dateTime);
		msg.sprintf("> Scaling images thread started.\n");
		ui.textEdit_MessagesOutput->append(msg);
		ui.actionNew->setEnabled(false);
		ui.actionOpen_Project->setEnabled(false);
		ui.actionSave->setEnabled(false);
		ui.actionSave_Project_as->setEnabled(false);
	}
}

void ProjectionPreProcessor::ScImgThreadThreadEnd()
{
	//-ju-09-Oct-2015 implement tiling
	if (m_processingParam.applyMemTiling && g_cntCurrentTile == 1)
	{
		uint64_t cnt = ui.spinBox_NumberProjections->value();
		ui.progressBar_ImageProcessing->setMaximum(cnt);

		Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);
		uint64_t imageSize = m_processingParam.imgHeightScaled *  m_processingParam.imgWidthScaled;

		ui.progressBar_ImageProcessing->setFormat(tr("Done"));

		for (int i = 0; i < cnt; i++)
		{
			uint64_t offset = imageSize*i;
			memcpy(visImage.data, &m_pMemScaledImageStack[offset], imageSize*sizeof(uchar));
			visImage.copyTo(m_visImageStack[i]);
		}
		ui.progressBar_ImageProcessing->setFormat(tr("Done"));
		ui.progressBar_ImageProcessing->setValue(0);

		Mat m;
		m_visImageStack[0].copyTo(m);
		ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
		ui.label_ImageView->setPixmap(Mat2Pixmap(m));
		QSize sz = ui.label_ImageView->pixmap()->size();
		ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
		ui.horizontalSlider_imageView->setValue(1);
		ui.spinBox_SliceNumber->setValue(1);
		ui.spinBox_SliceNumber->setMaximum(m_processingParam.selectedImages.count());
		ui.horizontalSlider_imageView->setMaximum(m_processingParam.selectedImages.count());


		QString msg;
		QString dateTime = QDateTime::currentDateTime().toString();
		ui.textEdit_MessagesOutput->append(tr("> ") + dateTime);
		msg.sprintf("> Scaling images finished.\n");
		ui.textEdit_MessagesOutput->append(msg);
		ui.pushButton_LoadInputData->setEnabled(true);
		ui.pushButton_LoadDataInterrupt->setEnabled(false);
		ui.actionNew->setEnabled(true);
		ui.actionOpen_Project->setEnabled(true);
		ui.actionSave->setEnabled(true);
		ui.actionSave_Project_as->setEnabled(true);
	}
	else
	{
		uint64_t cnt = ui.spinBox_NumberProjections->value();
		ui.progressBar_ImageProcessing->setMaximum(cnt);

		Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);
		uint64_t imageSize = m_processingParam.imgHeightScaled *  m_processingParam.imgWidthScaled;

		ui.progressBar_ImageProcessing->setFormat(tr("Done"));

		for (int i = 0; i < cnt; i++)
		{
			uint64_t offset = imageSize*i;
			memcpy(visImage.data, &m_pMemScaledImageStack[offset], imageSize*sizeof(uchar));
			visImage.copyTo(m_visImageStack[i]);
		}
		ui.progressBar_ImageProcessing->setFormat(tr("Done"));
		ui.progressBar_ImageProcessing->setValue(0);

		Mat m;
		m_visImageStack[0].copyTo(m);
		ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
		ui.label_ImageView->setPixmap(Mat2Pixmap(m));
		QSize sz = ui.label_ImageView->pixmap()->size();
		ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
		ui.horizontalSlider_imageView->setValue(1);
		ui.spinBox_SliceNumber->setValue(1);
		ui.spinBox_SliceNumber->setMaximum(m_processingParam.selectedImages.count());
		ui.horizontalSlider_imageView->setMaximum(m_processingParam.selectedImages.count());


		QString msg;
		QString dateTime = QDateTime::currentDateTime().toString();
		ui.textEdit_MessagesOutput->append(tr("> ") + dateTime);
		msg.sprintf("> Scaling images finished.\n");
		ui.textEdit_MessagesOutput->append(msg);
		ui.pushButton_LoadInputData->setEnabled(true);
		ui.pushButton_LoadDataInterrupt->setEnabled(false);
		ui.actionNew->setEnabled(true);
		ui.actionOpen_Project->setEnabled(true);
		ui.actionSave->setEnabled(true);
		ui.actionSave_Project_as->setEnabled(true);

	}
	//-ju-28-Feb-2018
	ui.actionLorentz_Filter->setEnabled(true);

}

void ProjectionPreProcessor::ProcessingThreadStart()
{
	ui.textEdit_MessagesOutput->append(tr("> Processing Thread started."));
	ui.pushButton_Run->setEnabled(false);
	ui.pushButton_SaveSettingsForRun->setEnabled(false);
	ui.pushButton_CancelRun->setEnabled(false);
	//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
	if (ui.comboBox_ClockWise->isEnabled())
	{
		ui.comboBox_ClockWise->setEnabled(false);
	}
	//-ju-23-09-2015 ui.pushButton_CancelRun->setEnabled(true);
	//-ju-28-Feb-2018
	ui.actionLorentz_Filter->setEnabled(false);
}

void ProjectionPreProcessor::ProcessingThreadEnd()
{
	ui.pushButton_Run->setEnabled(false);
	// to avoid processing again without reloading of data
	///////////////////////////////////////////////////////
	ui.pushButton_SaveSettingsForRun->setEnabled(false);
	ui.pushButton_CancelRun->setEnabled(false);
	//-ju-21-Oct-2015 enable LoadData Button
	ui.pushButton_LoadInputData->setEnabled(true);
	//-ju-20-Feb-2018 disable rotation direction combo box while processing is running
	if (!ui.comboBox_ClockWise->isEnabled())
	{
		ui.comboBox_ClockWise->setEnabled(true);
	}
	ui.textEdit_MessagesOutput->append(tr("> Processing Thread finished.\n"));
	m_processingParam.saveOnly = false;
}

void ProjectionPreProcessor::ProcessingThreadValueChanged(QString msg)
{
	ui.textEdit_MessagesOutput->append(msg);
}

void ProjectionPreProcessor::ProcessingThreadUpdateProgressbar(int32_t pos)
{
	ui.progressBar_Savedata->setValue(pos);
}

void ProjectionPreProcessor::RunProcessing()
{
	//check if output directory is specified
	/////////////////////////////////////////
	if (m_processingParam.outputDirectory.isEmpty())
	{
		QMessageBox::warning(this, tr("Missing Directory"), tr("No output directory specified \nDid you saved the project?"));
		return;
	}
	if (m_processingParam.outputFilepattern.isEmpty())
	{
		QMessageBox::warning(this, tr("Missing File Pattern"), tr("No output file pattern specified \nDid you saved the project?"));
		return;
	}
	ui.progressBar_Savedata->setMaximum(m_processingParam.cntProj);
	ui.tabWidget_IOSettings->setCurrentIndex(1);
	//-ju-15-Feb-2018 make sure that rotation direction is set --> in future new organisation
	m_processingParam.antiClockWise = ui.comboBox_ClockWise->currentIndex();
	m_pProcessingThread->start();
}

void ProjectionPreProcessor::RunSaving()
{
	m_processingParam.saveOnly = true;
	RunProcessing();
}

void ProjectionPreProcessor::ScImgThreadValueChanged(QString msg)
{
}

void ProjectionPreProcessor::ScImgThreadThreadUpdateProgressBar(int prog)
{
	ui.progressBar_ImageProcessing->setValue(prog);
}

void ProjectionPreProcessor::LoadThreadUpdateProgressBar(int prog)
{
	ui.progressBar_LoadData->setValue(prog);
}
// <-- handling signal of load files thread
////////////////////////////////////////////
bool ProjectionPreProcessor::TileProjections(const uint32_t NumTiles)
{
	// tiling
	//////////
	//std::vector<TileOffset> tileSegments;
	uint64_t height = m_processingParam.imgHeight;
	uint64_t width = m_processingParam.imgWidth;
	uint32_t numSeg = NumTiles;
	uint32_t segmentHeight = height / (numSeg);
	uint32_t remindingRows = height % segmentHeight;
	uint32_t maxSegSize = segmentHeight + remindingRows + 2;
	// segment overlap is one in every direction
	uint32_t overlap = 1;

	if (maxSegSize <= 128)
	{
		printf("Segments too small.\nAlgorithms are not applicable.\nNeed more memory\n");
		return false;
	}

	for (int i = 0; i < numSeg; i++)
	{
		TileInfo imgSegInfo;
		// first segement
		if (i == 0)
		{
			imgSegInfo.from = 0;
			imgSegInfo.offsetSegStart = 0;
			imgSegInfo.to = segmentHeight + overlap; // ".to" is exclusive, but need 1 Pixel overlap
			imgSegInfo.length = segmentHeight*width;
			imgSegInfo.height = segmentHeight + overlap;
			m_processingParam.tilesSegmentProperties.push_back(imgSegInfo);
		}
		// last segment
		if (i == numSeg - 1)
		{
			// last segment  
			// append with reminder tile
			if (remindingRows > 0)
			{
				imgSegInfo.from = i*segmentHeight - overlap; // -1 --> overlap to privious segment
				imgSegInfo.offsetSegStart = overlap*width; // one row in segment ahead
				imgSegInfo.to = (i + 1)*segmentHeight + remindingRows;
				imgSegInfo.length = (remindingRows + segmentHeight)*width;
				imgSegInfo.height = segmentHeight + remindingRows + overlap;
				m_processingParam.tilesSegmentProperties.push_back(imgSegInfo);
			}
			else // full tile
			{
				imgSegInfo.from = i*segmentHeight - overlap; // -1 --> overlap to privious segment
				imgSegInfo.offsetSegStart = overlap * width; // one row in segment ahead
				imgSegInfo.to = (i + 1)*segmentHeight;
				imgSegInfo.length = segmentHeight*width;
				imgSegInfo.height = segmentHeight + overlap;
				m_processingParam.tilesSegmentProperties.push_back(imgSegInfo);
			}
		}
		else
			if (i != 0) // segment between
			{
				imgSegInfo.from = i*segmentHeight - overlap; // -1 --> overlap to privious segment
				imgSegInfo.offsetSegStart = overlap * width; // one row in segment ahead
				imgSegInfo.to = (i + 1)*segmentHeight + overlap;
				imgSegInfo.length = segmentHeight*width;
				imgSegInfo.height = segmentHeight + 2 * overlap;
				m_processingParam.tilesSegmentProperties.push_back(imgSegInfo);
			}
	}
	return true;
}

uint32_t ProjectionPreProcessor::CheckTileMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	uint64_t memAvail = status.ullAvailPhys;

	//-ju- calulate memory usage for projection stack data type float
	uint64_t xDim = static_cast<uint64_t>(ui.spinBox_ProjectionWidth->value());
	uint64_t yDim = static_cast<uint64_t>(ui.spinBox_ProjectionHeight->value());
	uint64_t projCnt = static_cast<uint64_t>(ui.spinBox_NumberProjections->value());
	//-ju-06-Oct-2015 full stack
	uint64_t arraySize = xDim * yDim * projCnt;

	// add 10% memory usage for ongoing calculations
	uint64_t memSize = arraySize * sizeof(float);
	uint64_t memSizeExt = (arraySize + arraySize / 10) * sizeof(float);
	uint64_t MByte = static_cast<uint64_t>(1024 * 1024);

	// check maximal memory usage. Includes memory clone for RAC
	/////////////////////////////////////////////////////////////
	uint64_t maxMemUsage = ui.spinBox_MemMultFac->value() * memSizeExt;
	//if (maxMemUsage >= memAvail)
	//{
		// prepare of new alloc if image stack size changed
	if (arraySize != m_processingParam.tileArray3DMaxSize)
	{
		DeAllocTileImageStack();
	}
	// calculate number of tiles
	/////////////////////////////
	m_processingParam.numOfTiles = maxMemUsage / memAvail;
	m_processingParam.numOfTiles += 1; // if 1 then stack fits in memory

	// all fits in memory
	if (m_processingParam.numOfTiles == 1)
	{
		m_processingParam.tileArray3DMaxSize = arraySize;
	}
	else
	{
		// array size of tiled image stack should always fit in memory 
		m_processingParam.tileArray3DMaxSize = arraySize / m_processingParam.numOfTiles; // not memory in uchar!

		// do re-seting
		m_processingParam.tilesSegmentProperties.clear();

		//-ju-07-Oct-2015	create tiling info of projections;
		//					write info into tilesSegmentProperties 
		//////////////////////////////////////////////////////////
		if (TileProjections(m_processingParam.numOfTiles) == false)
		{
			// return 0 tiles if fails
			m_processingParam.tileArray3DMaxSize = 0;
			return 0;
		}
		uint64_t maxSegHeight = 0;
		for (int i = 0; i < m_processingParam.tilesSegmentProperties.size(); i++)
		{
			maxSegHeight = max(maxSegHeight, m_processingParam.tilesSegmentProperties[i].height);
		}
		// used for memory allocation of image tile stack
		// reusing allocated memory
		//////////////////////////////////////////////////
		m_processingParam.tileArray3DMaxSize = m_processingParam.imgWidth * m_processingParam.cntProj * maxSegHeight;
	}
	return m_processingParam.numOfTiles;
}


bool ProjectionPreProcessor::CheckAvailableMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	uint64_t memAvail = status.ullAvailPhys;

	//-ju- calulate memory usage for projection stack data type float
	uint64_t xDim = static_cast<uint64_t>(ui.spinBox_ProjectionWidth->value());
	uint64_t yDim = static_cast<uint64_t>(ui.spinBox_ProjectionHeight->value());
	uint64_t projCnt = static_cast<uint64_t>(ui.spinBox_NumberProjections->value());
	uint64_t arraySize = xDim * yDim * projCnt;
	
	// prepare of new alloc if image stack size changed
	if (arraySize != m_processingParam.array3DSize)
	{
		DeAllocImageStack();
	}

	// add 15% memory usage for ongoing calculations
	uint64_t memSize = (arraySize + arraySize/6) * sizeof(float);
	uint64_t MByte = static_cast<uint64_t>(1024 * 1024);

	if (memSize >= memAvail)
	{
		QString msg;
		msg.sprintf("Not enough memory to proceed process.\n"
			        "Need: %d MB get:%d MB\n"
					"Stop processing!", 
					memSize / MByte, memAvail / MByte);
		int ret = QMessageBox::critical(this, tr("Memory exhausted"), msg, QMessageBox::Ok);
		return false;
	}
	if (memSize + memSize/2 >= memAvail && ui.checkBox_StripeReduction->isChecked())
	{
		QString msg;
		msg.sprintf("Probably not enough memory to proceed process.\n"
			        "Need aproximatally: %d MB get:%d MB\n"
					"Disable stripe reduction or reduce padding", 
					(memSize + memSize / 2 )/ MByte, memAvail / MByte);
		int ret = QMessageBox::warning(this, tr("Memory exhausted"), msg, 
			                           QMessageBox::Ignore| QMessageBox::Abort);
		switch (ret)
		{
		case QMessageBox::Ignore:
			break;
		case QMessageBox::Abort:
			return false;
		}
	}
	m_processingParam.array3DSize = arraySize;
	m_processingParam.memAllocSize = arraySize*sizeof(float);
	m_processingParam.imgWidth = xDim;
	m_processingParam.imgHeight = yDim;
	m_processingParam.cntProj = projCnt;
	return true;
}

bool ProjectionPreProcessor::CreateProjectionFilesList()
{
	QDir projectionsDir;
	QString p = ui.lineEdit_InputDir->text();
	projectionsDir.setPath(ui.lineEdit_InputDir->text());
	QString filePattern1 = ui.lineEdit_InputFilePattern->text();
	QString filePattern2 = ui.lineEdit_InputFilePattern->text();
	filePattern1 += QString("*.tif");
	filePattern2 += QString("*.tiff");
	projectionsDir.setNameFilters(QStringList() << filePattern1 << filePattern2);

	// check validity of projection stack
	//////////////////////////////////////
	if (projectionsDir.entryList().empty())
	{
		int ret = QMessageBox::information(this, tr("No Files"), tr("No projection files found!"), QMessageBox::Ok);
		return false;
	}
	m_inputFileList.clear();
	QStringList tmpList = projectionsDir.entryList();
	for (int i = 0; i < projectionsDir.count(); i++)
	{
		if (i < ui.spinBox_NumberProjections->value())
		{
			QString path = ui.lineEdit_InputDir->text();
			path += "/";
			path += tmpList[i];
			m_inputFileList.push_back(path);
		}
		else
		{
			break;
		}
	}
	//m_inputFileList = projectionsDir.entryList();
	return true;
}


void ProjectionPreProcessor::I_LoadInputData()
{
	// check if directory and file pattern is specified
	////////////////////////////////////////////////////
	QString indir = ui.lineEdit_InputDir->text();
	indir = indir.trimmed();
	uint32_t szdir = indir.size();
	QString inpat = ui.lineEdit_InputFilePattern->text();
	inpat = inpat.trimmed();
	uint32_t szpat = inpat.size();
	uint32_t m = szdir * szpat;
	if (0 == m)
	{
		QMessageBox::information(this, tr("Missing Parameters"), tr("Missing file selection parameters!"), QMessageBox::Ok);
		return;
	}

	// check if image height and width and projection count is set
	///////////////////////////////////////////////////////////////
	uint64_t w = ui.spinBox_ProjectionWidth->value();
	uint64_t h = ui.spinBox_ProjectionHeight->value();
	uint64_t c = ui.spinBox_NumberProjections->value();
	uint64_t r = w * h * c;
	if (0 == r)
	{
		QMessageBox::information(this, tr("Missing Parameters"), tr("Missing projection parameters!"), QMessageBox::Ok);
		return;
	}

	//-ju-24-June-2024 calc. roi width
	uint32_t percentage = ui.spinBox_roi_percentage->value();
	uint32_t width = ui.spinBox_ProjectionWidth->value();
	m_processingParam.roiPadSize = width * percentage / 100;
	// hard coded for currently used filter width in ring artefact correction of 32
	////////////////////////////////////////////////////////////////////////////////
	const uint32_t corr_filter_RAC = 32;
	width = 2*width * percentage / 100 + width - corr_filter_RAC;
	m_processingParam.totalPadLocTomoSize = width;
	QString projection_width; 
	projection_width.sprintf("%d", width);
	ui.lineEdit_roi_show_width->setText(projection_width);
	// automatically estimate slope factor for the sigmoid
	m_processingParam.sigmoidSlope = 20.0f / static_cast<float>(m_processingParam.roiPadSize);
	ui.doubleSpinBox_sigmoid_slope->setValue(m_processingParam.sigmoidSlope);
	// store average range
	m_processingParam.locTomoAVGRange = ui.spinBox_AVG_range->value();
	// calculate weights for roi tomo padding
	Calc_Sigmoid_weight(m_processingParam.localTomoWeights, m_processingParam.roiPadSize, m_processingParam.sigmoidSlope);


	////////////////////////////////////////////////////////////////////////////////////////////
	//-ju-23-09-2015
	// switch between memory tile version and none
	////////////////////////////////////////////////////////////////////////////////////////////
	if (ui.checkBox_TileMemory->isChecked())
	{
		DeAllocImageStack();
		DeAllocTileImageStack();
		m_processingParam.applyMemTiling = true;
		m_processingParam.tilesSegmentProperties.clear();
		if (m_processingParam.tilesSegmentProperties.size() == 0)
		{
			m_processingParam.numOfTiles = CheckTileMemory();
			if (m_processingParam.numOfTiles == 0)
			{
				// 0 --> not able to do tiling
				//-ju-22-Oct-2015 need error message
				return;
			}
			if (m_processingParam.numOfTiles == 1)
			{
				QString msg;
				msg.sprintf("Tiling is not necessary, got only 1 tile.\n"
					"Please continue without tiling or increase memory save setting.");
				QMessageBox::information(this, tr("Tiling is not applicable"), msg,
					QMessageBox::Ok);
				m_processingParam.applyMemTiling = false;
				DeAllocTileImageStack();
				return;
			}
			//-ju-05-Oct-2015-new set to tile 1
			m_processingParam.runningTileNo = 1;
			//-ju-12-Oct-2015
			g_cntCurrentTile = 1;
		}
		if (m_inputFileList.size() == ui.spinBox_NumberProjections->value())
		{
			// load first tile & create image vizualisation	stack
			// allocate memory for tile stack
			if (m_inputFileList.size() == 0)
			{
				int ret = QMessageBox::information(this, tr("No Files"), tr("No projection files found!"), QMessageBox::Ok);
				return;
			}
			m_processingParam.selectedImages = m_inputFileList;
			if (m_pMemTileImageStack == 0)
			{
				AllocTileMemory();
			}
			m_pLoadFileThread->m_thread_stopped = false;
			// settings for progress bar
			ui.progressBar_LoadData->setMinimum(0);
			ui.progressBar_LoadData->setMaximum(m_processingParam.selectedImages.count());
			ui.progressBar_LoadData->setValue(0);
			// image view slider & spin box
			ui.spinBox_SliceNumber->setMinimum(1);
			ui.spinBox_SliceNumber->setValue(1);
			// set size of visualization image stack
			/////////////////////////////////////////
			m_visImageStack.resize(m_processingParam.selectedImages.count());
			// loading image stack to memory in a separate thread
			//////////////////////////////////////////////////////
			m_pLoadFileThread->start(); // call run method in thread

#define _IN_DEVELOP
#ifdef _IN_DEVELOP
//			exit(-999);
#endif
		}
		else
		{
			QMessageBox::warning(this, tr("Inconsistent Number of Projections"), 
				tr("Inconsistent Number of Projections. Please correct!"),
				QMessageBox::Ok);
			return;
		}

		// read scaled image stack and then first tile
		//////////////////////////////////////////////
		return; // bad style. But works!
	}

	// before loading data check available memory
	//////////////////////////////////////////////
	//-ju-20-Oct-2015 
	DeAllocImageStack();
	DeAllocTileImageStack();
	m_processingParam.numOfTiles = 0; // reset tiles -> need if tiling was enabled before
	m_processingParam.applyMemTiling = false;
	if (!CheckAvailableMemory())return;

	//--> memory stack in ProjectionPreProcessor definieren und in thread referenzieren
	//	tracking des pointers alloc/dealloc --> aendern falls grösse aendert

	if (m_inputFileList.size() != ui.spinBox_NumberProjections->value())
	{
		QString msg;
		msg.sprintf("Number of selected files (%d) does not match number of projections (%d)!\n"
			        "Loading %d projections using file pattern >> %s*.%s <<?",
					m_inputFileList.size(), 
					ui.spinBox_NumberProjections->value(), 
					ui.spinBox_NumberProjections->value(),
					ui.lineEdit_InputFilePattern->text().toStdString().c_str(),
					ui.comboBox_SelFileType->currentText().toStdString().c_str());
		int ret = QMessageBox::question(this, tr("Inconsistent Number of Projections"), msg,
			QMessageBox::Ok | QMessageBox::Cancel);


		Mat matIni = Mat::zeros(512, 512, CV_8U);
		switch (ret)
		{
		case QMessageBox::Ok:
			// do directory scanning of files using file pattern
			// to implement
			if (!CreateProjectionFilesList())return;
			m_processingParam.selectedImages = m_inputFileList;
			if (m_pMemImageStack == 0)
			{
				AllocMemory();
			}
			m_pLoadFileThread->m_thread_stopped = false;
			// settings for progress bar
			ui.progressBar_LoadData->setMinimum(0);
			ui.progressBar_LoadData->setMaximum(m_processingParam.selectedImages.count());
			ui.progressBar_LoadData->setValue(0);
			// set size of visualization image stack
			/////////////////////////////////////////
			m_visImageStack.clear();
			for (int i = 0; i < m_processingParam.selectedImages.count(); i++)
			{
				m_visImageStack.push_back(matIni);
			}
			// loading image stack to memory in a separate thread
			//////////////////////////////////////////////////////
			m_pLoadFileThread->start(); // call run method in thread
			break;
		case QMessageBox::Cancel:
			return;
		}
	}
	else
	{
		if (m_inputFileList.size() == 0)
		{
			int ret = QMessageBox::information(this, tr("No Files"), tr("No projection files found!"), QMessageBox::Ok);
			return;
		}
		m_processingParam.selectedImages = m_inputFileList;
		if (m_pMemImageStack == 0)
		{
			AllocMemory();
		}
		m_pLoadFileThread->m_thread_stopped = false;
		// settings for progress bar
		ui.progressBar_LoadData->setMinimum(0);
		ui.progressBar_LoadData->setMaximum(m_processingParam.selectedImages.count());
		ui.progressBar_LoadData->setValue(0);
		// image view slider & spin box
		ui.spinBox_SliceNumber->setMinimum(1);
		ui.spinBox_SliceNumber->setValue(1);
		// set size of visualization image stack
		/////////////////////////////////////////
		m_visImageStack.resize(m_processingParam.selectedImages.count());
		// loading image stack to memory in a separate thread
		//////////////////////////////////////////////////////
		m_pLoadFileThread->start(); // call run method in thread
	}
}

void ProjectionPreProcessor::I_LoadInputDataInterrupt()
{
	m_pLoadFileThread->m_interrupt = true;
}

void ProjectionPreProcessor::I_SelectInputFiles()
{
	QString currentText = ui.comboBox_SelFileType->itemText(ui.comboBox_SelFileType->currentIndex());
	if (currentText == "tif / tiff")
	{
		QStringList fList = QFileDialog::getOpenFileNames(this, tr("Select Projection Files"),
			m_lastProjectPath,
			//"f:/Data/test/Hematite_Filter3_Ti_140keV/Hematite_Filter3_Ti_140keV_0001",
			tr("Projection File (*.tif *.tiff)"));
		if (fList.count() == 0)return;
		m_inputFileList.clear();
		m_inputFileList = fList;

		QString fileName = m_inputFileList[0];
		QFileInfo file;
		file.setFile(fileName);
		QDir directory = file.absoluteDir();
		m_inputFilePattern = file.baseName();
		m_inputSuffix = file.suffix();
		m_inputDirName = file.absolutePath();
		m_inputFilePattern.truncate(m_inputFilePattern.length() - 4);
		ui.lineEdit_InputDir->setText(m_inputDirName);
		ui.lineEdit_InputFilePattern->setText(m_inputFilePattern);
		ui.spinBox_NumberProjections->setValue(m_inputFileList.size());
		QString msg;
		msg.sprintf("> Select %d files in directory %s", m_inputFileList.size(), m_inputDirName.toUtf8().data());
		ui.textEdit_MessagesOutput->append(msg);
		// open one file to get file information
		/////////////////////////////////////////
		QByteArray bStr = fileName.toUtf8();
		string projectionPathStr = bStr.data();
		string filePath = projectionPathStr;
		cv::Mat temp = imread(filePath, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);
		m_imgW_Cols = temp.cols;
		m_imgH_Rows = temp.rows;
		ui.spinBox_ProjectionWidth->setValue(m_imgW_Cols);
		ui.spinBox_ProjectionHeight->setValue(m_imgH_Rows);
		QString type(type2str(temp.type()).c_str());
		ui.label_CVDataType->setText(type);
		ui.textEdit_MessagesOutput->append(tr("> Get file info"));//appendPlainText(tr("Get file info"));
	}
}

void ProjectionPreProcessor::ClearProjectSettings()
{
	// project filename
	m_processingParam.projectFileName.clear();
	// project settings
	///////////////////
	ui.lineEdit_projectName->clear();
	ui.lineEdit_CreatorOwner->clear();
	ui.lineEdit_date->clear();
	m_processingParam.projectName.clear();
	m_processingParam.projectOwner.clear();
	m_processingParam.projectDate.clear();

	// file & projection setting
	/////////////////////////////
	ui.lineEdit_InputDir->clear();
	ui.lineEdit_InputFilePattern->clear();
	ui.spinBox_ProjectionHeight->setValue(0);
	ui.spinBox_ProjectionWidth->setValue(0);
	ui.spinBox_NumberProjections->setValue(0);
	ui.label_CVDataType->clear();
	ui.lineEdit_OutPutDir->clear();
	ui.lineEdit_OutRawPattern->clear();
	ui.comboBox_OutputFileType->setCurrentIndex(0);
	m_processingParam.inputDiretory.clear();
	m_processingParam.inputFilepattern.clear();
	m_processingParam.imgHeight = 0;
	m_processingParam.imgWidth = 0;
	m_processingParam.cntProj = 0;
	m_processingParam.dataTypeIn = -1;
	m_processingParam.selectedImages.clear();
	m_processingParam.outputDirectory.clear();
	m_processingParam.outputFilepattern.clear();
	m_processingParam.dataTypeOut = 0;

	// methods toolbox pages
	/////////////////////////
	ui.toolBox_ProcessingMethods->setCurrentIndex(0);

	// method selection -> normalize
	/////////////////////////////////
	ui.checkBox_Normalize->setChecked(true);
	ui.radioButton_UseFlatFieldNormalization->setChecked(true);
	m_processingParam.useNormalisation = 1;
	m_processingParam.useWinNormalisation = 0;
	// flat file normalization
	m_processingParam.useFlatFieldFileNormalisation = 1;
	ui.lineEdit_FlatFieldImage->clear();
	ui.lineEdit_DarkFieldImage->clear();
	m_processingParam.flatFieldImageFile.clear();
	m_processingParam.darkFieldImageFile.clear();
	// normalization using selected windows
	ui.spinBox_NormWinHeight->setValue(0);
	ui.spinBox_NormWinWidth->setValue(0);
	ui.spinBox_NormWinXPos->setValue(0);
	ui.spinBox_NormWinYPos->setValue(0);
	m_processingParam.xWinPos = 0;
	m_processingParam.yWinPos = 0;
	m_processingParam.widthWin = 0;
	m_processingParam.heightWin = 0;

	// method selection -> outlier
	/////////////////////////////////
	ui.checkBox_OutlierSuppression->setChecked(true);
	ui.comboBox_MethodSelection->setCurrentIndex(0);
	ui.stackedWidget_MethodsParameter->setCurrentIndex(0);
	ui.doubleSpinBox_SigmaMean9->setValue(6.0);
	ui.doubleSpinBox_SigmaMedian9->setValue(6.0);
	m_processingParam.useOutlierSupRAC = 1;
	m_processingParam.useOutlierSup = 1;
	m_processingParam.useRAC = 0;
	m_processingParam.correctAlgo = 0;
	m_processingParam.outlierSigmaMedian9 = 6.0;
	m_processingParam.outlierSigmaMean9 = 6.0;

	// local/ROI tomography (add 24-June-2024)
	//////////////////////////////////////////
	ui.checkBox_local_tomo->setChecked(false);
	ui.lineEdit_roi_show_width->setEnabled(false);
	ui.spinBox_roi_percentage->setEnabled(false);


	// method selection -> BHC
	/////////////////////////////////
	ui.checkBox_BHC->setChecked(false);
	ui.doubleSpinBox_BHCCorrectionExpo->setValue(2.0);

	// method selection -> stripe reduction
	////////////////////////////////////////
	ui.checkBox_StripeReduction->setChecked(false);
	ui.comboBox_PadMultFFT->setCurrentIndex(1); // pad by 2
	ui.checkBox_FFTRunMultiThread->setChecked(false);
	m_processingParam.useStripReduction = 0;
	m_processingParam.padFac = 2;
	m_processingParam.multiThread = 0;

	// image stack visualization
	/////////////////////////////
	ui.spinBox_SliceNumber->setValue(1);
	ui.doubleSpinBox_ContrastSlope->setValue(1.0);
	ui.doubleSpinBox_ContrastOffset->setValue(0.0);
	ui.checkBox_EnableWindowSelection->setChecked(false);
	ui.spinBox_xWinPos->setValue(0);
	ui.spinBox_yWinPos->setValue(0);
	ui.spinBox_WinWidth->setValue(0);
	ui.spinBox_WinHeight->setValue(0);
	ui.spinBox_SliceNumber->setMinimum(1);
	ui.spinBox_SliceNumber->setValue(1);
	ui.horizontalSlider_imageView->setMinimum(1);
	ui.horizontalSlider_imageView->setValue(1);
}

// slots
//////////
void ProjectionPreProcessor::ImageViewShowImage()
{
	Mat m = GetCurrentVizImage();
	int sliceNr = ui.spinBox_SliceNumber->value();
	ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
	ui.label_ImageView->setPixmap(Mat2Pixmap(m));
	ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
	ui.horizontalSlider_imageView->setValue(sliceNr);
	ui.spinBox_SliceNumber->setValue(sliceNr);

	if (ui.checkBox_EnableWindowSelection->isEnabled() == true)
	{
		QPixmap pix((*(ui.label_ImageView->pixmap())));
		QPainter paint(&pix);
		QPen pen(Qt::blue, 1);
		paint.setPen(pen);
		paint.drawRect(m_rectSelectionRedraw);
		ui.label_ImageView->setPixmap(pix);
	}
}

QPixmap ProjectionPreProcessor::Mat2Pixmap(Mat &imgMat)
{
	if (m_ColorTable.isEmpty())
	{
		for (int i = 0; i < 256; ++i)
			m_ColorTable.push_back(qRgb(i, i, i));
	}

	QImage image(imgMat.data, imgMat.cols, imgMat.rows, imgMat.step, QImage::Format_Indexed8);

	image.setColorTable(m_ColorTable);

	return QPixmap::fromImage(image);
}

void ProjectionPreProcessor::UndoImageProcessing()
{
	uint64_t cnt = ui.spinBox_NumberProjections->value();
	ui.progressBar_ImageProcessing->setMaximum(cnt);

	ui.doubleSpinBox_ContrastSlope->setValue(1.0);
	ui.doubleSpinBox_ContrastOffset->setValue(0.0);


	Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);
	uint64_t imageSize = m_processingParam.imgHeightScaled *  m_processingParam.imgWidthScaled;

	ui.progressBar_ImageProcessing->setFormat(tr("process undoing"));

	for (int i = 0; i < cnt; i++)
	{
		uint64_t offset = imageSize*i;
		memcpy(visImage.data, &m_pMemScaledImageStack[offset], imageSize*sizeof(uchar));
		visImage.copyTo(m_visImageStack[i]);
		ui.progressBar_ImageProcessing->setValue(i + 1);
	}
	ui.progressBar_ImageProcessing->setFormat(tr("Done"));
	ui.progressBar_ImageProcessing->setValue(0);

	Mat m = GetCurrentVizImage();
	ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
	ui.label_ImageView->setPixmap(Mat2Pixmap(m));
	ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
}

void ProjectionPreProcessor::EqualizeImages()
{
	uint64_t cnt = ui.spinBox_NumberProjections->value();
	ui.progressBar_ImageProcessing->setMaximum(cnt);

	Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);

	ui.progressBar_ImageProcessing->setFormat(tr("Equalize Images"));

	for (int i = 0; i < cnt; i++)
	{
		visImage = m_visImageStack[i];
		cv::equalizeHist(visImage, visImage);
		visImage.copyTo(m_visImageStack[i]);
		ui.progressBar_ImageProcessing->setValue(i + 1);
	}
	ui.progressBar_ImageProcessing->setFormat(tr("Done"));
	ui.progressBar_ImageProcessing->setValue(0);

	Mat m = GetCurrentVizImage();
	ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
	ui.label_ImageView->setPixmap(Mat2Pixmap(m));
	ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
}

void ProjectionPreProcessor::ChangeContrastOfCurrentImage(double)
{
	uint64_t cnt = ui.spinBox_NumberProjections->value();
	ui.progressBar_ImageProcessing->setMaximum(cnt);

	Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);

	int idx = ui.spinBox_SliceNumber->value();
	if (idx > 0)
	{
		m_visImageStack[idx - 1].copyTo(visImage);
		double slope = ui.doubleSpinBox_ContrastSlope->value();
		double offset = ui.doubleSpinBox_ContrastOffset->value();
		visImage.convertTo(visImage, -1, slope, offset);
		//visImage.copyTo(m_visImageStack[i]);


		Mat m;
		visImage.copyTo(m);
		ui.label_ImageView->setPixmap(Mat2Pixmap(m));
		ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
		ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
	}
	ui.horizontalSlider_imageView->setValue(idx);
	ui.spinBox_SliceNumber->setValue(idx);
	ui.spinBox_SliceNumber->setMaximum(m_processingParam.selectedImages.count());
	ui.horizontalSlider_imageView->setMaximum(m_processingParam.selectedImages.count());
}

void ProjectionPreProcessor::ContrastApplyToImages()
{
	uint64_t cnt = ui.spinBox_NumberProjections->value();
	ui.progressBar_ImageProcessing->setMaximum(cnt);

	Mat visImage = Mat::zeros(m_processingParam.imgHeightScaled, m_processingParam.imgWidthScaled, CV_8U);
	double slope = ui.doubleSpinBox_ContrastSlope->value();
	double offset = ui.doubleSpinBox_ContrastOffset->value();

	ui.progressBar_ImageProcessing->setFormat(tr("Change Contrast of Image Stack"));

	for (int i = 0; i < cnt; i++)
	{
		visImage = m_visImageStack[i];
		visImage.convertTo(visImage, -1, slope, offset);
		visImage.copyTo(m_visImageStack[i]);
		ui.progressBar_ImageProcessing->setValue(i + 1);
	}
	ui.progressBar_ImageProcessing->setFormat(tr("Done"));
	ui.progressBar_ImageProcessing->setValue(0);

	Mat m = GetCurrentVizImage();
	ui.label_ImageView->setPixmap(Mat2Pixmap(m));
	ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
	ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
}

void ProjectionPreProcessor::WindowsSelectionState()
{
	if (!ui.checkBox_EnableWindowSelection->isChecked())
	{
		m_rectSelection.setX(0);
		m_rectSelection.setY(0);
		m_rectSelection.setWidth(0);
		m_rectSelection.setHeight(0);
		Mat m = GetCurrentVizImage();
		ui.label_ImageView->setPixmap(Mat2Pixmap(m));
		ui.label_ImageView->setFixedSize(QSize(m.cols, m.rows));
		ui.label_ImageView->resize(ui.label_ImageView->pixmap()->size());
	}
}

Mat ProjectionPreProcessor::GetCurrentVizImage()
{
	Mat m;
	int sliceNr = ui.spinBox_SliceNumber->value();
	if (sliceNr> 0)
		m_visImageStack[sliceNr - 1].copyTo(m);
	return m;
}

void ProjectionPreProcessor::NormalizeSelect()
{
	if (ui.radioButton_UseFlatWindowNormalization->isChecked())
	{
		ui.groupBox_NormWin->setEnabled(true);
		ui.lineEdit_FlatFieldImage->setEnabled(false);
		ui.pushButton_SelectFlat->setEnabled(false);
		ui.lineEdit_DarkFieldImage->setEnabled(false);
		ui.pushButton_SelectDark->setEnabled(false);
	}
	else
	{
		ui.groupBox_NormWin->setEnabled(false);
		ui.lineEdit_FlatFieldImage->setEnabled(true);
		ui.pushButton_SelectFlat->setEnabled(true);
		ui.lineEdit_DarkFieldImage->setEnabled(true);
		ui.pushButton_SelectDark->setEnabled(true);
	}
}

void ProjectionPreProcessor::SetEnableMethods()
{
	if (ui.checkBox_Normalize->isChecked())
	{
		ui.page_MethodNormalization->setEnabled(true);
	}
	else
	{
		ui.page_MethodNormalization->setEnabled(false);
	}

	if (ui.checkBox_OutlierSuppression->isChecked())
	{
		ui.page_MethodOutlier->setEnabled(true);
	}
	else
	{
		ui.page_MethodOutlier->setEnabled(false);
	}

	if (ui.checkBox_BHC->isChecked())
	{
		ui.page_MethodBHC->setEnabled(true);
	}
	else
	{
		ui.page_MethodBHC->setEnabled(false);
	}

	if (ui.checkBox_StripeReduction->isChecked())
	{
		ui.page_StripeReduction->setEnabled(true);
	}
	else
	{
		ui.page_StripeReduction->setEnabled(false);
	}

}

// dark & flat field file loading
///////////////////////////////////
void ProjectionPreProcessor::LoadFlatFieldImage()
{
	QString flatFieldImage = QFileDialog::getOpenFileName(this, tr("Flat Field Image"), 
		tr(""),
		tr("Flat Field File (*.tif *.tiff)"));
	if (!flatFieldImage.isEmpty())
	{
		ui.lineEdit_FlatFieldImage->setText(flatFieldImage);
		m_processingParam.flatFieldImageFile = flatFieldImage;
	}
}

void ProjectionPreProcessor::LoadDarkFieldImage()
{

	QString darkFieldImage = QFileDialog::getOpenFileName(this, tr("Flat Field Image"),
		tr(""),
		tr("Dark Field File (*.tif *.tiff)"));
	if (!darkFieldImage.isEmpty())
	{
		ui.lineEdit_DarkFieldImage->setText(darkFieldImage);
		m_processingParam.darkFieldImageFile = darkFieldImage;
	}
}

void ProjectionPreProcessor::SaveOutputMessage()
{
	QString fileName = QFileDialog::getSaveFileName(this, 
		tr("Save Output Messages"),
		m_lastProjectPath,
		tr("Text File (*.txt)"));	
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
		QTextStream msgOut(&file);
		QString msg = ui.textEdit_MessagesOutput->toPlainText();
		msgOut << msg;
		file.close();
	}
}

void ProjectionPreProcessor::CheckSettingsForRun()
{
	if (m_pMemImageStack == 0 && m_pMemTileImageStack == 0)
	{
		QMessageBox::critical(this, tr("Check Data"), tr("No data was loaded"), QMessageBox::Ok);
		return;
	}
	else
	{
		//ju-23-Oct-2017 hack --> fix Lorentz filter bug
		SetupLorentzFilter();
		ui.pushButton_Run->setEnabled(true);
		//ui.pushButton_CancelRun->setEnabled(true);
		//-> set from thread via emit signal ui.pushButton_SaveSettingsForRun->setEnabled(false);
	}
}

void ProjectionPreProcessor::BHCStateChanged()
{
	if (ui.checkBox_BHC->isChecked())
	{
		ui.checkBox_Normalize->setChecked(true);
	}
}

void ProjectionPreProcessor::NormalizeStateChanged()
{
	if (!ui.checkBox_Normalize->isChecked())
	{
		ui.checkBox_BHC->setChecked(false);
	}
}

void ProjectionPreProcessor::NoLogStateChanged()
{
	m_processingParam.noLog = ui.checkBox_NoLogarithm->isChecked();
}

void ProjectionPreProcessor::SaveProcessedData()
{
	QString saveFiles = m_lastProjectPath + "/Projection_";
	QString saveFileName = QFileDialog::getSaveFileName(this, 
		tr("Save Processed Data"),
		saveFiles, 
		/*tr("Projection_"),*/
		tr("raw data files (*.raw)"));
	if (!saveFileName.isEmpty())
	{
		QFileInfo fInfo(saveFileName);
		QString directory = fInfo.absolutePath();
		QString filePattern = fInfo.baseName();
		filePattern = filePattern.trimmed();
		filePattern += "####";
		filePattern += ".raw";
		ui.lineEdit_OutPutDir->setText(directory);
		ui.lineEdit_OutRawPattern->setText(filePattern);
	}
}

void ProjectionPreProcessor::SaveFileProccess()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Project File"),
		m_lastProjectPath,
		tr("Project File (*.pprx)"));
	if (!fileName.isEmpty())
	{
		QFileInfo fileInfo(fileName);
		m_lastProjectPath = fileInfo.absolutePath();
		m_processingParam.projectFileName = fileName;
		WriteProjectParameterToFile();

		m_isModified = false;
		QString title = this->windowTitle();
		if (title[title.size() - 1] == '*')
		{
			title.truncate(title.size() - 1);
			this->setWindowTitle(title);
		}
	}
}

void ProjectionPreProcessor::WriteProjectParameterToFile() // adapt to new entries 28-Feb-2018
{
	ReadProjectParametersFromGUI();
	QFile file(m_processingParam.projectFileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream gui_out(&file);
	gui_out << "project_name=" << m_processingParam.projectName << "\n";
	gui_out << "project_owner=" << m_processingParam.projectOwner << "\n";
	gui_out << "project_date=" << m_processingParam.projectDate << "\n";
	gui_out << "in_directory=" << m_processingParam.inputDiretory << "\n";
	gui_out << "in_file_pattern=" << m_processingParam.inputFilepattern << "\n";
	gui_out << "image_height=" << m_processingParam.imgHeight << "\n";
	gui_out << "image_width=" << m_processingParam.imgWidth << "\n";
	gui_out << "cnt_projection=" << m_processingParam.cntProj << "\n";
	gui_out << "in_data_type=" << m_processingParam.dataTypeIn << "\n";
	gui_out << "out_directory=" << m_processingParam.outputDirectory << "\n";
	gui_out << "out_file_pattern=" << m_processingParam.outputFilepattern << "\n";
	gui_out << "out_data_type=" << m_processingParam.dataTypeOut << "\n";
	gui_out << "use_normalisation=" << m_processingParam.useNormalisation << "\n";
	gui_out << "use_flat_flield_file=" << m_processingParam.useFlatFieldFileNormalisation << "\n";
	gui_out << "use_flat_flield_win=" << m_processingParam.useWinNormalisation << "\n";
	gui_out << "flat_image_file=" << m_processingParam.flatFieldImageFile << "\n";
	gui_out << "dark_image_file=" << m_processingParam.darkFieldImageFile << "\n";
	gui_out << "x_norm_win_pos=" << m_processingParam.xWinPos << "\n";
	gui_out << "y_norm_win_pos=" << m_processingParam.yWinPos << "\n";
	gui_out << "norm_win_width=" << m_processingParam.widthWin << "\n";
	gui_out << "norm_win_height=" << m_processingParam.heightWin << "\n";
	gui_out << "use_outlier=" << m_processingParam.useOutlierSupRAC << "\n";
	gui_out << "use_outlier_sup=" << m_processingParam.useOutlierSup << "\n";
	gui_out << "use_RAC=" << m_processingParam.useRAC << "\n";
	gui_out << "correction_algo=" << m_processingParam.correctAlgo << "\n";
	gui_out << "outlier_sigma_med9=" << m_processingParam.outlierSigmaMedian9 << "\n";
	gui_out << "outlier_sigma_mean9=" << m_processingParam.outlierSigmaMean9 << "\n";
	gui_out << "use_BHC=" << m_processingParam.useBHC << "\n";
	gui_out << "coeff_BHC=" << m_processingParam.coeffBHC << "\n";
	gui_out << "const_coeff_BHC_A=" << m_processingParam.constCoeffBHC_A << "\n";
	gui_out << "const_coeff_BHC_B=" << m_processingParam.constCoeffBHC_B << "\n";
	gui_out << "use_strip_reduction=" << m_processingParam.useStripReduction << "\n";
	gui_out << "fft_padding_factor=" << m_processingParam.padFac << "\n";
	gui_out << "run_multi_thread=" << m_processingParam.multiThread << "\n";
	//-ju-02-Mar-2018 add save settings
	gui_out << "use_lorentz_filter=" << m_processingParam.useLorentzFilter << "\n";
	gui_out << "lorentz_filter_value=" << m_processingParam.alphaValue << "\n";
	gui_out << "is_dark_flat_corrected_projections=" << m_processingParam.isDarkFlatCorrected << "\n";
	// 0 is clock wise; 1 is anti clock wise
	gui_out << "rotation_direction_projections=" << m_processingParam.antiClockWise << "\n";
	file.close();
	// enable PFDK file export
	ui.actionExport_PFDK->setEnabled(true);
}

void ProjectionPreProcessor::WriteProjectParameterToGui() // adapt to new entries 28-Feb-2018
{
	ReadProjectParameterFromFile();

	// write to gui controls
	/////////////////////////

	// project settings
	///////////////////
	ui.lineEdit_projectName->setText(m_processingParam.projectName);
	ui.lineEdit_CreatorOwner->setText(m_processingParam.projectOwner);
	ui.lineEdit_date->setText(m_processingParam.projectDate);

	// file & projection setting
	/////////////////////////////
	ui.lineEdit_InputDir->setText(m_processingParam.inputDiretory);
	ui.lineEdit_InputFilePattern->setText(m_processingParam.inputFilepattern);
	ui.spinBox_ProjectionHeight->setValue(m_processingParam.imgHeight);
	ui.spinBox_ProjectionWidth->setValue(m_processingParam.imgWidth);
	ui.spinBox_NumberProjections->setValue(m_processingParam.cntProj);
	if (m_processingParam.dataTypeIn >= -1)
	{
		switch (m_processingParam.dataTypeIn)
		{
		case 0:
			ui.label_CVDataType->setText(tr("8UC1"));
			break;
		case 1:
			ui.label_CVDataType->setText(tr("8SC1"));
			break;
		case 2:
			ui.label_CVDataType->setText(tr("16UC1"));
			break;
		case 3:
			ui.label_CVDataType->setText(tr("16SC1"));
			break;
		case 4:
			ui.label_CVDataType->setText(tr("32SC1"));
			break;
		case 5:
			ui.label_CVDataType->setText(tr("32FC1"));
			break;
		case 6:
			ui.label_CVDataType->setText(tr("64FC1"));
			break;
		default:
			ui.label_CVDataType->setText(tr("unknown"));
		}
	}
	ui.lineEdit_OutPutDir->setText(m_processingParam.outputDirectory);
	ui.lineEdit_OutRawPattern->setText(m_processingParam.outputFilepattern);
	ui.comboBox_OutputFileType->setCurrentIndex(m_processingParam.dataTypeOut);

	// method selection -> normalize
	/////////////////////////////////
	ui.checkBox_Normalize->setChecked(m_processingParam.useNormalisation);
	if (m_processingParam.useFlatFieldFileNormalisation)
	{
		ui.radioButton_UseFlatWindowNormalization->setChecked(false);
		ui.radioButton_UseFlatFieldNormalization->setChecked(true);
	}
	else
	{
		ui.radioButton_UseFlatWindowNormalization->setChecked(true);
		ui.radioButton_UseFlatFieldNormalization->setChecked(false);
	}
	// flat file normalization
	ui.lineEdit_FlatFieldImage->setText(m_processingParam.flatFieldImageFile);
	ui.lineEdit_DarkFieldImage->setText(m_processingParam.darkFieldImageFile);
	// normalization using selected windows
	ui.spinBox_NormWinHeight->setValue(m_processingParam.heightWin);
	ui.spinBox_NormWinWidth->setValue(m_processingParam.widthWin);
	ui.spinBox_NormWinXPos->setValue(m_processingParam.xWinPos);
	ui.spinBox_NormWinYPos->setValue(m_processingParam.yWinPos);

	// method selection -> outlier
	/////////////////////////////////
	ui.checkBox_OutlierSuppression->setChecked(m_processingParam.useOutlierSupRAC);
	ui.checkBox_UseOutlierSuppression->setChecked(m_processingParam.useOutlierSup);
	ui.checkBox_UseRAC->setChecked(m_processingParam.useRAC);
	ui.comboBox_MethodSelection->setCurrentIndex(m_processingParam.correctAlgo);
	ui.doubleSpinBox_SigmaMean9->setValue(m_processingParam.outlierSigmaMedian9);
	ui.doubleSpinBox_SigmaMedian9->setValue(m_processingParam.outlierSigmaMean9);

	// method selection -> BHC
	/////////////////////////////////
	ui.checkBox_BHC->setChecked(m_processingParam.useBHC);
	ui.doubleSpinBox_BHCCorrectionExpo->setValue(m_processingParam.coeffBHC);
	ui.doubleSpinBox_BHCCorrectionLinearConstA->setValue(m_processingParam.constCoeffBHC_A);
	ui.doubleSpinBox_BHCCorrectionLinearConstB->setValue(m_processingParam.constCoeffBHC_B);

	// method selection -> stripe reduction
	////////////////////////////////////////
	ui.checkBox_StripeReduction->setChecked(m_processingParam.useStripReduction);
	switch (m_processingParam.padFac)
	{
	case 1:
		ui.comboBox_PadMultFFT->setCurrentIndex(0);
		break;
	case 2:
		ui.comboBox_PadMultFFT->setCurrentIndex(1);
		break;
	case 4:
		ui.comboBox_PadMultFFT->setCurrentIndex(2);
		break;
	case 8:
		ui.comboBox_PadMultFFT->setCurrentIndex(3);
		break;
	}
	ui.checkBox_FFTRunMultiThread->setChecked(m_processingParam.multiThread);

	//-ju-02-Mar-2018 use Lorentz filter
	ui.checkBox_applyLorentzFilter->setChecked(m_processingParam.useLorentzFilter);
	//-ju-02-Mar-2018 Lorentz filter value
	ui.doubleSpinBox_filterStrengthAlpha->setValue(m_processingParam.alphaValue);
	//-ju-02-Mar-2018 use dark/flat corrected projections
	ui.checkBox_useDarkFlatCorrected->setChecked(m_processingParam.isDarkFlatCorrected);
	//-ju-02-Mar-2018 scan direction
	ui.comboBox_ClockWise->setCurrentIndex(m_processingParam.antiClockWise);

	DeAllocImageStack();

	MakeEditable();
	if (!CreateProjectionFilesList())
	{
		QMessageBox::warning(this, tr("Error File List"), tr("Can not create file list"), QMessageBox::Ok);
		return;
	}

}

void ProjectionPreProcessor::ReadProjectParametersFromGUI() // adapt to new entries 28-Feb-2018
{
	// project settings
	///////////////////
	m_processingParam.projectName = ui.lineEdit_projectName->text();
	m_processingParam.projectOwner = ui.lineEdit_CreatorOwner->text();
	m_processingParam.projectDate = ui.lineEdit_date->text();

	// file & projection setting
	/////////////////////////////
	m_processingParam.inputDiretory = ui.lineEdit_InputDir->text();
	m_processingParam.inputFilepattern = ui.lineEdit_InputFilePattern->text();
	m_processingParam.imgHeight = ui.spinBox_ProjectionHeight->value();
	m_processingParam.imgWidth = ui.spinBox_ProjectionWidth->value();
	m_processingParam.cntProj = ui.spinBox_NumberProjections->value();
	m_processingParam.dataTypeIn = -1;
	QString dtype = ui.label_CVDataType->text();
	if (dtype == tr("8UC1"))
	{
		m_processingParam.dataTypeIn = 0;
	}
	if (dtype == tr("8SC1"))
	{
		m_processingParam.dataTypeIn = 1;
	}
	if (dtype == tr("16UC1"))
	{
		m_processingParam.dataTypeIn = 2;
	}
	if (dtype == tr("16SC1"))
	{
		m_processingParam.dataTypeIn = 3;
	}
	if (dtype == tr("32SC1"))
	{
		m_processingParam.dataTypeIn = 4;
	}
	if (dtype == tr("32FC1"))
	{
		m_processingParam.dataTypeIn = 5;
	}
	if (dtype == tr("64FC1"))
	{
		m_processingParam.dataTypeIn = 6;
	}
	m_processingParam.outputDirectory = ui.lineEdit_OutPutDir->text();
	m_processingParam.outputFilepattern = ui.lineEdit_OutRawPattern->text();
	m_processingParam.dataTypeOut = ui.comboBox_OutputFileType->currentIndex();

	// method selection -> normalize
	/////////////////////////////////
	m_processingParam.useNormalisation = ui.checkBox_Normalize->isChecked();
	m_processingParam.useFlatFieldFileNormalisation = ui.radioButton_UseFlatFieldNormalization->isChecked();
	if (ui.radioButton_UseFlatWindowNormalization->isChecked())
	{
		m_processingParam.useWinNormalisation = 1;
	}
	else
	{
		m_processingParam.useWinNormalisation = 0;
	}
	// flat file normalization
	m_processingParam.flatFieldImageFile = ui.lineEdit_FlatFieldImage->text();
	m_processingParam.darkFieldImageFile = ui.lineEdit_DarkFieldImage->text();
	// normalization using selected windows
	m_processingParam.xWinPos = ui.spinBox_NormWinXPos->value();
	m_processingParam.yWinPos = ui.spinBox_NormWinYPos->value();
	m_processingParam.widthWin = ui.spinBox_NormWinWidth->value();
	m_processingParam.heightWin = ui.spinBox_NormWinHeight->value();
	// windows selection
	if (ui.checkBox_EnableWindowSelection->isChecked())
	{
		m_processingParam.useWinNormalisation = 1;
	}

	// method selection -> outlier
	/////////////////////////////////
	m_processingParam.useOutlierSupRAC = ui.checkBox_OutlierSuppression->isChecked();
	m_processingParam.useOutlierSup = ui.checkBox_UseOutlierSuppression->isChecked();
	m_processingParam.useRAC = ui.checkBox_UseRAC->isChecked();
	m_processingParam.correctAlgo = ui.comboBox_MethodSelection->currentIndex();
	m_processingParam.outlierSigmaMedian9 = ui.doubleSpinBox_SigmaMean9->value();
	m_processingParam.outlierSigmaMean9 = ui.doubleSpinBox_SigmaMedian9->value();

	// method selection -> BHC
	/////////////////////////////////
	m_processingParam.useBHC = ui.checkBox_BHC->isChecked();
	m_processingParam.coeffBHC = ui.doubleSpinBox_BHCCorrectionExpo->value();
	m_processingParam.constCoeffBHC_A = ui.doubleSpinBox_BHCCorrectionLinearConstA->value();
	m_processingParam.constCoeffBHC_B = ui.doubleSpinBox_BHCCorrectionLinearConstB->value();

	// method selection -> stripe reduction
	////////////////////////////////////////
	m_processingParam.useStripReduction = ui.checkBox_StripeReduction->isChecked();
	int32_t idx = ui.comboBox_PadMultFFT->currentIndex();
	switch (idx)
	{
	case 0:
		m_processingParam.padFac = 1;
		break;
	case 1:
		m_processingParam.padFac = 2;
		break;
	case 2:
		m_processingParam.padFac = 4;
		break;
	case 3:
		m_processingParam.padFac = 8;
		break;
	}
	m_processingParam.multiThread = ui.checkBox_FFTRunMultiThread->isChecked();

	//-ju-02-Mar-2018 add use Lorentz filter
	m_processingParam.useLorentzFilter = ui.checkBox_applyLorentzFilter->isChecked();
	//-ju-02-Mar-2018 Lorentz filter value
	m_processingParam.alphaValue = ui.doubleSpinBox_filterStrengthAlpha->value();
	//-ju-02-Mar-2018 use dark flat corrected projections
	if (ui.checkBox_useDarkFlatCorrected->isChecked())
	{
		m_processingParam.isDarkFlatCorrected = 1;
	}
	else
	{
		m_processingParam.isDarkFlatCorrected = 0;
	}
	//-ju-02-Mar-2018 rotation direction of scan
	m_processingParam.antiClockWise = ui.comboBox_ClockWise->currentIndex();
}

void ProjectionPreProcessor::ReadProjectParameterFromFile() // adapt to new entries 28-Feb-2018
{
	QFile file(m_processingParam.projectFileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream gui_out(&file);
	// project name
	QString line = gui_out.readLine();
	QStringList paramList = line.split('=');
	m_processingParam.projectName = paramList[1];
	// project owner
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.projectOwner = paramList[1];
	// project date
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.projectDate = paramList[1];
	// input directory
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.inputDiretory = paramList[1];
	// input file pattern
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.inputFilepattern = paramList[1];
	// projection image height
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.imgHeight = paramList[1].toULongLong();
	// projection image width
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.imgWidth = paramList[1].toULongLong();
	// number of projections
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.cntProj = paramList[1].toULongLong();
	// input data type
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.dataTypeIn = paramList[1].toInt();
	// output directory
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.outputDirectory = paramList[1];
	// output file pattern
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.outputFilepattern = paramList[1];
	// output data type
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.dataTypeOut = paramList[1].toInt();
	// use normalisation
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useNormalisation = paramList[1].toUInt();
	// use flat field file for normalization
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useFlatFieldFileNormalisation = paramList[1].toUInt();
	// use windows selection for normalization
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useWinNormalisation = paramList[1].toUInt();
	// flat image file
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.flatFieldImageFile = paramList[1];
	// dark image file
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.darkFieldImageFile = paramList[1];
	// x position of sel. windows
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.xWinPos = paramList[1].toUInt();
	// y position of sel. windows
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.yWinPos = paramList[1].toUInt();
	// width of sel. windows
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.widthWin = paramList[1].toUInt();
	// height of sel. windows
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.heightWin = paramList[1].toUInt();
	// use outlier suppression RAC
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useOutlierSupRAC = paramList[1].toUInt(); //-ju-31-08-2015
	// use outlier suppression
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useOutlierSup = paramList[1].toUInt(); //-ju-31-08-2015
	// use RAC
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useRAC = paramList[1].toUInt(); //-ju-31-08-2015
	// correction algorithm
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.correctAlgo = paramList[1].toUInt();
	// sigma median9 filter
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.outlierSigmaMedian9 = paramList[1].toDouble();
	// sigma mean9 filter
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.outlierSigmaMean9 = paramList[1].toDouble();
	// use BHC
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useBHC = paramList[1].toUInt();
	// coefficient for BHC
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.coeffBHC = paramList[1].toDouble();
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.constCoeffBHC_A = paramList[1].toDouble();
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.constCoeffBHC_B = paramList[1].toDouble();
	// use strip reduction
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.useStripReduction = paramList[1].toUInt();
	// fft padding factor
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.padFac = paramList[1].toUInt();
	// run fft multithreaded
	line = gui_out.readLine();
	paramList = line.split('=');
	m_processingParam.multiThread = paramList[1].toUInt();

	//-ju-28-Feb-2018
	// Lorentz filter use settings
	line = gui_out.readLine();
	//-ju-19-Feb-2019 fix reading old projekt files
	////////////////////////////////////////////////
	if (!line.isNull())
	{
		paramList = line.split('=');
		m_processingParam.useLorentzFilter = paramList[1].toUInt();
	}
	else
	{
		m_processingParam.useLorentzFilter = 0;
	}
	// Lorentz filter value
	if (!line.isNull())
	{
			line = gui_out.readLine();
		paramList = line.split('=');
		m_processingParam.alphaValue = paramList[1].toDouble();
	}
	else
	{
		m_processingParam.alphaValue = 2.0;
	}

	//-ju-28-Feb-2018
	// use Dark/Flat corrected input projections
	line = gui_out.readLine();
	if (!line.isNull())
	{
		paramList = line.split('=');
		m_processingParam.isDarkFlatCorrected = paramList[1].toUInt();
	}
	else
	{
		m_processingParam.isDarkFlatCorrected = 0;
	}

	//-ju-28-Feb-2018
	// (anti) clock wise direction settings
	line = gui_out.readLine();
	if (!line.isNull())
	{
		paramList = line.split('=');
		m_processingParam.antiClockWise = paramList[1].toInt();
	}
	{
		m_processingParam.antiClockWise = 0;
	}
	//-ju-19-Feb-2019 fix reading old projekt files
	////////////////////////////////////////////////


	file.close();
}

void ProjectionPreProcessor::StartLorentzFilterDialog()
{
	LorentzFilterDialog *dialog = new LorentzFilterDialog(m_processingParam ,this, m_processingParam.alphaValue);
	uint32_t ret = dialog->exec();
	if (QDialog::Accepted == ret)
	{
		ui.doubleSpinBox_filterStrengthAlpha->setValue(dialog->m_detAlpha);
		// go to Lorentz Filter tab
		ui.toolBox_ProcessingMethods->setCurrentIndex(4);
		m_processingParam.alphaValue = dialog->m_detAlpha;
	}
	delete dialog;
}

void ProjectionPreProcessor::SetupLorentzFilter()
{
	bool applyLorentz = ui.checkBox_applyLorentzFilter->isChecked();
	if (applyLorentz)
	{
		m_processingParam.useLorentzFilter = true;
		//-ju-02-Mar-2018 m_processingParam.alphaValue = ui.doubleSpinBox_filterStrengthAlpha->value();
	}
	else
	{
		m_processingParam.useLorentzFilter = false;
		//-ju-02-Mar-2018 m_processingParam.alphaValue = ui.doubleSpinBox_filterStrengthAlpha->value();
	}
}

//-ju-15-Feb-2018 add clockwise
void ProjectionPreProcessor::ChangeDirection()
{
	m_processingParam.antiClockWise = ui.comboBox_ClockWise->currentIndex();
}

//-ju-23-Feb-2018 enable to work with already dark/falt corrected projections
void ProjectionPreProcessor::DarkFlatCorrectedStateChanged()
{
	// disable GUI elements
	if (ui.checkBox_useDarkFlatCorrected->isChecked())
	{
		ui.radioButton_UseFlatFieldNormalization->setEnabled(false);
		ui.radioButton_UseFlatWindowNormalization->setEnabled(false);
		ui.checkBox_NoLogarithm->setEnabled(false);
		ui.groupBox_Normalization->setEnabled(false);

		m_processingParam.isDarkFlatCorrected = 1;
	}
	else
	{
		ui.radioButton_UseFlatFieldNormalization->setEnabled(true);
		ui.radioButton_UseFlatWindowNormalization->setEnabled(true);
		ui.checkBox_NoLogarithm->setEnabled(true);
		ui.groupBox_Normalization->setEnabled(true);

		m_processingParam.isDarkFlatCorrected = 0;
	}
}

//-ju-24-June-2024 local tomography
void ProjectionPreProcessor::LocalTomoEnable()
{
	if (ui.checkBox_local_tomo->isChecked())
	{
		ui.spinBox_roi_percentage->setEnabled(true);
		ui.spinBox_AVG_range->setEnabled(true);
		m_processingParam.useROIPadding = 1;
	}
	else
	{
		ui.spinBox_roi_percentage->setEnabled(false);
		ui.spinBox_AVG_range->setEnabled(false);
		m_processingParam.useROIPadding = 0;
	}
}

void ProjectionPreProcessor::LocTomoPercentage()
{
	uint32_t percentage = ui.spinBox_roi_percentage->value();
	uint32_t width = ui.spinBox_ProjectionWidth->value();
	m_processingParam.roiPadSize = width * percentage / 100;
	// hard coded for currently used filter width in ring artefact correction of 32
	////////////////////////////////////////////////////////////////////////////////
	const uint32_t corr_filter_RAC = 32;
	width = 2 * width * percentage / 100 + width - corr_filter_RAC;
	m_processingParam.totalPadLocTomoSize = width;
	QString projection_width;
	projection_width.sprintf("%d", width);
	ui.lineEdit_roi_show_width->setText(projection_width);
	// automatically estimate slope factor for the sigmoid
	m_processingParam.sigmoidSlope = 20.0f / static_cast<float>(m_processingParam.roiPadSize);
	ui.doubleSpinBox_sigmoid_slope->setValue(m_processingParam.sigmoidSlope);
	Calc_Sigmoid_weight(m_processingParam.localTomoWeights, m_processingParam.roiPadSize, m_processingParam.sigmoidSlope);
}

void ProjectionPreProcessor::Calc_Sigmoid_weight(std::vector<float>& weight, const uint32_t extend, float slope)
{
	weight.clear();
	float center = extend / 2.0f;
	for (int i = 0; i < extend; i++)
	{
		float val = 1.0f / (1.0f + exp(-slope * (i - center)));
		weight.push_back(val);
	}
}

void ProjectionPreProcessor::AVGRange()
{
	m_processingParam.locTomoAVGRange = ui.spinBox_AVG_range->value();
}
