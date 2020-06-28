#ifndef CHART_H
#define CHART_H

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_text.h>
#include <memory>
#include <unordered_map>
#include "curve.h"
#include <QUuid>

class QStringHash
{
public:
    std::size_t operator()(QString const &var) const
    {
        return std::hash<std::string>{}(var.toStdString());
    }
};

class QUuidHash
{
public:
    std::size_t operator()(QUuid const &var) const
    {
        return QStringHash{}(var.toString());
    }
};

class Chart : public QwtPlot
{
    Q_OBJECT

public:
    static QFont axisFont();
    static QFont titleFont();
    static QwtText toQwtText(QString const &text, QFont const &font = axisFont());

public:
    explicit Chart(QWidget *parent = nullptr);

public:
    void appendCurve(QString const &key, QString const &title, QColor const &color);
	void setCurveColor(const QString &title, const QColor &color);
    void appendPoints(QString const &key, QJsonArray const &x, QJsonArray const &y);
    void appendValues(QString const &key, double inc, const QList<double> &values);
    void setMaxSeconds(double seconds);

	const std::unordered_map<QString, std::unique_ptr<Curve>, QStringHash> &curves() const { return _curves; }

protected:
    QSize minimumSizeHint() const override { return {200, 200}; }

private:
    void fit();

private:
    double _maxSeconds{0.0};
    QwtPlotGrid _grid;
    QwtLegend _legend;
    std::unordered_map<QString, std::unique_ptr<Curve>, QStringHash> _curves;
};

#endif // CHART_H
