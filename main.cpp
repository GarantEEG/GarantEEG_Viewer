#include "forms/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	if (!w.initialize())
		return 0;

    return a.exec();
}
