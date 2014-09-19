#-------------------------------------------------
#
# Project created by QtCreator 2014-09-18T15:49:15
#
#-------------------------------------------------

QT       += sql script xml xmlpatterns
CONFIG   += plugin
QT       -= gui

TARGET = SensorPlugInLoader
TEMPLATE = lib

DEFINES += SENSORPLUGINLOADER_LIBRARY

SOURCES += sensorpluginloader.cpp

HEADERS += sensorpluginloader.h\
        sensorpluginloader_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/release/ -lIDeviceFactory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/debug/ -lIDeviceFactory
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/ -lIDeviceFactory

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorUnit/release/ -lSensorUnit
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorUnit/debug/ -lSensorUnit
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/SensorUnit/ -lSensorUnit

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
