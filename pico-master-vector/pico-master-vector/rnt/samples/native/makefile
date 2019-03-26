#
#
#
#-I/usr/include/opencv4 这个目录是opencv4里面包含opencv2文件夹
OPENCV = -I/usr/lib \
-I/usr/include/opencv4 \
-I/usr/local/include -L/usr/local/lib \
-lopencv_dnn -lopencv_ml -lopencv_objdetect \
-lopencv_shape -lopencv_stitching -lopencv_superres \
-lopencv_videostab -lopencv_calib3d -lopencv_features2d \
-lopencv_highgui -lopencv_video -lopencv_photo -lopencv_imgproc \
-lopencv_flann -lopencv_core  -lopencv_ml -lopencv_imgcodecs \
 -lopencv_imgproc -lopencv_videoio \
 -I$(HOME)/anaconda3/include -L$(HOME)/anaconda3/lib
#不清楚opencv 的cascade 是哪个全都写上了
CFLAGS=-I../include -I../3rdparty/liblinear -I/usr/local/include/opencv 
#
#
#-L. -llbf_

output:
	g++  test.c ../../picornt.c -lrt  -lpthread   $(CFLAGS) -o pico -O3 -L. -llbf -lliblinear   $(OPENCV)		#pico
	#g++ src.cpp -fPIC -shared -o lib***.so
	#g++ test.c ../../picornt.c -lrt -fPIC -shared -lpthread   $(CFLAGS) -o libpico.so -O3 -L. -llbf -lliblinear  $(OPENCV)	#opencv 被前面的依赖 需要放到后面
	#g++ test.c ../../picornt.c -lrt  -lpthread   $(CFLAGS) -o pico -O3 -L. -llbf -lliblinear   $(OPENCV)	
	#g++ test.c ../../picornt.c -lrt -fPIC -shared -lpthread   $(CFLAGS) -o libpico.so -O3 -L. -llbf -lliblinear  $(OPENCV)		#pico.so
	
	#ARM-linux-gcc main.c -o main		#（32位Ubuntu虚拟机交叉编译命令，64位虚拟机可以使用）
	#arm-linux-g++
	#aarch64-linux-gnu-gcc				#（64位Ubuntu虚拟机交叉编译命令，32位虚拟机不可使用）
