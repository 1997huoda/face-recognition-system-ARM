project(com)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-fPIC )
find_package(OpenCV REQUIRED)
find_package(OpenMP)
find_package(Eigen3)
find_package(dlib REQUIRED)
cmake_policy(SET CMP0028 OLD)
set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
FIND_PACKAGE(ZMQ REQUIRED)
# 
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")

# add_definitions()


include_directories(../src)
# include_directories(../elm)
# include_directories(../new)
include_directories(../native)
include_directories(../libzmq)
include_directories(../command)
include_directories(${CMAKE_CURRENT_LIST_DIR})

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})


# include(../libpico.cmake)
# include(../libelm.cmake)
# include(../libzmq.cmake)

# link_directories(${OpenCV_LIBRARY_DIRS})
# link_directories(..)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# add_executable(pro ${SRC})
add_library(libcom SHARED ${SRC})
INSTALL(TARGETS libcom
#        RUNTIME DESTINATION bin
       LIBRARY DESTINATION /usr/local/lib
#        ARCHIVE DESTINATION libstatic
)
target_link_libraries(libcom libzmq ${ZMQ_LIBRARIES} libelm libnew libpico libfacedetection dlib::dlib ${OpenCV_LIBS})

# file(COPY ../native/shape_predictor_68_face_landmarks.dat DESTINATION ../build)

