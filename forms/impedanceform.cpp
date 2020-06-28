/**
@file impedanceform.cpp

@brief Реализация класса окна информации о импедансе

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "forms/impedanceform.h"
#include "ui_impedanceform.h"
//----------------------------------------------------------------------------------
ImpedanceForm::ImpedanceForm(QWidget *parent)
: QMainWindow(parent), ui(new Ui::ImpedanceForm)
{
	ui->setupUi(this);

	QHeaderView *headerView = ui->tw_ImpedanceTable->horizontalHeader();

	if (headerView != nullptr)
	{
		headerView->setMinimumSectionSize(100);
		headerView->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		headerView->setSectionResizeMode(1, QHeaderView::Stretch);
	}

	QStringList channels =
	{
		"Po7", "O1", "Oz", "P3", "Pz", "P4", "O2", "Po8", "Ref", "Ground"
	};

	ui->tw_ImpedanceTable->setRowCount(channels.size());

	for (int i = 0; i < channels.size(); i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(channels[i]);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui->tw_ImpedanceTable->setItem(i, 0, item);

		item = new QTableWidgetItem("? kOhm");
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui->tw_ImpedanceTable->setItem(i, 1, item);
	}
}
//----------------------------------------------------------------------------------
ImpedanceForm::~ImpedanceForm()
{
	delete ui;
}
//----------------------------------------------------------------------------------
void ImpedanceForm::resetValues()
{
	for (int i = 0; i < ui->tw_ImpedanceTable->rowCount(); i++)
	{
		QTableWidgetItem *item = ui->tw_ImpedanceTable->item(i, 1);

		if (item != nullptr)
		{
			item->setText("? kOhm");
			item->setBackgroundColor(QColor(255, 255, 255, 255));
		}
	}
}
//----------------------------------------------------------------------------------
void ImpedanceForm::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
	if (!isVisible())
		return;

	const GarantEEG::GARANT_EEG_RESISTANCE_DATA &resistanceData = eegData.ResistanceData;

	for (int i = 0; i < ui->tw_ImpedanceTable->rowCount(); i++)
	{
		QTableWidgetItem *item = ui->tw_ImpedanceTable->item(i, 1);

		if (item != nullptr)
		{
			double resistance;

			if (i < 8)
				resistance = resistanceData.Value[i];
			else if (i < 9)
				resistance = resistanceData.Ref;
			else
				resistance = resistanceData.Ground;

			item->setText(QString::asprintf("%.03f kOhm", resistance));

			if (resistance < 10.0f)
				item->setBackgroundColor(QColor(0, 255, 0, 128));
			else if (resistance < 20.0f)
				item->setBackgroundColor(QColor(255, 242, 0, 128));
			else if (resistance < 40.0f)
				item->setBackgroundColor(QColor(255, 128, 0, 128));
			else
				item->setBackgroundColor(QColor(255, 0, 0, 128));
		}
	}
}
//----------------------------------------------------------------------------------
