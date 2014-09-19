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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/PluginHelper/release/ -lPluginHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/PluginHelper/debug/ -lPluginHelper
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/PluginHelper/ -lPluginHelper

INCLUDEPATH += $$PWD/../../../app/sharelibs/PluginHelper
DEPENDPATH += $$PWD/../../../app/sharelibs/PluginHelper

INCLUDEPATH += $$PWD/../../../app/core/Core
DEPENDPATH += $$PWD/../../../app/core/Core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/core/Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/core/Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../../../../../app/core/Core/ -lCore

INCLUDEPATH += $$PWD/../../../app/device/Hardware
DEPENDPATH += $$PWD/../../../app/device/Hardware

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Hardware/release/ -lHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Hardware/debug/ -lHardware
else:unix: LIBS += -L$$OUT_PWD/../../../../../app/device/Hardware/ -lHardware

INCLUDEPATH += $$PWD/../../../app/device/Tranceiver
DEPENDPATH += $$PWD/../../../app/device/Tranceiver

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Tranceiver/release/ -lTranceiver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/Tranceiver/debug/ -lTranceiver
else:unix: LIBS += -L$$OUT_PWD/../../../../../app/device/Hardware/ -lTranceiver

INCLUDEPATH += $$PWD/../../../app/device/TrancieverLoader
DEPENDPATH += $$PWD/../../../app/device/TrancieverLoader

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/TrancieverLoader/release/ -lTrancieverLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/TrancieverLoader/debug/ -lTrancieverLoader
else:unix: LIBS += -L$$OUT_PWD/../../../../../app/device/TrancieverLoader/ -lTrancieverLoader

#------------------------------------------------------------------------
# copy needed dll
#-------------------------------------------------------------------------
win32{

# 1. copy IHardware.dll
FILENAME=Hardware.dll
SOURCEPATH=../../../app/device/Hardware/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 2. copy SensorUnit.dll
FILENAME=SensorUnit.dll
SOURCEPATH=../../../app/device/SensorUnit/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 3. copy SensorPlugInLoader.dll
FILENAME=SensorPlugInLoader.dll
SOURCEPATH=../../../app/device/SensorPlugInLoader/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 4. copy IDeviceFactory.dll
FILENAME=IDeviceFactory.dll
SOURCEPATH=../../../app/device/IDeviceFactory/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 5. copy PluginHelper.dll PluginHelper
FILENAME=PluginHelper.dll
SOURCEPATH=../../../app/sharelibs/PluginHelper/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 6. copy CommonVariables.dll
FILENAME=CommonVariables.dll
SOURCEPATH=../../../app/sharelibs/CommonVariables/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 7. copy Core.dll
FILENAME=Core.dll
SOURCEPATH=../../../app/core/Core/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 8. copy Tranceiver.dll
FILENAME=Tranceiver.dll
SOURCEPATH=../../../app/device/Tranceiver/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 8. copy Tranceiver.dll
FILENAME=TrancieverLoader.dll
SOURCEPATH=../../../app/device/TrancieverLoader/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

}
