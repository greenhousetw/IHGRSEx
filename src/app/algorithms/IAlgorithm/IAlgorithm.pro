#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T13:38:05
#
#-------------------------------------------------

QT       -= gui

TARGET = IAlgorithm
TEMPLATE = lib

DEFINES += IALGORITHM_LIBRARY

SOURCES += ialgorithm.cpp

HEADERS += ialgorithm.h\
        ialgorithm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

PROJECTNAME=IAlgorithm
message(PROJECT NAME=$$PROJECTNAME)
message(PRO Path=$$_PRO_FILE_PWD_)
message(PROJECT SOURCE CODE PATH=$$PWD)
message(-L$$OUT_PWD/../../sharelibs/CommonVariables/)
