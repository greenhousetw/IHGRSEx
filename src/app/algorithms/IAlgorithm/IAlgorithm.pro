#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T13:38:05
#
#-------------------------------------------------

QT       -= gui

TARGET = IAlgorithm
TEMPLATE = lib

DEFINES += IALGORITHM_LIBRARY

SOURCES += ialgorithm.cpp

HEADERS += ialgorithm.h\
        ialgorithm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

PROJECTNAME=IAlgorithm
message(PROJECT NAME=$$PROJECTNAME)
message(PRO Path=$$_PRO_FILE_PWD_)
message(PROJECT SOURCE CODE PATH=$$PWD)
message(OUTPUT Directory Path=$$OUT_PWD)

