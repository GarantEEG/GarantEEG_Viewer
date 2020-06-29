#include "forms/newfilterdialog.h"
#include "ui_newfilterdialog.h"
#include <QMessageBox>
#include "common.h"
#include "forms/filtersdialog.h"

NewFilterDialog::NewFilterDialog(QWidget *parent)
: QDialog(parent), ui(new Ui::NewFilterDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Initialize();
}

NewFilterDialog::~NewFilterDialog()
{
    delete ui;
}

NewFilterDialog *NewFilterDialog::Instance()
{
    static NewFilterDialog *form = new NewFilterDialog();
    return form;
}

void NewFilterDialog::Initialize()
{
    ui->cb_Type->setCurrentIndex(0);
    ui->sb_Order->setValue(2);
    ui->sb_RangeMin->setValue(1);
    ui->sb_RangeMax->setValue(45);
}

void NewFilterDialog::InitializeAndShow(GarantEEG::IGarantEEG *eeg, FiltersDialog *dialog)
{
    Initialize();
    m_Eeg = eeg;
    m_Dialog = dialog;
	GarantUtility::BringWidgetToTop(this);
}

void NewFilterDialog::SetEeg(GarantEEG::IGarantEEG *eeg)
{
    m_Eeg = eeg;
}

void NewFilterDialog::on_pb_OK_clicked()
{
    if (ui->sb_RangeMin->value() >= ui->sb_RangeMax->value())
    {
        QMessageBox::critical(this, "Invalid value", "The minimum value cannot be greater than the maximum!");
        return;
    }

    if (m_Eeg != nullptr)
    {
        GarantEEG::GARANT_EEG_FILTER_TYPE type = GarantEEG::FT_UNKNOWN;

        if (ui->cb_Type->currentIndex() == 0)
            type = GarantEEG::FT_BUTTERWORTH;

        auto filter = m_Eeg->AddFilter(type, ui->sb_Order->value());

        if (filter != nullptr)
        {
            m_Eeg->SetupFilter(filter, m_Eeg->GetRate(), ui->sb_RangeMin->value(), ui->sb_RangeMax->value());

            if (m_Dialog != nullptr)
                m_Dialog->OnAddedFilter(ui->cb_Type->currentText(), type, ui->sb_Order->value(), ui->sb_RangeMin->value(), ui->sb_RangeMax->value());
        }
        else
        {
            QMessageBox::critical(this, "Create filter error", "An error occurred while creating the filter!");
            return;
        }
    }

    hide();
}

void NewFilterDialog::on_pb_Cancel_clicked()
{
    hide();
}
