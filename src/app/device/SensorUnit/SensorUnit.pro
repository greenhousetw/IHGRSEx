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

SOURCES += sensorunit.cpp

HEADERS += sensorunit.h\
        sensorunit_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/release/ -lSensorRoot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/debug/ -lSensorRoot
else:unix: LIBS += -L$$OUT_PWD/../SensorRoot/ -lSensorRoot

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
