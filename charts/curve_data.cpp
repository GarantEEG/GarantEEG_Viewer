#include "curve_data.h"

CurveData::CurveData()
{
    d_boundingRect = QRectF{};
}

void CurveData::setPointsCount( int count )
{
    _data.resize(count);
    d_boundingRect.setRight(count);
}

void CurveData::appendValue(double value)
{
    if (_data.empty())
        return;

    int potential_index = _currentIndex%_data.size();
    _data[potential_index] = QPointF((double)potential_index,value);
    updateBoundingRect(value);
    _currentIndex++;
}

void CurveData::clear()
{
    _data.clear();
    d_boundingRect.setRect(d_boundingRect.right(), 0.0, 0.0, 0.0);
}

void CurveData::clear(double left)
{
    {
        auto it = std::upper_bound(_data.begin(), _data.end(), left, [](double val, auto const &item) { return val < item.x(); });
        _data.erase(_data.begin(), it);
    }

    if (_data.empty())
    {
        d_boundingRect = {};
        return;
    }

    auto it = _data.cbegin();

    double yMin = it->y();
    double yMax = it->y();

    while (++it != _data.cend())
    {
        if (it->y() < yMin)
            yMin = it->y();

        if (it->y() > yMax)
            yMax = it->y();
    }

    d_boundingRect.setRect(0, yMin, _data.size(), yMax - yMin);
}

void CurveData::updateBoundingRect(double value)
{
    if (value > d_boundingRect.bottom())
        d_boundingRect.setBottom(value);

    if (value < d_boundingRect.top())
        d_boundingRect.setTop(value);
}
