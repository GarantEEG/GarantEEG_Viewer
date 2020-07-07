/**
@file chart.cpp

@brief Реализация класса для графика

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "charts/chart.h"
#include "charts/curve_data.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMenu>
#include <QThread>
//----------------------------------------------------------------------------------
namespace
{
    auto gridPen()
    {
        QPen pen;
        pen.setColor(Qt::gray);
        pen.setWidthF(0.5);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setDashPattern({4.0, 4.0});
        return pen;
    }
} // namespace
//----------------------------------------------------------------------------------
QFont Chart::axisFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    return font;
}
//----------------------------------------------------------------------------------
QFont Chart::titleFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    return font;
}
//----------------------------------------------------------------------------------
QwtText Chart::toQwtText(QString const &text, QFont const &font)
{
    QwtText res{text};
    res.setFont(font);
    return res;
}
//----------------------------------------------------------------------------------
Chart::Chart(QWidget *parent)
    : QwtPlot{parent}
{
	plotLayout()->setAlignCanvasToScales(true);

	enableAxis(QwtPlot::xBottom);
	enableAxis(QwtPlot::yLeft);

	setAxisAutoScale(QwtPlot::yLeft);

	setAxisTitle(QwtPlot::xBottom, toQwtText(tr("points, sec*framerate")));

	_grid.setMajorPen(::gridPen());
	_grid.setMinorPen(::gridPen());
	_grid.attach(this);

	setPalette(Qt::white);

	auto canvas = static_cast<QwtPlotCanvas *>(this->canvas());
	canvas->setPalette(Qt::white);
	canvas->setBorderRadius(10.0);

	_mark.setLineStyle(QwtPlotMarker::VLine);
	_mark.setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
	_mark.setLinePen(QPen(Qt::green, 4, Qt::SolidLine));
	_mark.attach(this);
	_mark.setVisible(false);

	insertLegend(&_legend, QwtPlot::BottomLegend);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect( this, &Chart::customContextMenuRequested, this, &Chart::customMenuRequested );
	connect( &_myContext, &CSimpleContext::onNewDataSet, this, &Chart::setFixedBorder );
}
//----------------------------------------------------------------------------------
void Chart::restart()
{
	auto it = _curves.cbegin();
	while (it != _curves.end())
	{
		it->second->GetCurveData()->restart();
		it++;
	}
}
//----------------------------------------------------------------------------------
void Chart::reCalcBoundingRect(QString const &key)
{
	auto it = _curves.find(key);
	if (it == _curves.end())
		return;

	it->second->GetCurveData()->reCalcBoundingRect();
}
//----------------------------------------------------------------------------------
void Chart::setPointsCount(uint const & sec, uint const& framerate)
{
	Q_ASSERT(sec>0);
	Q_ASSERT(framerate>0);
	_pointsCount = sec*framerate;
	setAxisScale(xBottom, 0.0, _pointsCount, framerate);
}
//----------------------------------------------------------------------------------
void Chart::setParams(AutoScaleParams const &params)
{
	if (params.IsValid())
	{
		_autoscale = params.Autoscale;
		if (_autoscale)
		{
			setAxisAutoScale(QwtPlot::yLeft);
		}
		else
		{
			setAxisScale(yLeft, params.MinValue, params.MaxValue);
		}
		_myContext.setValues(params.MinValue, params.MaxValue);
	}
}
//----------------------------------------------------------------------------------
void Chart::appendCurve(QString const &key, QString const &title, QColor const &color)
{
	auto curve = std::make_unique<Curve>();
	curve->setPen(QColor{color}, 2.0);
	curve->setTitle(toQwtText(title));
	curve->GetCurveData()->setPointsCount(_pointsCount);
	curve->attach(this);
	_curves.emplace(key, std::move(curve));
	_mark.setVisible(_curves.size()==1);
}
//----------------------------------------------------------------------------------
void Chart::appendPoints(QString const &key, std::vector<float> const &points)
{
	if (points.empty())
		return;

	auto it = _curves.find(key);
	if (it == _curves.end())
		return;

	for (auto point : points)
		it->second->GetCurveData()->appendValue(point);

	fit();
	replot();
}
//----------------------------------------------------------------------------------
void Chart::appendPoint(QString const &key, float const &value)
{
	auto it = _curves.find(key);
	if (it == _curves.end())
		return;

	it->second->GetCurveData()->appendValue(value);
}
//----------------------------------------------------------------------------------
void Chart::updateView()
{
	fit();
	replot();
}
//----------------------------------------------------------------------------------
void Chart::fit()
{
	if (_curves.empty())
		return;

	auto it = _curves.cbegin();

	if (_mark.isVisible())
		_mark.setValue(it->second->GetCurveData()->getCurrentPos(), 0.0);
}
//----------------------------------------------------------------------------------
void Chart::customMenuRequested()
{
	QMenu *menu = new QMenu(this);

	QAction *pCheckAct = menu->addAction(tr("Autoscale"),this, &Chart::onAutoScale);
	pCheckAct->setCheckable(true);
	pCheckAct->setChecked(_autoscale);

	menu->addAction(tr("Set amplitude range"), this, [this] { _myContext.move(QCursor::pos()); _myContext.exec(); });
	menu->popup(QCursor::pos ());
}
//----------------------------------------------------------------------------------
AutoScaleParams Chart::params()
{
	AutoScaleParams params;
	params.Autoscale = _autoscale;
	params.MinValue = _myContext.getMin();
	params.MaxValue= _myContext.getMax();
	return params;
}
//----------------------------------------------------------------------------------
void Chart::setFixedBorder(double min, double max)
{
	Q_ASSERT(min<max);
	setAxisScale(yLeft, min, max);
	_autoscale = false;
	replot();

	emit onBorderDataChanged( params() );
}
//----------------------------------------------------------------------------------
void Chart::onAutoScale()
{
	_autoscale = !_autoscale;
	if (_autoscale)
	{
		setAxisAutoScale(QwtPlot::yLeft);
		replot();
		emit onBorderDataChanged(params());
	}
	else
	{
		_myContext.onOffAutoscale(); //=set fixed border
	}
}
//----------------------------------------------------------------------------------
