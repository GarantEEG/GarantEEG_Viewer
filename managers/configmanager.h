/**
@file configmanager.h

@brief Объявление класса конфигурации приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
//----------------------------------------------------------------------------------
#include <QMainWindow>
#include <include/GarantEEG_API_CPP.h>
//----------------------------------------------------------------------------------
//! Настройки для конфигурации по умолчанию
const QString CONFIG_DEFAULT_VALUE_ip = "192.168.127.125";
const int CONFIG_DEFAULT_VALUE_port = 12345;
const bool CONFIG_DEFAULT_VALUE_autoreconnect = true;
const int CONFIG_DEFAULT_VALUE_displaySeconds = 5;
const QString CONFIG_DEFAULT_VALUE_curveColors[8] =
{
	"#FF0000", //Qt::red
	"#000000", //Qt::black
	"#808080", //Qt::darkGray
	"#00FF00", //Qt::green
	"#0000FF", //Qt::blue
	"#FF00FF", //Qt::magenta
	"#FFFF00", //Qt::yellow
	"#808000" //Qt::darkYellow
};
//----------------------------------------------------------------------------------
//! Класс для хранения информации о фильтре
class CFilterInfo
{
public:
	/**
	 * @brief CFilterInfo Конструктор
	 */
	CFilterInfo() {}

	/**
	 * @brief ~CFilterInfo Деструктор
	 */
	~CFilterInfo() {}

	//! Тип фильтра
	int m_type = 0;

	//! Порядок фильтра
	int m_order = 0;

	//! Частота потока данных
	int m_rate = 0;

	//! Минимальная частота среза
	int m_lowFrequency = 0;

	//! Максимальная частота среза
	int m_hightFrequency = 0;

	//! Список каналов, для которых применяется фильтр
	QVector<int> m_channels;



	/**
	 * @brief toJson Получить JSON данные
	 * @return JSON фильтра
	 */
	QJsonObject toJson() const;

	/**
	 * @brief fromJson Создать объект инфомрации о фильтре из JSON
	 * @param obj Объект JSON
	 * @return Объект CFilterInfo
	 */
	static CFilterInfo fromJson(const QJsonObject &obj);
};
//----------------------------------------------------------------------------------
//! Класс окна информации о импедансе
class CConfigManager
{
public:
	/**
	 * @brief CConfigManager Конструктор
	 */
	CConfigManager();

	/**
	 * @brief ~CConfigManager Деструктор
	 */
	~CConfigManager();

	/**
	 * @brief instance Получить ссылку на синглтон объекта конфига
	 * @return Ссылка на глобальный объект конфига
	 */
	static CConfigManager &instance();

	/**
	 * @brief resetValues Сброс значений
	 */
	void resetValues();

	/**
	 * @brief load Загрузить конфигурацию
	 */
	void load();

	/**
	 * @brief save Сохранить конфигурацию
	 */
	void save();



	//! Сеттеры и геттеры
	const QString &ip() const { return m_ip; }
	void setIp(const QString &value) { m_ip = value; }

	const int &port() const { return m_port; }
	void setPort(const int &value) { m_port = value; }

	const bool &autoreconnect() const { return m_autoreconnect; }
	void setAutoreconnect(const bool &value) { m_autoreconnect = value; }

	const int &displaySeconds() const { return m_displaySeconds; }
	void setDisplaySeconds(const int &value) { m_displaySeconds = value; }

	QString curveColor(uint index) const { return (index < 8 ? m_curveColors[index] : "#0"); }
	void setCurveColor(uint index, const QString &value) { if (index < 8) m_curveColors[index] = value; }

	bool curveIsChecked(uint index) const { return (index < 8 ? m_curveIsChecked[index] : false); }
	void setCurveIsChecked(uint index, const bool &value) { if (index < 8) m_curveIsChecked[index] = value; }

	QList<CFilterInfo> &filters() { return m_filters; }

protected:
	//! ИД для подключения к ЭЭГ
	QString m_ip = CONFIG_DEFAULT_VALUE_ip;

	//! Порт для подключения к ЭЭГ
	int m_port = CONFIG_DEFAULT_VALUE_port;

	//! Флаг автопереподключения к устройству при потере соединения
	bool m_autoreconnect = CONFIG_DEFAULT_VALUE_autoreconnect;

	//! Количество отображаемых секунд на графике
	int m_displaySeconds = CONFIG_DEFAULT_VALUE_displaySeconds;

	//! Цвета для графиков ЭЭГ
	QString m_curveColors[8] =
	{
		CONFIG_DEFAULT_VALUE_curveColors[0],
		CONFIG_DEFAULT_VALUE_curveColors[1],
		CONFIG_DEFAULT_VALUE_curveColors[2],
		CONFIG_DEFAULT_VALUE_curveColors[3],
		CONFIG_DEFAULT_VALUE_curveColors[4],
		CONFIG_DEFAULT_VALUE_curveColors[5],
		CONFIG_DEFAULT_VALUE_curveColors[6],
		CONFIG_DEFAULT_VALUE_curveColors[7]
	};

	//! Состояние выбора для графиков ЭЭГ
	bool m_curveIsChecked[8] =
	{
		true, true, true, true,
		true, true, true, true
	};

	//! Список фильтров
	QList<CFilterInfo> m_filters;
};
//----------------------------------------------------------------------------------
#endif // CONFIGMANAGER_H
//----------------------------------------------------------------------------------
