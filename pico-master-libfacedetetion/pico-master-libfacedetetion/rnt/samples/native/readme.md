## Compiling the program

To compile and run the sample, you will need:

* a C compiler
* OpenCV library, <http://opencv.org/>

Use the provided makefile on *nix machines (some small modifications are usually required).

The sample uses the OpenCV library to obtain data from webcams and to load/save images in common image formats (JPG, PNG, etc.).
Thus, if you wish to redistribute it or its modifications in binary form, you have to reproduce the OpenCV license (read more at the official web page).

## Invoking the program

You always have to specify a path to the detection cascade as the first command line argument, like this:

	$ ./pico ../cascades/facefinder

This will run the detector with *default parameters* on video stream obtained from a *webcam* attached to the computer.

### Optional command line arguments

* `-i` followed by a string: sets a file path to an image that you would like to process.
* `-o` followed by a string: store the processed image to the specified path when done; meaningful only with the `-i` option.
* `-m` or `--minsize` followed by and integer: sets the *minimum* size at which to look for an object (default is 128).
* `-M` or `--maxsize` followed by and integer: sets the *maximum* size at which to look for an object (default is 1024).
* `-q` or `--qthreshold` followed by a real number: detection quality threshold (>=0.0); all detections with estimated quality below this threshold will be discarded (default is 5.0); if you're experiencing too many false positives, try a larger number here (for example, 7.5).
* `-c` or `--scalefactor` followed by a real number: how much to rescale the window during the multiscale detection process (defauls is 1.1); increasing this value leads to lower number of detections and higher processing speed; for example, set to 1.2 if you're using pico on a mobile device.
* `-t` or `--stridefactor` followed by a real number: how much to move the window between neighboring detections (default is 0.1, i.e., 10%): increasing this value leads to lower number of detections and higher processing speed; for example, set to 0.05 if you want really high recall.
* `-u` or `--usepyr`: turns on the coarse image pyramid support; can improve noise and aliasing problems in some applications; set to 1 if pico fails to detect large objects.
* `-n` or `--noclustering`: turns off detection clustering; useful mainly for "debugging" failure cases.
* `-v` or `--verbose`: print details of the detection process to `stdout`.

An example:

	$ ./pico ../cascades/facefinder -m 100 --usepyr

Compare to the following options:

	$ ./pico ../cascades/facefinder -m 100 --usepyr -n -q 0.0

# 3.14新版注意事项

.so更新寻找opencv文件的目录为opencv4 
include文件夹文件更新（作用同上）
.so 中liblinear.so去掉了_下划线
去重方法更新

# 3.18更新

将四个线程程序去重 只保留一个
更新pico源代码优化1ms

不提供返回值函数 自行extern参数

新的参数更改 -0.3 后面输入数字更改最后聚类交集与并集的比值

### 更改检测尺寸 严重影响检测速度

#### 修改召回率影响检测速度和质量

## 下一步 查找十帧之内的 相同人脸 进行存储 比对