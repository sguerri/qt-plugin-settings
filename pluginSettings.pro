QT -= gui
QT += widgets

TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++17

VERSION = 0.0.1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PSettings.cpp \
    PSettingsData.cpp \
    PSettingsPage.cpp

HEADERS += \
    PSettings.h \
    PSettingsData.h \
    PSettingsPage.h

FORMS += \
    PSettingsPage.ui

TRANSLATIONS += \
    i18n/pluginSettings_en_US.ts \
    i18n/pluginSettings_fr_FR.ts

RESOURCES += \
    pluginSettings.qrc

DISTFILES += \
    LICENSE \
    README.md \
    TODO.md

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


