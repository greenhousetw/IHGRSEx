#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T18:22:01
#
#-------------------------------------------------

QT       += network sql script xml xmlpatterns
CONFIG   +=plugin
QT       -= gui

TARGET = SensorUnit
TEMPLATE = lib

DEFINES += SENSORUNIT_LIBRARY

SOURCES += \
    sensor.cpp

HEADERS +=\
        sensorunit_global.h \
    sensor.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/release/ -lSensorRoot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/debug/ -lSensorRoot
else:unix: LIBS += -L$$OUT_PWD/../SensorRoot/ -lSensorRoot

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json