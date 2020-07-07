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
#include <QTableWidgetItem>
#include <include/GarantEEG_API_CPP.h>
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
	 * @param parent Виджет-родитель
	 */
	explicit SettingsForm(GarantEEG::IGarantEEG *eeg, QWidget *parent = nullptr);

	/**
	 * @brief ~SettingsForm Деструктор
	 */
	~SettingsForm();

	/**
	 * @brief UpdateEegFilters Обновить все фильтры
	 */
	void UpdateEegFilters();

signals:
	void updateEegChannelsSummary();

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
	 * @brief on_pb_Close_clicked Нажатие на кнопку ОК
	 */
	void on_pb_Close_clicked();

	/**
	 * @brief on_pb_AddFilter_clicked Нажатие на кнопку добавления нового фильтра
	 */
	void on_pb_AddFilter_clicked();

	/**
	 * @brief on_pb_RemoveSelectedFilter_clicked Нажатие на кнопку удаления текущего выбранного фильтра
	 */
	void on_pb_RemoveSelectedFilter_clicked();

	/**
	 * @brief on_pb_RemoveAllFilters_clicked Удаление всех фильтров
	 */
	void on_pb_RemoveAllFilters_clicked();

	/**
	 * @brief OnAddFilter Добавление нового фильтра
	 * @param type Тип фильтра (строкой)
	 * @param typeId Идентификатор типа фильтра
	 * @param order Порядок фильтра
	 * @param rangeMin Минимальная частота
	 * @param rangeMax Максимальная частота
	 */
	void OnAddFilter(QString type, int typeId, int order, int rangeMin, int rangeMax);

	void on_gb_UseFilters_toggled(bool arg1);

	void on_tw_EegChannels_itemChanged(QTableWidgetItem *item);

private:
	//! Указатель на UI диалога
	Ui::SettingsForm *ui;

	//! Указатель на интерфейс для работы с устройством
	GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Флаг загрузки данных
	bool m_loading = true;

	//! Список смещений для данных по фильтрам
	enum FILTER_VARIABLE_INDEX
	{
		FVI_TYPE = 0,
		FVI_TYPE_ID,
		FVI_ORDER,
		FVI_RANGE_MIN,
		FVI_RANGE_MAX
	};
};
//----------------------------------------------------------------------------------
#endif // SETTINGSFORM_H
//----------------------------------------------------------------------------------
