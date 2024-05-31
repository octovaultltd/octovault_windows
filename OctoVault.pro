QT       += core gui network concurrent positioning qml quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OctoVault
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp

BUILDDIR =  $$OUT_PWD/tmp/
OBJECTS_DIR = $${BUILDDIR}
MOC_DIR = $${BUILDDIR}
RCC_DIR = $${BUILDDIR}
UI_DIR = $${BUILDDIR}

include(ui/ui.pri)
include(utils/utils.pri)
include(libs/libs.pri)
include(vpn/vpn.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += assets/assets.qrc

RC_ICONS = assets\logo.ico
macx:ICON = assets/logo.icns
