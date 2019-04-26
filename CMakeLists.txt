project(pro)
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -O3")
# add_compile_options(-fPIC)
# add_definitions()


include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/elm)
include_directories(${CMAKE_CURRENT_LIST_DIR}/native)
include_directories(${CMAKE_CURRENT_LIST_DIR}/libzmq)

INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_LIST_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/libpico.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libelm.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libzmq.cmake)

link_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${CMAKE_CURRENT_LIST_DIR})

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(pro ${SRC})
# add_library(libpico SHARED ${SRC})

target_link_libraries(pro libpico libfacedetection dlib::dlib libelm libzmq ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_LIST_DIR}/native/shape_predictor_68_face_landmarks.dat DESTINATION ${CMAKE_CURRENT_LIST_DIR}/build)
