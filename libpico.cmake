project(pico)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
# find_package(OpenMP)
# if(OPENMP_FOUND)
#     message("OPENMP FOUND")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
# endif()
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")
add_definitions(-fPIC  -fopenmp)

#include_directories(../src)
#include_directories(../native)
# include_directories(..)
include_directories(${OpenCV_INCLUDE_DIRS}/native)
include_directories(${OpenCV_INCLUDE_DIRS}/src)

include(${CMAKE_CURRENT_LIST_DIR}/libsrc.cmake)

link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/native/*.cpp)

#add_executable(pico ${SRC})
add_library(libpico SHARED ${SRC})
# INSTALL(TARGETS libpico
# 	#        RUNTIME DESTINATION bin
# 	LIBRARY DESTINATION /usr/local/lib
# 	#        ARCHIVE DESTINATION libstatic
# 	)
target_link_libraries(libpico libfacedetection ${OpenCV_LIBS})

# file(COPY ${CMAKE_CURRENT_LIST_DIR}/test.hpp DESTINATION /usr/local/include)
