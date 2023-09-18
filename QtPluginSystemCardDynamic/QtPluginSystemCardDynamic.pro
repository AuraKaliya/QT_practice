QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
DEFINES += QTPLUGINSYSTEMCARDDYNAMIC_LIBRARY

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS += /permissive-

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    plugincardmanager.cpp \
    qtpluginsystemcarddynamic.cpp

HEADERS += \
    PluginManagerInterface.h \
    QtPluginSystemCardDynamic_global.h \
    plugincardmanager.h \
    qtpluginsystemcarddynamic.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/../QtPluginSystemTest/lib/ -lQtPluginSystemMainAppStatic

INCLUDEPATH += $$PWD/../QtPluginSystemTest/include
DEPENDPATH += $$PWD/../QtPluginSystemTest/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../QtPluginSystemTest/lib/QtPluginSystemMainAppStatic.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../QtPluginSystemTest/lib/libQtPluginSystemMainAppStatic.a
