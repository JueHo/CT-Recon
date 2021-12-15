/**
*  Copyright © [2012], Empa, Juergen Hofmann
*/

#include "histogramremap.h"
#include <omp.h>

const int NUMBER_BINS=999;

HistogramRemap::HistogramRemap(QWidget *parent)
	: QMainWindow(parent),m_histColor(Qt::darkGray)
{
	ui.setupUi(this);
	// install event filter on plotter widget
	//////////////////////////////////////////
	ui.qwtPlot_histogram->installEventFilter(this);

	// fallbacks
	/////////////
	if(!ReadSettings())
	{
		FallBackSettings();
	}

	// do some initialisation
	/////////////////////////
	ui.progressBar_readImageStack->setValue(0);

	// initialise widgets
	//////////////////////

	QwtText plotTitle("Histogram");
    plotTitle.setFont(QFont("Consolas", 12));
	ui.qwtPlot_histogram->setTitle(plotTitle);

	// grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin(true);
	grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::black,1,Qt::DotLine));
    grid->setMinorPen(QPen(Qt::white,0,Qt::DotLine));
    grid->attach(ui.qwtPlot_histogram);

	QwtText yTitle("Counts");
    yTitle.setFont(QFont("Consolas",10));
	yTitle.setRenderFlags(Qt::AlignRight);
	ui.qwtPlot_histogram->setAxisTitle(QwtPlot::yLeft,yTitle);

	QwtText xTitle("Gray Values");
    xTitle.setFont(QFont("Consolas", 10));
	xTitle.setRenderFlags(Qt::AlignRight);
	ui.qwtPlot_histogram->setAxisTitle(QwtPlot::xBottom,xTitle);

	ui.qwtPlot_histogram->setAxisFont(QwtPlot::yLeft,QFont("Consolas",8,QFont::Bold));
	ui.qwtPlot_histogram->setAxisFont(QwtPlot::xBottom,QFont("Consolas",8,QFont::Bold));


	ui.qwtPlot_histogram->
		setCanvasBackground(QBrush(QColor(m_iniPlotRed,m_iniPlotGreen,m_iniPlotBlue,m_iniPlotAlpha)));
	
	ui.qwtPlot_histogram->setAxisMaxMajor(QwtPlot::xBottom,5);
	ui.qwtPlot_histogram->setAxisMaxMinor(QwtPlot::xBottom,10);

	m_pPicker = new HistPicker(QwtPlot::xBottom,QwtPlot::yLeft,
		                    QwtPlotPicker::CrossRubberBand, 
						    QwtPicker::AlwaysOn, 
							(QwtPlotCanvas *)ui.qwtPlot_histogram->canvas());
    //picker->setStateMachine(new QwtPickerClickPointMachine());
    m_pPicker->setStateMachine(new QwtPickerDragPointMachine());
    m_pPicker->setRubberBandPen(QColor(Qt::green));
    m_pPicker->setRubberBand(QwtPicker::CrossRubberBand);
    m_pPicker->setTrackerPen(QColor(Qt::black));

	QColor color(m_iniHistRed,m_iniHistGreen,m_iniHistBlue,m_iniHistAlpha);
	m_histColor = color;
	
    m_pHistoCurve = new QwtPlotIntervalCurve("Histo");
	m_pHistoCurve->setBrush(QBrush(m_histColor));
	m_pHistoCurve->setStyle(QwtPlotIntervalCurve::Tube);
    m_pHistoCurve->setPen(QPen(m_histColor));
    m_pHistoCurve->setYAxis( QwtPlot::yLeft );
    m_pHistoCurve->attach(ui.qwtPlot_histogram);

	// Signal/Slot Verbindungen
	////////////////////////////
    connect(ui.doubleSpinBox_rightBound,SIGNAL(valueChanged(double)),this,SLOT(SetRightBound()));
    connect(ui.doubleSpinBox_leftBound,SIGNAL(valueChanged(double)),this,SLOT(SetLeftBound()));
	connect(ui.pushButton_selectImageStack,SIGNAL(clicked()),this,SLOT(GetImageStackDirectory())); 
	connect(ui.pushButton_destinationDir,SIGNAL(clicked()),this,SLOT(GetImageDestinationDirectory()));
	connect(ui.pushButton_readImageStack,SIGNAL(clicked()),this,SLOT(ReadImageStack()));
	connect(ui.checkBox_calcMinMaxStack,SIGNAL(toggled(bool)),this,SLOT(SetMinMaxLogGroupState()));
	connect(ui.pushButton_readFromLogFile,SIGNAL(clicked()),this,SLOT(GetMinMaxFromLogFile()));
	connect(ui.pushButton_rePlot,SIGNAL(clicked()),this,SLOT(PopulateHistogram()));
	connect(ui.pushButton_selectColor,SIGNAL(clicked()),this,SLOT(SelectHistogramColor()));
	connect(ui.pushButton_PlotBackgroundColor,SIGNAL(clicked()),this,SLOT(SelectPlotColor()));
	connect(ui.pushButton_Real32Byte,SIGNAL(clicked()),this,SLOT(ConvertToUChar()));
	connect(ui.pushButton_Real32Uint16,SIGNAL(clicked()),this,SLOT(ConvertToUShort()));
}

bool HistogramRemap::eventFilter(QObject *targetCtrl, QEvent *event)
{
	if(targetCtrl == ui.qwtPlot_histogram)
	{
		if(event->type() == QEvent::MouseButtonPress || QEvent::KeyPress)
		{
			QMouseEvent *mEvt = static_cast<QMouseEvent*>(event);
			if(mEvt->button() == Qt::LeftButton && mEvt->modifiers() == Qt::ShiftModifier)
			{
				QPoint pointPos = m_pPicker->trackerPosition();
				QPointF fPointPos = m_pPicker->posToPlotCoord(pointPos);
				ui.doubleSpinBox_leftBound->setValue(fPointPos.rx());
				SetLeftBound(fPointPos);
			}
			if(mEvt->button() == Qt::RightButton && mEvt->modifiers() == Qt::ShiftModifier)
			{
				QPoint pointPos = m_pPicker->trackerPosition();
				QPointF fPointPos = m_pPicker->posToPlotCoord(pointPos);
				ui.doubleSpinBox_rightBound->setValue(fPointPos.rx());
				SetRightBound(fPointPos);
			}
		}
	}
	return QMainWindow::eventFilter(targetCtrl,event);
}

HistogramRemap::~HistogramRemap()
{

}

void  HistogramRemap::SetRightBound(QPointF &fPos)
{
    m_markerRight.setLineStyle(QwtPlotMarker::VLine);
    m_markerRight.setLabelAlignment(Qt::AlignLeft|Qt::AlignTop);
	m_markerLeft.setSpacing(2);
    m_markerRight.setLinePen(QPen(Qt::blue,2,Qt::DashDotLine));
    m_markerRight.attach(ui.qwtPlot_histogram);

	//set marker
	QString label;
    label.sprintf("RBound: %.6f",fPos.rx());
    QwtText text(label);
    text.setFont(QFont("Consolas",10,QFont::Bold));
	text.setColor(QColor(Qt::darkBlue));

	QwtInterval interv = ui.qwtPlot_histogram->axisInterval(QwtPlot::xBottom);
	double minimal = interv.minValue();
	double maximal = interv.maxValue();
	double offsetBottom = (maximal-minimal)/4.0; 
    m_markerRight.setValue(fPos.rx(),-1/*offsetBottom*/);
    m_markerRight.setLabel(text);
	ui.qwtPlot_histogram->replot();
}

void HistogramRemap::SetLeftBound(QPointF &fPos)
{
    m_markerLeft.setLineStyle(QwtPlotMarker::VLine);
    m_markerLeft.setLabelAlignment(Qt::AlignRight|Qt::AlignBottom);
	m_markerLeft.setSpacing(2);
    m_markerLeft.setLinePen(QPen(Qt::red,2,Qt::DashDotLine));
    m_markerLeft.attach(ui.qwtPlot_histogram);

	//set marker
	QString label;
    label.sprintf( "LBound: %.6f",fPos.rx());
    QwtText text(label);
    text.setFont(QFont("Consolas",10,QFont::Bold));
	text.setColor(QColor(Qt::darkRed));

	QwtInterval interv = ui.qwtPlot_histogram->axisInterval(QwtPlot::xBottom);
	double minimal = interv.minValue();
	double maximal = interv.maxValue();
	double offsetBottom = (maximal-minimal)/4.0; 
    m_markerLeft.setValue(fPos.rx(),-1/*offsetBottom*/); // second parameter is dummy value?!
    m_markerLeft.setLabel(text);
	ui.qwtPlot_histogram->replot();
}


void HistogramRemap::SetRightBound()
{
	double x = ui.doubleSpinBox_rightBound->value();
	QPointF pnt(x,0.0);
	SetRightBound(pnt);
}

void HistogramRemap::SetLeftBound()
{
	double x = ui.doubleSpinBox_leftBound->value();
	QPointF pnt(x,0.0);
	SetLeftBound(pnt);
}

// slots
////////////
void HistogramRemap::GetImageStackDirectory()
{
	 QString directory = 
		QFileDialog::getExistingDirectory(this, 
										  tr("Open Directory"),
                                          m_iniSrcDir,
                                          QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	if(!directory.isEmpty())
	{
		m_imageStackDirectory = directory;
		ui.lineEdit_sourceDir->setText(m_imageStackDirectory);
		m_iniSrcDir = m_imageStackDirectory;

		ui.pushButton_Real32Byte->setDisabled(true);
		ui.pushButton_Real32Uint16->setDisabled(true);

		WriteSettings();
	}
}

void HistogramRemap::GetImageDestinationDirectory()
{
	 QString directory = 
		QFileDialog::getExistingDirectory(this, 
										  tr("Open Directory"),
                                          m_iniDestDir,
                                          QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
	if(!directory.isEmpty())
	{
		m_imageDestinationDirectory = directory;
		ui.lineEdit_destinationDir->setText(m_imageDestinationDirectory);
		m_iniDestDir = m_imageDestinationDirectory;
		WriteSettings();
	}
}

void HistogramRemap::ReadImageStack()
{
	// initialise min / max values
	m_minGray = FLT_MAX;
	m_maxGray = FLT_MIN;

	// read filter name
	////////////////////
	m_usedFilter = ui.comboBox_fileSuffix->currentText();
	QStringList filters;
    filters << m_usedFilter;

	QDir imageStackSourceDir = QDir(m_imageStackDirectory);
	if(!imageStackSourceDir.exists(m_imageStackDirectory))
	{
		QString errMsg = QString("Error open directory: %1%2").arg(m_imageStackDirectory).arg("!");
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}
    imageStackSourceDir.setNameFilters(filters);
	QStringList qsl = imageStackSourceDir.entryList();

	if(qsl.count() == 0)
	{
		QString errMsg = QString("No files in directory %1 with suffix %2 found!").arg(m_imageStackDirectory).arg(m_usedFilter);
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}

	// set maximum value of progress bar
	ui.progressBar_readImageStack->setMaximum(qsl.count());
	int progressCounter = 0;

	std::ifstream inFile;
	std::vector<float> filebuffer(ui.spinBox_imgWidth->value()*ui.spinBox_imgHeight->value());
	if(ui.checkBox_calcMinMaxStack->isChecked())
	{
		ui.statusBar->showMessage(tr("determine min/max gray values of image stack"),240);
	}
	int inc = 0;
	//-ju-13-Dec-2018
	int ic = 0;
	for(ic = 0; ic < qsl.count(); ic++)
	{
		//-ju-13-Dec-2018
		QString file = qsl.at(ic);
		QCoreApplication::processEvents();
		//-ju-13-Dec-2018
		QString fileName = QString("%1/%2").arg(imageStackSourceDir.path()).arg(file);
        QFileInfo finfo(fileName);
		// file size in bytes
		long long fileSizeBytes = finfo.size();
		// size from gui
		ui.spinBox_imgWidth->value();
		long long sizeFromGui = 
			static_cast<long long>(ui.spinBox_imgWidth->value()) * 
			static_cast<long long>(ui.spinBox_imgHeight->value())*sizeof(float);
		if(fileSizeBytes != sizeFromGui)
		{
			QString errMsg = QString("File size of %1 not correct!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		if(ui.checkBox_calcMinMaxStack->isChecked())
		{
			// pre read stack to determine min/max value
			inFile.open(fileName.toStdString().c_str(),std::ios::binary);
			if(!inFile.is_open())
			{
				QString errMsg = QString("Can not open %1!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
				return;
			}
			// assuming file size is always the same no clear() of vector have to be done
			inFile.read((char*) &filebuffer[0],fileSizeBytes);
			//std::vector<float>::iterator pos;

			typedef std::vector<float>::iterator iter;
			std::pair<iter, iter> minMaxValPair;
			// Find the smallest and largest values
			minMaxValPair = std::minmax_element(filebuffer.begin(), filebuffer.end());
			float minGray = *(minMaxValPair.first);
			float maxGray = *(minMaxValPair.second);
			m_minGray = __min(minGray,m_minGray);
			m_maxGray = __max(maxGray,m_maxGray);
			inFile.close();
			ui.progressBar_readImageStack->setValue(++progressCounter);
			ui.statusBar->showMessage(tr("determine min/max gray values of image stack"), 240);
		}
		else
		{
			// read content of file and create histogram
		}
	}
	ui.statusBar->showMessage(tr("finished"), 240);

	// in case of automatic calculation of min/max
	// calculate histogram
	///////////////////////////////////////////////
	ui.progressBar_readImageStack->setValue(0);
	progressCounter = 0;
	m_histoIntervalLen = (m_maxGray - m_minGray)/NUMBER_BINS;
	ui.doubleSpinBox_leftBound->setSingleStep(m_histoIntervalLen);
	ui.doubleSpinBox_rightBound->setSingleStep(m_histoIntervalLen);
	m_volumeHistogram.resize(NUMBER_BINS+1,0);
	if(ui.checkBox_calcMinMaxStack->isChecked())
	{
		ui.statusBar->showMessage(tr("create histogram"),240);
		ui.doubleSpinBox_minGray->setValue(m_minGray);
		ui.doubleSpinBox_maxGray->setValue(m_maxGray);
		foreach (QString file, qsl) 
		{
			QCoreApplication::processEvents(); //-ju-13-Dec-2018
			QString fileName = QString("%1/%2").arg(imageStackSourceDir.path()).arg(file);
			QFileInfo finfo(fileName);
			// file size in bytes
			long long fileSizeBytes = finfo.size();
			// size from gui
			ui.spinBox_imgWidth->value();
			long long sizeFromGui = 
				static_cast<long long>(ui.spinBox_imgWidth->value()) * 
				static_cast<long long>(ui.spinBox_imgHeight->value())*sizeof(float);
			if(fileSizeBytes != sizeFromGui)
			{
				QString errMsg = QString("File size of %1 not correct!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
				return;
			}
			inFile.open(fileName.toStdString().c_str(), std::ios::binary);
			if(!inFile.is_open())
			{
				QString errMsg = QString("Can not open %1!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
				return;
			}
			inFile.read((char*) &filebuffer[0],fileSizeBytes);
			for(int i = 0; i<filebuffer.size(); i++)
			{
				int idx = static_cast<unsigned int>((static_cast<double>(filebuffer[i]) + fabs(m_minGray))/m_histoIntervalLen);
				m_volumeHistogram[idx]++;
			}
			inc++;
			if (inc % 100)
			{
				printf("Read %d\n", inc);
			}
			inFile.close();
			ui.progressBar_readImageStack->setValue(++progressCounter);
			ui.statusBar->showMessage(tr("create histogram"), 240);
		}
	}
	progressCounter = 0;
	ui.progressBar_readImageStack->setValue(0);
	// populate histogram
	PopulateHistogram();

	ui.pushButton_Real32Byte->setEnabled(true);
	ui.pushButton_Real32Uint16->setEnabled(true);

}

void HistogramRemap::SetMinMaxLogGroupState()
{
	if(ui.checkBox_calcMinMaxStack->isChecked())
	{
		ui.doubleSpinBox_minGray->setDisabled(true);
		ui.doubleSpinBox_maxGray->setDisabled(true);
		ui.pushButton_readFromLogFile->setDisabled(true);
	}
	else
	{
		ui.doubleSpinBox_minGray->setEnabled(true);
		ui.doubleSpinBox_maxGray->setEnabled(true);
		ui.pushButton_readFromLogFile->setEnabled(true);
	}
}

void HistogramRemap::GetMinMaxFromLogFile()
{
	m_logFileName = 
		QFileDialog::getOpenFileName(this, tr("Open Log File"),"./", tr("Log File (*.log *.* *)"));
	if(!m_logFileName.isEmpty())
	{
		ui.lineEdit_logFile->setText(m_logFileName);
		ui.lineEdit_logFile->setAlignment(Qt::AlignRight);
		// open file and read values
		GetMinMax(m_logFileName);
	}
}

// private functions
//////////////////////////////////
bool HistogramRemap::GetMinMax(const QString &fileName)
{
	bool found[2];
	bool isOk;
	found[0] = found[1] = false;
	QFile logFile(fileName);
	if(!logFile.open(QIODevice::ReadOnly|QIODevice::Text)) 
	{
		QString errMsg = QString("Can not open File %1").arg(fileName);
		QMessageBox::warning(0,tr("Error Open File"),errMsg);
		return false;
	}
	while (!logFile.atEnd()) 
	{
		QByteArray line = logFile.readLine();
		if (!line.trimmed().isEmpty() &&
			!line.trimmed().startsWith('#'))
		{
			QString tokLine = line;
			QStringList elemList = tokLine.split(':');
			QString elem;
			foreach(elem, elemList)
			{
				if(elem == "Minimal gray value")
				{
					m_minGray = elemList[1].trimmed().toDouble(&isOk);
					if(!isOk)
					{
						QString errMsg = QString("Can not convert %1 to float").arg(elemList[1].trimmed());
						QMessageBox::critical(0,tr("Error Open File"),errMsg);
						logFile.close();
						return false;
					}
					ui.doubleSpinBox_minGray->setValue(m_minGray);
					found[0] = true;
				}
				if(elem == "Maximal gray value")
				{
					m_maxGray = elemList[1].trimmed().toDouble(&isOk);
					if(!isOk)
					{
						QString errMsg = QString("Can not convert %1 to float").arg(elemList[1].trimmed());
						QMessageBox::critical(0,tr("Error Open File"),errMsg);
						logFile.close();
						return false;
					}
					ui.doubleSpinBox_maxGray->setValue(m_maxGray);
					found[1] = true;
				}
			}
		}
	}
	logFile.close();
	if(found[0] && found[1]) return true;
	return false;
}

bool HistogramRemap::PopulateHistogram()
{
	QVector<QwtIntervalSample> sample;
	long long maxEntryHist = 0;
	double logOffset = 0;
	if(ui.checkBox_yLog10->isChecked())
	{
		logOffset = 0.1;
	}
	for(int i = 0; i < m_volumeHistogram.size(); i++)
	{
		double step = i*m_histoIntervalLen + m_minGray;
		QwtIntervalSample item(step,logOffset,m_volumeHistogram[i]+logOffset);
		sample.push_front(item);
		QwtIntervalSample item2(step+m_histoIntervalLen,logOffset,m_volumeHistogram[i]+logOffset);
		sample.push_front(item2);
		maxEntryHist = __max(m_volumeHistogram[i],maxEntryHist);
		if (i % 100)
		{
			printf("%d\n", i);
		}
	}
	m_pHistoCurve->setSamples(sample);
	// todo new scaling
	ui.qwtPlot_histogram->setAxisScale(QwtPlot::xBottom,m_minGray,m_maxGray);
	ui.qwtPlot_histogram->setAxisScale(QwtPlot::yLeft,logOffset,maxEntryHist);
	if(ui.checkBox_yLog10->isChecked())
	{	
		ui.qwtPlot_histogram->setAxisScaleEngine(QwtPlot::yLeft,new QwtLogScaleEngine(10));
	}
	else
	{
		ui.qwtPlot_histogram->setAxisScaleEngine(QwtPlot::yLeft,new QwtLinearScaleEngine);
	}
	ui.qwtPlot_histogram->replot();
	return true;
}

void HistogramRemap::SelectHistogramColor()
{
	QColorDialog col;
	m_histColor = col.getColor(Qt::white,0,"Histogram Color",QColorDialog::ShowAlphaChannel);
	m_pHistoCurve->setBrush(QBrush(m_histColor));
	m_pHistoCurve->setPen(QPen(m_histColor));
	QString style = QString("background-color: rgba(%1,%2,%3,%4)")
							.arg(m_histColor.red())
							.arg(m_histColor.green())
							.arg(m_histColor.blue())
							.arg(m_histColor.alpha());
	ui.label_histogramColor->setStyleSheet(style);
	m_iniHistRed	= m_histColor.red();
	m_iniHistGreen	= m_histColor.green();
	m_iniHistBlue	= m_histColor.blue();
	m_iniHistAlpha	= m_histColor.alpha();
	WriteSettings();
	ui.qwtPlot_histogram->replot();
}

void HistogramRemap::SelectPlotColor()
{
	QColorDialog col;
	QColor color = col.getColor(Qt::white,0,"Pol Background Color",QColorDialog::ShowAlphaChannel);
	QString style = QString("background-color: rgba(%1,%2,%3,%4)")
							.arg(color.red())
							.arg(color.green())
							.arg(color.blue())
							.arg(color.alpha());
	ui.label_plotBackgroundColor->setStyleSheet(style);
	ui.qwtPlot_histogram->setCanvasBackground(QBrush(color));
	m_iniPlotRed	= color.red();
	m_iniPlotGreen	= color.green();
	m_iniPlotBlue	= color.blue();
	m_iniPlotAlpha	= color.alpha();
	WriteSettings();
	ui.qwtPlot_histogram->replot();
}

void HistogramRemap::ConvertToUChar()
{
	// read filter name
	////////////////////
	m_usedFilter = ui.comboBox_fileSuffix->currentText();
	QStringList filters;
    filters << m_usedFilter;

	QDir imageStackSourceDir = QDir(m_imageStackDirectory);
	if(!imageStackSourceDir.exists(m_imageStackDirectory))
	{
		QString errMsg = QString("Error open directory: %1%2").arg(m_imageStackDirectory).arg("!");
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}
	// chech if dest. dir exists and is not equal to ??
    imageStackSourceDir.setNameFilters(filters);
	QStringList qsl = imageStackSourceDir.entryList();

	if(qsl.count() == 0)
	{
		QString errMsg = QString("No files in directory %1 with suffix %2 found!").arg(m_imageStackDirectory).arg(m_usedFilter);
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}

	// set maximum value of progress bar
	ui.progressBar_convertImageStack->setMaximum(qsl.count());
	int progressCounter = 0;

	std::ifstream inFile;
	std::vector<float> filebuffer(ui.spinBox_imgWidth->value()*ui.spinBox_imgHeight->value());
	if(ui.checkBox_calcMinMaxStack->isChecked())
	{
		ui.statusBar->showMessage(tr("convert image stack: Floats to bytes"),240);
	}
	//-ju-13-Dec-2018
	int ic = 0;
	for(ic = 0; ic < qsl.count(); ic++)
	{
		//-ju-13-Dec-2019
		QString file = qsl.at(ic);
		QCoreApplication::processEvents();
		//
		QString fileName = QString("%1/%2").arg(imageStackSourceDir.path()).arg(file);
        QFileInfo finfo(fileName);
		// file size in bytes
		long long fileSizeBytes = finfo.size();
		// size from gui
		ui.spinBox_imgWidth->value();
		long long imageSize = 
			static_cast<long long>(ui.spinBox_imgWidth->value()) * 
			static_cast<long long>(ui.spinBox_imgHeight->value());
		long long sizeFromGui = imageSize*sizeof(float);
		if(fileSizeBytes != sizeFromGui)
		{
			QString errMsg = QString("File size of %1 not correct!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		if(m_imageDestinationDirectory.isEmpty())
		{
			QString errMsg = QString("No destination directory defined");
				QMessageBox::critical(0,tr("Error Destination Directory"),errMsg);
			return;
		}
		ConvertFloatToByte(fileName,
			               imageSize,
						   ui.doubleSpinBox_leftBound->value(),
						   ui.doubleSpinBox_rightBound->value());
		ui.progressBar_convertImageStack->setValue(++progressCounter);
		ui.statusBar->showMessage(tr("convert image stack: Floats to bytes"), 240);//-ju-13-Dec-2018
	}
	ui.statusBar->showMessage(tr("finished"), 240);//-ju-13-Dec-2018
	ui.progressBar_convertImageStack->setValue(0);
}

void HistogramRemap::ConvertToUShort()
{
	// read filter name
	////////////////////
	m_usedFilter = ui.comboBox_fileSuffix->currentText();
	QStringList filters;
    filters << m_usedFilter;

	QDir imageStackSourceDir = QDir(m_imageStackDirectory);
	if(!imageStackSourceDir.exists(m_imageStackDirectory))
	{
		QString errMsg = QString("Error open directory: %1%2").arg(m_imageStackDirectory).arg("!");
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}
	// chech if dest. dir exists and is not equal to ??
    imageStackSourceDir.setNameFilters(filters);
	QStringList qsl = imageStackSourceDir.entryList();

	if(qsl.count() == 0)
	{
		QString errMsg = QString("No files in directory %1 with suffix %2 found!").arg(m_imageStackDirectory).arg(m_usedFilter);
		QMessageBox::critical(0,tr("Error open directory"),errMsg);
		return;
	}

	// set maximum value of progress bar
	ui.progressBar_convertImageStack->setMaximum(qsl.count());
	int progressCounter = 0;

	std::ifstream inFile;
	std::vector<float> filebuffer(ui.spinBox_imgWidth->value()*ui.spinBox_imgHeight->value());
	if(ui.checkBox_calcMinMaxStack->isChecked())
	{
		ui.statusBar->showMessage(tr("convert image stack: Floats to unsigned short"),240);
	}
	//-ju-13-Dec-2018
	int ic = 0;
	for (ic = 0; ic < qsl.count(); ic++)
	{
		//-ju-13-Dec-2019
		QString file = qsl.at(ic);
		QCoreApplication::processEvents();
		//-ju-13-Dec-2018
		QString fileName = QString("%1/%2").arg(imageStackSourceDir.path()).arg(file);
        QFileInfo finfo(fileName);
		// file size in bytes
		long long fileSizeBytes = finfo.size();
		// size from gui
		ui.spinBox_imgWidth->value();
		long long imageSize = 
			static_cast<long long>(ui.spinBox_imgWidth->value()) * 
			static_cast<long long>(ui.spinBox_imgHeight->value());
		long long sizeFromGui = imageSize*sizeof(float);
		if(fileSizeBytes != sizeFromGui)
		{
			QString errMsg = QString("File size of %1 not correct!").arg(fileName);
				QMessageBox::critical(0,tr("Error open file"),errMsg);
			return;
		}
		if(m_imageDestinationDirectory.isEmpty())
		{
			QString errMsg = QString("No destination directory defined");
				QMessageBox::critical(0,tr("Error Destination Directory"),errMsg);
			return;
		}
		ConvertFloatToUShort(fileName,
			                 imageSize,
						     ui.doubleSpinBox_leftBound->value(),
						     ui.doubleSpinBox_rightBound->value());
		ui.progressBar_convertImageStack->setValue(++progressCounter);
		ui.statusBar->showMessage(tr("convert image stack: Floats to unsigned short"), 240);//-ju-13-Dec-2018
	}
	ui.statusBar->showMessage(tr("finished"), 240); //-ju-13-Dec-2018
	ui.progressBar_convertImageStack->setValue(0);
}

bool HistogramRemap::ReadSettings()
{
	char *homeDrive = getenv("HOMEDRIVE");
	char *homePath  = getenv("HOMEPATH");
	if(!homePath || !homeDrive) return false;

	QString iniFileName = homeDrive + tr("") + homePath + tr("/") + tr("HistogramPlot.ini");
	QFile inifile(iniFileName);
	if(!inifile.open(QIODevice::ReadOnly|QIODevice::Text)) return false;

	m_iniSrcDir = m_iniDestDir = "";
	m_iniHistRed = m_iniHistGreen = m_iniHistBlue = m_iniHistAlpha = -1;
	m_iniPlotRed = m_iniPlotGreen = m_iniPlotBlue = m_iniPlotAlpha = -1;

	QTextStream ini(&inifile);

	QString line = ini.readLine();
	QStringList dirs = line.trimmed().split(';');
	m_iniSrcDir = dirs[0];
	m_iniDestDir = dirs[1];

	QString iniHistRed = "";
	QString iniHistGreen = "";
	QString iniHistBlue = "";
	QString iniHistAlpha = "";
	QString iniPlotRed = "";
	QString iniPlotGreen = "";
	QString iniPlotBlue = "";
	QString iniPlotAlpha = "";

	ini >> iniHistRed >> iniHistGreen >> iniHistBlue >> iniHistAlpha;
	ini >> iniPlotRed >> iniPlotGreen >> iniPlotBlue >> iniPlotAlpha;
	inifile.close();
	if(m_iniSrcDir.isEmpty()  ||
	   m_iniDestDir.isEmpty() ||
	   iniHistRed.isEmpty()	  ||
	   iniHistGreen.isEmpty() ||
	   iniHistBlue.isEmpty()  ||
	   iniHistAlpha.isEmpty() ||
	   iniPlotRed.isEmpty()	  ||
	   iniPlotGreen.isEmpty() ||
	   iniPlotBlue.isEmpty()  ||
	   iniPlotAlpha.isEmpty()
	   )
	{
		return false;
	}
	m_iniHistRed	= iniHistRed.toInt();
	m_iniHistGreen	= iniHistGreen.toInt();
	m_iniHistBlue	= iniHistBlue.toInt();
	m_iniHistAlpha	= iniHistAlpha.toInt();
	m_iniPlotRed	= iniPlotRed.toInt();
	m_iniPlotGreen	= iniPlotGreen.toInt();
	m_iniPlotBlue	= iniPlotBlue.toInt();
	m_iniPlotAlpha	= iniPlotAlpha.toInt();

	QString styleP = QString("background-color: rgba(%1,%2,%3,%4)")
							.arg(m_iniPlotRed)
							.arg(m_iniPlotGreen)
							.arg(m_iniPlotBlue)
							.arg(m_iniPlotAlpha);
	ui.label_plotBackgroundColor->setStyleSheet(styleP);

	QString styleH = QString("background-color: rgba(%1,%2,%3,%4)")
							.arg(m_iniHistRed)
							.arg(m_iniHistGreen)
							.arg(m_iniHistBlue)
							.arg(m_iniHistAlpha);
	ui.label_histogramColor->setStyleSheet(styleH);

	return true;
}

void HistogramRemap::WriteSettings()
{
	char *homeDrive = getenv("HOMEDRIVE");
	char *homePath  = getenv("HOMEPATH");
	if(!homePath || !homeDrive) return;

	QString iniFileName = homeDrive + tr("") + homePath + tr("/") + tr("HistogramPlot.ini");
	QFile inifile(iniFileName);
	if(!inifile.open(QIODevice::WriteOnly|QIODevice::Text)) return;

	QTextStream ini(&inifile);
	ini << m_iniSrcDir << ";" << m_iniDestDir <<  "\n";
	ini << m_iniHistRed << " " << m_iniHistGreen << " " << m_iniHistBlue << " " << m_iniHistAlpha << "\n";
	ini << m_iniPlotRed << " " << m_iniPlotGreen << " " << m_iniPlotBlue << " " << m_iniPlotAlpha << "\n";
	inifile.close();
}

void HistogramRemap::FallBackSettings()
{
	m_iniSrcDir		= tr("c:/");
	m_iniDestDir	= tr("c:/");

	m_iniHistRed	= 50;
	m_iniHistGreen	= 50;
	m_iniHistBlue	= 50;
	m_iniHistAlpha	= 126;

	m_iniPlotRed	= 225;
	m_iniPlotGreen	= 225;
	m_iniPlotBlue	= 225;
	m_iniPlotAlpha	= 255;
}