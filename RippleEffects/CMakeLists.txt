cmake_minimum_required(VERSION 3.14)

project(RippleEffects LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SOURCES "DATA/*.h" "DATA/*.cpp" "DATA/baseClass/*.h" "DATA/baseClass/*.cpp" "TOOL/*.cpp" "TOOL/template/*.hpp")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(RippleEffects SHARED
  RippleEffects_global.h
  rippleeffects.cpp
  rippleeffects.h
   ripple.cpp
   ripple.h
  ${SOURCES}

)

target_link_libraries(RippleEffects PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(RippleEffects PRIVATE RIPPLEEFFECTS_LIBRARY)
