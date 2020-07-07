#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T15:30:37
#
#-------------------------------------------------

QT       += core gui widgets quick quickwidgets qml

TARGET = GarantEEG_Viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += c++14
CONFIG += qwt

INCLUDEPATH += \
    $$PWD/qwt/include

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$PWD/qwt/lib

        LIBS += \
                -lqwtd
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$PWD/qwt/lib

        LIBS += \
                -lqwt
}

QT += \
    printsupport

DEFINES += \
    QWT_DLL

include("$$PWD/../GarantEEG_API/GarantEEG_API.pri")

INCLUDEPATH += $$PWD/../GarantEEG_API/

SOURCES += \
		charts/chart.cpp \
		charts/curve.cpp \
		charts/curve_data.cpp \
	common.cpp \
	forms/impedanceform.cpp \
	forms/newfilterdialog.cpp \
	forms/settingsform.cpp \
        main.cpp \
		forms/mainwindow.cpp \
	managers/configmanager.cpp

HEADERS += \
		charts/chart.h \
		charts/curve.h \
		charts/curve_data.h \
		common.h \
		forms/impedanceform.h \
		forms/mainwindow.h \
		forms/newfilterdialog.h \
		forms/settingsform.h \
		managers/configmanager.h

FORMS += \
		forms/impedanceform.ui \
		forms/mainwindow.ui \
		forms/newfilterdialog.ui \
		forms/settingsform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resource.qrc
