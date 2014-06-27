#-------------------------------------------------
#
# Project created by QtCreator 2014-06-24T15:06:08
#
#-------------------------------------------------

QT       += sql script scripttools xml xmlpatterns testlib

QT       -= gui

TARGET = tst_testcontrolhardwaremanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testcontrolhardwaremanagertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

BUILDTARGET=debug

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/release/ -lControlHardwareManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/debug/ -lControlHardwareManager
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/ -lControlHardwareManager

INCLUDEPATH += $$PWD/../../../app/device/ControlHardwareManager
DEPENDPATH += $$PWD/../../../app/device/ControlHardwareManager

OTHER_FILES += \
    HardwareControlTable.js

win32{
    for(FILE,OTHER_FILES){
        SOURCEDATAPATH=$$PWD/$${FILE}
        DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$${FILE}
        QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEDATAPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)
    }
}
