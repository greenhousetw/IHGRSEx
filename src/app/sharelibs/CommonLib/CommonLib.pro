#-------------------------------------------------
#
# Project created by QtCreator 2014-10-13T17:37:54
#
#-------------------------------------------------

QT       += widgets declarative qml quick network opengl sql script scripttools xml xmlpatterns

QT       -= gui

TARGET = CommonLib
TEMPLATE = lib

DEFINES += COMMONLIB_LIBRARY

SOURCES += commonlib.cpp

HEADERS += commonlib.h\
        commonlib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
