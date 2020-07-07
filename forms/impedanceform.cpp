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

	QStringList channels = channelNames();

	QQuickItem *root = ui->qw_Electrodes->rootObject();
	ui->tw_ImpedanceTable->setRowCount(channels.size());

	for (int i = 0; i < channels.size(); i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem(channels[i]);
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui->tw_ImpedanceTable->setItem(i, 0, item);

		item = new QTableWidgetItem("? kOhm");
		item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui->tw_ImpedanceTable->setItem(i, 1, item);

		if (root != nullptr)
		{
			QVariant returnedValue;

			QMetaObject::invokeMethod((QObject*)root,
										  "addElectode",
										  Q_RETURN_ARG(QVariant, returnedValue),
										  Q_ARG(QVariant, channels[i]),
										  Q_ARG(QVariant, i));
		}
	}
}
//----------------------------------------------------------------------------------
ImpedanceForm::~ImpedanceForm()
{
	delete ui;
}
//----------------------------------------------------------------------------------
QStringList ImpedanceForm::channelNames()
{
	return QStringList
			{
				"Po7", "O1", "Oz", "P3", "Pz", "P4", "O2", "Po8", "Ref", "Gnd"
			};
}
//----------------------------------------------------------------------------------
void ImpedanceForm::resetValues()
{
	QQuickItem *root = ui->qw_Electrodes->rootObject();

	for (int i = 0; i < ui->tw_ImpedanceTable->rowCount(); i++)
	{
		QTableWidgetItem *item = ui->tw_ImpedanceTable->item(i, 1);

		if (item != nullptr)
		{
			item->setText("? kOhm");
			item->setBackgroundColor(QColor(255, 255, 255, 255));
		}

		if (root != nullptr)
		{
			QVariant returnedValue;

			QMetaObject::invokeMethod((QObject*)root,
									  "setElectrodeState",
									  Q_RETURN_ARG(QVariant, returnedValue),
									  Q_ARG(QVariant, i),
									  Q_ARG(QVariant, 255.0),
									  Q_ARG(QVariant, false));
		}
	}
}
//----------------------------------------------------------------------------------
void ImpedanceForm::OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData)
{
	if (!isVisible())
		return;

	QQuickItem *root = ui->qw_Electrodes->rootObject();

	const GarantEEG::GARANT_EEG_RESISTANCE_DATA &resistanceData = eegData.ResistanceData;

	for (int i = 0; i < ui->tw_ImpedanceTable->rowCount(); i++)
	{
		double resistance;

		if (i < 8)
			resistance = resistanceData.Value[i];
		else if (i < 9)
			resistance = resistanceData.Ref;
		else
			resistance = resistanceData.Ground;

		QTableWidgetItem *item = ui->tw_ImpedanceTable->item(i, 1);

		if (item != nullptr)
		{
			item->setText(QString::asprintf("%.03f kOhm", resistance));

			if (resistance < 10.0f)
				item->setBackgroundColor(QColor(0, 255, 0, 128));
			else if (resistance < 20.0f)
				item->setBackgroundColor(QColor(255, 242, 0, 128));
			else if (resistance < 30.0f)
				item->setBackgroundColor(QColor(255, 128, 0, 128));
			else
				item->setBackgroundColor(QColor(255, 0, 0, 128));
		}

		if (root != nullptr)
		{
			QVariant returnedValue;

			QMetaObject::invokeMethod((QObject*)root,
									  "setElectrodeState",
									  Q_RETURN_ARG(QVariant, returnedValue),
									  Q_ARG(QVariant, i),
									  Q_ARG(QVariant, resistance),
									  Q_ARG(QVariant, false));
		}
	}
}
//----------------------------------------------------------------------------------
void ImpedanceForm::on_pb_Close_clicked()
{
	close();
}
//----------------------------------------------------------------------------------
