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
    size_t size() const override { return _currentIndex<_data.size()? _currentIndex: _data.size(); }
    QRectF boundingRect() const override { return d_boundingRect; }
    void setPointsCount( int count );
    const int getCurrentPos() const{ return _data.size()!=0 ? _currentIndex%_data.size() : _currentIndex; }

public:
    void appendValue(double value);
    void clear();
    void clear(double left);

private:
    void updateBoundingRect(double value);

private:
    int _currentIndex{0};
    std::vector<QPointF> _data;
};

#endif //CURVE_DATA_H
