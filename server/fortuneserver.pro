
HEADERS       = server.h
SOURCES       = server.cpp \
                main.cpp
QT           += network
QT           += sql
QT           -= gui
CONFIG   += console
CONFIG   -= app_bundle
# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS fortuneserver.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
INSTALLS += target sources

symbian {
    TARGET.UID3 = 0xA000E406
    include($$PWD/../../symbianpkgrules.pri)
    TARGET.CAPABILITY = "NetworkServices ReadUserData"
    TARGET.EPOCHEAPSIZE = 0x20000 0x2000000
}
maemo5: include($$PWD/../../maemo5pkgrules.pri)
contains(MEEGO_EDITION,harmattan): include($$PWD/../../harmattanpkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
contains(MEEGO_EDITION,harmattan): warning(This example might not fully work on Harmattan platform)
simulator: warning(This example might not fully work on Simulator platform)


