#-------------------------------------------------
#
# Project created by QtCreator 2014-06-26T11:22:11
#
#-------------------------------------------------

QT       += sql xml xmlpatterns

QT       -= gui

TARGET = IRepository
TEMPLATE = lib

DEFINES += IREPOSITORY_LIBRARY

SOURCES += irepository.cpp

HEADERS += irepository.h\
        irepository_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    IHGRS.db

BUILDTARGET=debug

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

#-------------------------------------------------
# copy test data to output dir
#-------------------------------------------------
win32{

    for(FILE,OTHER_FILES){
        SOURCEDATAPATH=$$PWD/$${FILE}
        DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$${FILE}
        QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEDATAPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)
    }

}
