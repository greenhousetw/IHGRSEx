#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T15:21:14
#
#-------------------------------------------------

QT       += sql script scripttools xml

QT       -= gui

TARGET = SQLiter
TEMPLATE = lib

DEFINES += SQLITER_LIBRARY

SOURCES += sqliter.cpp

HEADERS += sqliter.h\
        sqliter_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IRepository/release/ -lIRepository
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IRepository/debug/ -lIRepository
else:unix: LIBS += -L$$OUT_PWD/../IRepository/ -lIRepository

INCLUDEPATH += $$PWD/../IRepository
DEPENDPATH += $$PWD/../IRepository

OTHER_FILES += \
    Bosswin.db3
