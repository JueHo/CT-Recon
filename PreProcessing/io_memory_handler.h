#ifndef _IO_MEMORY_HANDLER_H
#define _IO_MEMORY_HANDLER_H

#include <windows.h>
#include <fstream>
#include "definitions_public.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>
#include <blitz/array.h>
#include "ui_projectionpreprocessor.h"

class IOMemoryHandler
{
public:
	IOMemoryHandler(){};
	IOMemoryHandler(PreprocParam param)
	:m_parameter(param)
	{
		m_memoryStack = 0;
	}

	~IOMemoryHandler();

	//-ju-check memory and alloc memory
	// if fails return MSG_CODE and message string
	///////////////////////////////////////////////
	MSG_CODE AllocProjectionStack(QString &msgStr);
	//-ju-free memory
	//////////////////
	void DeAllocProjectionStack();
	float *GetStackPTR()
	{
		return m_memoryStack; //-ju->0 invalid
	}

	MSG_CODE LoadProjectionsToMemory(QString &msgStr);
	static void LoadProjectionsToMemory(QMutex mtx, Ui::ProjectionPreProcessorClass ui);
	MSG_CODE SaveProjections(float *vol);

	QStringList GetProjectionFilesList()
	{
		return m_projectionFileList;
	}
private:
	//IOMemoryHandler(){}; //-ju-hide std-cto
	// holds pointer to memory
	float *m_memoryStack;
	PreprocParam m_parameter;
	QStringList m_projectionFileList;

private:
	MSG_CODE CreateProjectionFilesList();
	QString GetFileExtension();
};

#endif // _IO_MEMORY_HANDLER_H