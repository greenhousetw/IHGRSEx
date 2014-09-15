#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T18:03:39
#
#-------------------------------------------------

QT       += sql script xml xmlpatterns
CONFIG   += plugin
QT       -= gui

TARGET = SensorRoot
TEMPLATE = lib

DEFINES += SENSORROOT_LIBRARY

SOURCES += sensorroot.cpp

HEADERS += sensorroot.h\
        sensorroot_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

OTHER_FILES += \
    info.json
