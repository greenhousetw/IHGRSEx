#-------------------------------------------------
#
# Project created by QtCreator 2014-06-20T17:32:45
#
#-------------------------------------------------

QT       += testlib xml xmlpatterns

QT       -= gui

TARGET = tst_testxmlhlpertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_testxmlhlpertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OTHER_FILES += UnitTest.XmlData.xml

BUILDTARGET=debug

CONFIG(release, debug|release) {
    $$BUILDTARGET=release
}


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/XmlHelper/release/ -lXmlHelper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../app/sharelibs/XmlHelper/debug/ -lXmlHelper
else:unix: LIBS += -L$$OUT_PWD/../../../app/sharelibs/XmlHelper/ -lXmlHelper

INCLUDEPATH += $$PWD/../../../app/sharelibs/XmlHelper
DEPENDPATH += $$PWD/../../../app/sharelibs/XmlHelper

win32{

    for(FILE,OTHER_FILES){
        DESTIDATAPATH=$$OUT_PWD/$$BUILDTARGET/$${FILE}
        SOURCEDATAPATH=$$PWD/$${FILE}
        QMAKE_POST_LINK +=$$QMAKE_COPY $$shell_path($$SOURCEDATAPATH) $$shell_path($$DESTIDATAPATH) $$escape_expand(\\n\\t)
    }

}

OTHER_FILES += \
    UnitTest.XmlData.xml
