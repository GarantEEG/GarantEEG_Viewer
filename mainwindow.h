#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <include/GarantEEG_API_CPP.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_Start_clicked();

    void on_pb_Stop_clicked();

private:
    Ui::MainWindow *ui;

    GarantEEG::IGarantEEG *m_Eeg = nullptr;
};

#endif // MAINWINDOW_H
