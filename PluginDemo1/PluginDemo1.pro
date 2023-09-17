QT += widgets

TEMPLATE = lib
DEFINES += PLUGINDEMO1_LIBRARY

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS += /permissive-
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    form.cpp \
    plugindemo1.cpp

HEADERS += \
    PluginDemo1_global.h \
    PluginInterface.h \
    form.h \
    plugindemo1.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui
