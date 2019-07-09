# 嵌入式人脸识别系统

arm : now=1.0GHz armv7l  512M RAM 16G sd card

 enable_neon  -mfpu=vfpv3 -march=armv7-a 

detect 23.7ms（一米多近两米）（3米距离68ms）

feature point 19ms

alignment 9ms

elm-in-elm test 61ms

##### **代码结构**：

make.cpp为主文件

command /*.cpp封装函数 被make.cpp调用

new/*.cpp为ELM-In-ELM基本算法

elm/*.cpp 调用new 实现人脸识别

align/*.cpp 封装人脸对齐函数

native/*.cpp 封装人脸检测函数

libzmq/*.cpp 封装zmq常用函数

zmq/*.cpp 为无界面server代码 方便ARM调试

Qt/server/* 为Qt可视化界面代码 采用CMake管理 Qmake保证不能用

Android系统可视化界面代码请见另外一个仓库 AS-ELM ，使用时注意OpenCV的配置

##### 使用说明

本项目统一使用CMake管理，为了方便用户PC上使用，不再需要分模块编译，现使用当前目录下CMakeLists完成统一编译。

> mkdir build;cd build;cmake ..;make -j4;

cmake  -DCMAKE_BUILD_TYPE=Release ..

##### 依赖库

本项目PC版本运行在Arch系统：

OpenCV，需要手动安装OpenCV的依赖项VTK；

本项目保存了当时依赖的Dlib库的源文件，可以自行编译安装；

在ARM与可视化界面（PC上的QT，安卓上的App）的信息通讯依赖于ZeroMQ，通过Arch官方库安装；

其他依赖项没想起来欢迎反馈QAQ

