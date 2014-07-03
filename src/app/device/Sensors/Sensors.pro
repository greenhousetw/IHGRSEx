#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T14:10:48
#
#-------------------------------------------------

QT       += qml sql script scripttools xml xmlpatterns

QT       -= gui

TARGET = Sensors
TEMPLATE = lib

DEFINES += SENSORS_LIBRARY

SOURCES += \
    sensorcontroller.cpp \
    sensor.cpp

HEADERS +=\
        sensors_global.h \
    sensorcontroller.h \
    sensor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/release/ -lNotifyPackage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/debug/ -lNotifyPackage
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/ -lNotifyPackage

INCLUDEPATH += $$PWD/../../sharelibs/NotifyPackage
DEPENDPATH += $$PWD/../../sharelibs/NotifyPackage

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../algorithms/IAlgorithm
DEPENDPATH += $$PWD/../../algorithms/IAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/SimpleAlgorithm/release/ -lSimpleAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/SimpleAlgorithm/debug/ -lSimpleAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../algorithms/SimpleAlgorithm/ -lSimpleAlgorithm

INCLUDEPATH += $$PWD/../../algorithms/SimpleAlgorithm
DEPENDPATH += $$PWD/../../algorithms/SimpleAlgorithm
