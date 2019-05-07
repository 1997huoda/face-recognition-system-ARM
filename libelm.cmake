project(elm)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
find_package(OpenMP)
find_package(Eigen3)

if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")
add_definitions(-fPIC -pthread -fopenmp)

include_directories(${OpenCV_INCLUDE_DIRS})
# INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/elm)


file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/elm/*.cpp)

# add_subdirectory(../native-dlib/dlib dlib_build)
link_directories(${OpenCV_LIBRARY_DIRS})

# add_executable(elm ${SRC})
add_library(libelm SHARED ${SRC})

target_link_libraries(libelm  ${OpenCV_LIBS})
# dlib::dlib

