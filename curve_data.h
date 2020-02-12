#ifndef CURVE_DATA_H
#define CURVE_DATA_H

#include <qwt_series_data.h>
#include <vector>

class CurveData : public QwtSeriesData<QPointF>
{
public:
    CurveData();

public:
    QPointF sample(size_t i) const override { return _data[i]; }
    size_t size() const override { return _data.size(); }
    QRectF boundingRect() const override { return d_boundingRect; }

public:
    void appendPoint(double x, double y);
    void appendValue(double inc, double value);
    void clear();
    void clear(double left);

private:
    void updateBoundingRect(double x, double y);

private:
    std::vector<QPointF> _data;
};

#endif //CURVE_DATA_H
