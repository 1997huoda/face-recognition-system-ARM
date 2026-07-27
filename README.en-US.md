# Embedded Face Recognition System

arm : now=1.0GHz armv7l  512M RAM 16G sd card

 enable_neon  -mfpu=vfpv3 -march=armv7-a 

detect 23.7ms (at a distance of over 1m to nearly 2m) (68ms at 3m distance)

feature point 19ms

alignment 9ms

elm-in-elm test 61ms

##### **Code Structure**:

`make.cpp` is the main file

`command /*.cpp` encapsulates functions called by `make.cpp`

`new/*.cpp` contains the basic ELM-In-ELM algorithm

`elm/*.cpp` calls `new` to implement face recognition

`align/*.cpp` encapsulates face alignment functions

`native/*.cpp` encapsulates face detection functions

`libzmq/*.cpp` encapsulates common zmq functions

`zmq/*.cpp` is the headless server code for easier ARM debugging

`Qt/server/*` is the Qt visualization interface code, managed by CMake (Qmake is no longer supported)

For the Android system visualization interface code, please refer to another repository: AS-ELM. Please pay attention to the OpenCV configuration when using it.

##### Usage Instructions

This project is uniformly managed using CMake. To make it easier for users to use on a PC, modular compilation is no longer required; unified compilation is now completed using the `CMakeLists` in the current directory.

> mkdir build;cd build;cmake ..;make -j4;

cmake  -DCMAKE_BUILD_TYPE=Release ..

##### Dependency Libraries

The PC version of this project runs on the Arch system:

OpenCV (requires manual installation of the VTK dependency for OpenCV);

This project preserves the source files of the Dlib library used at the time; you can compile and install it yourself;

Information communication between ARM and the visualization interfaces (QT on PC, App on Android) depends on ZeroMQ, installed via the official Arch repository;

If I missed any other dependencies, feel free to provide feedback QAQ


##### Detailed Introduction

`new.cpp` contains the settings for the number of hidden layer nodes and sub-model quantity of ELMs.

In `test.cpp`, `size_box` is the standard size of the training images.

`nor` is the parameter for face detection.


##### Dataset Test Results (After illumination preprocessing)

![1566211954205](/picture/1.png)

![1566211954205](/picture/2.png)

![1566211954205](/picture/3.png)

| Training Set Size | Test Set Size | Histogram Equalization | PIE Sample Description                                |
| ---------- | ---------- | ------------ | ------------------------------------------ |
| 3          | 21         | 0.849        | One frontal, two with different lighting directions (half white, half black) |
| 5          | 19         | 0.682        | One frontal, two for each of two lighting directions (strong and weak light) |
| 6          | 18         | 0.667        | Two frontal, two for each of two lighting directions (strong and weak light) |
| 4          | 20         | 0.799        | One frontal, two with different lighting directions + wearing glasses |
| 3          | 21         | 0.676        | Two with different lighting directions + wearing glasses |
| 2          | 22         | 0.638        | Two with different lighting directions |
| 3          | 21         | 0.346        | Three frontal faces with strong light |
| 3          | 21         | 0.861        | Three frontal faces with weak light |
| 3          | 21         | 0.732        | Three frontal faces with slightly bright light |

Selecting training samples is also very important. If there is a specific application scenario, it is best to control the sample conditions when inputting training samples, as this can improve the recognition success rate.
