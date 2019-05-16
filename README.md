# 嵌入式人脸识别系统
###
arm : up-1.2Ghz armv7l  512M RAM 16G sd card

 enable_neon  -mfpu=vfpv3 -march=armv7-a 

detect 27ms

feature point 20ms

alignment 10ms

elm-in-elm test 60ms

'''代码结构：'''

###
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

#分支说明

###
master为ARM当前版本代码

PCA 为PCA实现人脸识别

LDA 为LDA实现人脸识别

Linux为PC上运行测试的版本 作者用来传输数据使用 并非真正的编译版本 如果使用 去掉CMake指定编译器和NEON操作即可编译
