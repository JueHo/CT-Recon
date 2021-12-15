/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#pragma once
#ifndef _CROSS_PLOT_H
#define _CROSS_PLOT_H
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>

// overwrite QwtPlotPicker to get access to 
// protected member invTransform()
/////////////////////////////////////////////
class CrossPlotPicker : public QwtPlotPicker
{
public:
	CrossPlotPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas *canvas)
		:QwtPlotPicker(xAxis, yAxis, rubberBand, trackerMode, canvas)
	{}

	QPointF posToPlotCoord(const QPoint &pos)
	{
		return QwtPlotPicker::invTransform(pos);
	}
};

#endif // _HIST_PICKER_H