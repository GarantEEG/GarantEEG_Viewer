#include "curve_data.h"

CurveData::CurveData()
{
    d_boundingRect = QRectF{};
}

void CurveData::appendPoint(double x, double y)
{
    _data.emplace_back(x, y);
    updateBoundingRect(x, y);
}

void CurveData::appendValue(double inc, double value)
{
    appendPoint(d_boundingRect.right() + inc, value);
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

    double xMin = it->x();
    double xMax = it->x();
    double yMin = it->y();
    double yMax = it->y();

    while (++it != _data.cend())
    {
        if (it->x() < xMin)
            xMin = it->x();

        if (it->x() > xMax)
            xMax = it->x();

        if (it->y() < yMin)
            yMin = it->y();

        if (it->y() > yMax)
            yMax = it->y();
    }

    d_boundingRect.setRect(xMin, yMin, xMax - xMin, yMax - yMin);
}

void CurveData::updateBoundingRect(double x, double y)
{
    if (d_boundingRect.x() == 0.0 || d_boundingRect.y() == 0.0)
    {
        d_boundingRect.setRect(x, y, 0.0, 0.0);
        return;
    }

    d_boundingRect.setRight(x);

    if (y > d_boundingRect.bottom())
        d_boundingRect.setBottom(y);

    if (y < d_boundingRect.top())
        d_boundingRect.setTop(y);
}
