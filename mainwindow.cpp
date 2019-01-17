#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow *g_MainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    g_MainWindow = this;

    qRegisterMetaType<GarantEEG::GARANT_EEG_DATA>("GarantEEG::GARANT_EEG_DATA");

    connect(this, &MainWindow::UpdateEegData, this, &MainWindow::OnUpdateEegData);

    ui->gv_Graphics->setChart(new QChart());
    ui->gv_Graphics->setRubberBand(QChartView::VerticalRubberBand);

    QChart *chart = (QChart*)ui->gv_Graphics->chart();
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->setTitle("EEG");

    m_Eeg = GarantEEG::CreateDevice(GarantEEG::DT_GARANT);

    if (m_Eeg != nullptr)
    {
        m_Eeg->SetCallback_OnStartStateChanged([](uint state)
        {
            qDebug() << "StartStateChanged" << state;
        });

        m_Eeg->SetCallback_OnRecordingStateChanged([](uint state)
        {
            qDebug() << "RecordingStateChanged" << state;
        });

        m_Eeg->SetCallback_ReceivedData([](const GarantEEG::GARANT_EEG_DATA *eegData)
        {
            qDebug() << "ReceivedData";

            if (g_MainWindow != nullptr)
                emit g_MainWindow->UpdateEegData(*eegData);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Start_clicked()
{
     if (m_Eeg == nullptr)
         return;

     if (m_Eeg->Start(true, 500, true, qPrintable(ui->le_IP->text()), ui->sb_Port->value()))
     {
         ui->pb_Start->setEnabled(false);
         ui->pb_Stop->setEnabled(true);

         ui->pb_PauseStream->setEnabled(true);
         ui->pb_ResumeStream->setEnabled(false);

         ui->pb_RecordStart->setEnabled(true);
         ui->pb_RecordStop->setEnabled(false);

         ui->pb_RecordPause->setEnabled(false);
         ui->pb_RecordResume->setEnabled(false);
     }
}

void MainWindow::on_pb_Stop_clicked()
{
    if (m_Eeg == nullptr)
        return;

    m_Eeg->Stop();

    ui->pb_Start->setEnabled(true);
    ui->pb_Stop->setEnabled(false);

    ui->pb_PauseStream->setEnabled(false);
    ui->pb_ResumeStream->setEnabled(false);

    ui->pb_RecordStart->setEnabled(false);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);
}

void MainWindow::on_pb_PauseStream_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || m_Eeg->IsRecording() || m_Eeg->IsPaused())
        return;

    m_Eeg->StopDataTranslation();
    ui->pb_PauseStream->setEnabled(false);
    ui->pb_ResumeStream->setEnabled(true);

    ui->pb_RecordStart->setEnabled(false);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);
}

void MainWindow::on_pb_ResumeStream_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || m_Eeg->IsRecording() || !m_Eeg->IsPaused())
        return;

    m_Eeg->StartDataTranslation();
    ui->pb_PauseStream->setEnabled(true);
    ui->pb_ResumeStream->setEnabled(false);

    ui->pb_RecordStart->setEnabled(true);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);
}

void MainWindow::on_pb_RecordStart_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || m_Eeg->IsRecording() || m_Eeg->IsPaused())
        return;

    if (m_Eeg->StartRecord("user"))
    {
        ui->pb_RecordStart->setEnabled(false);
        ui->pb_RecordStop->setEnabled(true);

        ui->pb_RecordPause->setEnabled(true);
        ui->pb_RecordResume->setEnabled(false);
    }
}

void MainWindow::on_pb_RecordStop_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || !m_Eeg->IsRecording() || m_Eeg->IsPaused())
        return;

    m_Eeg->StopRecord();
    ui->pb_RecordStart->setEnabled(true);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);
}

void MainWindow::on_pb_RecordPause_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || !m_Eeg->IsRecording() || m_Eeg->IsRecordPaused())
        return;

    m_Eeg->PauseRecord();
    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(true);
}

void MainWindow::on_pb_RecordResume_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted() || !m_Eeg->IsRecording() || !m_Eeg->IsRecordPaused())
        return;

    m_Eeg->ResumeRecord();
    ui->pb_RecordPause->setEnabled(true);
    ui->pb_RecordResume->setEnabled(false);
}

void MainWindow::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
    QChart *chart = (QChart*)ui->gv_Graphics->chart();

    if (chart == nullptr)
        return;

    chart->removeAllSeries();

    m_AxisX = new QValueAxis();
    m_AxisX->setLabelFormat("%.01f");
    m_AxisX->setTitleText("Time, sec");
    chart->addAxis(m_AxisX, Qt::AlignBottom);

    m_AxisY = new QValueAxis();
    m_AxisY->setLabelFormat("%i");
    m_AxisY->setTitleText("Value, uV");
    chart->addAxis(m_AxisY, Qt::AlignLeft);

    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->setName("C1");

    double maxRange = 0.0;
    static double time = 0.0;

    for (int i = 0; i < eegData.DataRecordsCount; i++)
    {
        double value = eegData.ChannelsData[i].Value[0];

        maxRange = std::max(maxRange, value);
        lineSeries->append(time, value);

        time += 0.1;
    }

    chart->addSeries(lineSeries);

    lineSeries->attachAxis(m_AxisX);
    lineSeries->attachAxis(m_AxisY);

    m_AxisY->setMax(maxRange);
}
