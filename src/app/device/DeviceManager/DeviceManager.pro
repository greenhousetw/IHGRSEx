#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T15:23:02
#
#-------------------------------------------------

QT       += qml quick sql script scripttools xml xmlpatterns
QT       += plugin
QT       -= gui

TARGET = DeviceManager
TEMPLATE = lib

DEFINES += DEVICEMANAGER_LIBRARY

SOURCES += devicemanager.cpp

HEADERS += devicemanager.h\
        devicemanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
