#-------------------------------------------------
#
# Project created by QtCreator 2018-12-13T17:23:22
#
#-------------------------------------------------

QT       += core xml network gui widgets serialport webchannel websockets webengine webenginewidgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SemiPhySim
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
DEFINES += _UNICODE WIN64 QT_DLL QT_CHARTS_LIB QT_NETWORK_LIB QT_SERIALPORT_LIB QT_WEBCHANNEL_LIB QT_WEBSOCKETS_LIB QT_WEBENGINE_LIB QT_WEBENGINECORE_LIB QT_WEBENGINEWIDGETS_LIB QT_WIDGETS_LIB QT_XML_LIB

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    SandRBox.cpp \
    serialSetup.cpp

HEADERS += \
        mainwindow.h \
    protocols.h \
    protocols.h \
    SandRBox.h \
    serialSetup.h

FORMS += \
        mainwindow.ui \
    SandRBox.ui \
    serialSetup.ui
