project(elm)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(Eigen3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -O3")
add_definitions(-fPIC -fopenmp)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/elm)
include_directories(${CMAKE_CURRENT_LIST_DIR}/new)

file(GLOB ELMSRC ${CMAKE_CURRENT_LIST_DIR}/elm/*.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/libnew.cmake)

# link_directories(${OpenCV_LIBRARY_DIRS})
# add_executable(elm ${SRC})
add_library(libelm SHARED ${ELMSRC})
# INSTALL(TARGETS libelm
# 	#        RUNTIME DESTINATION bin
# 	LIBRARY DESTINATION /usr/local/lib
# 	#        ARCHIVE DESTINATION libstatic
# 	)
target_link_libraries(libelm  libnew ${OpenCV_LIBS})
# dlib::dlib

file(COPY ${CMAKE_CURRENT_LIST_DIR}/elm/elm.hpp DESTINATION /usr/local/include)
