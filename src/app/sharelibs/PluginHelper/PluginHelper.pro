#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T17:11:14
#
#-------------------------------------------------

QT       += sql script xml xmlpatterns

QT       -= gui

TARGET = PluginHelper
TEMPLATE = lib

DEFINES += PLUGINHELPER_LIBRARY

SOURCES += pluginhelper.cpp

HEADERS += pluginhelper.h\
        pluginhelper_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
