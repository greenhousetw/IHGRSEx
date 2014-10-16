#-------------------------------------------------
#
# Project created by QtCreator 2014-09-20T15:23:02
#
#-------------------------------------------------

QT       += qml quick sql script scripttools xml xmlpatterns core
CONFIG       += plugin
QT       -= gui

TARGET = DeviceManager
TEMPLATE = lib

DEFINES += DEVICEMANAGER_LIBRARY

SOURCES += devicemanager.cpp \
    devicemangerhandler.cpp

HEADERS += devicemanager.h\
        devicemanager_global.h \
    devicemangerhandler.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../Hardware/ -lHardware

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/release/ -lPluginHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/debug/ -lPluginHelper
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/PluginHelper/ -lPluginHelper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../core/Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../core/Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../../core/Core/ -lCore

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../core/Core
DEPENDPATH += $$PWD/../../core/Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonLib/release/ -lCommonLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonLib/debug/ -lCommonLib
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonLib/ -lCommonLib

INCLUDEPATH += $$PWD/../../sharelibs/CommonLib
DEPENDPATH += $$PWD/../../sharelibs/CommonLib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json \
    config.json \
    sensorconfig.json \
    tranceieverconfig.json \
    repositoryconfig.json
