#-------------------------------------------------
#
# Project created by QtCreator 2014-06-24T14:50:55
#
#-------------------------------------------------

QT       += qml sql script scripttools xml xmlpatterns

QT       -= gui

TARGET = ControlHardwareManager
TEMPLATE = lib

DEFINES += CONTROLHARDWAREMANAGER_LIBRARY

SOURCES += controlhardwaremanager.cpp

HEADERS += controlhardwaremanager.h\
        controlhardwaremanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
