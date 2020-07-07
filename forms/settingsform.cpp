/**
@file settingsform.cpp

@brief Реализация класса окна настроек

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "forms/settingsform.h"
#include "ui_settingsform.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QColorDialog>
#include <QHeaderView>
#include "forms/newfilterdialog.h"
#include "common.h"
#include "managers/configmanager.h"
#include "forms/impedanceform.h"
#include <QDebug>
//----------------------------------------------------------------------------------
SettingsForm::SettingsForm(GarantEEG::IGarantEEG *eeg, QWidget *parent)
: QDialog(parent), ui(new Ui::SettingsForm), m_Eeg(eeg)
{
	ui->setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	m_loading = true;

	if (m_Eeg != nullptr && m_Eeg->IsStarted())
	{
		ui->sb_IndicationValue->setEnabled(true);
		ui->pb_IndicationStart->setEnabled(true);
		ui->pb_IndicationStop->setEnabled(false);
		ui->pb_PowerOff->setEnabled(true);
	}
	else
	{
		ui->sb_IndicationValue->setEnabled(false);
		ui->pb_IndicationStart->setEnabled(false);
		ui->pb_IndicationStop->setEnabled(false);
		ui->pb_PowerOff->setEnabled(false);
	}

	QHeaderView *headerView = ui->tw_EegChannels->horizontalHeader();

	if (headerView != nullptr)
	{
		headerView->setMinimumSectionSize(70);
		headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		headerView->setSectionResizeMode(1, QHeaderView::Stretch);
	}

	CConfigManager &config = CConfigManager::instance();
	QStringList channels = ImpedanceForm::channelNames();

	for (int i = 0; i < 8; i++)
	{
		int row = ui->tw_EegChannels->rowCount();
		ui->tw_EegChannels->setRowCount(row + 1);

		QTableWidgetItem *item = new QTableWidgetItem(channels[i]);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setCheckState(config.curveIsChecked(i) ? Qt::Checked : Qt::Unchecked);
		ui->tw_EegChannels->setItem(row, 0, item);

		item = new QTableWidgetItem();
		item->setBackgroundColor(QColor(config.curveColor(i)));
		ui->tw_EegChannels->setItem(row, 1, item);
	}

	/*QSettings settings("Neurotrend", "GarantEegStreamer");

	ui->gb_UseFilters->setChecked(GarantUtility::GetSettingInt(settings, "UseFilters", 1) != 0);
	int filtersCount = GarantUtility::GetSettingInt(settings, "FiltersCount", 1);

	for (int i = 0; i < filtersCount; i++)
	{
		OnAddFilter(settings.value(QString("Filter%1_Type").arg(i), "Butterworth").toString(),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_TypeId").arg(i), 1),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_Order").arg(i), 2),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_RangeMin").arg(i), 1),
					  GarantUtility::GetSettingInt(settings, QString("Filter%1_RangeMax").arg(i), 45));
	}*/

	m_loading = false;
}
//----------------------------------------------------------------------------------
SettingsForm::~SettingsForm()
{
	delete ui;
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_PowerOff_clicked()
{
	if (m_Eeg == nullptr || !m_Eeg->IsStarted())
		return;

	if (m_Eeg->IsRecording())
	{
		if (QMessageBox::question(this, tr("Record is started"), tr("Record is started on device.\nTurn off device anyway?")) != QMessageBox::Yes)
			return;
	}

	m_Eeg->PowerOff();
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_IndicationStart_clicked()
{
	if (m_Eeg == nullptr || !m_Eeg->IsStarted())
		return;

	ui->sb_IndicationValue->setEnabled(false);
	ui->pb_IndicationStart->setEnabled(false);
	ui->pb_IndicationStop->setEnabled(true);
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_IndicationStop_clicked()
{
	if (m_Eeg == nullptr || !m_Eeg->IsStarted())
		return;

	ui->sb_IndicationValue->setEnabled(true);
	ui->pb_IndicationStart->setEnabled(true);
	ui->pb_IndicationStop->setEnabled(false);
}
//----------------------------------------------------------------------------------
void SettingsForm::on_tw_EegChannels_cellClicked(int row, int column)
{
	if (column != 1)
		return;

	QTableWidgetItem *itemName = ui->tw_EegChannels->item(row, 0);

	if (itemName == nullptr)
		return;

	QTableWidgetItem *itemColor = ui->tw_EegChannels->item(row, 1);

	if (itemColor == nullptr)
		return;

	QColorDialog dialog(itemColor->backgroundColor(), this);

	if (dialog.exec())
	{
		QColor color = dialog.selectedColor();
		itemColor->setBackground(color);

		CConfigManager &config = CConfigManager::instance();
		config.setCurveColor(row, QString::asprintf("#%06X", color.rgb() & 0x00FFFFFF));
		emit updateEegChannelsSummary();
	}

	ui->tw_EegChannels->setCurrentCell(row, 0);
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_Close_clicked()
{
	close();
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_AddFilter_clicked()
{
	NewFilterDialog dialog(m_Eeg, this);

	connect(&dialog, &NewFilterDialog::AddFilter, this, &SettingsForm::OnAddFilter, Qt::DirectConnection);

	dialog.exec();

	disconnect(&dialog, &NewFilterDialog::AddFilter, this, &SettingsForm::OnAddFilter);
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_RemoveSelectedFilter_clicked()
{
	int index = ui->lw_Filters->currentRow();

	if (m_Eeg != nullptr && index != -1)
	{
		if (QMessageBox::question(this, tr("Remove filter?"), tr("Are you sure you want to delete the selected filter?")) != QMessageBox::Yes)
			return;

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
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_RemoveAllFilters_clicked()
{
	if (QMessageBox::question(this, tr("Remove filters?"), tr("Are you sure you want to delete the all filters?")) != QMessageBox::Yes)
		return;

	ui->lw_Filters->clear();

	if (m_Eeg != nullptr)
		m_Eeg->RemoveAllFilters();
}
//----------------------------------------------------------------------------------
void SettingsForm::OnAddFilter(QString type, int typeId, int order, int rangeMin, int rangeMax)
{
	QListWidgetItem *item = new QListWidgetItem(QString("%1, order: %2, %3-%4 Hz").arg(type).arg(order).arg(rangeMin).arg(rangeMax));

	item->setData(Qt::UserRole + FVI_TYPE, type);
	item->setData(Qt::UserRole + FVI_TYPE_ID, typeId);
	item->setData(Qt::UserRole + FVI_ORDER, order);
	item->setData(Qt::UserRole + FVI_RANGE_MIN, rangeMin);
	item->setData(Qt::UserRole + FVI_RANGE_MAX, rangeMax);

	ui->lw_Filters->addItem(item);
}
//----------------------------------------------------------------------------------
void SettingsForm::UpdateEegFilters()
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
//----------------------------------------------------------------------------------
void SettingsForm::on_gb_UseFilters_toggled(bool arg1)
{

}
//----------------------------------------------------------------------------------
void SettingsForm::on_tw_EegChannels_itemChanged(QTableWidgetItem *item)
{
	if (m_loading)
		return;

	if (item != nullptr && item->column() == 0)
	{
		CConfigManager &config = CConfigManager::instance();
		config.setCurveIsChecked(item->row(), item->checkState() == Qt::Checked);
		emit updateEegChannelsSummary();
	}
}
//----------------------------------------------------------------------------------
