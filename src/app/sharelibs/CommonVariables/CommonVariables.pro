#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T14:10:32
#
#-------------------------------------------------

QT       -= gui

TARGET = CommonVariables
TEMPLATE = lib

DEFINES += COMMONVARIABLES_LIBRARY

SOURCES += commonvariables.cpp

HEADERS += commonvariables.h\
        commonvariables_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
