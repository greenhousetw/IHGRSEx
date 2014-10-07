#-------------------------------------------------
#
# Project created by QtCreator 2014-09-11T15:21:40
#
#-------------------------------------------------

QT       -= gui
QT       += sql
CONFIG +=plugin
TARGET = Core
TEMPLATE = lib
DEFINES += CORE_LIBRARY

SOURCES += core.cpp \
    datapacket.cpp \
    coreone.cpp

HEADERS += core.h\
        core_global.h \
    datapacket.h \
    coreone.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/release/ -lNotifyPackage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/debug/ -lNotifyPackage
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/NotifyPackage/ -lNotifyPackage

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables
