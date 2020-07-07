/**
@file newfilterdialog.h

@brief Объявление класса окна добавления нового фильтра

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef NEWFILTERDIALOG_H
#define NEWFILTERDIALOG_H
//----------------------------------------------------------------------------------
#include <QDialog>

#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
namespace Ui
{
    class NewFilterDialog;
}
//----------------------------------------------------------------------------------
//! Класс окна добавления нового фильтра
class NewFilterDialog : public QDialog
{
    Q_OBJECT

public:
	/**
	 * @brief NewFilterDialog Конструктор
	 * @param eeg Указатель на интерфейс для работы с устройством
	 * @param parent Виджет-родитель
	 */
	explicit NewFilterDialog(GarantEEG::IGarantEEG *eeg, QWidget *parent = nullptr);

	/**
	 * @brief ~NewFilterDialog Деструктор
	 */
    ~NewFilterDialog();

signals:
	/**
	 * @brief AddFilter Сигнал добавления нового фильтра
	 * @param type Тип фильтра (строкой)
	 * @param typeId Идентификатор типа фильтра
	 * @param order Порядок фильтра
	 * @param rangeMin Минимальная частота
	 * @param rangeMax Максимальная частота
	 */
	void AddFilter(QString type, int typeId, int order, int rangeMin, int rangeMax);

private slots:
	/**
	 * @brief on_pb_OK_clicked Нажатие на кнопку ОК
	 */
    void on_pb_OK_clicked();

	/**
	 * @brief on_pb_Cancel_clicked Нажатие на кнопку отмена
	 */
    void on_pb_Cancel_clicked();

private:
	//! Указатель на UI диалога
    Ui::NewFilterDialog *ui;

	//! Указатель на интерфейс для работы с устройством
	GarantEEG::IGarantEEG *m_Eeg = nullptr;
};
//----------------------------------------------------------------------------------
#endif // NEWFILTERDIALOG_H
//----------------------------------------------------------------------------------
