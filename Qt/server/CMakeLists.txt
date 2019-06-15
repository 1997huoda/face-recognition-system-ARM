cmake_minimum_required(VERSION 3.7)
project(Qt)
set(TARGET_NAME Qt)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set(QT Core Gui Widgets Network DBus Sql)
# find_package(Qt5 REQUIRED ${QT})
find_package(Qt5 COMPONENTS Core Gui  REQUIRED)
find_package(Qt5 REQUIRED Widgets)
# find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(../../libzmq)
include(../../liblibzmq.cmake)

file(GLOB_RECURSE SOURCES main.cpp mainwindow.cpp)
file(GLOB_RECURSE HEADERS mainwindow.h)
file(GLOB_RECURSE FORMS mainwindow.ui)
# file(GLOB_RECURSE RESOURCES *.qrc)

add_executable(${TARGET_NAME} ${SOURCES}  ${FORMS} )
# ${RESOURCES}  ${HEADERS}
target_link_libraries(${TARGET_NAME} libzmq Qt5::Core Qt5::Gui  Qt5::Widgets)
# qt5_use_modules(${TARGET_NAME} ${QT})
set(CMAKE_INSTALL_PREFIX /usr)
