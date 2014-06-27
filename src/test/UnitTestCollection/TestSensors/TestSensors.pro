#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T15:14:17
#
#-------------------------------------------------

QT       += sql script scripttools testlib xml xmlpatterns

QT       -= gui

TARGET = tst_testsensorstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testsensorstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/IAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/IAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/release/ -lSimpleAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/debug/ -lSimpleAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/ -lSimpleAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/release/ -lSensorBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/debug/ -lSensorBase
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/ -lSensorBase

INCLUDEPATH += $$PWD/../../../app/device/SensorBase
DEPENDPATH += $$PWD/../../../app/device/SensorBase

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/release/ -lSensors
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/debug/ -lSensors
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/Sensors/ -lSensors

INCLUDEPATH += $$PWD/../../../app/device/Sensors
DEPENDPATH += $$PWD/../../../app/device/Sensors

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../../app/sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../../app/sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/release/ -lDeviceBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/debug/ -lDeviceBase
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/ -lDeviceBase

INCLUDEPATH += $$PWD/../../../app/device/DeviceBase
DEPENDPATH += $$PWD/../../../app/device/DeviceBase
