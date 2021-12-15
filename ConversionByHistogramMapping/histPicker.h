/**
*  Copyright © [2012], Empa, Juergen Hofmann
*/

#ifndef _HIST_PICKER_H
#define _HIST_PICKER_H
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>

// overwrite QwtPlotPicker to get access to 
// protected member invTransform()
/////////////////////////////////////////////
class HistPicker : public QwtPlotPicker
{
public:
	HistPicker(int xAxis,int yAxis,RubberBand rubberBand,DisplayMode trackerMode,QwtPlotCanvas *canvas)
    :QwtPlotPicker(xAxis,yAxis,rubberBand,trackerMode,canvas)
	{}

	QPointF posToPlotCoord(const QPoint &pos)
	{
		return QwtPlotPicker::invTransform(pos);
	}
};

#endif // _HIST_PICKER_H