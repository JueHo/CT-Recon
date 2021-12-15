/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include "project_serialize.h"
#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtWidgets/QMessageBox>
#include "symbols.h"
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMessageBox>

#define TR QObject::tr

void ProjectSerialize::ReadFromFile(const QString &filename, 
									CtrlSerialize &elements,
									QStringList &fileList,
									QVector<QMap<QString,double> > &limAngSinograms,
									bool isASCII)
{
	if(isASCII)
	{
		ReadASCIIFile(filename,elements,fileList,limAngSinograms);
	}
}

bool ProjectSerialize::WriteToFile(const QString &filename, bool isASCII)
{
	if(isASCII)
	{
		return WriteASCIIFile(filename);
	}
	return true;
}

// private functions
////////////////////
bool ProjectSerialize::ReadFileList(QStringList &fileList,QString filename)
{
	QFileInfo info(filename);
	QString path = info.absolutePath();
	QString baseName = info.baseName();
	path = path + TR("/") + baseName;
	QFile SinoListFile(path + TR("_SinFList.lst"));
	if(!SinoListFile.open(QIODevice::ReadOnly))
	{
		QString msg;
		msg.sprintf("Can not read file list in File: %s", SinoListFile.fileName().toStdString().c_str());
		QMessageBox::warning(0, QObject::tr("Error Reading File"), msg);
		return false;
	}
	fileList.clear();
	QTextStream sinoFileList(&SinoListFile);
	QString textLine;
	while(1)
	{
		textLine = sinoFileList.readLine();
		if(textLine.isNull())
			break;
		textLine.trimmed();
		QStringList line = textLine.split(TR("="));
		fileList.append(line[0]);
	}
	return true;
}

bool ProjectSerialize::ReadSegmentedFileList(QVector<QMap<QString,double> > &limAngSinograms,QString filename)
{
	QFileInfo info(filename);
	QString path = info.absolutePath();
	QString baseName = info.baseName();
	path = path + TR("/") + baseName;
	QFile SinoListFile(path + TR("_LimAngFList.lst"));
	if(!SinoListFile.open(QIODevice::ReadOnly))
	{
		QString msg;
		msg.sprintf("Can not read file list in File: %s", SinoListFile.fileName().toStdString().c_str());
		QMessageBox::warning(0, QObject::tr("Error Reading File"), msg);
		return false;
	}
	limAngSinograms.clear();
	QTextStream sinoFileList(&SinoListFile);
	QString textLine;
	QString segment;

	QMap<QString,double> fileAngles;
	///////////////////////////
	textLine = sinoFileList.readLine();
	if(textLine.isNull())
		return false;
	textLine.trimmed();
	QStringList line = textLine.split(TR("="));
	segment = line[0].trimmed();
	bool isOK;
	double ang = line[2].trimmed().toDouble(&isOK);
	if(!isOK)
	{
		QString msg;
		msg.sprintf("Angle value in >> %s << is invalid", textLine);
		QMessageBox::warning(0, QObject::tr("Error Reading File"), msg);
		return false;
	}
	fileAngles.insert(line[1].trimmed(),ang);
	//////////////////////////
	while(1)
	{
		textLine = sinoFileList.readLine();
		if(textLine.isNull())
			break;
		textLine.trimmed();
		QStringList line = textLine.split(TR("="));
		if(line[0].trimmed() == segment)
		{
			bool isOK;
			double angle = line[2].trimmed().toDouble(&isOK);
			if(!isOK)
			{
				QString msg;
				msg.sprintf("Angle value in >> %s << is invalid", textLine);
				QMessageBox::warning(0, QObject::tr("Error Reading File"), msg);
				return false;
			}
			fileAngles.insert(line[1].trimmed(),angle);
			segment = line[0].trimmed();
		}
		else
		{
			limAngSinograms.append(fileAngles);
			fileAngles.clear();
			bool isOK;
			double angle = line[2].trimmed().toDouble(&isOK);
			if(!isOK)
			{
				QString msg;
				msg.sprintf("Angle value in >> %s << is invalid", textLine);
				QMessageBox::warning(0, QObject::tr("Error Reading File"), msg);
				return false;
			}
			fileAngles.insert(line[1].trimmed(),angle);
			segment = line[0].trimmed();
		}
	}
	// add last seegment
	limAngSinograms.append(fileAngles);
	fileAngles.clear();

	return true;
}

bool ProjectSerialize::ReadASCIIFile(const QString& filename, 
									 CtrlSerialize &elements,
									 QStringList &fileList,
									 QVector<QMap<QString,double> >	&limAngSinograms)
{
	QFile asciiFile(filename);
	if(!asciiFile.open(QIODevice::ReadOnly))
	{
		QString msg;
		msg.sprintf("Can not read project file: %s", 
					filename.toStdString().c_str());
		QMessageBox::warning(0, TR("Error opening File"), msg);
		return false;
	}
	// init switches to 0
	elements.doBackprojection = 0;
	elements.doLimitedAngleReconstruction = 0;
	elements.doWeightAndFiltering = 0;
	elements.useFileList = 0;
	elements.useMPI = 0;

	QTextStream projFile(&asciiFile);
	QString textLine;
	while(1)
	{
		textLine = projFile.readLine();
		if(textLine.isNull())
			break;
		textLine.trimmed();
		if(textLine.startsWith(TR("#")))
			continue;
		if(textLine.isEmpty())
			continue;
		QStringList keyVal = textLine.split(TR("="));
		QString key = keyVal[0];
		key = key.trimmed();
		QString val = keyVal[1];
		val = val.trimmed();
		// parse keys
		//read switches first!
		///////////////////////
		if(key.toStdString() == USE_FILE_LIST)
		{
			bool isOK;
			elements.useFileList = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(USE_FILE_LIST);
				return false;
			}
			m_ctrl.checkBox_useFileList->setChecked(elements.useFileList);
		}
		if(key.toStdString() == LIM_ANG_BPROJ)
		{
			bool isOK;
			elements.doLimitedAngleReconstruction = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(LIM_ANG_BPROJ);
				return false;
			}
			m_ctrl.radioButton_limitedAngleRecon->setChecked(elements.doLimitedAngleReconstruction);
		}
		if(key.toStdString() == CNT_PROJ)
		{
			bool isOK;
			elements.numberOfProjections = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(CNT_PROJ);
				return false;
			}
			m_ctrl.SBox_NumberOfProjections->setValue(elements.numberOfProjections);
		}
		if(key.toStdString() == START_IDX)
		{
			bool isOK;
			elements.startIndex = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(START_IDX);
				return false;
			}
			m_ctrl.SBox_NumStartIndex->setValue(elements.startIndex);
		}
		if(key.toStdString() == START_ANGLE)
		{
			bool isOK;
			elements.startAngle = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(START_ANGLE);
				return false;
			}
			m_ctrl.DSBox_SinoStartAtAngle->setValue(elements.startAngle);
		}
		if(key.toStdString() == IMG_WIDTH)
		{
			bool isOK;
			elements.imageWidth = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(IMG_WIDTH);
				return false;
			}
			m_ctrl.SBox_ImgWidth->setValue(elements.imageWidth);
		}
		if(key.toStdString() == IMG_HEIGHT)
		{
			bool isOK;
			elements.imageHeight = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(IMG_HEIGHT);
				return false;
			}
			m_ctrl.SBox_ImgHeight->setValue(elements.imageHeight);
		}
		if(key.toStdString() == PIXEL_SIZE)
		{
			bool isOK;
			elements.pixelSize = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(PIXEL_SIZE);
				return false;
			}
			m_ctrl.DSBOX_PixelSize->setValue(elements.pixelSize);
		}
		if(key.toStdString() == GPU_MEM_USE)
		{
			bool isOK;
			elements.gpuMemUsage = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(GPU_MEM_USE);
				return false;
			}
			m_ctrl.DSBox_GPUMemUsage->setValue(elements.gpuMemUsage);
		}
		if(key.toStdString() == CPU_MEM_USE)
		{
			bool isOK;
			elements.cpuMemUsage = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(CPU_MEM_USE);
				return false;
			}
			m_ctrl.DSBox_CPUMemUsage->setValue(elements.cpuMemUsage);
		}
		if(key.toStdString() == THREADS_X)
		{
			bool isOK;
			elements.gpuThreadX = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(THREADS_X);
				return false;
			}
			m_ctrl.SBox_GPUThreadsX->setValue(elements.gpuThreadX);
		}
		if(key.toStdString() == THREADS_Y)
		{
			bool isOK;
			elements.gpuThreadY = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(THREADS_Y);
				return false;
			}
			m_ctrl.SBox_GPUThreadsY->setValue(elements.gpuThreadY);
		}
		//-ju-04-Nov-2016 add fast accurate interpolation
		//////////////////////////////////////////////////
		if (key.toStdString() == HI_ACC)
		{
			bool isOK;
			elements.interpolFast = val.toInt(&isOK);
			if (!isOK)
			{
				PrintParameterError(HI_ACC);
				return false;
			}
			if (elements.interpolFast == 0)
			{
				m_ctrl.radioButton_fast->setChecked(true);
			}
			else
			{
				m_ctrl.radioButton_accurate->setChecked(true);
			}			
		}

		if(key.toStdString() == NUM_GPUS_USE)
		{
			bool isOK;
			elements.numOfGPUThreads = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(NUM_GPUS_USE);
				return false;
			}
			m_ctrl.SBox_UseNumGPUs->setValue(elements.numOfGPUThreads);
		}
		if(key.toStdString() == CT_SYSTEM)
		{
			bool isOK;
			elements.CTSystem = val;
			int index = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(CT_SYSTEM);
				return false;
			}
			m_ctrl.CBox_CT_SystemSelection->setCurrentIndex(index);
		}
		if(key.toStdString() == W_ORIG_X)
		{
			bool isOK;
			elements.volOrigX = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(W_ORIG_X);
				return false;
			}
			m_ctrl.SBox_VolumeOriginX->setValue(elements.volOrigX);
		}
		if(key.toStdString() == W_ORIG_Y)
		{
			bool isOK;
			elements.volOrigY = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(W_ORIG_Y);
				return false;
			}
			m_ctrl.SBox_VolumeOriginY->setValue(elements.volOrigY);
		}
		if(key.toStdString() == W_ORIG_Z)
		{
			bool isOK;
			elements.volOrigZ = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(W_ORIG_Z);
				return false;
			}
			m_ctrl.SBox_VolumeOriginZ->setValue(elements.volOrigZ);
		}
		if(key.toStdString() == VOL_X)
		{
			bool isOK;
			elements.volWidth = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(VOL_X);
				return false;
			}
			m_ctrl.SBox_VolumeWidth->setValue(elements.volWidth);
		}
		if(key.toStdString() == VOL_Y)
		{
			bool isOK;
			elements.volHeight = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(VOL_Y);
				return false;
			}
			m_ctrl.SBox_VolumeHeight->setValue(elements.volHeight);
		}
		if(key.toStdString() == VOL_Z)
		{
			bool isOK;
			elements.volDepth = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(VOL_Z);
				return false;
			}
			m_ctrl.SBox_VolumeDepth->setValue(elements.volDepth);
		}
		if(key.toStdString() == HORIZ_SHIFT)
		{
			bool isOK;
			elements.horizShift = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(HORIZ_SHIFT);
				return false;
			}
			m_ctrl.DSBox_HorizontalShift->setValue(elements.horizShift);
		}
		//-ju-18-June-2021 add tilt axis correction parameters
		//////////////////////////////////////////////////////
		if (key.toStdString() == APPLY_TILT_CORR)
		{
			bool isOK;
			elements.useTiltCorr = val.toInt(&isOK);
			if (!isOK)
			{
				PrintParameterError(APPLY_TILT_CORR);
				return false;
			}
			if (elements.useTiltCorr)
				m_ctrl.checkBox_applyTiltAxCorr->setChecked(true);
			else
				m_ctrl.checkBox_applyTiltAxCorr->setChecked(false);
		}
		if (key.toStdString() == TILT_CORR_SLOPE_M)
		{
			bool isOK;
			elements.slopeTiltCorr = val.toDouble(&isOK);
			if (!isOK)
			{
				PrintParameterError(TILT_CORR_SLOPE_M);
				return false;
			}
			m_ctrl.doubleSpinBox_corrSlope_m->setValue(elements.slopeTiltCorr);
		}
		if (key.toStdString() == TILT_CORR_CONST_C)
		{
			bool isOK;
			elements.offsetTiltCorr = val.toDouble(&isOK);
			if (!isOK)
			{
				PrintParameterError(TILT_CORR_CONST_C);
				return false;
			}
			m_ctrl.doubleSpinBox_corrOffset_c->setValue(elements.offsetTiltCorr);
		}

		//////////////////////////////////////////////////////
		if(key.toStdString() == VERT_SHIFT)
		{
			bool isOK;
			elements.vertShift = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(VERT_SHIFT);
				return false;
			}
			m_ctrl.DSBox_VerticalShift->setValue(elements.vertShift);
		}
		if(key.toStdString() == DSD)
		{
			bool isOK;
			elements.distSrcDet = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(DSD);
				return false;
			}
			m_ctrl.DSBox_DistSrcDetector->setValue(elements.distSrcDet);
		}
		if(key.toStdString() == DSO)
		{
			bool isOK;
			elements.distSrcRot = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(DSO);
				return false;
			}
			m_ctrl.DSBox_DistSrcRotCentre->setValue(elements.distSrcRot);
		}
		if(key.toStdString() == IN_DATATYPE)
		{
			bool isOK;
			elements.inDataFormat = val;
			int index = m_ctrl.CBox_InDataFormat->findText(val);
			if(index == -1)
			{
				PrintParameterError(IN_DATATYPE);
				return false;
			}
			m_ctrl.CBox_InDataFormat->setCurrentIndex(index);
		}
		if(key.toStdString() == OUT_DATATYPE)
		{
			bool isOK;
			elements.outDataFormat = val;
			int index = m_ctrl.CBox_TomoOutDataFormat->findText(val);
			if(index == -1)
			{
				PrintParameterError(OUT_DATATYPE);
				return false;
			}
			m_ctrl.CBox_TomoOutDataFormat->setCurrentIndex(index);
		}
		if(key.toStdString() == SINO_NAME)
		{
			elements.sinoNamePattern = val;
			m_ctrl.LEd_SinoNamePattern->setText(val);
		}
		if(key.toStdString() == TOMO_NAME)
		{
			elements.tomoName = val;
			m_ctrl.LEd_TomoName->setText(val);
		}
		if(key.toStdString() == SINO32_DIR)
		{
			elements.sino32Dir = val;
			m_ctrl.LEd_PreprocSinoDirectory->setText(val);
		}
		if(key.toStdString() == SINO32_DIR_LIM)
		{
			elements.sino32Dir = val;
			m_ctrl.LEd_LimAnglePreProcDir->setText(val);
		}
		if(key.toStdString() == SINO_DIR)
		{
			elements.sinoDir = val;
			m_ctrl.LEd_SinogramDirectory->setText(val);
		}
		if(key.toStdString() == TOMO_DIR)
		{
			elements.tomoDir = val;
			m_ctrl.LEd_TomoOutDir->setText(val);
		}
		if(key.toStdString() == APPLY_FILTER)
		{
			bool isOK;
			elements.filterType = val;
			int index = m_ctrl.CBox_FilterType->findText(val);
			if(index == -1)
			{
				PrintParameterError(APPLY_FILTER);
				return false;
			}
			m_ctrl.CBox_FilterType->setCurrentIndex(index);
		}
        //-ju-14-Apr-2015 add view direction
        // MicroCT is: X-ray sourec to direction (0)
		if(key.toStdString() == VIEW_DIRECTION)
		{
			bool isOK;
			elements.filterType = val;
			int index = m_ctrl.CBox_ViewDirection->currentIndex();
			if(index == -1)
			{
				PrintParameterError(VIEW_DIRECTION);
				return false;
			}
			m_ctrl.CBox_FilterType->setCurrentIndex(index);
		}

		//-ju-28-July-2014 add phase contrast filter
		// have be scan after APPLY_FILTER !!!
		if(key.toStdString() == USE_DCP)
		{
			bool isOK;
			elements.phaseContrastFilter = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(USE_DCP);
				return false;
			}
			switch(elements.phaseContrastFilter)
			{
			case 0:
				break;
			case 1:
				m_ctrl.CBox_FilterType->setCurrentIndex(2);
				break;
			}
		}
		if(key.toStdString() == FLIP_IMAGE)
		{
			bool isOK;
			elements.flipImage = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(FLIP_IMAGE);
				return false;
			}
			switch(elements.flipImage)
			{
			case none:
				m_ctrl.CBox_FlipSinogramImage->setCurrentIndex(noneFlip);
				break;
			case horizontalAxis:
				m_ctrl.CBox_FlipSinogramImage->setCurrentIndex(xAxis);
				break;
			case verticalAxis:
				m_ctrl.CBox_FlipSinogramImage->setCurrentIndex(yAxis);
				break;
			case bothAxis:
				m_ctrl.CBox_FlipSinogramImage->setCurrentIndex(xyAxis);
				break;
			}
		}
		if(key.toStdString() == ANGLE_INCR)
		{
			bool isOK;
			elements.angleIncr = val.toDouble(&isOK);
			if(!isOK)
			{
				PrintParameterError(ANGLE_INCR);
				return false;
			}
			m_ctrl.DSBox_AngleIncr->setValue(elements.angleIncr);
		}
		if(key.toStdString() == DO_WEIGHT_FILTER)
		{
			bool isOK;
			elements.doWeightAndFiltering = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(DO_WEIGHT_FILTER);
				return false;
			}
			if(elements.doWeightAndFiltering)
				m_ctrl.CkBox_WeightFilter->setChecked(true);
			else
				m_ctrl.CkBox_WeightFilter->setChecked(false);
		}
		if(key.toStdString() == DO_BACK_PROJECT)
		{
			bool isOK;
			elements.doBackprojection = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(DO_BACK_PROJECT);
				return false;
			}
			if(elements.doBackprojection)
				m_ctrl.CkBox_Backprojection->setChecked(true);
			else
				m_ctrl.CkBox_Backprojection->setChecked(false);
		}
		//-ju-08-July-2011
		/*-ju-08-Nov-2011
		if(key.toStdString() == MPI_VERSION)
		{
			bool isOK;
			elements.MPIVersion = val;
			int index = m_ctrl.CBox_MPIVersion->findText(val);
			m_ctrl.CBox_MPIVersion->setCurrentIndex(index);
		}
		if(key.toStdString() == GPU_COMP_VERS)
		{
			bool isOK;
			elements.gpuVersion = val;
			int index = m_ctrl.CBox_GPUCompaVers->findText(val);
			m_ctrl.CBox_GPUCompaVers->setCurrentIndex(index);
		}
		if(key.toStdString() == USE_MPI)
		{
			bool isOK;
			elements.useMPI = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(USE_MPI);
				return false;
			}
			if(elements.useMPI)
				m_ctrl.CkBox_UseMPI->setChecked(true);
			else
				m_ctrl.CkBox_UseMPI->setChecked(false);
		}
		-ju-08-Nov-2011 */
		//-ju-08-Nov-2011 add thread parameter
		if(key.toStdString() == NUM_THREADS)
		{
			bool isOK;
			elements.numMPIProcesses = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(NUM_THREADS);
				return false;
			}
			m_ctrl.SBox_NumberOfMPIProcesses->setValue(elements.numMPIProcesses);
		}
		//-ju-10-Nov-2011 add blockfile file parameters
		if(key.toStdString() == SINO32_BLOCK_WRITE)
		{
			bool isOK;
			elements.sino32BlockWrite = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(SINO32_BLOCK_WRITE);
				return false;
			}
			if(elements.sino32BlockWrite)
				m_ctrl.CkBox_WriteToPreProcBlockFile->setChecked(true);
			else
				m_ctrl.CkBox_WriteToPreProcBlockFile->setChecked(false);
		}
		if(key.toStdString() == SINO32_BlOCK_USE)
		{
			bool isOK;
			elements.sino32BlockUse = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(SINO32_BlOCK_USE);
				return false;
			}
			if(elements.sino32BlockUse)
				m_ctrl.CkBox_UsePreProcBlockFile->setChecked(true);
			else
				m_ctrl.CkBox_UsePreProcBlockFile->setChecked(false);
		}
		if(key.toStdString() == TOMO_BLOCK_WRITE)
		{
			bool isOK;
			elements.tomoBlockWrite = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(TOMO_BLOCK_WRITE);
				return false;
			}
			if(elements.tomoBlockWrite)
				m_ctrl.CkBox_WriteBlockFile->setChecked(true);
			else
				m_ctrl.CkBox_WriteBlockFile->setChecked(false);
		}
		if(key.toStdString() == CONV_Block_INTERNAL)
		{
			bool isOK;
			elements.convBlockInternal = val.toInt(&isOK);
			if(!isOK)
			{
				PrintParameterError(CONV_Block_INTERNAL);
				return false;
			}
			if(elements.convBlockInternal)
				m_ctrl.CkBox_StoreConvTomoBlockFile->setChecked(true);
			else
				m_ctrl.CkBox_StoreConvTomoBlockFile->setChecked(false);
		}
	}
	// file list
	if(elements.useFileList)
	{
		// limit. angle
		if(elements.doLimitedAngleReconstruction)
		{
			if(ReadSegmentedFileList(limAngSinograms,filename))
			{
				m_ctrl.TreeWidget_LimAngleSeg->clear();
				for(int i = 0; i < limAngSinograms.size(); i++)
				{
					QMap<QString,double> keyVal = limAngSinograms[i];
					AddChildsToTree(i+1,keyVal,m_ctrl.TreeWidget_LimAngleSeg);
				}
				m_ctrl.TabWidget_SinogramSettings->setCurrentWidget(m_ctrl.tab_LimAngle);
			}
		}
		else // file list only
		{
			if(ReadFileList(fileList,filename))
			{
				m_ctrl.ListWidget_SinogramList->clear();
				int i = 0;
				foreach(QString file, fileList)
				{
					new QListWidgetItem(fileList[i], m_ctrl.ListWidget_SinogramList);
					i++;
				}
				m_ctrl.TabWidget_SinogramSettings->setCurrentWidget(m_ctrl.tab_FullAngle);
			}
		}
	}
	else //-ju-07-July-2011 add
	{
		m_ctrl.TreeWidget_LimAngleSeg->clear();
		m_ctrl.ListWidget_SinogramList->clear();
		m_ctrl.radioButton_fullAngleRecon->setChecked(true);
	}

	return true;
}

bool ProjectSerialize::WriteASCIIFile(const QString &filename)
{
	QFile asciiFile(filename);
	if (!asciiFile.open(QIODevice::WriteOnly))
	{
		QString msg;
		msg.sprintf("Can not create/write to File: %s", filename.toStdString().c_str());
		QMessageBox::warning(0, QObject::tr("Error creating/writing File"), msg);
		return false;
	}
	//QDir fileHandler;
	QTextStream outFile(&asciiFile);
	WriteASCIIHeader(outFile);
	QString pl;
	QString nl;
	nl.sprintf("\n");
	// write sinogram image parameters
	outFile << nl;
	WriteUnderLine(outFile);
	WriteCommentLine("Sinogram image settings",outFile);
	WriteCommentLine("	width in pixel",outFile);
	WriteCommentLine("  height in pixel",outFile);
	WriteCommentLine("  size in mm",outFile);
	WriteCommentLine("  sinogram data type (byte/short16/ushort16/int32/real32)",outFile);
	WriteCommentLine("  process limited angle [default: 0]",outFile);
	WriteCommentLine("  use sinogram file list (for lim. angle process. always 1) [default: 0]",outFile);
	WriteCommentLine("  sinogram name",outFile);
	WriteCommentLine("  sinogram directory",outFile);
	WriteCommentLine("  preprocessed sinogram directory",outFile);
	WriteCommentLine("	write pre-processed sinograms to block file (0/1) [default: 1]",outFile);
	WriteUnderLine(outFile);						   
	// print left aligned pad size 28
	int fieldLength = 28;							   
	pl.sprintf("%-*s = %-4d", fieldLength, IMG_WIDTH, m_ctrl.SBox_ImgWidth->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, IMG_HEIGHT, m_ctrl.SBox_ImgHeight->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, PIXEL_SIZE, m_ctrl.DSBOX_PixelSize->value());
	outFile << pl << nl;
	QString dataTypeIn = GetDataType(m_ctrl.CBox_InDataFormat->currentText());
	pl.sprintf("%-*s = %s", fieldLength, IN_DATATYPE, dataTypeIn.toStdString().c_str());
	outFile << pl << nl;
	// from options settings
	if(m_ctrl.radioButton_fullAngleRecon->isChecked())
	{
		pl.sprintf("%-*s = %-4d", fieldLength, LIM_ANG_BPROJ, 0);
		outFile << pl << nl;
		if(!m_ctrl.checkBox_useFileList->isChecked())
		{
			pl.sprintf("%-*s = %-4d", fieldLength, USE_FILE_LIST, 0);
			outFile << pl << nl;
			if(!ValidateTextField(m_ctrl.LEd_SinoNamePattern, TR("No sinogram name specified")))
			{
				outFile.setStatus(QTextStream::ReadCorruptData);
				return false;
			}
			pl.sprintf("%-*s = %s", fieldLength, SINO_NAME,
				m_ctrl.LEd_SinoNamePattern->text().toStdString().c_str());
			outFile << pl << nl;

			if(!ValidateTextField(m_ctrl.LEd_SinogramDirectory, TR("No sinogram directory specified")))
			{
				outFile.setStatus(QTextStream::ReadCorruptData);
				return false;
			}
			pl.sprintf("%-*s = %s", fieldLength, SINO_DIR, 
				m_ctrl.LEd_SinogramDirectory->text().toStdString().c_str());
			outFile << pl << nl;

			//-ju-11-11-2011 if(!ValidateTextField(m_ctrl.LEd_PreprocSinoDirectory, TR("No pre-processed sinogram directory specified")))
			if(!Validate(m_ctrl.CkBox_WriteToPreProcBlockFile,m_ctrl.LEd_PreprocSinoDirectory,
				TR("Neither pre-processed sinogram directory nor write to pre-processed sinogram Block File specified")))
			{
				outFile.setStatus(QTextStream::ReadCorruptData);
				return false;
			}
			pl.sprintf("%-*s = %s", fieldLength, SINO32_DIR,
				m_ctrl.LEd_PreprocSinoDirectory->text().toStdString().c_str());
			outFile << pl << nl;

		}
		else // use file list
		{
			pl.sprintf("%-*s = %-4d", fieldLength, USE_FILE_LIST, 1);
			outFile << pl << nl;
			if(!ValidateTextField(m_ctrl.LEd_PreprocSinoDirectory, TR("No pre-processed sinogram directory specified")))
			{
				outFile.setStatus(QTextStream::ReadCorruptData);
				return false;
			}
			pl.sprintf("%-*s = %s", fieldLength, SINO32_DIR,
				m_ctrl.LEd_PreprocSinoDirectory->text().toStdString().c_str());
			outFile << pl << nl;

			//read file list and write it to seperate file
			// format:
			// filename		angle
			int sz = m_ctrl.ListWidget_SinogramList->count();
			if(sz == 0)
			{
				QMessageBox::information(0,TR("No Files"), 
					TR("No sinograms selected - nothing written"));
				return false;
			}
			QFileInfo info(filename);
			QString path = info.absolutePath();
			QString baseName = info.baseName();
			path = path + TR("/") + baseName;
			QFile SinoListFile(path + TR("_SinFList.lst"));
			if(!SinoListFile.open(QIODevice::WriteOnly))
			{
				QString msg;
				msg.sprintf("Can not create/write to File: %s", SinoListFile.fileName().toStdString().c_str());
				QMessageBox::warning(0, QObject::tr("Error creating/writing File"), msg);
				return false;
			}
			QTextStream sino(&SinoListFile);
			double startAngle = m_ctrl.DSBox_SinoStartAtAngle->value();
			double incrAngle  = m_ctrl.DSBox_AngleIncr->value();
			for(int i = 0; i < sz; i++)
			{
				QListWidgetItem *item;
				item = m_ctrl.ListWidget_SinogramList->item(i);
				QString sinoFileName = item->text();
				double angle = startAngle + i*incrAngle;
				sino << sinoFileName << TR("\t=\t") << angle << "\n";
			}
		}
	}
	else // limited angle
	{
		pl.sprintf("%-*s = %-4d", fieldLength, LIM_ANG_BPROJ, 1);
		outFile << pl << nl;
		pl.sprintf("%-*s = %-4d", fieldLength, USE_FILE_LIST, 1);
		outFile << pl << nl;
		if(!ValidateTextField(m_ctrl.LEd_LimAnglePreProcDir, TR("No pre-processed sinogram directory specified")))
		{
			outFile.setStatus(QTextStream::ReadCorruptData);
			return false;
		}
		pl.sprintf("%-*s = %s", fieldLength, SINO32_DIR_LIM,
			m_ctrl.LEd_LimAnglePreProcDir->text().toStdString().c_str());
		outFile << pl << nl;
		//read file list and write it to seperate file
		// format:
		// filename		angle
		int sz = m_ctrl.TreeWidget_LimAngleSeg->topLevelItemCount();
		if(sz == 0)
		{
			QMessageBox::information(0,TR("No Files"), 
				TR("No sinograms selected - nothing written"));
			return false;
		}
		QFileInfo info(filename);
		QString path = info.absolutePath();
		QString baseName = info.baseName();
		path = path + TR("/") + baseName;
		QFile SinoListFile(path + TR("_LimAngFList.lst"));
		if(!SinoListFile.open(QIODevice::WriteOnly))
		{
			QString msg;
			msg.sprintf("Can not create/write to File: %s", SinoListFile.fileName().toStdString().c_str());
			QMessageBox::warning(0, QObject::tr("Error creating/writing File"), msg);
			return false;
		}
		QTextStream sino(&SinoListFile);
		for(int i = 0; i < sz; i++)
		{
			QTreeWidgetItem *topLevelItem = m_ctrl.TreeWidget_LimAngleSeg->topLevelItem(i);
			QString topicLine = topLevelItem->text(0);
			QStringList topicLineParts = topicLine.split(TR(": "));
			QString directory = topicLineParts[1];
			int cnt = topLevelItem->childCount();
			for(int j = 0; j < cnt; j++)
			{
				QTreeWidgetItem *child = topLevelItem->child(j);
				// column 0
				QString fileName = child->text(0);
				// column 1
				QString degree   = child->text(1);
				degree.chop(1);
				sino << topicLineParts[0] << TR("\t=\t") 
					 << directory << TR("/") 
					 << fileName << TR("\t=\t") 
					 << degree << "\n";
			}
		}
	}
	pl.sprintf("%-*s = %-4d", fieldLength, SINO32_BLOCK_WRITE, m_ctrl.CkBox_WriteToPreProcBlockFile->isChecked());
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Projection settings",outFile);
	WriteCommentLine("	number of projections",outFile);
	WriteCommentLine("  first file index [default: 1]",outFile);
	WriteCommentLine("  angle increment",outFile);
	WriteCommentLine("  projections start at angle [default: 0 Grad]",outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-4d", fieldLength, CNT_PROJ, m_ctrl.SBox_NumberOfProjections->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, START_IDX, m_ctrl.SBox_NumStartIndex->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, ANGLE_INCR, m_ctrl.DSBox_AngleIncr->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, START_ANGLE, m_ctrl.DSBox_SinoStartAtAngle->value());
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Geometry & filter settings",outFile);
	WriteCommentLine("	filter type (SheppLogan/Ramp/PhaseContrast)",outFile);
	WriteCommentLine("	phase contrast set internal filter to ramp (only for size used) (value 0/1 off/on)",outFile);
	WriteCommentLine("	flip sinogram along none/x-axis/y-axis/xy-axis (2/0/1/-1)",outFile);
	WriteCommentLine("  horizontal shift in (sub)pixel",outFile);
	WriteCommentLine("  horizontal shift in (sub)pixel",outFile);
	WriteCommentLine("  distance source detector in mm",outFile);
	WriteCommentLine("  distance source rotation centre in mm",outFile);
	WriteUnderLine(outFile);
	if(m_ctrl.CBox_FilterType->currentText().toStdString() == "PhaseContrast")
	{
		pl.sprintf("%-*s = %s", fieldLength, APPLY_FILTER, "Ramp");
		outFile << pl << nl;
		outFile << "use_phase_contrast_filter	 = 1" << nl;
	}
	else
	{
		pl.sprintf("%-*s = %s", fieldLength, APPLY_FILTER, m_ctrl.CBox_FilterType->currentText().toStdString().c_str());
		outFile << pl << nl;
		outFile << "use_phase_contrast_filter	 = 0" << nl;
	}
    //-ju-14-Apr-2015
    /////////////////
	pl.sprintf("%-*s = %-4d", fieldLength, VIEW_DIRECTION, m_ctrl.CBox_ViewDirection->currentIndex());
	outFile << pl << nl;


	QString axisStr = m_ctrl.CBox_FlipSinogramImage->currentText();
	int axis = GetFlipAxis(axisStr);
	pl.sprintf("%-*s = %-4d", fieldLength, FLIP_IMAGE, axis);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+6.3f", fieldLength, HORIZ_SHIFT, m_ctrl.DSBox_HorizontalShift->value());
	outFile << pl << nl;
	//-ju-18-June-2021 add tilt correction
	//////////////////////////////////////
	if (m_ctrl.checkBox_applyTiltAxCorr->isChecked())
	{
		outFile << "apply_tilted_axis_correction = 1" << nl;
	}
	else
	{
		outFile << "apply_tilted_axis_correction = 0" << nl;
	}
	pl.sprintf("%-*s = %-+10.8f", fieldLength, TILT_CORR_SLOPE_M, m_ctrl.doubleSpinBox_corrSlope_m->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+10.8f", fieldLength, TILT_CORR_CONST_C, m_ctrl.doubleSpinBox_corrOffset_c->value());
	outFile << pl << nl;
	//////////////////////////////////////
	pl.sprintf("%-*s = %-+6.3f", fieldLength, VERT_SHIFT, m_ctrl.DSBox_VerticalShift->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, DSD, m_ctrl.DSBox_DistSrcDetector->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, DSO, m_ctrl.DSBox_DistSrcRotCentre->value());
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Reconstruction & tomogram parameters",outFile);
	WriteCommentLine("	binning factor [default: 1] (no binning)",outFile);
	WriteCommentLine("	volume width in voxel",outFile);
	WriteCommentLine("  volume height in voxel",outFile);
	WriteCommentLine("  volume depth in voxel",outFile);
	WriteCommentLine("  volume origin x in voxel",outFile);
	WriteCommentLine("  volume origin y in voxel",outFile);
	WriteCommentLine("  volume origin z in voxel",outFile);
	WriteCommentLine("  volume origin z in voxel",outFile);
	WriteCommentLine("  tomogram data type (byte/short16/ushort16/real32)",outFile);
	WriteCommentLine("  tomogram name",outFile);
	WriteCommentLine("  tomogram directory",outFile);
	WriteCommentLine("	CT system (Micro_CT/Detect_CT 0/1)",outFile);
	WriteCommentLine("	use pre-processed sinograms to block file for recon. (0/1) [default: 1]",outFile);
	WriteCommentLine("	write tomogram block files (not possible for batch) (0/1) [default: 1]",outFile);
	WriteCommentLine("	write converted tomograms back to block file (0/1) [default: 0]",outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-4d", fieldLength, PREVIEW_SCALE, m_ctrl.SBox_BinningFactor->value());
	outFile << pl << nl;
	if(m_ctrl.SBox_BinningFactor->value() == 1 && CheckMaxVolRecSize())
	{
		outFile.setStatus(QTextStream::ReadCorruptData);
		return false;
	}
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_X, m_ctrl.SBox_VolumeWidth->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_Y, m_ctrl.SBox_VolumeHeight->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_Z, m_ctrl.SBox_VolumeDepth->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_X, m_ctrl.SBox_VolumeOriginX->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_Y, m_ctrl.SBox_VolumeOriginY->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_Z, m_ctrl.SBox_VolumeOriginZ->value());
	outFile << pl << nl;
	QString dataTypeOut = GetDataType(m_ctrl.CBox_TomoOutDataFormat->currentText());
	pl.sprintf("%-*s = %s", fieldLength, OUT_DATATYPE, dataTypeOut.toStdString().c_str());
	outFile << pl << nl;
	if(!ValidateTextField(m_ctrl.LEd_TomoName, TR("No tomogram name specified")))
	//if(!Validate(m_ctrl.CkBox_WriteBlockFile,m_ctrl.LEd_TomoName,TR("Neither tomogram name nor Block File write specified")))
	{
		outFile.setStatus(QTextStream::ReadCorruptData);
		return false;
	}
	pl.sprintf("%-*s = %s",fieldLength, TOMO_NAME,m_ctrl.LEd_TomoName->text().toStdString().c_str());
	outFile << pl << nl;
	if(!ValidateTextField(m_ctrl.LEd_TomoOutDir, TR("No tomogram output directory specified")))
	//if(!Validate(m_ctrl.CkBox_WriteBlockFile,m_ctrl.LEd_TomoOutDir,TR("Neither tomogram output directory nor Block File write specified")))
	{
		outFile.setStatus(QTextStream::ReadCorruptData);
		return false;
	}
	pl.sprintf("%-*s = %s",fieldLength, TOMO_DIR,m_ctrl.LEd_TomoOutDir->text().toStdString().c_str());
	outFile << pl << nl;
	int ctSystem = m_ctrl.CBox_CT_SystemSelection->currentIndex();
	pl.sprintf("%-*s = %-4d", fieldLength, CT_SYSTEM, ctSystem);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, SINO32_BlOCK_USE, m_ctrl.CkBox_UsePreProcBlockFile->isChecked());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, TOMO_BLOCK_WRITE, m_ctrl.CkBox_WriteBlockFile->isChecked());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, CONV_Block_INTERNAL, m_ctrl.CkBox_StoreConvTomoBlockFile->isChecked());
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("CPU and GPU settings & Interpolation type",outFile);
	WriteCommentLine("	CPU Memory usage  in % [default: 95%]",outFile);
	WriteCommentLine("	GPU Memory usage  in % [default: 95%]",outFile);
	WriteCommentLine("	GPU Threads X [default: 22]",outFile);
	WriteCommentLine("	GPU Threads Y [default: 23]",outFile);
	WriteCommentLine("	GPU Compatibility Version (1.x/2.x)",outFile);
	WriteCommentLine("	Number of GPUs used [default: 1]",outFile);
	WriteCommentLine("  Bilinear Interpolation fast/accurate [default: 1 = fast]", outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-+6.3f", fieldLength, CPU_MEM_USE, m_ctrl.DSBox_CPUMemUsage->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+6.3f", fieldLength, GPU_MEM_USE, m_ctrl.DSBox_GPUMemUsage->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, THREADS_X, m_ctrl.SBox_GPUThreadsX->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, THREADS_Y, m_ctrl.SBox_GPUThreadsY->value());
	outFile << pl << nl;
	//pl.sprintf("%-*s = %s", fieldLength, GPU_COMP_VERS,
	//		   m_ctrl.CBox_GPUCompaVers->currentText().toStdString().c_str());
	//outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, NUM_GPUS_USE, m_ctrl.SBox_UseNumGPUs->value());
	outFile << pl << nl;
	if (m_ctrl.radioButton_fast->isChecked())
	{
		pl.sprintf("%-*s = %-4d", fieldLength, HI_ACC, 0);
		outFile << pl << nl;
	}
	else
	{
		pl.sprintf("%-*s = %-4d", fieldLength, HI_ACC, 1);
		outFile << pl << nl;
	}
	WriteUnderLine(outFile);
	outFile << nl;

	// Write gui settings and switches.
	// Will be ignored by reconstruction programs
	//////////////////////////////////////////////
	WriteUnderLine(outFile);
	WriteCommentLine("GUI settings, not used for backprojection",outFile);
	WriteUnderLine(outFile);						   
	//WriteCommentLine("	Use MPI [default: on]",outFile);
	//WriteCommentLine("	Version of MPI to use (DeinoMPI1.x/DeinoMPI2.x/MPICH2/undef]",outFile);
	//WriteCommentLine("	Number of MPI processes",outFile);
	WriteCommentLine("	Number of thread to use [default: 3]",outFile);
	WriteCommentLine("	Do processing of weighting and filtering [default: on]",outFile);
	WriteCommentLine("	Do backprojection processing [default: on]",outFile);
	WriteUnderLine(outFile);
	//pl.sprintf("%-*s = %-4d", fieldLength, USE_MPI, m_ctrl.CkBox_UseMPI->isChecked());
	//outFile << pl << nl;
	//QString mpiVers = m_ctrl.CBox_MPIVersion->currentText();
	//pl.sprintf("%-*s = %s", fieldLength, MPI_VERSION, mpiVers.toStdString().c_str());
	//outFile << pl << nl;
	//pl.sprintf("%-*s = %-4d", fieldLength, NUM_MPI_PROC, m_ctrl.SBox_NumberOfMPIProcesses->value());
	//outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, NUM_THREADS, m_ctrl.SBox_NumberOfMPIProcesses->value());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, DO_WEIGHT_FILTER, m_ctrl.CkBox_WeightFilter->isChecked());
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, DO_BACK_PROJECT, m_ctrl.CkBox_Backprojection->isChecked());
	outFile << pl << nl;
	WriteUnderLine(outFile);						   

	return true;
}

void ProjectSerialize::WriteASCIIHeader(QTextStream &outFile)
{
	QString userStr;
	userStr = QObject::tr(getenv("USERNAME"));
	QDateTime dateTime;
	QString timeStr = dateTime.currentDateTime().toString();
	outFile << QString(TR("#####################################################################\n"));
	outFile << TR("#\n#\tAutomatically generated file.\n");
	outFile << TR("#\tCreated/modified Date/Time:  ") << timeStr << TR("\n");
	outFile << TR("#\tCreated/modified by: ") << userStr << TR("\n");
	outFile << QString(TR("#\n#####################################################################\n"));
}

void ProjectSerialize::WriteCommentLine(const char *msg, QTextStream &outFile)
{
	QString str;
	str.sprintf("# %s\n", msg);
	outFile << str;
}

void ProjectSerialize::WriteUnderLine(QTextStream &outFile)
{
	QString str;
	str.sprintf("###############################################################################\n");
	outFile << str;

}

QString ProjectSerialize::GetDataType(QString dType)
{
	if(dType == "byte")
	{
		return SERIAL_BYTE;
	}
	else 
	if(dType == "short16")
	{
		return SERIAL_SHORT;
	}
	else 
	if(dType == "ushort16")
	{
		return SERIAL_USHORT;
	}
	else 
	if(dType == "int32")
	{
		return SERIAL_INT;
	}
	else 
	if(dType == "real32")
	{
		return SERIAL_REAL;
	}
	else
	{
		return SERIAL_UNDEF;
	}
}

int ProjectSerialize::GetFlipAxis(QString axis)
{
	if(axis == "none")
	{
		return 2;
	}
	else 
	if(axis == "x-axis")
	{
		return 0;
	}
	else
	if(axis == "y-axis")
	{
		return 1;
	}
	else
	if(axis == "x/y-axis")
	{
		return -1;
	}
	else
	{
		return 2;
	}
}

bool ProjectSerialize::ValidateTextField(QLineEdit *textField, QString message)
{
	if(textField->text().isEmpty())
	{
		QMessageBox::information(0,TR("Missing Parameter"), 
			TR("Mandatory field is empty; see Statusbar for Information"));
		QString msg(TR("Error reading Parameter: "));
		msg += message;
		m_ctrl.statusBar->showMessage(msg);
		return false;
	}
	return true;
}

bool ProjectSerialize::Validate(QCheckBox *chkBox, QLineEdit *textField, QString message)
{
	if(textField->text().isEmpty() && chkBox->checkState() == Qt::Unchecked)
	{
		QMessageBox::information(0,TR("Missing Parameter"), 
			TR("Mandatory field is empty; see Statusbar for Information"));
		QString msg(TR("Error reading Parameter: "));
		msg += message;
		m_ctrl.statusBar->showMessage(msg);
		return false;
	}
	return true;
}

void ProjectSerialize::PrintParameterError(const char* parameter)
{
	QString msg;
	msg.sprintf("Error reading parameter >> %s <<",parameter);
	QMessageBox::warning(0,TR("Error reading parameter"),msg);
}

void ProjectSerialize::AddChildsToTree(int node, const QMap<QString,double> &fileDegree, QTreeWidget *toplevel)
{
	QString root;
	root.sprintf("Segment-%02d:", node);
	QStringList list;


	QMap<QString,double>::const_iterator iter = fileDegree.constBegin();
	if(iter != fileDegree.constEnd())
	{
		QFileInfo dir(iter.key());
		QString path  = dir.path();
		root = root + TR(" ") + path;
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

bool ProjectSerialize::CheckMaxVolRecSize()
{
		int w = m_ctrl.SBox_VolumeWidth->value();
		int h = m_ctrl.SBox_VolumeHeight->value();
		int d = m_ctrl.SBox_VolumeDepth->value();
		int x = m_ctrl.SBox_VolumeOriginX->value();
		int y = m_ctrl.SBox_VolumeOriginY->value();
		int z = m_ctrl.SBox_VolumeOriginZ->value();
		int w_max = m_ctrl.SBox_ImgWidth->value();
		int h_max = m_ctrl.SBox_ImgHeight->value();
		int d_max = w_max;
		bool flag = false;
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
			m_ctrl.SBox_VolumeWidth->setValue(w);
			m_ctrl.SBox_VolumeOriginX->setValue(x);
			QString msg;
			msg.sprintf("Volume selection (width) to large.\nResize selection.");
			QMessageBox::warning(0,TR("Change Volume Selection"),msg);
			flag = true;
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
			m_ctrl.SBox_VolumeHeight->setValue(h);
			m_ctrl.SBox_VolumeOriginY->setValue(y);
			QString msg;
			msg.sprintf("Volume selection (height) to large.\nResize selection.");
			QMessageBox::warning(0,TR("Change Volume Selection"),msg);
			flag = true;
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
			m_ctrl.SBox_VolumeDepth->setValue(d);
			m_ctrl.SBox_VolumeOriginZ->setValue(z);
			QString msg;
			msg.sprintf("Volume selection (depth) to large.\nResize selection.");
			QMessageBox::warning(0,TR("Change Volume Selection"),msg);
			flag = true;
		}
		return flag;
}