#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>

#include <include/GarantEEG_API_CPP.h>
#include <charts/chart.h>

namespace Ui
{
	class SettingsForm;
}

class SettingsForm : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsForm(GarantEEG::IGarantEEG *eeg, Chart *chart, QWidget *parent = nullptr);
	~SettingsForm();

private slots:
	void on_pb_PowerOff_clicked();

	void on_pb_IndicationStart_clicked();

	void on_pb_IndicationStop_clicked();

	void on_tw_EegChannels_cellClicked(int row, int column);

	void on_pb_OK_clicked();

private:
	Ui::SettingsForm *ui;

	GarantEEG::IGarantEEG *m_Eeg = nullptr;

	Chart *m_Chart = nullptr;
};

#endif // SETTINGSFORM_H
