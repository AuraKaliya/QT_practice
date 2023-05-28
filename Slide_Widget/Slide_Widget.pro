QT       += core gui
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
CONFIG += c++17

 QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus

CONFIG += c++17
 QMAKE_CXXFLAGS += -std=c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
win32: {
    QMAKE_CXXFLAGS += /permissive-
}

MSVC: {
    QMAKE_CXXFLAGS += /permissive-
}

RESOURCES += \
    image.qrc
