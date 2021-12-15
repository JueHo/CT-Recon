/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#include "statehandler.h"

StateHandler::StateHandler(QObject *parent, Ui::ProjectionPreProcessorClass *ui)
	: QObject(parent), m_ui(ui)
{

}

StateHandler::~StateHandler()
{

}

void StateHandler::InitStateHandler(Ui::ProjectionPreProcessorClass *ui, QObject *parent)
{
	//QObject(parent);
	m_ui = ui;
}

void StateHandler::NewProject()
{
	
}
