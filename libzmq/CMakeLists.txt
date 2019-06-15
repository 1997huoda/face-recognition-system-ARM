cmake_minimum_required(VERSION 2.8)
PROJECT(transmit)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_CXX_STANDARD 11)


add_definitions(-fPIC)
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_MODULE_PATH ./)
FIND_PACKAGE(ZMQ REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})
#include_directories(${CMAKE_CURRENT_LIST_DIR})
set(LIBRARY ${ZMQ_LIBRARIES} ${OpenCV_LIBS})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(libzmq SHARED ${SRC})
INSTALL(TARGETS libzmq
	#        RUNTIME DESTINATION bin
	LIBRARY DESTINATION /usr/local/lib
	#        ARCHIVE DESTINATION libstatic
	)
target_link_libraries(libzmq ${LIBRARY})


file(COPY ${CMAKE_CURRENT_LIST_DIR}/libzmq.hpp DESTINATION /usr/local/include)
