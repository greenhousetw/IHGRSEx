#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T17:56:31
#
#-------------------------------------------------

QT       += xml xmlpatterns
QT       -= gui

TARGET = Hardware
TEMPLATE = lib

DEFINES += HARDWARE_LIBRARY

SOURCES += hardware.cpp

HEADERS += hardware.h\
        hardware_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
