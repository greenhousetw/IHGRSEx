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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/release/ -lSensors
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/debug/ -lSensors
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/Sensors/ -lSensors

INCLUDEPATH += $$PWD/../../../app/device/Sensors
DEPENDPATH += $$PWD/../../../app/device/Sensors

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/NotifyPackage/release/ -lNotifyPackage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/NotifyPackage/debug/ -lNotifyPackage
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/NotifyPackage/ -lNotifyPackage

INCLUDEPATH += $$PWD/../../../app/sharelibs/NotifyPackage
DEPENDPATH += $$PWD/../../../app/sharelibs/NotifyPackage


#------------------------------------------------------------------------
# copy needed dll
#-------------------------------------------------------------------------
win32{

#[Share library portion]
# 1. copy XmlHelper.dll
FILENAME=XmlHelper.dll
SOURCEPATH=../../../app/sharelibs/XmlHelper/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy CommonVariables.dll
FILENAME=CommonVariables.dll
SOURCEPATH=../../../app/sharelibs/CommonVariables/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 3. copy NotifyPackage.dll
FILENAME=NotifyPackage.dll
SOURCEPATH=../../../app/sharelibs/NotifyPackage/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

#[Algorithm portion]
# 1. copy IAlgorithm.dll
FILENAME=IAlgorithm.dll
SOURCEPATH=../../../app/algorithms/IAlgorithm/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy SimpleAlgorithm.dll
FILENAME=SimpleAlgorithm.dll
SOURCEPATH=../../../app/algorithms/SimpleAlgorithm/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

#[Device portion]
# 1. copy SensorBase.dll
FILENAME=SensorBase.dll
SOURCEPATH=../../../app/device/SensorBase/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy Sensors.dll
FILENAME=Sensors.dll
SOURCEPATH=../../../app/device/sensors/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 3. copy DeviceBase.dll
FILENAME=DeviceBase.dll
SOURCEPATH=../../../app/device/DeviceBase/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 4. copy ControlHardwareManager.dll
FILENAME=ControlHardwareManager.dll
SOURCEPATH=../../../app/device/ControlHardwareManager/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

}
