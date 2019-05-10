project(pro)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
add_definitions(-fPIC   )


# set(CMAKE_C_COMPILER /usr/local/bin/arm-linux-gnueabi-gcc )
# set(CMAKE_CXX_COMPILER /usr/local/bin/arm-linux-gnueabi-g++ )
 set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
 set(CMAKE_C_COMPILER /usr/bin/gcc-5)
  add_definitions(-D_ENABLE_NEON  )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mcpu=cortex-a7 -mfpu=neon-vfpv4 -o3")
cmake_policy(SET CMP0028 OLD)

find_package(OpenCV REQUIRED)
find_package(OpenMP)
find_package(Eigen3)
find_package(dlib REQUIRED)
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/libzmq)
FIND_PACKAGE(ZMQ REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g  -O3")
# add_compile_options(-fPIC)
# add_definitions()


INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})


# include(${CMAKE_CURRENT_LIST_DIR}/libcom.cmake)

# link_directories(${OpenCV_LIBRARY_DIRS})
# link_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(pro ${SRC})
# add_library(libpico SHARED ${SRC})
# INSTALL(TARGETS pro
#        RUNTIME DESTINATION /usr/local/bin
#        LIBRARY DESTINATION /usr/local/lib
#        ARCHIVE DESTINATION libstatic
# )
target_link_libraries(pro libcom libzmq ${ZMQ_LIBRARIES} libelm libnew libpico libfacedetection libalign dlib::dlib ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_LIST_DIR}/shape_predictor_68_face_landmarks.dat DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/none.bmp DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/make.hpp DESTINATION /usr/local/include)
# cmake  -DCMAKE_BUILD_TYPE=Release ..
