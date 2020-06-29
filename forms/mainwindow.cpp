
#include <QMessageBox>
#include <QJsonArray>
#include <QDebug>

#include "forms/mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/settingsform.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<GarantEEG::GARANT_EEG_DATA>("GarantEEG::GARANT_EEG_DATA");

    connect(this, &MainWindow::UpdateEegData, this, &MainWindow::OnUpdateEegData);

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

	ui->qwt_Chart->setMaxSeconds(m_DisplaySeconds, 500);
	ui->qwt_Chart->appendCurve("EEG1", "Po7", Qt::red);
	ui->qwt_Chart->appendCurve("EEG2", "O1", Qt::black);
	ui->qwt_Chart->appendCurve("EEG3", "Oz", Qt::darkGray);
	ui->qwt_Chart->appendCurve("EEG4", "P3", Qt::green);
	ui->qwt_Chart->appendCurve("EEG5", "Pz", Qt::blue);
	ui->qwt_Chart->appendCurve("EEG6", "P4", Qt::magenta);
	ui->qwt_Chart->appendCurve("EEG7", "O2", Qt::yellow);
	ui->qwt_Chart->appendCurve("EEG8", "Po8", Qt::darkYellow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	if (m_ImpedanceForm != nullptr)
	{
		disconnect(this, &MainWindow::UpdateEegData, m_ImpedanceForm, &ImpedanceForm::OnUpdateEegData);

		delete m_ImpedanceForm;
		m_ImpedanceForm = nullptr;
	}

	QApplication::closeAllWindows();
	e->accept();
}

void MainWindow::on_pb_Start_clicked()
{
     if (m_Eeg == nullptr)
         return;

     if (m_Eeg->Start(true, 500, qPrintable(ui->le_IP->text()), ui->sb_Port->value()))
     {
         ui->le_IP->setEnabled(false);
         ui->sb_Port->setEnabled(false);

         ui->pb_Start->setEnabled(false);
         ui->pb_Stop->setEnabled(true);

         ui->pb_PauseStream->setEnabled(true);
         ui->pb_ResumeStream->setEnabled(false);

         ui->pb_RecordStart->setEnabled(true);
         ui->pb_RecordStop->setEnabled(false);

         ui->pb_RecordPause->setEnabled(false);
         ui->pb_RecordResume->setEnabled(false);

		 ui->pb_CheckImpedance->setEnabled(true);
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

    ui->pb_PauseStream->setEnabled(false);
    ui->pb_ResumeStream->setEnabled(false);

    ui->pb_RecordStart->setEnabled(false);
    ui->pb_RecordStop->setEnabled(false);

    ui->pb_RecordPause->setEnabled(false);
    ui->pb_RecordResume->setEnabled(false);

	ui->pb_CheckImpedance->setEnabled(false);

	if (m_ImpedanceForm != nullptr && m_ImpedanceForm->isVisible())
		m_ImpedanceForm->hide();
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

void MainWindow::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
    if (m_Eeg == nullptr || !m_Eeg->IsStarted())
        return;

    //192.168.127.125
    if (eegData.DataRecordsCount > 0)
    {
        double rate = 0.0005;// (double)m_Eeg->GetRate() / 1000.0;
		//qDebug() << "m_Eeg->GetRate()" << m_Eeg->GetRate() << ((double)m_Eeg->GetRate() / 1000.0);
        double timeStep = 1000.0 / (double)m_Eeg->GetRate();

        for (int i = 0; i < 8; i++)
        {
			std::vector<double> x;
			std::vector<double> y;
            //QList<double> dataList;

            for (int j = 0; j < eegData.DataRecordsCount; j++)
            {
                //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4.0) * 1.0);
                //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4) * 0.001);
                double value = eegData.RawChannelsData[j].Value[i];

				x.push_back(eegData.Time + (j * timeStep));
				y.push_back(value);
                //dataList << value;
            }

            ui->qwt_Chart->appendPoints(QString("EEG%1").arg(i + 1), x, y);

            //ui->qwt_Chart->appendValues(QString("EEG%1").arg(i + 1), rate, dataList);
        }

        ui->qwt_Chart->update();
    }
}

void MainWindow::on_pb_Settings_clicked()
{
	SettingsForm(m_Eeg, ui->qwt_Chart, this).exec();
}

void MainWindow::on_pb_CheckImpedance_clicked()
{
	if (m_ImpedanceForm == nullptr)
	{
		m_ImpedanceForm = new ImpedanceForm();
		connect(this, &MainWindow::UpdateEegData, m_ImpedanceForm, &ImpedanceForm::OnUpdateEegData);
	}

	if (!m_ImpedanceForm->isVisible())
		m_ImpedanceForm->resetValues();

	GarantUtility::BringWidgetToTop(m_ImpedanceForm);
}
