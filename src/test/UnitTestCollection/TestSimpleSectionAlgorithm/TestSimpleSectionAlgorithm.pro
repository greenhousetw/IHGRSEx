#-------------------------------------------------
#
# Project created by QtCreator 2014-06-23T14:43:18
#
#-------------------------------------------------

QT       += qml scripttools xml xmlpatterns testlib script
QT       -= gui

TARGET = tst_testsimplesectionalgorithmtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_testsimplesectionalgorithmtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

#-------------------------------------------------
# Show information about project's qmake
#-------------------------------------------------
PROJECTNAME=TestSimpleSectionAlgorithm
BUILDTARGET=debug
message(Qt version: $$[QT_VERSION])
message(PROJECT NAME=$$PROJECTNAME)
#message(PRO Path=$$_PRO_FILE_PWD_)
#message(PROJECT SOURCE CODE PATH=$$PWD)
message(OUTPUT Directory Path=$$OUT_PWD)

CONFIG(release, debug|release){
    $$BUILDTARGET=release
}

message(CURRENT CONFIG=$$BUILDTARGET)

#-------------------------------------------------
# set library link for IAlgorithm
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/IAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/IAlgorithm

#-------------------------------------------------
# set library link for SimpleAlgorithm
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/release/ -lSimpleAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/debug/ -lSimpleAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/ -lSimpleAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm

#-------------------------------------------------
# Other files
#-------------------------------------------------
OTHER_FILES += \
    Algorithm.Simple.Setup.xml \
    tomato.js

#-------------------------------------------------
# copy test data to output dir
#-------------------------------------------------
win32{

    for(FILE,OTHER_FILES){
        SOURCEDATAPATH=$$PWD/$${FILE}
        DESTIDATAPATH=$$OUT_PWD/$${FILE}
        QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEDATAPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)
    }

}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../../app/sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../../app/sharelibs/CommonVariables

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/release/ -lSimpleAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/debug/ -lSimpleAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/SimpleAlgorithm/ -lSimpleAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/SimpleAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../../../app/algorithms/IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../../../app/algorithms/IAlgorithm
DEPENDPATH += $$PWD/../../../app/algorithms/IAlgorithm

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
