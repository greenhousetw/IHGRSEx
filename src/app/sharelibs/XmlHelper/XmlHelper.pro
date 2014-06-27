#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T15:33:17
#
#-------------------------------------------------

QT       +=  sql script webkit webkitwidgets xml xmlpatterns testlib

QT       -= gui

TARGET = XmlHelper
TEMPLATE = lib

DEFINES += XMLHELPER_LIBRARY

SOURCES += xmlhelper.cpp

HEADERS += xmlhelper.h\
        xmlhelper_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

