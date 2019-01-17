#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/GarantEEG_API_CPP.h>

#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPolarChart>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

Q_SIGNALS:
    void UpdateEegData(GarantEEG::GARANT_EEG_DATA);

private slots:
    void on_pb_Start_clicked();

    void on_pb_Stop_clicked();

    void on_pb_PauseStream_clicked();

    void on_pb_ResumeStream_clicked();

    void on_pb_RecordStart_clicked();

    void on_pb_RecordStop_clicked();

    void on_pb_RecordPause_clicked();

    void on_pb_RecordResume_clicked();

    void OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

private:
    Ui::MainWindow *ui;

    GarantEEG::IGarantEEG *m_Eeg = nullptr;

    QValueAxis *m_AxisX = nullptr;
    QValueAxis *m_AxisY = nullptr;

    QLineSeries *m_LineSeries = nullptr;
};

#endif // MAINWINDOW_H
