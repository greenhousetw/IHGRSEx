greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
folder_01.source = html
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

BuildTarget=debug

CONFIG(release, debug|release){
    $$BuildTarget=release
}


# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

#-------------------------------------------------
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

#------------------------------------------------------------------------
# copy needed dll
#-------------------------------------------------------------------------
win32{
#-------------------------------------------------------------------------
#[Share library portion]
#-------------------------------------------------------------------------
# 1. copy XmlHelper.dll
FILENAME=XmlHelper.dll
SOURCEPATH=../../../app/sharelibs/XmlHelper/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/sharelibs/
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 2. copy CommonVariables.dll
FILENAME=CommonVariables.dll
SOURCEPATH=../../../app/sharelibs/CommonVariables/$$BuildTarget/$$FILENAME
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 3. copy NotifyPackage.dll
FILENAME=NotifyPackage.dll
SOURCEPATH=../../../app/sharelibs/NotifyPackage/$$BuildTarget/$$FILENAME
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

#-------------------------------------------------------------------------
#[Share algorithm portion]
#-------------------------------------------------------------------------
# 1. copy IAlgorithm.dll
FILENAME=IAlgorithm.dll
SOURCEPATH=../../../app/algorithms/IAlgorithm/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/algorithms/
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 2. copy SimpleAlgorithm.dll
FILENAME=SimpleAlgorithm.dll
SOURCEPATH=../../../app/algorithms/SimpleAlgorithm/$$BuildTarget/$$FILENAME
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
FILENAME=Algorithm.Simple.Setup.xml
SOURCEPATH=../../../app/algorithms/SimpleAlgorithm/$$BuildTarget/$$FILENAME
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
FILENAME=tomato.js
SOURCEPATH=../../../app/algorithms/SimpleAlgorithm/$$BuildTarget/$$FILENAME
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

#-------------------------------------------------------------------------
#[Share devices portion]
#-------------------------------------------------------------------------
# 1. copy ControlHardwareManager.dll
FILENAME=ControlHardwareManager.dll
SOURCEPATH=../../../app/device/ControlHardwareManager/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/device/
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
FILENAME=HardwareControlTable.js
SOURCEPATH=../../../app/device/ControlHardwareManager/$$BuildTarget/$$FILENAME
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 2. copy DeviceBase.dll
FILENAME=DeviceBase.dll
SOURCEPATH=../../../app/device/DeviceBase/$$BuildTarget/$$FILENAME
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 3. copy SensorBase.dll
FILENAME=SensorBase.dll
SOURCEPATH=../../../app/device/SensorBase/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/device/
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 4. copy Sensors.dll
FILENAME=Sensors.dll
SOURCEPATH=../../../app/device/Sensors/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/device/
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
}

#-------------------------------------------------------------------------
#[Share repository portion]
#-------------------------------------------------------------------------
# 1. copy IRepository.dll
FILENAME=IRepository.dll
SOURCEPATH=../../../app/Repository/IRepository/$$BuildTarget/$$FILENAME
DESTIDATAPATH=$$OUT_PWD/$$BuildTarget/repository/
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
FILENAME=IHGRS.db
SOURCEPATH=../../../app/Repository/IRepository/$$BuildTarget/$$FILENAME
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))

# 2. copy SQLiter.dll
FILENAME=SQLiter.dll
SOURCEPATH=../../../app/Repository/SQLiter/$$BuildTarget/$$FILENAME
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))


# 3. copy RepositoryManager.dll
FILENAME=RepositoryManager.dll
SOURCEPATH=../../../app/Repository/RepositoryManager/$$BuildTarget/$$FILENAME
#QMAKE_POST_LINK +=$$quote(mkdir $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t))
QMAKE_POST_LINK +=$$quote(xcopy "$$shell_path($$SOURCEPATH)" $$shell_path($$DESTIDATAPATH) /e /c /i /y $$escape_expand(\\n\\t))
