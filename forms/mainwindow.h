#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>

#include <include/GarantEEG_API_CPP.h>

#include "forms/impedanceform.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
	virtual void closeEvent(QCloseEvent *e) override;

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

    void on_cb_AutoReconnection_stateChanged(int arg1);

	void on_pb_Settings_clicked();

	void on_pb_CheckImpedance_clicked();

private:
    Ui::MainWindow *ui;

    GarantEEG::IGarantEEG *m_Eeg = nullptr;

    int m_DisplaySeconds = 10;

	ImpedanceForm *m_ImpedanceForm = nullptr;

};

#endif // MAINWINDOW_H
