#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T18:03:05
#
#-------------------------------------------------

QT       -= gui

TARGET = IRepositoryManager
TEMPLATE = lib

CONFIG   += plugin


DEFINES += IREPOSITORYMANAGER_LIBRARY

SOURCES += irepositorymanager.cpp

HEADERS += irepositorymanager.h\
        irepositorymanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
