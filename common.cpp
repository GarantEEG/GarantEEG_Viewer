/**
@file common.cpp

@brief Реализация класса для общих функци приложения

@author Мустакимов Т.Р.
**/
//----------------------------------------------------------------------------------
#include "common.h"
#include <QDir>
//----------------------------------------------------------------------------------
QString GarantUtility::BoolToText(const bool &value)
{
	if (value)
		return "true";

	return "false";
}
//----------------------------------------------------------------------------------
bool GarantUtility::RawStringToBool(QString value)
{
	value = value.toLower();
	bool result = false;

	if (value == "true" || value == "on")
		result = true;
	else
		result = (value.toInt() != 0);

	return result;
}
//----------------------------------------------------------------------------------
void GarantUtility::BringWidgetToTop(QWidget *window)
{
	if (window != nullptr)
	{
		if (window->isMinimized())
		{
			if (window->isMaximized())
				window->showMaximized();
			else
				window->showNormal();
		}
		else if (window->isVisible())
			window->activateWindow();
		else
			window->show();
	}
}
//----------------------------------------------------------------------------------
void GarantUtility::CreateDirectoryFromFilePath(QString filePath)
{
	int lastChar = qMax(filePath.lastIndexOf("/"), filePath.lastIndexOf("\\"));

	if (lastChar != -1)
		filePath.resize(lastChar);

	if (filePath.length())
		QDir().mkpath(filePath);
}
//----------------------------------------------------------------------------------
int GarantUtility::GetSettingInt(QSettings &settings, const QString &name, int defaultValue)
{
    bool ok = false;

    int reuslt = settings.value(name).toInt(&ok);

    if (!ok)
        reuslt = defaultValue;

    return reuslt;
}
//----------------------------------------------------------------------------------
