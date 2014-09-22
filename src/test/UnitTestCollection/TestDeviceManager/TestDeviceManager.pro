#-------------------------------------------------
#
# Project created by QtCreator 2014-09-22T12:53:20
#
#-------------------------------------------------

QT       += sql script xml xmlpatterns testlib

QT       -= gui

TARGET = tst_testdevicemanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testdevicemanagertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

BUILDTARGET=debug

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../../app/sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../../app/sharelibs/CommonVariables

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

INCLUDEPATH += $$PWD/../../../app/device/DeviceManager
DEPENDPATH += $$PWD/../../../app/device/DeviceManager

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceManager/release/ -lDeviceManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/device/DeviceManager/debug/ -lDeviceManager
else:unix: LIBS += -L$$OUT_PWD/../../../../../app/device/DeviceManager/ -lDeviceManager

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

# 9. copy TranceiverLoader.dll
FILENAME=TrancieverLoader.dll
SOURCEPATH=../../../app/device/TrancieverLoader/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 9. copy DeviceManager.dll
FILENAME=DeviceManager.dll
SOURCEPATH=../../../app/device/DeviceManager/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 10. copy config.json
FILENAME=config.json
SOURCEPATH=../../../../../../src/app/device/DeviceManager/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 11. copy sensorconfig.json
FILENAME=sensorconfig.json
SOURCEPATH=../../../../../../src/app/device/DeviceManager/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

}
