HEADERS       = client.h
SOURCES       = client.cpp \
                main.cpp
QT           += network
CONFIG += mobility
MOBILITY += location
MOBILITY += systeminfo
MOBILITY += messaging
# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS fortuneclient.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
INSTALLS += target sources

symbian {
    include($$PWD/../../symbianpkgrules.pri)
    TARGET.CAPABILITY = "NetworkServices ReadUserData WriteUserData Location"
    TARGET.EPOCHEAPSIZE = 0x20000 0x2000000
}
maemo5: include($$PWD/../../maemo5pkgrules.pri)
contains(MEEGO_EDITION,harmattan): include($$PWD/../../harmattanpkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
contains(MEEGO_EDITION,harmattan): warning(This example might not fully work on Harmattan platform)
simulator: warning(This example might not fully work on Simulator platform)
