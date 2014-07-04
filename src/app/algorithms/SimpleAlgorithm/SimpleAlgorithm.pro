#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T15:34:49
#
#-------------------------------------------------

QT       += sql script scripttools xml xmlpatterns core

QT       -= gui

TARGET = SimpleAlgorithm
TEMPLATE = lib

DEFINES += SIMPLEALGORITHM_LIBRARY

SOURCES += simplealgorithm.cpp

HEADERS += simplealgorithm.h\
        simplealgorithm_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

PROJECTNAME=TestSimpleSectionAlgorithm
message(PROJECT NAME=$$PROJECTNAME)
message(PRO Path=$$_PRO_FILE_PWD_)
message(PROJECT SOURCE CODE PATH=$$PWD)
message(OUTPUT Directory Path=$$OUT_PWD)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithm/release/ -lIAlgorithm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IAlgorithm/debug/ -lIAlgorithm
else:unix: LIBS += -L$$OUT_PWD/../IAlgorithm/ -lIAlgorithm

INCLUDEPATH += $$PWD/../IAlgorithm
DEPENDPATH += $$PWD/../IAlgorithm

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/XmlHelper/release/ -lXmlHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/XmlHelper/debug/ -lXmlHelper
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/XmlHelper/ -lXmlHelper

INCLUDEPATH += $$PWD/../../sharelibs/XmlHelper
DEPENDPATH += $$PWD/../../sharelibs/XmlHelper

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/release/ -lCommonVariables
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/debug/ -lCommonVariables
else:unix: LIBS += -L$$OUT_PWD/../../sharelibs/CommonVariables/ -lCommonVariables

INCLUDEPATH += $$PWD/../../sharelibs/CommonVariables
DEPENDPATH += $$PWD/../../sharelibs/CommonVariables

OTHER_FILES += \
    Algorithm.Simple.Setup.xml \
    tomato.js


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

