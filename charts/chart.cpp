/**
@file chart.cpp

@brief Реализация класса для графика

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "chart.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMenu>
#include <QThread>
//----------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------
QFont Chart::axisFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    return font;
}
//----------------------------------------------------------------------------------
QFont Chart::titleFont()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    return font;
}
//----------------------------------------------------------------------------------
QwtText Chart::toQwtText(QString const &text, QFont const &font)
{
    QwtText res{text};
    res.setFont(font);
    return res;
}
//----------------------------------------------------------------------------------
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

    _mark.setValue(0.0, 0.0);
    _mark.setLineStyle(QwtPlotMarker::VLine);
    _mark.setLabelAlignment(Qt::AlignRight | Qt::AlignBottom);
    _mark.setLinePen(QPen(Qt::green, 4, Qt::SolidLine));
    _mark.attach(this);

    insertLegend(&_legend, QwtPlot::BottomLegend);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect( this, &Chart::customContextMenuRequested, this, &Chart::customMenuRequested );
    connect( &m_myContext, &CSimpleContext::onNewDataSet, this, &Chart::setFixedBorder );

    //connect( &m_myContext, &CSimpleContext::rejected, this, [this]{dialogRelease = true; qDebug()<<"1"; } );
    //connect( &m_myContext, &CSimpleContext::finished, this, [this]{dialogRelease = true; qDebug()<<"2"; }  );
    //connect( &m_myContext, &CSimpleContext::accepted, this, [this]{dialogRelease = true; qDebug()<<"3"; } );
}
//----------------------------------------------------------------------------------
void Chart::customMenuRequested()
{
    QMenu *menu = new QMenu(this);

    QAction *pCheckAct = menu->addAction("Autoscale",this,[this]{ m_autoscale = !m_autoscale;
                                                                if (!m_autoscale){m_myContext.onOffAutoScale();} else{ setAxisAutoScale(QwtPlot::yLeft, true); } });
    pCheckAct->setCheckable(true);
    pCheckAct->setChecked(m_autoscale);

    //menu->addAction("Set border", this, [this]{m_myContext.move(QCursor::pos()); execDialog = m_myContext.open(); qDebug()<<"ex diag"<<execDialog; });
    //menu->popup(QCursor::pos ());
}
//----------------------------------------------------------------------------------
void Chart::appendCurve(QString const &key, QString const &title, QColor const &color)
{
    auto curve = std::make_unique<Curve>();
    curve->setPen(QColor{color}, 2.0);
    curve->setTitle(toQwtText(title));
    curve->attach(this);
    curve->setMaxPoints(floor(_maxSeconds*_frameRate));
    _curves.emplace(key, std::move(curve));

    _mark.setVisible(_curves.size()==1);
}
//----------------------------------------------------------------------------------
void Chart::setCurveColor(const QString &title, const QColor &color)
{
	for (auto it = _curves.begin(); it != _curves.end(); ++it)
	{
		if (it->second->title().text() == title)
		{
			it->second->setPen(color, 2.0);
			break;
		}
	}
}
//----------------------------------------------------------------------------------
void Chart::appendPoints(QString const &key, std::vector<double> const &x, std::vector<double> const &y)
{
    if (x.empty())
        return;

    auto it = _curves.find(key);
    if (it == _curves.end())
        return;

//    if (it->second->isGoingToLeft(x[0]))
//        it->second->clear();

    for (int i = 0; i < x.size(); ++i)
        it->second->appendPoint(x[i]/ 1000.0, y[i]);

    if( _curves.size()==1 )
    {
        _mark.setValue(it->second->getCurrentPos(), 0.0);
    }

    fit();
    replot();
}
//----------------------------------------------------------------------------------
void Chart::appendValues(QString const &key, double inc, std::vector<double> const &values)
{
    auto it = _curves.find(key);
    if (it == _curves.end())
        return;

    for (int i = 0; i < values.size(); ++i)
        it->second->appendValue(inc, values[i]);

    fit();
    replot();
}
//----------------------------------------------------------------------------------
void Chart::setMaxSeconds(double seconds, double frameRate)
{
    Q_ASSERT(seconds > 0.0);
    Q_ASSERT(frameRate > 0.0);

    _maxSeconds = seconds;
    _frameRate = frameRate;
    setAxisScale(xBottom, 0.0, _maxSeconds*_frameRate);

    if (execDialog){
        dialogRelease = false;
        m_myContext.done(0);

        while( !dialogRelease ){
            QThread::msleep(1);
        }
    }
}
//----------------------------------------------------------------------------------
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

    setAxisScale(xBottom, min, max);
}
//----------------------------------------------------------------------------------
void Chart::setFixedBorder(double min, double max)
{
    Q_ASSERT(min<max);
    m_autoscale = false;
    setAxisScale(yLeft, min, max);
}
//----------------------------------------------------------------------------------
Chart::~Chart()
{
    m_myContext.clearFocus();
    m_myContext.done(0);
    m_myContext.accept();
    m_myContext.close();
}
//----------------------------------------------------------------------------------
void Chart::setOffDialog()
{
    qDebug()<<"exec dial value"<<execDialog;
    //dialogRelease = false;
    m_myContext.done(0);

    /*while( !dialogRelease ){
        QThread::msleep(1);
    }*/
}
//----------------------------------------------------------------------------------
CSimpleContext::CSimpleContext():QDialog{}
{
    auto mainLayout = new QGridLayout{this};

    mainLayout->addWidget(new QLabel("minBord"), 0,1,1,1);
    mainLayout->addWidget(new QLabel("maxBord"), 0,2,1,1);
    mainLayout->addWidget(&m_minBord, 1,1,1,1);
    mainLayout->addWidget(&m_maxBord, 1,2,1,1);
    mainLayout->addWidget(&m_setButton, 2,1,1,2);

    m_minBord.setMinimum(-1e9);
    m_minBord.setMaximum(1e9);

    m_setButton.setText("set bord");

    setVisible(false);
    connect( &m_setButton, &QPushButton::clicked, this, &CSimpleContext::onSetButtonClick );

    setWindowFlags(Qt ::WindowCloseButtonHint);
}
//----------------------------------------------------------------------------------
void CSimpleContext::onSetButtonClick()
{
    if (m_minBord.value()>m_maxBord.value())
    {
		QMessageBox::warning(this, "Warning!", "min border>max border");
        return;
    }
    setVisible(false);
    emit onNewDataSet(m_minBord.value(), m_maxBord.value());
}
//----------------------------------------------------------------------------------
void CSimpleContext::onOffAutoScale()
{
    emit onNewDataSet(m_minBord.value(), m_maxBord.value());
}
//----------------------------------------------------------------------------------
