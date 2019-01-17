#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Eeg = GarantEEG::CreateDevice(GarantEEG::DT_GARANT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Start_clicked()
{
     if (m_Eeg == nullptr)
         return;

     if (m_Eeg->Start())
     {
         ui->pb_Start->setEnabled(false);
         ui->pb_Stop->setEnabled(true);
     }
}

void MainWindow::on_pb_Stop_clicked()
{
    if (m_Eeg == nullptr)
        return;

    m_Eeg->Stop();

    ui->pb_Start->setEnabled(true);
    ui->pb_Stop->setEnabled(false);
}
