/**
@file mainwindow.h

@brief Объявление класса основного окна приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//----------------------------------------------------------------------------------
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QCloseEvent>

#include <include/GarantEEG_API_CPP.h>

#include "forms/impedanceform.h"
//----------------------------------------------------------------------------------
namespace Ui
{
	class MainWindow;
}
//----------------------------------------------------------------------------------
//! Класс основного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/**
	 * @brief MainWindow Конструктор
	 * @param parent Виджет-родитель
	 */
    explicit MainWindow(QWidget *parent = nullptr);

	/**
	 * @brief ~MainWindow Деструктор
	 */
    ~MainWindow();

	/**
	 * @brief initialize Инициализация главного окна приложения
	 * @return true если инициализация прошла успешно, false если что-то пошло не так
	 */
	bool initialize();

protected:
	/**
	 * @brief closeEvent Событие закрытия окна
	 * @param e Указатель на событие
	 */
	virtual void closeEvent(QCloseEvent *e) override;

signals:
	/**
	 * @brief UpdateEegData Сигнал обновления данных с устройства
	 * @param eegData Данные
	 */
	void UpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

public slots:
	void onUpdateEegChannelsSummary();

private slots:
	/**
	 * @brief on_pb_Start_clicked Нажатие на кнопку запуска
	 */
    void on_pb_Start_clicked();

	/**
	 * @brief on_pb_Stop_clicked Нажатие на кнопку остановки
	 */
    void on_pb_Stop_clicked();

	/**
	 * @brief on_pb_PauseStream_clicked Нажатие на кнопку паузы трансляции данных
	 */
    void on_pb_PauseStream_clicked();

	/**
	 * @brief on_pb_ResumeStream_clicked Нажатие на кнопку возобновления трансляции данных
	 */
    void on_pb_ResumeStream_clicked();

	/**
	 * @brief on_pb_RecordStart_clicked Нажатие на кнопку запуска записи данных в файл
	 */
    void on_pb_RecordStart_clicked();

	/**
	 * @brief on_pb_RecordStop_clicked Нажатие на кнопку остановки записи данных в файл
	 */
    void on_pb_RecordStop_clicked();

	/**
	 * @brief on_pb_RecordPause_clicked Нажатие на кнопку паузы записи данных в файл
	 */
    void on_pb_RecordPause_clicked();

	/**
	 * @brief on_pb_RecordResume_clicked Нажатие на кнопку возобновления записи данных в файл
	 */
    void on_pb_RecordResume_clicked();

	/**
	 * @brief OnUpdateEegData Событие прихода новой порции данных с устройства
	 * @param eegData Данные
	 */
    void OnUpdateEegData(GarantEEG::GARANT_EEG_DATA eegData);

	/**
	 * @brief on_cb_AutoReconnection_stateChanged Изменение состояния галочки автореконнекта
	 * @param arg1 Новое состояние
	 */
    void on_cb_AutoReconnection_stateChanged(int arg1);

	/**
	 * @brief on_le_IP_textChanged Изменение значения IP адреса для подключения к ЭЭГ
	 * @param arg1 Новое значение
	 */
	void on_le_IP_textChanged(const QString &arg1);

	/**
	 * @brief on_sb_Port_valueChanged Изменение значения порта для подключения к ЭЭГ
	 * @param arg1 Новое значение
	 */
	void on_sb_Port_valueChanged(int arg1);

	/**
	 * @brief on_pb_Settings_clicked Нажатие на кнопку открытия диалога настроек
	 */
	void on_pb_Settings_clicked();

	/**
	 * @brief on_pb_CheckImpedance_clicked Нажатие на кнопку проверки импеданса
	 */
	void on_pb_CheckImpedance_clicked();

private:
	//! Указатель на UI формы
    Ui::MainWindow *ui;

	//! Указатель на интерфейс для работы с устройством
    GarantEEG::IGarantEEG *m_Eeg = nullptr;

	//! Указатель на форму проверки импеданса
	ImpedanceForm *m_ImpedanceForm = nullptr;

	//! Флаг загрузки данных
	bool m_loading = true;

	//! Таймер записи
	QTimer m_RecordingTimer;

	//! Время записи
	QElapsedTimer m_RecordTime;
};
//----------------------------------------------------------------------------------
#endif // MAINWINDOW_H
//----------------------------------------------------------------------------------
