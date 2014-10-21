#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T15:59:10
#
#-------------------------------------------------

QT       += sql script scripttools xml testlib

QT       -= gui

TARGET = IAlgorithmFactory
TEMPLATE = lib

DEFINES += IALGORITHMFACTORY_LIBRARY

SOURCES += ialgorithmfactory.cpp

HEADERS += ialgorithmfactory.h\
        ialgorithmfactory_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../IAlgorithm/ -lIAlgorithm


unix {
    target.path = /usr/lib
    INSTALLS += target
}
