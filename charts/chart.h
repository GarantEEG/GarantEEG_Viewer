#ifndef CHART_H
#define CHART_H

//#include <hash_functions.h>
#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>
#include <memory>
#include <unordered_map>
#include "curve.h"
#include <QUuid>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDialog>

// вместо #include <hash_functions.h>
class  QStringHash
{
public:
    std::size_t operator()(QString const &var) const
    {
        return std::hash<std::string>{}(var.toStdString());
    }
};

class  QUuidHash
{
public:
    std::size_t operator()(QUuid const &var) const
    {
        return QStringHash{}(var.toString());
    }
};

class CSimpleContext:public QDialog{
    Q_OBJECT
public:
    CSimpleContext();

public:
    void onSetButtonClick();
    //bool close(){ setVisible(false); }
    void onOffAutoScale();

signals:
    void onNewDataSet(double min, double max);

private:
    QPushButton m_setButton;
    QDoubleSpinBox m_minBord;
    QDoubleSpinBox m_maxBord;
};

// сам chart
class Chart : public QwtPlot
{
    Q_OBJECT
public:
    ~Chart();

    static QFont axisFont();
    static QFont titleFont();
    static QwtText toQwtText(QString const &text, QFont const &font = axisFont());

public:
    explicit Chart(QWidget *parent = nullptr);

public:
    void appendCurve(QString const &key, QString const &title, QColor const &color);
	void setCurveColor(const QString &title, const QColor &color);
    void appendPoints(QString const &key, std::vector<double> const &x, std::vector<double> const &y);
    void appendValues(QString const &key, double inc, std::vector<double> const &values);
    void setMaxSeconds(double seconds, double frameRate);
    void setOffDialog();

	const std::unordered_map<QString, std::unique_ptr<Curve>, QStringHash> &curves() const { return _curves; }

protected:
	QSize minimumSizeHint() const override { return {50, 50}; }
    void setFixedBorder(double min, double max);

private:
    void fit();
    void customMenuRequested();

private:
    bool m_autoscale{true};
    bool dialogRelease{false};
    double _maxSeconds{0.0};
    double _frameRate{0.0};
    int execDialog{0};
    QwtPlotGrid _grid;
    QwtLegend _legend;
    QwtPlotMarker _mark;
    std::unordered_map<QString, std::unique_ptr<Curve>, QStringHash> _curves;

    CSimpleContext m_myContext;
};

#endif // CHART_H
