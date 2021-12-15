#ifndef CONVERTBYHISTOGRAMMAPPING_H
#define CONVERTBYHISTOGRAMMAPPING_H

#include <QtWidgets/QMainWindow>
#include "ui_convertbyhistogrammapping.h"

class ConvertByHistogramMapping : public QMainWindow
{
	Q_OBJECT

public:
	ConvertByHistogramMapping(QWidget *parent = 0);
	~ConvertByHistogramMapping();

private:
	Ui::ConvertByHistogramMappingClass ui;
};

#endif // CONVERTBYHISTOGRAMMAPPING_H
