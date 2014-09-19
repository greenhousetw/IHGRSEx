#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T18:45:46
#
#-------------------------------------------------

QT       += sql script scripttools
CONFIG   += plugin
QT       -= gui

TARGET = TrancieverLoader
TEMPLATE = lib

DEFINES += TRANCIEVERLOADER_LIBRARY

SOURCES += trancieverloader.cpp

HEADERS += trancieverloader.h\
        trancieverloader_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/release/ -lIDeviceFactory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/debug/ -lIDeviceFactory
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/IDeviceFactory/ -lIDeviceFactory

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Tranceiver/release/ -lTranceiver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Tranceiver/debug/ -lTranceiver
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/Tranceiver/ -lTranceiver


unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    info.json
