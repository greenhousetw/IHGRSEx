#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T13:24:40
#
#-------------------------------------------------

QT       += qml sql script scripttools xml xmlpatterns

QT       -= gui

TARGET = DeviceBase
TEMPLATE = lib

DEFINES += DEVICEBASE_LIBRARY

SOURCES += devicebase.cpp

HEADERS += devicebase.h\
        devicebase_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
