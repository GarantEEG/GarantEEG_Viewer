#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H

#include <QDialog>

#include <include/GarantEEG_API_CPP.h>

namespace Ui
{
    class FiltersDialog;
}

class FiltersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FiltersDialog(QWidget *parent = nullptr);
    ~FiltersDialog();

    void SaveSettings();

    static FiltersDialog *Instance();

    bool GetUseFilters();

    void UpdateEegFilters();

    void SetEeg(GarantEEG::IGarantEEG *eeg);

    void OnAddedFilter(const QString &type, int typeId, int order, int rangeMin, int rangeMax);

private slots:
    void on_pb_Add_clicked();

    void on_pb_RemoveSelected_clicked();

    void on_pb_RemoveAll_clicked();

private:
    Ui::FiltersDialog *ui;

    GarantEEG::IGarantEEG *m_Eeg = nullptr;

    enum FILTER_VARIABLE_INDEX
    {
        FVI_TYPE = 0,
        FVI_TYPE_ID,
        FVI_ORDER,
        FVI_RANGE_MIN,
        FVI_RANGE_MAX
    };
};

#endif // FILTERSDIALOG_H
