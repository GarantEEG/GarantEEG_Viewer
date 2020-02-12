#include "chart.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <QJsonArray>

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

QFont Chart::axisFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    return font;
}

QFont Chart::titleFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    return font;
}

QwtText Chart::toQwtText(QString const &text, QFont const &font)
{
    QwtText res{text};
    res.setFont(font);
    return res;
}

Chart::Chart(QWidget *parent)
    : QwtPlot{parent}
{
    plotLayout()->setAlignCanvasToScales(true);

    enableAxis(QwtPlot::xBottom);
    enableAxis(QwtPlot::yLeft);

    setAxisAutoScale(QwtPlot::yLeft);

    setAxisTitle(QwtPlot::xBottom, toQwtText(tr("time, sec")));

    _grid.setMajorPen(::gridPen());
    _grid.setMinorPen(::gridPen());
    _grid.attach(this);

    setPalette(Qt::white);

    auto canvas = static_cast<QwtPlotCanvas *>(this->canvas());
    canvas->setPalette(Qt::white);
    canvas->setBorderRadius(10.0);

    insertLegend(&_legend, QwtPlot::BottomLegend);
}

void Chart::appendCurve(QString const &key, QString const &title, QColor const &color)
{
    auto curve = std::make_unique<Curve>();
    curve->setPen(QColor{color}, 2.0);
    curve->setTitle(toQwtText(title));
    curve->attach(this);
    _curves.emplace(key, std::move(curve));
}

void Chart::appendPoints(QString const &key, QJsonArray const &x, QJsonArray const &y)
{
    if (x.empty())
        return;

    auto it = _curves.find(key);
    if (it == _curves.end())
        return;

    if (it->second->isGoingToLeft(x.first().toDouble()))
        it->second->clear();

    for (int i = 0; i < x.size(); ++i)
        it->second->appendPoint(x[i].toDouble() / 1000.0, y[i].toDouble());

    fit();
    replot();
}

void Chart::appendValues(QString const &key, double inc, const QList<double> &values)
{
    auto it = _curves.find(key);
    if (it == _curves.end())
        return;

    for (int i = 0; i < values.size(); ++i)
        it->second->appendValue(inc, values[i]);

    fit();
    replot();
}

void Chart::setMaxSeconds(double seconds)
{
    Q_ASSERT(seconds > 0.0);
    _curves.clear();
    _maxSeconds = seconds;
    setAxisScale(xBottom, 0.0, _maxSeconds);
}

void Chart::fit()
{
    if (_curves.empty())
        return;

    auto it = _curves.cbegin();

    double min = it->second->left();
    double max = it->second->right();

    while (++it != _curves.cend())
    {
        if (it->second->left() < min)
            min = it->second->left();

        if (it->second->right() > max)
            max = it->second->right();
    }

    min = std::floor(max / _maxSeconds) * _maxSeconds;
    max = min + _maxSeconds;

    if (max - min <= _maxSeconds)
        for (auto &curve : _curves)
            curve.second->clear(min);

    setAxisScale(xBottom, min, max);
}
