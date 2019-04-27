cmake_minimum_required(VERSION 3.14)
PROJECT(transmit)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#list(APPEND CMAKE_MODULE_PATH "./cmake_modules")
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

add_definitions(-fPIC -pthread -fopenmp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_MODULE_PATH ./)
FIND_PACKAGE(ZMQ REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR})
set(LIBRARY ${ZMQ_LIBRARIES} ${OpenCV_LIBS})

# file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

#add executable file
ADD_EXECUTABLE(server ${CMAKE_CURRENT_LIST_DIR}/server.cpp)
ADD_EXECUTABLE(client ${CMAKE_CURRENT_LIST_DIR}/client.cpp)

add_library(libserver SHARED ${CMAKE_CURRENT_LIST_DIR}/server.cpp)
add_library(libclient SHARED ${CMAKE_CURRENT_LIST_DIR}/client.cpp)

target_link_libraries(server ${LIBRARY})
target_link_libraries(client ${LIBRARY})

#add link library
