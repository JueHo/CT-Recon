/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef THREADLOAD_H
#define THREADLOAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex> 
#include "ui_projectionpreprocessor.h"
#include <memory.h>
class ProjectionPreProcessor;

class ThreadLoad : public QThread
{
	Q_OBJECT

public:
	ThreadLoad(QObject *parent, bool intrp = false, bool thsp = false);
	~ThreadLoad();

	void run();

	// interrupting thread
	bool m_interrupt;
	bool m_thread_stopped;

signals:
	void valueChanged(QString);
	void updateProgressBar(int);
	void threadStart();
	void threadEnd();
	void threadStopped();

public slots:


private:
	QMutex m_mutex;
	ProjectionPreProcessor *m_parentObject;
	double m_maxGreyInStack;
};

#endif // THREADLOAD_H
