#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T18:22:01
#
#-------------------------------------------------

QT       += network sql script xml xmlpatterns
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/release/ -lPluginHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/debug/ -lPluginHelper
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/ -lPluginHelper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/release/ -lNotifyPackage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/debug/ -lNotifyPackage
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lNotifyPackage

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/AlgorithmLoader/release/ -lAlgorithmLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/AlgorithmLoader/debug/ -lAlgorithmLoader
else:unix: LIBS += -L$$OUT_PWD/../../algorithms/AlgorithmLoader/ -lAlgorithmLoader

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithmFactory/release/ -lIAlgorithmFactory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithmFactory/debug/ -lIAlgorithmFactory
else:unix: LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithmFactory/ -lIAlgorithmFactory

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../algorithms/AlgorithmLoader
DEPENDPATH += $$PWD/../../algorithms/AlgorithmLoader



unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
