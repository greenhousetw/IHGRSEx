#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T17:49:54
#
#-------------------------------------------------

QT       += sql script xml xmlpatterns

QT       -= gui

TARGET = Tranceiver
TEMPLATE = lib

DEFINES += TRANCEIVER_LIBRARY

SOURCES += tranceiver.cpp

HEADERS += tranceiver.h\
        tranceiver_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

INCLUDEPATH += $$PWD/../../core/Core
DEPENDPATH += $$PWD/../../core/Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../core/Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../core/Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../../core/Core/ -lCore

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/release/ -lSensorRoot
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SensorRoot/debug/ -lSensorRoot
#else:unix: LIBS += -L$$OUT_PWD/../SensorRoot/ -lSensorRoot

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../device/qextserialport/build/ -lqextserialport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../device/qextserialport/build/ -lqextserialportd
else:unix: LIBS += -L$$OUT_PWD/../../device/qextserialport/build/ -lqextserialport

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
