QT -= gui
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS += /permissive-
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    cardmanager.cpp \
    qtpluginsystemmainappstatic.cpp \
    uimainwidget.cpp \
    uiwidget.cpp

HEADERS += \
    PluginInterface.h \
    card.h \
    cardmanager.h \
    manager.h \
    qtpluginsystemmainappstatic.h \
    uimainwidget.h \
    uiwidget.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

QT += widgets
