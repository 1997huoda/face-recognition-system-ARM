project(new)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -O3")
add_definitions(-fPIC -fopenmp)

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/new)

file(GLOB NEWSRC ${CMAKE_CURRENT_LIST_DIR}/new/*.cpp)

# link_directories(${OpenCV_LIBRARY_DIRS})

# add_executable(elm ${SRC})
add_library(libnew SHARED ${NEWSRC})
# INSTALL(TARGETS libnew
# 	#        RUNTIME DESTINATION bin
# 	LIBRARY DESTINATION /usr/local/lib
# 	#        ARCHIVE DESTINATION libstatic
# 	)
target_link_libraries(libnew  )

# file(COPY ${CMAKE_CURRENT_LIST_DIR}/new/new.hpp DESTINATION /usr/local/include)
