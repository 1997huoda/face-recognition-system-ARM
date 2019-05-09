# CMakeLists for libfacedetectcnn

add_definitions(-fPIC  -pthread )
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE  Release)
option(ENABLE_INT8 "use int8" ON)
option(ENABLE_AVX2 "use avx2" OFF)
option(ENABLE_NEON "whether use neon, if use arm please set it on" ON)

FILE(GLOB fdt_source_files ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
LIST(SORT         fdt_source_files)

if(ENABLE_INT8)
	message("using int8")
	add_definitions(-D_ENABLE_INT8)
endif()

if(ENABLE_AVX2)
	message("using avx2")
	add_definitions(-D_ENABLE_AVX2)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma -o3")
endif()

if(ENABLE_NEON)
	message("using arm")
	add_definitions(-D_ENABLE_NEON)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

INCLUDE_DIRECTORIES(${fdt_inc_dir})

# Create a shared library (.so)
ADD_LIBRARY(libfacedetection SHARED ${fdt_source_files})

if (GSTREAMER)
    find_package(OpenCV REQUIRED)

    include(FindPkgConfig)
    pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)
    pkg_search_module(GSTREAMER_BASE REQUIRED gstreamer-base-1.0)
    pkg_search_module(GSTREAMER_VIDEO REQUIRED gstreamer-video-1.0)

    add_library(gstfacedetect SHARED
        example/libfacedetect.cpp
    )

    include_directories(gstfacedetect PRIVATE
        ${GSTREAMER_INCLUDE_DIRS}
        ${GSTREAMER_BASE_INCLUDE_DIRS}
        ${GSTREAMER_VIDEO_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
    )

    target_link_libraries(gstfacedetect
        ${GSTREAMER_LIBRARIES}
        ${GSTREAMER_BASE_LIBRARIES}
        ${GSTREAMER_VIDEO_LIBRARIES}
        ${OpenCV_LIBS}
        ${fdt_lib_shared}
    )

endif()

