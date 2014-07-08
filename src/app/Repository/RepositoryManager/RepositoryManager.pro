#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T17:28:07
#
#-------------------------------------------------

QT       += sql xml xmlpatterns

QT       -= gui

TARGET = RepositoryManager
TEMPLATE = lib

DEFINES += REPOSITORYMANAGER_LIBRARY

SOURCES += repositorymanager.cpp

HEADERS += repositorymanager.h\
        repositorymanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IRepository/release/ -lIRepository
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IRepository/debug/ -lIRepository
else:unix: LIBS += -L$$OUT_PWD/../IRepository/ -lIRepository

INCLUDEPATH += $$PWD/../IRepository
DEPENDPATH += $$PWD/../IRepository

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SQLiter/release/ -lSQLiter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SQLiter/debug/ -lSQLiter
else:unix: LIBS += -L$$OUT_PWD/../SQLiter/ -lSQLiter

INCLUDEPATH += $$PWD/../SQLiter
DEPENDPATH += $$PWD/../SQLiter
