DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE405E2BA

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian

SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui

QT += network
CONFIG += mobility
MOBILITY += location
MOBILITY += systeminfo
MOBILITY += messaging


symbian {
    include($$PWD/../../symbianpkgrules.pri)
    TARGET.CAPABILITY = "NetworkServices ReadUserData WriteUserData Location"
    TARGET.EPOCHEAPSIZE = 0x20000 0x2000000
}

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()




