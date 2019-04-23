cmake_minimum_required(VERSION 2.8)

find_package(OpenCV REQUIRED)
find_package(OpenMP)

if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_definitions(-fPIC -pthread -fopenmp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

include(${CMAKE_CURRENT_LIST_DIR}/3rdparty/liblinear/liblinear.cmake)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/include/*.cpp)

#add_library(lib3000fps STATIC ${SRC})
#target_link_libraries(lib3000fps liblinear ${OpenCV_LIBS})

#set(SRC src/main.cpp
#        src/prepare.cpp
#        src/test.cpp
#        src/train.cpp)
add_library(lib7000 SHARED ${SRC})
#add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(lib7000 liblinear ${OpenCV_LIBS})
