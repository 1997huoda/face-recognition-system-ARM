cmake_minimum_required(VERSION 3.7)
project(Qt)
set(TARGET_NAME Qt)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT Core Gui Widgets Network DBus Sql)
find_package(Qt5 REQUIRED ${QT})

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")

add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
qt5_use_modules(${TARGET_NAME} ${QT})
