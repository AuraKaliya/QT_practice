QT -= gui

TEMPLATE = lib
DEFINES += ENGINEPLUGINTEST_LIBRARY

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS += /permissive-
TARGET = TestPlugin.engine
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DATA/baseClass/basicdata.cpp \
    DATA/baseClass/clicklabel.cpp \
    DATA/baseClass/componentobject.cpp \
    DATA/baseClass/dynamicitem.cpp \
    DATA/baseClass/engineplugin.cpp \
    DATA/baseClass/gamedemo.cpp \
    DATA/baseClass/gameobject.cpp \
    DATA/baseClass/gameobjectchilditem.cpp \
    DATA/baseClass/gameobjectitem.cpp \
    DATA/baseClass/instructionobject.cpp \
    DATA/baseClass/map2ddynamicitem.cpp \
    DATA/baseClass/map2ditem.cpp \
    DATA/baseClass/mapitem.cpp \
    DATA/baseClass/pixsource.cpp \
    DATA/baseClass/sourcemetadata.cpp \
    DATA/baseClass/systemobject.cpp \
    DATA/baseClass/uiwidget.cpp \
    DATA/constvalue.cpp \
    DATA/eigenstyle.cpp \
    DATA/enginestate.cpp \
    DATA/enginestyle.cpp \
    DATA/instructioncontext.cpp \
    engineplugintest.cpp \


HEADERS += \
    DATA/baseClass/basicdata.h \
    DATA/baseClass/clicklabel.h \
    DATA/baseClass/componentobject.h \
    DATA/baseClass/dynamicitem.h \
    DATA/baseClass/engineplugin.h \
    DATA/baseClass/gamedemo.h \
    DATA/baseClass/gameobject.h \
    DATA/baseClass/gameobjectchilditem.h \
    DATA/baseClass/gameobjectitem.h \
    DATA/baseClass/instructionobject.h \
    DATA/baseClass/map2ddynamicitem.h \
    DATA/baseClass/map2ditem.h \
    DATA/baseClass/mapitem.h \
    DATA/baseClass/pixsource.h \
    DATA/baseClass/sourcemetadata.h \
    DATA/baseClass/systemobject.h \
    DATA/baseClass/uiwidget.h \
    DATA/constvalue.h \
    DATA/eigenstyle.h \
    DATA/enginestate.h \
    DATA/enginestyle.h \
    DATA/instructioncontext.h \
    EnginePluginTest_global.h \
    TOOL/template/Factory.hpp \
    TOOL/template/Registor.hpp \
    TOOL/template/ThreadPool.hpp \
    engineplugintest.h \


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
