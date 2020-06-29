//----------------------------------------------------------------------------------
#ifndef COMMON_H
#define COMMON_H
//----------------------------------------------------------------------------------
#include <QWidget>
#include <QSettings>
//----------------------------------------------------------------------------------
class GarantUtility
{
public:
	GarantUtility() {}

	static QString BoolToText(const bool &value);

	static bool RawStringToBool(QString value);

	static void BringWidgetToTop(QWidget *window);

	static void CreateDirectoryFromFilePath(QString filePath);

    static int GetSettingInt(QSettings &settings, const QString &name, int defaultValue);
};
//----------------------------------------------------------------------------------
#endif // COMMON_H
//----------------------------------------------------------------------------------
