project(pico)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
find_package(dlib REQUIRED)
cmake_policy(SET CMP0028 OLD)
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

include_directories(../src)
include_directories(../native)
# include_directories(..)
include_directories(${OpenCV_INCLUDE_DIRS})

# include(../libYu.cmake)

link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB SRC ../native/*.cpp)
# add_subdirectory(../native/dlib dlib_build)

#add_executable(pico ${SRC})
add_library(libpico SHARED ${SRC})
INSTALL(TARGETS libpico
#        RUNTIME DESTINATION bin
       LIBRARY DESTINATION /usr/local/lib
#        ARCHIVE DESTINATION libstatic
)
target_link_libraries(libpico libfacedetection dlib::dlib ${OpenCV_LIBS})



