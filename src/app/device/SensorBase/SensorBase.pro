#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T13:28:35
#
#-------------------------------------------------

QT       -= gui

TARGET = SensorBase
TEMPLATE = lib

DEFINES += SENSORBASE_LIBRARY

SOURCES += sensorbase.cpp

HEADERS += sensorbase.h\
        sensorbase_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
