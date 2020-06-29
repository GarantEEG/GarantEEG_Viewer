#include "forms/filtersdialog.h"
#include "ui_filtersdialog.h"
#include "forms/newfilterdialog.h"
#include "common.h"

FiltersDialog::FiltersDialog(QWidget *parent)
: QDialog(parent), ui(new Ui::FiltersDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QSettings settings("Neurotrend", "GarantEegStreamer");

	ui->cb_UseFilters->setChecked(GarantUtility::GetSettingInt(settings, "UseFilters", 1) != 0);
	int filtersCount = GarantUtility::GetSettingInt(settings, "FiltersCount", 1);

    for (int i = 0; i < filtersCount; i++)
    {
        OnAddedFilter(settings.value(QString("Filter%1_Type").arg(i), "Butterworth").toString(),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_TypeId").arg(i), 1),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_Order").arg(i), 2),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_RangeMin").arg(i), 1),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_RangeMax").arg(i), 45));
    }
}

FiltersDialog::~FiltersDialog()
{
    delete ui;
}

void FiltersDialog::SaveSettings()
{
    QSettings settings("Neurotrend", "GarantEegStreamer");

    settings.setValue("FiltersCount", ui->cb_UseFilters->isChecked() ? 1 : 0);

    int count = ui->lw_Filters->count();

    settings.setValue("FiltersCount", count);

    for (int i = 0; i < count; i++)
    {
        QListWidgetItem *item = ui->lw_Filters->item(i);

        if (item != nullptr)
        {
            settings.setValue(QString("Filter%1_Type").arg(i), item->data(Qt::UserRole + FVI_TYPE));
            settings.setValue(QString("Filter%1_TypeId").arg(i), item->data(Qt::UserRole + FVI_TYPE_ID));
            settings.setValue(QString("Filter%1_Order").arg(i), item->data(Qt::UserRole + FVI_ORDER));
            settings.setValue(QString("Filter%1_RangeMin").arg(i), item->data(Qt::UserRole + FVI_RANGE_MIN));
            settings.setValue(QString("Filter%1_RangeMax").arg(i), item->data(Qt::UserRole + FVI_RANGE_MAX));
        }
    }
}

FiltersDialog *FiltersDialog::Instance()
{
    static FiltersDialog *form = new FiltersDialog();
    return form;
}

bool FiltersDialog::GetUseFilters()
{
    return ui->cb_UseFilters->isChecked();
}

void FiltersDialog::UpdateEegFilters()
{
    if (m_Eeg != nullptr)
    {
        m_Eeg->RemoveAllFilters();

        int count = ui->lw_Filters->count();

        for (int i = 0; i < count; i++)
        {
            QListWidgetItem *item = ui->lw_Filters->item(i);

            if (item != nullptr)
            {
auto filter = m_Eeg->AddFilter(item->data(Qt::UserRole + FVI_TYPE_ID).toInt(), item->data(Qt::UserRole + FVI_ORDER).toInt());

if (filter != nullptr)
    m_Eeg->SetupFilter(filter, m_Eeg->GetRate(), item->data(Qt::UserRole + FVI_RANGE_MIN).toInt(), item->data(Qt::UserRole + FVI_RANGE_MAX).toInt());
            }
        }
    }
}

void FiltersDialog::SetEeg(GarantEEG::IGarantEEG *eeg)
{
    m_Eeg = eeg;
}

void FiltersDialog::OnAddedFilter(const QString &type, int typeId, int order, int rangeMin, int rangeMax)
{
    QListWidgetItem *item = new QListWidgetItem(QString("%1, order: %2, %3-%4 Hz").arg(type).arg(order).arg(rangeMin).arg(rangeMax));

    item->setData(Qt::UserRole + FVI_TYPE, type);
    item->setData(Qt::UserRole + FVI_TYPE_ID, typeId);
    item->setData(Qt::UserRole + FVI_ORDER, order);
    item->setData(Qt::UserRole + FVI_RANGE_MIN, rangeMin);
    item->setData(Qt::UserRole + FVI_RANGE_MAX, rangeMax);

    ui->lw_Filters->addItem(item);
}

void FiltersDialog::on_pb_Add_clicked()
{
    NewFilterDialog::Instance()->InitializeAndShow(m_Eeg, this);
}

void FiltersDialog::on_pb_RemoveSelected_clicked()
{
    int index = ui->lw_Filters->currentRow();

    if (m_Eeg != nullptr && index != -1)
    {
        auto item = ui->lw_Filters->takeItem(index);

        if (item != nullptr)
            delete item;

        if (index < m_Eeg->GetFiltersCount())
        {
            auto filters = m_Eeg->GetFilters();

            if (filters != nullptr)
                m_Eeg->RemoveFilter(filters[index]);
        }
    }
}

void FiltersDialog::on_pb_RemoveAll_clicked()
{
    ui->lw_Filters->clear();

    if (m_Eeg != nullptr)
        m_Eeg->RemoveAllFilters();
}
