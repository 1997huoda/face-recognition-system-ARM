project(com)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)




add_definitions(-fPIC )
find_package(OpenCV REQUIRED)
find_package(OpenMP)

cmake_policy(SET CMP0028 OLD)
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
FIND_PACKAGE(ZMQ REQUIRED)
#

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")

INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})


file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(zmq ${SRC})
# add_library(zmq SHARED ${SRC})

target_link_libraries(zmq libzmq ${ZMQ_LIBRARIES}  ${OpenCV_LIBS})

# file(COPY ../native/shape_predictor_68_face_landmarks.dat DESTINATION ../build)

