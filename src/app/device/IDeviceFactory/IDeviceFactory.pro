#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T14:43:59
#
#-------------------------------------------------

QT       += xml xmlpatterns
CONFIG   += plugin
QT       -= gui

TARGET = IDeviceFactory
TEMPLATE = lib

DEFINES += IDEVICEFACTORY_LIBRARY

SOURCES += idevicefactory.cpp

HEADERS += idevicefactory.h\
        idevicefactory_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SensorUnit/release/ -lSensorUnit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SensorUnit/debug/ -lSensorUnit
else:unix: LIBS += -L$$OUT_PWD/../SensorUnit/ -lSensorUnit

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    sinfo.json
