#include "curve.h"
#include "curve_data.h"

Curve::Curve()
    : QwtPlotCurve{}
    , _data{new CurveData{}}
{
    setStyle(QwtPlotCurve::Lines);
    setRenderHint(QwtPlotItem::RenderAntialiased, true);
    setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
    setData(_data);
}

void Curve::appendPoint(double x, double y)
{
    _data->appendValue(y);
}

void Curve::appendValue(double inc, double value)
{
    _data->appendValue(value);
}

void Curve::clear()
{
    _data->clear();
}

void Curve::clear(double left)
{
    _data->clear(left);
}

bool Curve::isGoingToLeft(double x) const
{
    return x < right();
}

double Curve::left() const
{
    return _data->boundingRect().left();
}

double Curve::right() const
{
    return _data->boundingRect().right();
}

void Curve::setMaxPoints( int count )
{
    _data->setPointsCount(count);
}

int Curve::getCurrentPos() const
{
    return _data->getCurrentPos();
}
