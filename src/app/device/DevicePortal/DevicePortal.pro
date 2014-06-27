#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T15:34:20
#
#-------------------------------------------------

QT       += qml sql script scripttools xml xmlpatterns core

QT       -= gui

TARGET = DevicePortal
TEMPLATE = lib

DEFINES += DEVICEPORTAL_LIBRARY

SOURCES += deviceportal.cpp

HEADERS += deviceportal.h\
        deviceportal_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Sensors/release/ -lSensors
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Sensors/debug/ -lSensors
else:unix: LIBS += -L$$OUT_PWD/../Sensors/ -lSensors

INCLUDEPATH += $$PWD/../Sensors
DEPENDPATH += $$PWD/../Sensors

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SensorBase/release/ -lSensorBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SensorBase/debug/ -lSensorBase
else:unix: LIBS += -L$$OUT_PWD/../SensorBase/ -lSensorBase

INCLUDEPATH += $$PWD/../SensorBase
DEPENDPATH += $$PWD/../SensorBase

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DeviceBase/release/ -lDeviceBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DeviceBase/debug/ -lDeviceBase
else:unix: LIBS += -L$$OUT_PWD/../DeviceBase/ -lDeviceBase

INCLUDEPATH += $$PWD/../DeviceBase
DEPENDPATH += $$PWD/../DeviceBase

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ControlHardwareManager/release/ -lControlHardwareManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ControlHardwareManager/debug/ -lControlHardwareManager
else:unix: LIBS += -L$$OUT_PWD/../ControlHardwareManager/ -lControlHardwareManager

INCLUDEPATH += $$PWD/../ControlHardwareManager
DEPENDPATH += $$PWD/../ControlHardwareManager
