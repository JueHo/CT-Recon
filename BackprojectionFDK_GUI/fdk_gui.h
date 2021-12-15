/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef FDK_GUI_H
#define FDK_GUI_H

#include <QtWidgets/QMainWindow>
#include "ui_fdk_gui.h"
#include "image_dlg.h"
#include "import_dlg.h"
#include <QtGui/qtguiglobal.h>
#include <QtCore/qfile.h>
#include <QtCore/qprocess.h>
#include <QtCore/qtimer.h>
#include "project_serialize.h"

//-ju- temp hardcode image zoom
#define ZOOM 2

class FDK_GUI : public QMainWindow
{
	Q_OBJECT

public:
	FDK_GUI(QWidget *parent = 0);
	~FDK_GUI();
public:
	Ui::FDK_GUIClass GetUI()
	{
		return ui;
	}

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);
	void closeEvent(QCloseEvent *event);

private:
	Ui::FDK_GUIClass ui;
	ImageDLG *m_imgDlg;
	ImportDLG *m_importDlg;
	QStringList m_fileList;
	QString m_LimAnglePreProcDir;
	QVector<QMap<QString,double> > m_LimAngleSinoFileList;
	QProcess m_filterProc;
	QProcess m_reconProc;

	// timer
	QTimer m_timer;
	double  m_procTime;

	QString m_projectName;
	QLabel *m_toolLabel;

	// path to data and mpi
	QString m_mpiPath;
	QString m_dataPath;

	ProjectSerialize projSerialize;

	QString m_StyleSheet_DSBox_AngleIncr;
	QString m_StyleSheet_DSBox_SinoStartAtAngle;

	bool m_volSelecTooBig;
	bool m_stopBatch;
	int  m_batchCnt;
	int  m_batchIndex;
private:
	// additional helper functions
	void SetAddtionalControlProperties();
	void SetAdditionalConnections();

	void DeleteItemSelectionFromList();

	void AddChildsToTree(int node,const QMap<QString,double> &fileDegree,QTreeWidget *toplevel);
	void DelFromLimAngleSinoFileList(int topIndex);
	void ReListLimAngleSinoFileList();
	void SetFilePattern(QString sinogramDir);

	//-ju-
	void SaveProjectAs(QString &filename);
	void SaveProject(/*QString filename*/);
	void SetGUIOnSave(bool enable);
	void OpenProjectFile(QString &filename);

	void GetMPIVersion();
	//bool VersionNumbers(int &major,int &submajor,int &minor,int &subminor);

template<typename ImageType>
void DisplaySinograms(ImageType MaxVal)
{
	int w = ui.SBox_ImgWidth->value();
	int h = ui.SBox_ImgHeight->value();

	int rowNo = ui.ListWidget_SinogramList->currentRow();
	QString rowNoStr;
	rowNoStr.sprintf("   #%d",rowNo);
	QList<QListWidgetItem*> wList = ui.ListWidget_SinogramList->selectedItems();
	QByteArray imgData;
	std::vector<ImageType> ucharTmp;
	if(wList.size() > 0)
	{
		QString itemFilename = wList[0]->text();


		std::vector<unsigned char> rawdata;
		if(rawFile2Image<ImageType>(itemFilename,rawdata,w,h,MaxVal,0))
		{
			if(m_imgDlg == 0)
			{
				m_imgDlg = new ImageDLG(this);
			}
			m_imgDlg->show();
			m_imgDlg->raise();
			QFile imageFile(itemFilename);
			QVector<QRgb> colorTable;
			for (int i = 0; i < 256; i++)
				colorTable.push_back(qRgb(i, i, i));

			QByteArray imageData((const char*)&rawdata[0],w*h);
			QImage image((uchar*)imageData.data(),w,h,w,QImage::Format_Indexed8);

			//-ju-24-June-2011 perform scaling
			w /= m_imgDlg->GetZoom();
			h /= m_imgDlg->GetZoom();
			image = image.scaled(w,h);

			image.setColorTable(colorTable);
			QString winTitle(itemFilename);
			winTitle += rowNoStr;
			m_imgDlg->setWindowTitle(winTitle); 

			QPixmap *pix = new QPixmap(w,h);
			m_imgDlg->GetImageArea()->setPixmap(pix->fromImage(image, 0));

			//-ju-24-June-2011 lim. max. size of label widget to image size
			m_imgDlg->GetImageArea()->setMaximumHeight(h);
			m_imgDlg->GetImageArea()->setMaximumWidth(w);

			ui.ListWidget_SinogramList->setFocus();

		}
		else
		{
			if(m_imgDlg != 0)
				m_imgDlg->hide();
			return;
		}
	}
}


private slots:
	void SinoFileSelections();
	void EditFilePattern();
	void SinogramDir();
	void SinogramPreProcDir();
	void RemSelSinoFromList();
public slots:
	// make it public to use for image viewer
	void ShowSinogram();
private slots:
	void LimAnglePreProcDirSel();
	void LimAngleAddSegment();
	void LimAngleRemoveSegment();
	void RunReconstruction();
	void UpdateFromFilterProc();
	//void UpdateErrMsgFromFilterProc();
	void UpdateFromRecProc();
	//void UpdateErrMsgFromRecProc();
	void ProcStarted();
	void ProcFinished();
	void ProcStartedRec();
	void ProcFinishedRec();
	void DeleteALLItemFromList();
	void SavePathSetting();
	void LoadPathSetting();
	void SetUseFileList();
	void SetupMPIPath();
	void SetupDataTopPath();
	void SetupTomoDir();
	void SetupControls();
	void ChangeGPUThreads();
	void SetVolumeCoord();
	void SetVolumeSelectionButton();
	void StopWFProcess();
	void StopRecProcess();
	void SetBinningSettings();
	void CheckMaxVolRecSize();
	void updateProcTime();
	void AddProjectToBatch();
	void RemoveProjectFromBatch();
	void RunBatch();
	void SaveProcessOutput();
	void StopBatch();
	void CkeckBlockStatus();
	void ResetBlockFileSettings(int val);
	void ResetDisplaySettings(bool val);
	void ResetDisplaySettingsFS(int val);

	//-ju-17-June-2021 new
	void SetTiltCorr();
	void SlopeTiltValueChanged();
	void ConstTiltValueChanged();

	// modifier
	void SetGuiModified();
	void SetOptionModified();

	// actions
	void ActionSaveProject();
	void ActionSaveProjectAs();
	void ActionSwitchView();
	void ActionOpenProject();
	void ActionCheckParameters();
	void ActionNewProject();
	void ActionImportDetectData();
};

#endif // FDK_GUI_H