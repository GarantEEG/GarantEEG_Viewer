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
//----------------------------------------------------------------------------------
SettingsForm::SettingsForm(GarantEEG::IGarantEEG *eeg, Chart *chart, QWidget *parent)
: QDialog(parent), ui(new Ui::SettingsForm), m_Eeg(eeg), m_Chart(chart)
{
	ui->setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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

	if (m_Chart != nullptr)
	{
		const auto &curves = m_Chart->curves();

		for (auto it = curves.begin(); it != curves.end(); ++it)
		{
			int row = ui->tw_EegChannels->rowCount();
			ui->tw_EegChannels->setRowCount(row + 1);

			QTableWidgetItem *item = new QTableWidgetItem(it->second->title().text());
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui->tw_EegChannels->setItem(row, 0, item);

			item = new QTableWidgetItem();
			item->setBackgroundColor(it->second->pen().color());
			ui->tw_EegChannels->setItem(row, 1, item);
		}
	}
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
	if (column != 1 || m_Chart == nullptr)
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
		m_Chart->setCurveColor(itemName->text(), color);
	}

	ui->tw_EegChannels->setCurrentCell(row, 0);
}
//----------------------------------------------------------------------------------
void SettingsForm::on_pb_OK_clicked()
{
	close();
}
//----------------------------------------------------------------------------------
