#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T16:05:07
#
#-------------------------------------------------

QT       += sql script scripttools xml

QT       -= gui

TARGET = AlgorithmLoader
TEMPLATE = lib

DEFINES += ALGORITHMLOADER_LIBRARY

SOURCES += algorithmloader.cpp

HEADERS += algorithmloader.h\
        algorithmloader_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/release/ -lPluginHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/debug/ -lPluginHelper
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/ -lPluginHelper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithmFactory/release/ -lIAlgorithmFactory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithmFactory/debug/ -lIAlgorithmFactory
else:unix: LIBS += -L$$OUT_PWD/../IAlgorithmFactory/ -lIAlgorithmFactory

OTHER_FILES += \
    info.json
