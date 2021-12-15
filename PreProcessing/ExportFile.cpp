/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "ExportFile.h"
#include <QtCore/QString>


bool ProjectSerialize::WriteASCIIFile(const QString &filename, CtrlSerialize param)
{
	QFile asciiFile(filename);
	if (!asciiFile.open(QIODevice::WriteOnly))
	{
		QString msg;
		msg.sprintf("Can not create/write to File: %s", filename.toStdString().c_str());
		QMessageBox::warning(0, QObject::tr("Error creating/writing File"), msg);
		return false;
	}
	QTextStream outFile(&asciiFile);
	WriteASCIIHeader(outFile);
	QString pl;
	QString nl;
	nl.sprintf("\n");
	// write sinogram image parameters
	outFile << nl;
	WriteUnderLine(outFile);
	WriteCommentLine("Sinogram image settings", outFile);
	WriteCommentLine("	width in pixel", outFile);
	WriteCommentLine("  height in pixel", outFile);
	WriteCommentLine("  size in mm", outFile);
	WriteCommentLine("  sinogram data type (byte/short16/ushort16/int32/real32)", outFile);
	WriteCommentLine("  process limited angle [default: 0]", outFile);
	WriteCommentLine("  use sinogram file list (for lim. angle process. always 1) [default: 0]", outFile);
	WriteCommentLine("  sinogram name", outFile);
	WriteCommentLine("  sinogram directory", outFile);
	WriteCommentLine("  preprocessed sinogram directory", outFile);
	WriteCommentLine("	write pre-processed sinograms to block file (0/1) [default: 1]", outFile);
	WriteUnderLine(outFile);
	// print left aligned pad size 28
	int fieldLength = 28;
	pl.sprintf("%-*s = %-4d", fieldLength, IMG_WIDTH, param.imageWidth);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, IMG_HEIGHT, param.imageHeight);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, PIXEL_SIZE, param.pixelSize);
	outFile << pl << nl;
	pl.sprintf("%-*s = %s", fieldLength, IN_DATATYPE, param.inDataFormat.toStdString().c_str());
	outFile << pl << nl;
	// from options settings
	pl.sprintf("%-*s = %-4d", fieldLength, LIM_ANG_BPROJ, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, USE_FILE_LIST, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %s", fieldLength, SINO_NAME,
		param.sinoNamePattern.toStdString().c_str());
	outFile << pl << nl;

	pl.sprintf("%-*s = %s", fieldLength, SINO_DIR,
		param.sinoDir.toStdString().c_str());
	outFile << pl << nl;

	pl.sprintf("%-*s = %s", fieldLength, SINO32_DIR,
		param.sino32Dir.toStdString().c_str());
	outFile << pl << nl;

	pl.sprintf("%-*s = %-4d", fieldLength, SINO32_BLOCK_WRITE, param.sino32BlockWrite);
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Projection settings", outFile);
	WriteCommentLine("	number of projections", outFile);
	WriteCommentLine("  first file index [default: 1]", outFile);
	WriteCommentLine("  angle increment", outFile);
	WriteCommentLine("  projections start at angle [default: 0 Grad]", outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-4d", fieldLength, CNT_PROJ, param.numberOfProjections);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, START_IDX, param.startIndex);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, ANGLE_INCR, param.angleIncr);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, START_ANGLE, param.startAngle);
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Geometry & filter settings", outFile);
	WriteCommentLine("	filter type (SheppLogan/Ramp/PhaseContrast)", outFile);
	WriteCommentLine("	phase contrast set internal filter to ramp (only for size used) (value 0/1 off/on)", outFile);
	WriteCommentLine("	flip sinogram along none/x-axis/y-axis/xy-axis (2/0/1/-1)", outFile);
	WriteCommentLine("  horizontal shift in (sub)pixel", outFile);
	WriteCommentLine("  horizontal shift in (sub)pixel", outFile);
	WriteCommentLine("  distance source detector in mm", outFile);
	WriteCommentLine("  distance source rotation centre in mm", outFile);
	WriteUnderLine(outFile);
	if (param.filterType.toStdString() == "PhaseContrast")
	{
		pl.sprintf("%-*s = %s", fieldLength, APPLY_FILTER, "Ramp");
		outFile << pl << nl;
		outFile << "use_phase_contrast_filter	 = 1" << nl;
	}
	else
	{
		pl.sprintf("%-*s = %s", fieldLength, APPLY_FILTER, param.filterType.toStdString().c_str());
		outFile << pl << nl;
		outFile << "use_phase_contrast_filter	 = 0" << nl;
	}
	////-ju-14-Apr-2015
	///////////////////
	pl.sprintf("%-*s = %-4d", fieldLength, VIEW_DIRECTION, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, FLIP_IMAGE, 2);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+6.3f", fieldLength, HORIZ_SHIFT, param.horizShift);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+6.3f", fieldLength, VERT_SHIFT, 0.0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, DSD, param.distSrcDet);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-6.3f", fieldLength, DSO, param.distSrcRot);
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("Reconstruction & tomogram parameters", outFile);
	WriteCommentLine("	binning factor [default: 1] (no binning)", outFile);
	WriteCommentLine("	volume width in voxel", outFile);
	WriteCommentLine("  volume height in voxel", outFile);
	WriteCommentLine("  volume depth in voxel", outFile);
	WriteCommentLine("  volume origin x in voxel", outFile);
	WriteCommentLine("  volume origin y in voxel", outFile);
	WriteCommentLine("  volume origin z in voxel", outFile);
	WriteCommentLine("  volume origin z in voxel", outFile);
	WriteCommentLine("  tomogram data type (byte/short16/ushort16/real32)", outFile);
	WriteCommentLine("  tomogram name", outFile);
	WriteCommentLine("  tomogram directory", outFile);
	WriteCommentLine("	CT system (Micro_CT/Detect_CT 0/1)", outFile);
	WriteCommentLine("	use pre-processed sinograms to block file for recon. (0/1) [default: 1]", outFile);
	WriteCommentLine("	write tomogram block files (not possible for batch) (0/1) [default: 1]", outFile);
	WriteCommentLine("	write converted tomograms back to block file (0/1) [default: 0]", outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-4d", fieldLength, PREVIEW_SCALE, 1);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_X, param.volWidth);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_Y, param.volHeight);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, VOL_Z, param.volWidth);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_X, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_Y, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, W_ORIG_Z, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %s", fieldLength, OUT_DATATYPE, "real32");
	outFile << pl << nl;
	pl.sprintf("%-*s = %s", fieldLength, TOMO_NAME, param.tomoName.toStdString().c_str());
	outFile << pl << nl;
	pl.sprintf("%-*s = %s", fieldLength, TOMO_DIR, param.tomoDir.toStdString().c_str());
	outFile << pl << nl;
	int ctSystem = 0;
	pl.sprintf("%-*s = %-4d", fieldLength, CT_SYSTEM, ctSystem);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, SINO32_BlOCK_USE, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, TOMO_BLOCK_WRITE, 0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, CONV_Block_INTERNAL, 0);
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	WriteUnderLine(outFile);
	WriteCommentLine("CPU and GPU settings", outFile);
	WriteCommentLine("	CPU Memory usage  in % [default: 90%]", outFile);
	WriteCommentLine("	GPU Memory usage  in % [default: 90%]", outFile);
	WriteCommentLine("	GPU Threads X [default: 16]", outFile);
	WriteCommentLine("	GPU Threads Y [default: 16]", outFile);
	WriteCommentLine("	GPU Compatibility Version (1.x/2.x)", outFile);
	WriteCommentLine("	Number of GPUs used [default: 1]", outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-+6.3f", fieldLength, CPU_MEM_USE, 90.0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-+6.3f", fieldLength, GPU_MEM_USE, 90.0);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, THREADS_X, 16);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, THREADS_Y, 16);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, NUM_GPUS_USE, 1);
	outFile << pl << nl;
	WriteUnderLine(outFile);
	outFile << nl;

	// Write gui settings and switches.
	// Will be ignored by reconstruction programs
	//////////////////////////////////////////////
	WriteUnderLine(outFile);
	WriteCommentLine("GUI settings, not used for backprojection", outFile);
	WriteUnderLine(outFile);
	WriteCommentLine("	Number of thread to use [default: 3]", outFile);
	WriteCommentLine("	Do processing of weighting and filtering [default: on]", outFile);
	WriteCommentLine("	Do backprojection processing [default: on]", outFile);
	WriteUnderLine(outFile);
	pl.sprintf("%-*s = %-4d", fieldLength, NUM_THREADS, 8);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, DO_WEIGHT_FILTER, 1);
	outFile << pl << nl;
	pl.sprintf("%-*s = %-4d", fieldLength, DO_BACK_PROJECT, 0);
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

bool ProjectSerialize::ReadLogFile(const QString &filename, CtrlSerialize &logParam)
{
	std::ifstream logFile;
	bool legacyFlag = false; // old dso and dsd
	logFile.open(filename.toStdString().c_str());
	if (!logFile.is_open())
	{
		return false;
	}
	char line[101];
	QString lineIn;
	QStringList splitLine;
	while (logFile.getline(line, 100))
	{
		lineIn = line;
		splitLine = lineIn.split(':');
		QString item = splitLine[0].trimmed();
		item.replace(QString("[deg]"), QString(""));
		item = item.trimmed();
		item.replace(QString("[mm]"), QString(""));
		item = item.trimmed();
		if (QObject::tr("Startangle") == item)
		{
			logParam.startAngle = splitLine[1].toDouble();
		}
		if (QObject::tr("Anglestep") == item)
		{
			logParam.angleIncr = splitLine[1].toDouble();
		}
		if (QObject::tr("Binning mode") == item)
		{
			int binning = splitLine[1].toInt();
			if (binning == 1)
			{
				logParam.pixelSize = 0.2;
			}
			else
			{
				logParam.pixelSize = 0.4;
			}
		}
		if (QObject::tr("Distance source-detector") == item) 
		{
			logParam.distSrcDet = splitLine[1].toDouble();
			//-ju-03-Nov-2016 set legacy flag
			legacyFlag = true;
		}
		//-ju-Nov-2016 assume "Distance source-detector [mm]" is before "Xpos"
		if (QObject::tr("Xpos") == item && legacyFlag)
		{
			logParam.distSrcRot = splitLine[1].toDouble();
		}
		//-ju-Nov-2016 new logfile type
		///////////////////////////////
		if (QObject::tr("DSD") == item)
		{
			logParam.distSrcDet = splitLine[1].toDouble();
		}
		if (QObject::tr("DSO") == item)
		{
			logParam.distSrcRot = splitLine[1].toDouble();
		}
		//-ju-Nov-2016
		//////////////

	}

	return true;
}
