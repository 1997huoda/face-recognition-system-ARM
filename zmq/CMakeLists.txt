project(com)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
set(CMAKE_C_COMPILER /usr/bin/gcc-5)
#add_definitions(-D_ENABLE_NEON  )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mcpu=cortex-a7 -mfpu=neon-vfpv4 -o3")


add_definitions(-fPIC )
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
FIND_PACKAGE(ZMQ REQUIRED)
#

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(zmq ${SRC})

target_link_libraries(zmq libzmq )


