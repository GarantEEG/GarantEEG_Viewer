/**
@file configmanager.cpp

@brief Реализация класса конфигурации приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "managers/configmanager.h"
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
//----------------------------------------------------------------------------------
QJsonObject CFilterInfo::toJson() const
{
	QJsonArray channels;

	for (int i : m_channels)
	{
		channels << QJsonObject{ { "id", i } };
	}

	return QJsonObject
	{
		{ "type", m_type },
		{ "order", m_order },
		{ "rate", m_rate },
		{ "low_frequency", m_lowFrequency },
		{ "hight_frequency", m_hightFrequency },
		{ "channels", channels }
	};
}
//----------------------------------------------------------------------------------
CFilterInfo CFilterInfo::fromJson(const QJsonObject &obj)
{
	CFilterInfo filter;

	if (obj.contains("type") && obj["type"].isDouble())
		filter.m_type = obj["type"].toInt();

	if (obj.contains("order") && obj["order"].isDouble())
		filter.m_order = obj["order"].toInt();

	if (obj.contains("rate") && obj["rate"].isDouble())
		filter.m_type = obj["rate"].toInt();

	if (obj.contains("low_frequency") && obj["low_frequency"].isDouble())
		filter.m_lowFrequency = obj["low_frequency"].toInt();

	if (obj.contains("hight_frequency") && obj["hight_frequency"].isDouble())
		filter.m_hightFrequency = obj["hight_frequency"].toInt();

	if (obj.contains("channels") && obj["channels"].isArray())
	{
		QJsonArray channelsArray = obj["channels"].toArray();

		for (const auto &value : channelsArray)
		{
			if (!value.isObject())
				continue;

			QJsonObject obj = value.toObject();

			if (obj.contains("id") && obj["id"].isDouble())
				filter.m_channels << obj.value("id").toInt();
		}
	}

	return filter;
}
//----------------------------------------------------------------------------------
CConfigManager::CConfigManager()
{
}
//----------------------------------------------------------------------------------
CConfigManager::~CConfigManager()
{
}
//----------------------------------------------------------------------------------
CConfigManager &CConfigManager::instance()
{
	static CConfigManager *config = new CConfigManager();
	return *config;
}
//----------------------------------------------------------------------------------
void CConfigManager::resetValues()
{
	m_ip = CONFIG_DEFAULT_VALUE_ip;
	m_port = CONFIG_DEFAULT_VALUE_port;
	m_autoreconnect = CONFIG_DEFAULT_VALUE_autoreconnect;
	m_displaySeconds = CONFIG_DEFAULT_VALUE_displaySeconds;

	for (int i = 0; i < 8; i++)
	{
		m_curveColors[i] = CONFIG_DEFAULT_VALUE_curveColors[i];
		m_curveIsChecked[i] = true;
	}
}
//----------------------------------------------------------------------------------
void CConfigManager::load()
{
	QString configFilePath = QDir::currentPath() + QDir::separator() + "gv_config.json";
	QFile file(configFilePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		resetValues();
		return;
	}

	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();

	QJsonObject jsonObj = doc.object();

	if (jsonObj.contains("ip") && jsonObj["ip"].isString())
		m_ip = jsonObj["ip"].toString();
	else
		m_ip = CONFIG_DEFAULT_VALUE_ip;

	if (jsonObj.contains("port") && jsonObj["port"].isDouble())
		m_port = jsonObj["port"].toInt();
	else
		m_port = CONFIG_DEFAULT_VALUE_port;

	if (jsonObj.contains("autoreconnect") && jsonObj["autoreconnect"].isBool())
		m_autoreconnect = jsonObj["autoreconnect"].toBool();
	else
		m_autoreconnect = CONFIG_DEFAULT_VALUE_autoreconnect;

	if (jsonObj.contains("display_seconds") && jsonObj["display_seconds"].isDouble())
		m_displaySeconds = jsonObj["display_seconds"].toInt();
	else
		m_displaySeconds = CONFIG_DEFAULT_VALUE_displaySeconds;

	if (jsonObj.contains("eeg_colors") && jsonObj["eeg_colors"].isArray())
	{
		QJsonArray eegColorsArray = jsonObj["eeg_colors"].toArray();
		int i = 0;

		for (const auto &value : eegColorsArray)
		{
			if (!value.isObject())
				continue;

			QJsonObject obj = value.toObject();

			if (obj.contains("color") && obj["color"].isString())
				m_curveColors[i] = obj.value("color").toString();
			else
				m_curveColors[i] = CONFIG_DEFAULT_VALUE_curveColors[i];

			if (obj.contains("checked") && obj["checked"].isBool())
				m_curveIsChecked[i] = obj.value("checked").toBool();
			else
				m_curveIsChecked[i] = true;

			i++;
		}
	}

	if (jsonObj.contains("filters") && jsonObj["filters"].isArray())
	{
		QJsonArray filtersArray = jsonObj["filters"].toArray();

		for (const auto &value : filtersArray)
		{
			if (value.isObject())
				m_filters << CFilterInfo::fromJson(value.toObject());
		}
	}
}
//----------------------------------------------------------------------------------
void CConfigManager::save()
{
	QString configFilePath = QDir::currentPath() + QDir::separator() + "gv_config.json";
	QFile file(configFilePath);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::critical(nullptr, qAppName(), QWidget::tr("Failed to open file to write:\n%1\n%2").arg(configFilePath).arg(file.errorString()));
		return;
	}

	QJsonArray eegColors;

	for (int i = 0; i < 8; i++)
	{
		eegColors << QJsonObject
					{
						{ "color", m_curveColors[i] },
						{ "checked", m_curveIsChecked[i] }
					};
	}

	QJsonArray filtersArray;

	for (const CFilterInfo &filter : m_filters)
	{
		filtersArray << filter.toJson();
	}

	QJsonDocument doc
	{
		QJsonObject
		{
			{ "ip", m_ip },
			{ "port", m_port },
			{ "autoreconnect", m_autoreconnect },
			{ "display_seconds", m_displaySeconds },
			{ "eeg_colors", eegColors },
			{ "filters", filtersArray }
		}
	};

	file.write(doc.toJson());
	file.close();
}
//----------------------------------------------------------------------------------
