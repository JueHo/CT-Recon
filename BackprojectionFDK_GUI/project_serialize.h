/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _PROJECT_SERIALIZE_H
#define _PROJECT_SERIALIZE_H

#include "ui_fdk_gui.h"

enum Flip_Axis
{
	none=2,
	verticalAxis=1,
	horizontalAxis=0,
	bothAxis=-1,
};

enum Flip_Axis_Index
{
	noneFlip=0,
	xAxis=1,
	yAxis=2,
	xyAxis=3,
};

struct CtrlSerialize
{
	QString							projectName;
	int								imageWidth;
	int								imageHeight;
	int								numberOfProjections;
	double							angleIncr;
	double							pixelSize;
	double							horizShift;
	double							vertShift;
	//-ju-18-June-2021 add tilt corr
	int								useTiltCorr;
	double							slopeTiltCorr;
	double							offsetTiltCorr;
	//////
	double							distSrcDet;
	double							distSrcRot;
	QString							inDataFormat;
	int								startIndex;
	double							startAngle;
	QString							filterType;
	int								phaseContrastFilter;
	int		 						flipImage;
	int								binFactor;
	int								volWidth;
	int								volHeight;
	int								volDepth;
	int								volOrigX;
	int								volOrigY;
	int								volOrigZ;
	QString							outDataFormat;
	QString							tomoName;
	QString							tomoDir;
	double							cpuMemUsage;
	double							gpuMemUsage;
	int								gpuThreadX;
	int								gpuThreadY;
	QString							gpuVersion;
	int								interpolFast;
	int								numOfGPUThreads;
	QString 						CTSystem;
	bool							useMPI;
	QString 						MPIVersion;
	QStringList 					sinoList;
	QString							sinoNamePattern;
	QString							sinoDir;
	QString							sino32Dir;
	int								useFileList;
	int								doLimitedAngleReconstruction;
	QVector<QMap<QString,double> >	limitedAngleSinograms;
	QStringList						sinogramList;
	QString							limitedAngleSinoDir;
	int								doWeightAndFiltering;
	int								doBackprojection;
	int								numMPIProcesses;
	int								sino32BlockWrite;
	int								sino32BlockUse;
	int								tomoBlockWrite;
	int								convBlockInternal;
};


class ProjectSerialize
{
public:
	void Init(Ui_FDK_GUIClass &ui)
	{
		m_ctrl = ui;
	}
	void ReadIniFile();
	void WriteIniFile();
	bool WriteToFile(const QString &filename, bool isASCII = true);
	void ReadFromFile(const QString& filename, 
					  CtrlSerialize &elements,
					  QStringList &fileList,
					  QVector<QMap<QString,double> > &limAngSinograms,
					  bool isASCII = true);
private:
	bool ReadASCIIFile(const QString& filename, 
					   CtrlSerialize &elements,
					   QStringList &fileList,
					   QVector<QMap<QString,double> > &limAngSinograms);
	bool WriteASCIIFile(const QString &filename);
	void WriteASCIIHeader(QTextStream &outFile);
	void WriteCommentLine(const char *, QTextStream &outFile);
	void WriteUnderLine(QTextStream &outFile);
	QString GetDataType(QString dType);
	int GetFlipAxis(QString flipAxis);
	bool ValidateTextField(QLineEdit *textField, QString message);
	bool Validate(QCheckBox *chkBox, QLineEdit *textField, QString message);
	void PrintParameterError(const char* parameter);
	bool ReadSegmentedFileList(QVector<QMap<QString,double> > &limAngSinograms,
							   QString filename);
	bool ReadFileList(QStringList &fileList,QString filename);
	void AddChildsToTree(int node,const QMap<QString,double> &fileDegree,QTreeWidget *toplevel);
	bool CheckMaxVolRecSize();
private:
	Ui_FDK_GUIClass m_ctrl;
};



#endif //_PROJECT_SERIALIZE_H