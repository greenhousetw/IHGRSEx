#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T13:07:31
#
#-------------------------------------------------

QT       -= gui

TARGET = NotifyPackage
TEMPLATE = lib

DEFINES += NOTIFYPACKAGE_LIBRARY

SOURCES += notifypackage.cpp

HEADERS += notifypackage.h\
        notifypackage_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../CommonVariables
DEPENDPATH += $$PWD/../CommonVariables
