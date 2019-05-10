project(new)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
set(CMAKE_C_COMPILER /usr/bin/gcc-5)
 add_definitions(-D_ENABLE_NEON  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mcpu=cortex-a7 -mfpu=neon-vfpv4 -o3")

# find_package(OpenCV REQUIRED)
find_package(Eigen3)

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -O3")
add_definitions(-fPIC )

# include_directories(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
#include_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# add_subdirectory(../native-dlib/dlib dlib_build)
# link_directories(${OpenCV_LIBRARY_DIRS})

# add_executable(elm ${SRC})
add_library(libnew SHARED ${SRC})
INSTALL(TARGETS libnew
	#        RUNTIME DESTINATION bin
	LIBRARY DESTINATION /usr/local/lib
	#        ARCHIVE DESTINATION libstatic
	)
target_link_libraries(libnew  )
# dlib::dlib

file(COPY ${CMAKE_CURRENT_LIST_DIR}/new.hpp DESTINATION /usr/local/include)
