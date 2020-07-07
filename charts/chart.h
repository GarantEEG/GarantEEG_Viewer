/**
@file chart.h

@brief Объявление класса для графика

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef CHART_H
#define CHART_H
//----------------------------------------------------------------------------------
//#include <hash_functions.h>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>
#include <memory>
#include <unordered_map>
#include "charts/curve.h"
#include "charts/custom_context.h"
#include <QUuid>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDialog>
//----------------------------------------------------------------------------------
// вместо #include <hash_functions.h>
class QStringHash
{
public:
    std::size_t operator()(QString const &var) const
    {
        return std::hash<std::string>{}(var.toStdString());
    }
};
//----------------------------------------------------------------------------------
class  QUuidHash
{
public:
    std::size_t operator()(QUuid const &var) const
    {
        return QStringHash{}(var.toString());
    }
};
//----------------------------------------------------------------------------------
struct AutoScaleParams{
	bool IsValid()const{ return MinValue<MaxValue;  }

	bool Autoscale;
	double MinValue;
	double MaxValue;
};
//----------------------------------------------------------------------------------
class Chart : public QwtPlot
{
	Q_OBJECT

public:
	~Chart() { releaseDialog(); }
	static QFont axisFont();
	static QFont titleFont();
	static QwtText toQwtText(QString const &text, QFont const &font = axisFont());

public:
	explicit Chart(QWidget *parent = nullptr);

public:
	void appendCurve(QString const &key, QString const &title, QColor const &color);
	void appendPoints(QString const &key, std::vector<float> const &points);
	void appendPoint(QString const &key, float const &value);
	void setParams(AutoScaleParams const& params );
	void releaseDialog() { _myContext.done(0); }
	void restart();
	void reCalcBoundingRect(QString const &key);
	void updateView();
	inline void clearCurves(){ _curves.clear(); }
	void setPointsCount(uint const & sec, uint const& framerate);

signals:
	void onBorderDataChanged(AutoScaleParams const &params);

protected:
	QSize minimumSizeHint() const override { return {200, 200}; }
	QSize sizeHint() const override { return {200, 200}; }

private:
	void fit();
	void customMenuRequested();
	void onAutoScale();
	void setFixedBorder(double min, double max);
	AutoScaleParams params();

private:
	bool _autoscale{true};
	uint _pointsCount{0};
	QwtPlotGrid _grid;
	QwtLegend _legend;
	QwtPlotMarker _mark;
	std::unordered_map<QString, std::unique_ptr<Curve>, QStringHash> _curves;
	CSimpleContext _myContext;
};
//----------------------------------------------------------------------------------
#endif // CHART_H
//----------------------------------------------------------------------------------
