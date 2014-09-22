#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T15:23:02
#
#-------------------------------------------------

QT       += qml quick sql script scripttools xml xmlpatterns core
CONFIG       += plugin
QT       -= gui

TARGET = DeviceManager
TEMPLATE = lib

DEFINES += DEVICEMANAGER_LIBRARY

SOURCES += devicemanager.cpp \
    devicemangerhandler.cpp

HEADERS += devicemanager.h\
        devicemanager_global.h \
    devicemangerhandler.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

INCLUDEPATH += $$PWD/../../core/Core
DEPENDPATH += $$PWD/../../core/Core

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json \
    config.json \
    sensorconfig.json
