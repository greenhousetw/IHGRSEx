#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T15:14:17
#
#-------------------------------------------------

QT       += sql script scripttools testlib xml xmlpatterns

QT       -= gui

TARGET = tst_testsensorstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testsensorstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

BUILDTARGET=debug

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/IAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/IAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/release/ -lSimpleAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/debug/ -lSimpleAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/ -lSimpleAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/release/ -lSensorBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/debug/ -lSensorBase
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/SensorBase/ -lSensorBase

INCLUDEPATH += $$PWD/../../../app/device/SensorBase
DEPENDPATH += $$PWD/../../../app/device/SensorBase

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/release/ -lSensors
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Sensors/debug/ -lSensors
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/Sensors/ -lSensors

INCLUDEPATH += $$PWD/../../../app/device/Sensors
DEPENDPATH += $$PWD/../../../app/device/Sensors

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../../app/sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../../app/sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/release/ -lDeviceBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/debug/ -lDeviceBase
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/DeviceBase/ -lDeviceBase

INCLUDEPATH += $$PWD/../../../app/device/DeviceBase
DEPENDPATH += $$PWD/../../../app/device/DeviceBase

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/release/ -lControlHardwareManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/debug/ -lControlHardwareManager
else:unix: LIBS += -L$$OUT_PWD/../../../app/device/ControlHardwareManager/ -lControlHardwareManager

INCLUDEPATH += $$PWD/../../../app/device/ControlHardwareManager
DEPENDPATH += $$PWD/../../../app/device/ControlHardwareManager


#------------------------------------------------------------------------
# copy needed dll
#-------------------------------------------------------------------------
win32{

# 1. copy SensorUnit.dll
FILENAME=Hardware.dll
SOURCEPATH=../../../app/device/Hardware/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy IHardware.dll
FILENAME=SensorUnit.dll
SOURCEPATH=../../../app/device/SensorUnit/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)


#[Share library portion]
# 1. copy XmlHelper.dll
# FILENAME=XmlHelper.dll
# SOURCEPATH=../../../app/sharelibs/XmlHelper/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy CommonVariables.dll
FILENAME=CommonVariables.dll
SOURCEPATH=../../../app/sharelibs/CommonVariables/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 3. copy NotifyPackage.dll
# FILENAME=NotifyPackage.dll
# SOURCEPATH=../../../app/sharelibs/NotifyPackage/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

#[Algorithm portion]
# 1. copy IAlgorithm.dll
# FILENAME=IAlgorithm.dll
# SOURCEPATH=../../../app/algorithms/IAlgorithm/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy SimpleAlgorithm.dll
# FILENAME=SimpleAlgorithm.dll
#SOURCEPATH=../../../app/algorithms/SimpleAlgorithm/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

#[Device portion]
# 1. copy SensorBase.dll
# FILENAME=SensorBase.dll
# SOURCEPATH=../../../app/device/SensorBase/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy Sensors.dll
# FILENAME=Sensors.dll
# SOURCEPATH=../../../app/device/sensors/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 3. copy DeviceBase.dll
# FILENAME=DeviceBase.dll
# SOURCEPATH=../../../app/device/DeviceBase/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 4. copy ControlHardwareManager.dll
# FILENAME=ControlHardwareManager.dll
# SOURCEPATH=../../../app/device/ControlHardwareManager/$$BUILDTARGET/$$FILENAME
# DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
# QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

}
