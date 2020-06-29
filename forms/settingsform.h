/**
@file settingsform.h

@brief Объявление класса окна настроек

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H
//----------------------------------------------------------------------------------
#include <QDialog>

#include <include/GarantEEG_API_CPP.h>
#include <charts/chart.h>
//----------------------------------------------------------------------------------
namespace Ui
{
	class SettingsForm;
}
//----------------------------------------------------------------------------------
//! Класс диалога настроек
class SettingsForm : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief SettingsForm Конструктор
	 * @param eeg Указатель на интерфейс для работы с устройством
	 * @param chart Указатель на виджет с графиками
	 * @param parent Виджет-родитель
	 */
	explicit SettingsForm(GarantEEG::IGarantEEG *eeg, Chart *chart, QWidget *parent = nullptr);

	/**
	 * @brief ~SettingsForm Деструктор
	 */
	~SettingsForm();

private slots:
	/**
	 * @brief on_pb_PowerOff_clicked Нажатие на кнопку выключения питания на устройстве
	 */
	void on_pb_PowerOff_clicked();

	/**
	 * @brief on_pb_IndicationStart_clicked Нажатие на запуска кнопку теста индикации
	 */
	void on_pb_IndicationStart_clicked();

	/**
	 * @brief on_pb_IndicationStop_clicked Нажатие на остановки кнопку теста индикации
	 */
	void on_pb_IndicationStop_clicked();

	/**
	 * @brief on_tw_EegChannels_cellClicked Клик по ячейке в списке каналов
	 * @param row Строка
	 * @param column Столбец
	 */
	void on_tw_EegChannels_cellClicked(int row, int column);

	/**
	 * @brief on_pb_OK_clicked Нажатие на кнопку ОК
	 */
	void on_pb_OK_clicked();

private:
	//! Указатель на UI диалога
	Ui::SettingsForm *ui;

	//! Указатель на интерфейс для работы с устройством
	GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Указатель для работы с виджетом графиков
	Chart *m_Chart = nullptr;
};
//----------------------------------------------------------------------------------
#endif // SETTINGSFORM_H
//----------------------------------------------------------------------------------
