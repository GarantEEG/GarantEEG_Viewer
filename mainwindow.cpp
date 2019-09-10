#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include <include/../src/Filtering/ButterworthFilter.hpp>


void ParseEegFile()
{
    int cl[8] = {1,2,3,4,5,6,7,8};
    GarantEEG::CBaseFilter *filter = GarantEEG::CButterworthFilter<1, 8>::Create(4, &cl[0]);

    if (filter == nullptr)
        return;

    filter->Setup(500, 1, 45);

    QFile f("D:/EEG8_Viewer/Cheng_Yong_eeg_0.bdf.csv");
    QFile f2("D:/EEG8_Viewer/Cheng_Yong_eeg_0_50hz.bdf.csv");

    if (!f2.open(QIODevice::WriteOnly))
        return;

    QVector<float> channels[8];

    Dsp::SimpleFilter<Dsp::Butterworth::BandPass<4>, 8> btwFilter;

    double centerFrequency = ((1 + (45 - 1)) / 2.0);
    double widthFrequency = ((45 - 1) / 2.0);

    btwFilter.setup(4, 500, centerFrequency, widthFrequency);

    if (f.open(QIODevice::ReadOnly))
    {
        //Header
        f2.write(f.readLine());

        for (int i = 0; i < 8; i++)
            channels[i].reserve(500);

        while (!f.atEnd())
        {
            QStringList list = QString(f.readLine()).split(";", QString::SkipEmptyParts);

            if (list.size() < 8)
                continue;

            for (int i = 0; i < 8; i++)
                channels[i].push_back(list[i].toFloat() * 1000000.0);

            if (channels[0].size() >= 500)
            {
                float *tablePtr[8] =
                {
                    &channels[0][0],
                    &channels[1][0],
                    &channels[2][0],
                    &channels[3][0],
                    &channels[4][0],
                    &channels[5][0],
                    &channels[6][0],
                    &channels[7][0]
                };

                btwFilter.process(500, &tablePtr[0]);
                //filter->Process(500, &tablePtr[0]);

                for (int i = 0; i < 500; i++)
                {
                    QByteArray arr;
                    for (int j = 0; j < 8; j++)
                    {
                        arr.push_back(QByteArray::number(channels[j][i], 'g', 10).replace('.', ','));
                        if (j < 7)
                            arr.push_back(';');
                    }
                    arr.push_back("\r\n");
                    f2.write(arr);
                }
                f2.flush();

                for (int i = 0; i < 8; i++)
                {
                    channels[i].clear();
                    channels[i].reserve(500);
                }
            }
        }

        f.close();
    }

    qDebug() << "channels[0].size()" << channels[0].size();

    /*float *tablePtr[8] =
    {
        &channels[0][0],
        &channels[1][0],
        &channels[2][0],
        &channels[3][0],
        &channels[4][0],
        &channels[5][0],
        &channels[6][0],
        &channels[7][0]
    };

    filter->Process(channels[0].size(), &tablePtr[0]);

    for (int i = 0; i < channels[0].size(); i++)
    {
        QByteArray arr;
        for (int j = 0; j < 8; j++)
        {
            arr.push_back(QByteArray::number(channels[j][i], 'g', 10).replace('.', ','));
            if (j < 7)
                arr.push_back(';');
        }
        arr.push_back("\r\n");
        f2.write(arr);
    }*/

    f2.close();
}

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ParseEegFile();

    qRegisterMetaType<GarantEEG::GARANT_EEG_DATA>("GarantEEG::GARANT_EEG_DATA");

    connect(this, &MainWindow::UpdateEegData, this, &MainWindow::OnUpdateEegData);

    ui->gv_Graphics->setChart(new QChart());
    ui->gv_Graphics->setRubberBand(QChartView::VerticalRubberBand);

    QChart *chart = (QChart*)ui->gv_Graphics->chart();
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->setTitle("EEG");

    m_AxisX = new QValueAxis();
    m_AxisX->setLabelFormat("%.01f");
    m_AxisX->setTitleText("Time, sec");
    //chart->addAxis(m_AxisX, Qt::AlignBottom);
    m_AxisX->setRange(0, m_DisplaySeconds * 500);

    m_AxisY = new QValueAxis();
    m_AxisY->setLabelFormat("%.03f");
    m_AxisY->setTitleText("Value, uV");
    //chart->addAxis(m_AxisY, Qt::AlignLeft);
    //m_AxisY->setRange(-4.5, 4.0);
    m_AxisY->setRange(-0.05, 0.05);

    for (int i = 0; i < 8; i++)
    {
        m_LineSeries[i] = new QLineSeries();
        m_LineSeries[i]->setName("C" + QString::number(i));
        m_LineSeries[i]->setUseOpenGL();

        chart->addSeries(m_LineSeries[i]);

        //m_LineSeries[i]->attachAxis(m_AxisX);
        //m_LineSeries[i]->attachAxis(m_AxisY);

        chart->setAxisX(m_AxisX, m_LineSeries[i]);
        chart->setAxisY(m_AxisY, m_LineSeries[i]);
    }

    m_Eeg = GarantEEG::CreateDevice(GarantEEG::DT_GARANT);

    if (m_Eeg != nullptr)
    {
        m_Eeg->SetCallback_OnStartStateChanged(this, [](void *userData, uint state)
        {
            Q_UNUSED(userData);
            qDebug() << "StartStateChanged" << state;
        });

        m_Eeg->SetCallback_OnRecordingStateChanged(this, [](void *userData, uint state)
        {
            Q_UNUSED(userData);
            qDebug() << "RecordingStateChanged" << state;
        });

        m_Eeg->SetCallback_ReceivedData(this, [](void *userData, const GarantEEG::GARANT_EEG_DATA *eegData)
        {
            //qDebug() << "ReceivedData";

            if (userData != nullptr)
                emit ((MainWindow*)userData)->UpdateEegData(*eegData);
        });
    }

    /*QFile bf("tmp.bat");

    if (bf.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream(&bf) << "chcp 1251 >nul\nnetsh wlan show int > temp_wlan_info.txt";
        bf.close();
    }

    system("tmp.bat");
    QFile f("temp_wlan_info.txt");

    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString::fromLocal8Bit(f.readAll());
        f.close();
    }

    QFile::remove("tmp.bat");
    QFile::remove("temp_wlan_info.txt");*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Start_clicked()
{
     if (m_Eeg == nullptr)
         return;

     if (m_Eeg->Start(true, 500, ui->cb_ProtectedMode->isChecked(), qPrintable(ui->le_IP->text()), ui->sb_Port->value()))
     {
         ui->le_IP->setEnabled(false);
         ui->sb_Port->setEnabled(false);

         ui->pb_Start->setEnabled(false);
         ui->pb_Stop->setEnabled(true);

         ui->cb_ProtectedMode->setEnabled(false);

         ui->pb_PauseStream->setEnabled(true);
         ui->pb_ResumeStream->setEnabled(false);

         ui->pb_RecordStart->setEnabled(true);
         ui->pb_RecordStop->setEnabled(false);

         ui->pb_RecordPause->setEnabled(false);
         ui->pb_RecordResume->setEnabled(false);

         ui->sb_IndicationValue->setEnabled(true);
         ui->pb_IndicationStart->setEnabled(true);
         ui->pb_IndicationStop->setEnabled(false);
         ui->pb_PowerOff->setEnabled(true);
     }
}

void MainWindow::on_pb_Stop_clicked()
{
    if (m_Eeg == nullptr)
        return;

    m_Eeg->Stop();

    ui->le_IP->setEnabled(true);
    ui->sb_Port->setEnabled(true);

    ui->pb_Start->setEnabled(true);
    ui->pb_Stop->setEnabled(false);

    ui->cb_ProtectedMode->setEnabled(true);

    ui->pb_PauseStream->setEnabled(false);
    ui->pb_ResumeStream->setEnabled(false);

    ui->pb_RecordStart->setEnabled(false);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);

    ui->sb_IndicationValue->setEnabled(false);
    ui->pb_IndicationStart->setEnabled(false);
    ui->pb_IndicationStop->setEnabled(false);
    ui->pb_PowerOff->setEnabled(false);
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

void MainWindow::on_cb_AutoReconnection_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    if (m_Eeg != nullptr)
        m_Eeg->SetAutoReconnection(ui->cb_AutoReconnection->isChecked());
}

void MainWindow::on_pb_PowerOff_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted())
        return;

    if (m_Eeg->IsRecording())
    {
        if (QMessageBox::question(this, "Record is started",  "Record is started on device.\nTorn off device anyway?") != QMessageBox::Yes)
            return;
    }

    m_Eeg->PowerOff();
}

void MainWindow::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
    QChart *chart = (QChart*)ui->gv_Graphics->chart();

    if (chart == nullptr)
        return;

    double minValue = 999.0;
    double maxValue = -999.0;
    static int positions[8] = { 0 };

    for (int i = 0; i < 8; i++)
    {
        QVector<QPointF> points = m_LineSeries[i]->pointsVector();

        int maxSize = m_DisplaySeconds * 500;
        int size = points.size();

        if (size < maxSize)
        {
            points.resize(maxSize);

            for (int j = size; j < maxSize; j++)
                points[j] = QPointF(j, 0.0);
        }

        int &position = positions[i];

        for (int j = 0; j < eegData.DataRecordsCount; j++)
        {
            //double value = eegData.ChannelsData[j].Value[i] + ((i - 4.0) * 1.0);
            //double value = eegData.ChannelsData[j].Value[i] + ((i - 4) * 0.001);
            double value = eegData.ChannelsData[j].Value[i];

            points[position] = QPointF(position, value);
            position++;

            if (position >= points.size())
                position = 0;
        }

        for (const QPointF &point : points)
        {
            minValue = std::min(minValue, point.y());
            maxValue = std::max(maxValue, point.y());
        }

        m_LineSeries[i]->replace(points);
    }

    m_AxisY->setRange(minValue, maxValue);
}

void MainWindow::on_pb_IndicationStart_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted())
        return;

    ui->sb_IndicationValue->setEnabled(false);
    ui->pb_IndicationStart->setEnabled(false);
    ui->pb_IndicationStop->setEnabled(true);
}

void MainWindow::on_pb_IndicationStop_clicked()
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted())
        return;

    ui->sb_IndicationValue->setEnabled(true);
    ui->pb_IndicationStart->setEnabled(true);
    ui->pb_IndicationStop->setEnabled(false);
}
