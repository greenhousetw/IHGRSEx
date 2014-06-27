#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T11:22:11
#
#-------------------------------------------------

QT       += sql xml xmlpatterns

QT       -= gui

TARGET = IRepository
TEMPLATE = lib

DEFINES += IREPOSITORY_LIBRARY

SOURCES += irepository.cpp

HEADERS += irepository.h\
        irepository_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
