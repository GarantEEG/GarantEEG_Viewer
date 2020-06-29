#ifndef NEWFILTERDIALOG_H
#define NEWFILTERDIALOG_H

#include <QDialog>

#include <include/GarantEEG_API_CPP.h>

namespace Ui
{
    class NewFilterDialog;
}

class NewFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewFilterDialog(QWidget *parent = nullptr);
    ~NewFilterDialog();

    static NewFilterDialog *Instance();

    void Initialize();

    void InitializeAndShow(GarantEEG::IGarantEEG *eeg, class FiltersDialog *dialog);

    void SetEeg(GarantEEG::IGarantEEG *eeg);

private slots:
    void on_pb_OK_clicked();

    void on_pb_Cancel_clicked();

private:
    Ui::NewFilterDialog *ui;

    GarantEEG::IGarantEEG *m_Eeg = nullptr;

    class FiltersDialog *m_Dialog = nullptr;
};

#endif // NEWFILTERDIALOG_H
