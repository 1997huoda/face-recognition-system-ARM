# 嵌入式人脸识别系统

arm : now=1.0GHz armv7l  512M RAM 16G sd card

 enable_neon  -mfpu=vfpv3 -march=armv7-a 

detect 23.7ms（一米多近两米）（3米距离68ms）

feature point 19ms

alignment 9ms

elm-in-elm test 61ms

**代码结构**：

make.cpp为主文件

command /*.cpp封装函数 被make.cpp调用

new/*.cpp为ELM-In-ELM基本算法

elm/*.cpp 调用new 实现人脸识别

align/*.cpp 封装人脸对齐函数

native/*.cpp 封装人脸检测函数

libzmq/*.cpp 封装zmq常用函数

zmq/*.cpp 为无界面server代码 方便ARM调试

Qt/server/* 为Qt可视化界面代码 采用CMake管理 Qmake保证不能用

以上所有模块函数 请mkdir build；cd build；cmake ..;make;make install;(/usr/local/lib)如果没有添加lib路径请自行添加

Android系统可视化界面代码请见另外一个仓库 AS-ELM ，使用时注意OpenCV的配置



###
master为ARM当前版本代码

 如果LINUX使用 去掉CMake指定编译器和NEON操作即可编译
