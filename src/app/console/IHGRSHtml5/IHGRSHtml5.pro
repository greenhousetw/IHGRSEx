greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets sql

# Add more folders to ship with the application, here
folder_01.source = html
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

BUILDTARGET=debug

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/ -lCommonVariables

#INCLUDEPATH += $$PWD/../../../app/sharelibs/CommonVariables
#DEPENDPATH += $$PWD/../../../app/sharelibs/CommonVariables

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

#-------------------------------------------------
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonLib/release/ -lCommonLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonLib/debug/ -lCommonLib
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonLib/ -lCommonLib

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

# 12. copy tranceieverconfig.json
FILENAME=tranceieverconfig.json
SOURCEPATH=../../../../../../src/app/device/DeviceManager/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 13. copy NotifyPackage.dll
FILENAME=NotifyPackage.dll
SOURCEPATH=../../../app/sharelibs/NotifyPackage/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# copy ihgrs.qserialport.json
FILENAME=ihgrs.qserialport.json
SOURCEPATH=../../../../../../src/app/device/Tranceiver/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)


# 13. copy qextserialportd.dll
FILENAME=qextserialportd.dll
SOURCEPATH=../../../app/device/qextserialport/build/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 14. copy IRepository.dll
FILENAME=IRepository.dll
SOURCEPATH=../../../app/Repository/IRepository/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 15. copy IRepositoryManager.dll
FILENAME=IRepositoryManager.dll
SOURCEPATH=../../../app/Repository/IRepositoryManager/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 16. copy SQLiter.dll
FILENAME=SQLiter.dll
SOURCEPATH=../../../app/Repository/SQLiter/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 17. copy RepositoryManager.dll
FILENAME=RepositoryManager.dll
SOURCEPATH=../../../app/Repository/RepositoryManager/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 19. copy tranceieverconfig.json
FILENAME=repositoryconfig.json
SOURCEPATH=../../../../../../src/app/device/DeviceManager/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)


# 20. copy Bosswin.db3
FILENAME=Bosswin.db3
SOURCEPATH=../../../../../../src/app/Repository/SQLiter/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)

# 21. copy CommonLib.dll
FILENAME=CommonLib.dll
SOURCEPATH=../../../app/sharelibs/CommonLib/$$BUILDTARGET/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$$FILENAME
QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)
}

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()
