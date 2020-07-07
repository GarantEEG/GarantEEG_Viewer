/**
@file impedanceform.h

@brief Объявление класса окна информации о импедансе

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef IMPEDANCEFORM_H
#define IMPEDANCEFORM_H
//----------------------------------------------------------------------------------
#include <QMainWindow>
#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
	class ImpedanceForm;
}
//----------------------------------------------------------------------------------
//! Класс окна информации о импедансе
class ImpedanceForm : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * @brief ImpedanceForm Конструктор
	 * @param parent Виджет-родитель
	 */
	explicit ImpedanceForm(QWidget *parent = nullptr);

	/**
	 * @brief ~ImpedanceForm Деструктор
	 */
	~ImpedanceForm();

	/**
	 * @brief channelNames Получить названия каналов ЭЭГ
	 * @return Массив каналов
	 */
	static QStringList channelNames();

	/**
	 * @brief resetValues Сброс значений импеданса
	 */
	void resetValues();

public slots:
	/**
	 * @brief OnUpdateEegData Событие прихода новых данных с устройства
	 * @param eegData Данные
	 */
	void OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

private slots:
	/**
	 * @brief on_pb_Close_clicked Нажатие на кнопку закрыть
	 */
	void on_pb_Close_clicked();

private:
	//! Указатель на UI окна
	Ui::ImpedanceForm *ui;
};
//----------------------------------------------------------------------------------
#endif // IMPEDANCEFORM_H
//----------------------------------------------------------------------------------
