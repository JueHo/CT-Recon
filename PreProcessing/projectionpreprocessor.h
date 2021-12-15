/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef _PROJECTIONPREPROCESSOR_H
#define _PROJECTIONPREPROCESSOR_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
//#include <QtConcurrent>
#include <QtCore/QFuture>
#include <QtCore/QMutexLocker>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/QMessageBox>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <opencv2/opencv.hpp>
#include <cstdint>
#include "ui_projectionpreprocessor.h"
#include "statehandler.h"
#include "threadload.h"
#include "ThreadProcessing.h"
#include "ScaleImageDownThread.h"
#include <windows.h>
#include "ExportFile.h"

using namespace std;
using namespace cv;

const uint64_t MAX_IMAGE_SIZE = 512;

class ProjectionPreProcessor : public QMainWindow
{
	Q_OBJECT

protected:
	bool eventFilter(QObject *targetCtrl, QEvent *event);

public:
	ProjectionPreProcessor(QWidget *parent = 0);
	~ProjectionPreProcessor();

	ThreadLoad *m_pLoadFileThread;
	ThreadScImage *m_pScaleImageThread;
	ThreadProcessing *m_pProcessingThread;

	string type2str(int type) 
	{
		string r;

		uchar depth = type & CV_MAT_DEPTH_MASK;
		uchar chans = 1 + (type >> CV_CN_SHIFT);

		switch (depth) 
		{
		case CV_8U:  r = "8U"; break;
		case CV_8S:  r = "8S"; break;
		case CV_16U: r = "16U"; break;
		case CV_16S: r = "16S"; break;
		case CV_32S: r = "32S"; break;
		case CV_32F: r = "32F"; break;
		case CV_64F: r = "64F"; break;
		default:     r = "User"; break;
		}

		r += "C";
		r += (chans + '0');

		return r;
	}

	QVector<Mat> GetVisImageVector()
	{
		return m_visImageStack;
	}

	void SetVisImageVector(QVector<Mat> vec)
	{
		m_visImageStack = vec;
	}

private:
	Ui::ProjectionPreProcessorClass ui;
	StateHandler m_stateHandler;
	float *m_pMemImageStack;
	float *m_pMemTileImageStack;
	uchar *m_pMemScaledImageStack;
	QVector<Mat> m_visImageStack;
	ProcessParameter m_processingParam;
	QVector<QRgb>  m_ColorTable;

	void SaveSettings();
	QString m_lastProjectPath;


	bool CreateProjectionFilesList();
	void ClearProjectSettings();
	void EnableForOpen();
	void MakeEditable();
	void MakeOpenEditable();
	void SaveFileProccess();

	void WriteProjectParameterToFile();
	void WriteProjectParameterToGui();
	void ReadProjectParametersFromGUI();
	void ReadProjectParameterFromFile();

	bool AllocMemory();
	bool AllocTileMemory();
	void DeAllocImageStack();
	void DeAllocTileImageStack();
	bool AllocScaledImgStacKMemory(uint64_t arr3DSz);
	void DeAllocScaledImageStack();

	bool TileProjections(const uint32_t NumTiles);

private slots:
	void I_SelectInputFiles();
	void I_LoadInputData();
	void I_LoadInputDataInterrupt();
	void LoadValueChanged(QString msg);
	void LoadThreadStopped();
	void LoadThreadStart();
	void LoadThreadEnd();
	void LoadThreadUpdateProgressBar(int prog);
	// image processing
	void UndoImageProcessing();
	void EqualizeImages();
	void ChangeContrastOfCurrentImage(double);
	void ContrastApplyToImages();
	// scaled images
	void ScImgThreadValueChanged(QString msg);
	void ScImgThreadThreadStart();
	void ScImgThreadThreadEnd();
	void ScImgThreadThreadUpdateProgressBar(int prog);
	// processing
	void RunProcessing();
	void RunSaving();
	void ProcessingThreadStart();
	void ProcessingThreadEnd();
	void ProcessingThreadValueChanged(QString msg);
	void ProcessingThreadUpdateProgressbar(int);
	// normalize
	void NormalizeSelect();
	//method selection
	void SetEnableMethods();
	// running panel
	void SaveOutputMessage();
	// check settings
	void CheckSettingsForRun();

	// Save processed data
	void SaveProcessedData();

	// load flat & dark field
	void LoadFlatFieldImage();
	void LoadDarkFieldImage();

	// check BHC
	void BHCStateChanged();
	void NormalizeStateChanged();
	//-ju-21-Oct-2015
	void NoLogStateChanged();
	//-ju-23-Feb-2018 enable to work with already dark/falt corrected projections
	void DarkFlatCorrectedStateChanged();

	void NewProject();
	void SetModified();
	void SaveProject();
	void SaveProjectAs();
	void OpenProject();
	void ExportPFDK();
	void About();
	void UpdateMainWindow();
	void ImageViewShowImage();
	void WindowsSelectionState();

	// start lorentz filter dialog
	//////////////////////////////
	void StartLorentzFilterDialog();
	void SetupLorentzFilter();

	//-ju-15-Feb-2018 add clockwise
	void ChangeDirection();

public:
	void DisableAllCntrl();
	void EnableAllCntrl();
	bool CheckValidityForRun();
	bool CheckAvailableMemory();
	//-ju-23-09-2015 add
	uint32_t CheckTileMemory();
	Mat GetCurrentVizImage();

	float *GetMemoryStackPtr();
	float *GetTileMemoryStackPtr();
	uchar *GetScaledImageStackPtr();
	ProcessParameter GetprocessingParam();
	void  SetScaleFactor(uint32_t scFac);
	//-ju-23-Feb-2018
	void SetMaxGreyValue(double greyVal);
	
	
	QPixmap Mat2Pixmap(Mat &img);

private:
	QStringList m_inputFileList;
	QString m_inputFilePattern;
	QString m_inputDirName;
	QString m_inputSuffix;
	uint32_t m_imgW_Cols;
	uint32_t m_imgH_Rows;
	StateHandler m_stateHnd;
	bool m_isModified;
	uint32_t m_scalFactor;
	//-ju-23-Feb-2018
	double m_maxGreyVal;

	QPoint m_startMove;
	QRect  m_rectSelection;
	QRect  m_rectSelectionRedraw;
	bool m_doDrawing;
	QPixmap m_pix;
	int32_t m_x;
	int32_t m_y;
};

#endif // _PROJECTIONPREPROCESSOR_H
