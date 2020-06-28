#ifndef CURVE_H
#define CURVE_H

#include <qwt_plot_curve.h>

class CurveData;

class Curve : public QwtPlotCurve
{
public:
    Curve();

public:
    void appendPoint(double x, double y);
    void appendValue(double inc, double value);
    void setMaxPoints( int count );
    void clear();
    void clear(double left);
    bool isGoingToLeft(double x) const;
    double left() const;
    double right() const;
    int getCurrentPos() const;

private:
    CurveData *_data;
};

#endif //CURVE_H
