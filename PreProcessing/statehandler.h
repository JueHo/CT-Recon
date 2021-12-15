/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <QtCore/QObject>
#include "ui_projectionpreprocessor.h"
#include "ProcessParameterTypes.h"

class StateHandler : public QObject
{
	Q_OBJECT

public:
	StateHandler(QObject *parent = 0, Ui::ProjectionPreProcessorClass *ui = 0);
	~StateHandler();

	void InitStateHandler(Ui::ProjectionPreProcessorClass *ui, QObject *parent = 0);
	void NewProject();
	ProcessParameter GetProcessParameter()
	{
		return m_processParameters;
	}

private:
	Ui::ProjectionPreProcessorClass *m_ui;
	ProcessParameter m_processParameters;
	
};

#endif // STATEHANDLER_H
