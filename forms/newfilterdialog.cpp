/**
@file newfilterdialog.cpp

@brief Реализация класса окна добавления нового фильтра

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "forms/newfilterdialog.h"
#include "ui_newfilterdialog.h"
#include <QMessageBox>
#include "common.h"
#include "managers/configmanager.h"
//----------------------------------------------------------------------------------
NewFilterDialog::NewFilterDialog(GarantEEG::IGarantEEG *eeg, QWidget *parent)
: QDialog(parent), ui(new Ui::NewFilterDialog), m_Eeg(eeg)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->cb_Type->setCurrentIndex(0);
	ui->sb_Order->setValue(2);
	ui->sb_RangeMin->setValue(1);
	ui->sb_RangeMax->setValue(45);
}
//----------------------------------------------------------------------------------
NewFilterDialog::~NewFilterDialog()
{
    delete ui;
}
//----------------------------------------------------------------------------------
void NewFilterDialog::on_pb_OK_clicked()
{
    if (ui->sb_RangeMin->value() >= ui->sb_RangeMax->value())
    {
		QMessageBox::critical(this, tr("Invalid value"), tr("The minimum value cannot be greater than the maximum!"));
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
			emit AddFilter(ui->cb_Type->currentText(), type, ui->sb_Order->value(), ui->sb_RangeMin->value(), ui->sb_RangeMax->value());
        }
        else
        {
			QMessageBox::critical(this, tr("Create filter error"), tr("An error occurred while creating the filter!"));
            return;
        }
    }

    hide();
}
//----------------------------------------------------------------------------------
void NewFilterDialog::on_pb_Cancel_clicked()
{
    hide();
}
//----------------------------------------------------------------------------------
