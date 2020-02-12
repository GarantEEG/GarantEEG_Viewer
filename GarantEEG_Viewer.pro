#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T15:30:37
#
#-------------------------------------------------

QT       += core gui widgets charts

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
        chart.cpp \
        curve.cpp \
        curve_data.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        chart.h \
        curve.h \
        curve_data.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
