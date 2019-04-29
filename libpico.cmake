project(pico)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
find_package(OpenMP)

if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")
add_definitions(-fPIC -pthread -fopenmp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/native)
# include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

include(${CMAKE_CURRENT_LIST_DIR}/libYu.cmake)

link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/native/*.cpp)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/native/dlib dlib_build)

#add_executable(pico ${SRC})
add_library(libpico SHARED ${SRC})

target_link_libraries(libpico libfacedetection dlib::dlib ${OpenCV_LIBS})
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
