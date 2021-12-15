/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef _SCALE_IMAGE_DOWN_THREAD_H
#define _SCALE_IMAGE_DOWN_THREAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex> 
#include "ui_projectionpreprocessor.h"
#include <memory.h>
class ProjectionPreProcessor;

class ThreadScImage : public QThread
{
	Q_OBJECT

public:
	ThreadScImage(QObject *parent);
	~ThreadScImage();

	void run();


signals:
	void valueChanged(QString);
	void updateProgressBar(int);
	void threadStart();
	void threadEnd();

	public slots:


private:
	QMutex m_mutex;
	ProjectionPreProcessor *m_parentObject;
};


#endif //_SCALE_IMAGE_DOWN_THREAD_H