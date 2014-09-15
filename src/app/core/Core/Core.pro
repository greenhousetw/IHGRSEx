#-------------------------------------------------
#
# Project created by QtCreator 2014-09-11T15:21:40
#
#-------------------------------------------------

QT       -= gui
CONFIG +=plugin
TARGET = Core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

SOURCES += core.cpp \
    datapacket.cpp \
    coreone.cpp

HEADERS += core.h\
        core_global.h \
    datapacket.h \
    coreone.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
