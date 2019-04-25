
#-I/usr/include/opencv4 这个目录是opencv4里面包含opencv2文件夹
OPENCV = -I/usr/lib \
-I/usr/include/opencv4 \
-I/usr/local/include -L/usr/local/lib -L/usr/lib \
-lopencv_dnn -lopencv_ml -lopencv_objdetect \
-lopencv_shape -lopencv_stitching -lopencv_superres \
-lopencv_videostab -lopencv_calib3d -lopencv_features2d \
-lopencv_highgui -lopencv_video -lopencv_photo -lopencv_imgproc \
-lopencv_flann -lopencv_core  -lopencv_ml -lopencv_imgcodecs \
 -lopencv_imgproc -lopencv_videoio \
 -I$(HOME)/anaconda3/include -L$(HOME)/anaconda3/lib
#不清楚opencv 的cascade 是哪个全都写上了
CFLAGS=-I../include -I../3rdparty/liblinear -I/usr/include/eigen3/ -I../src -I../elm -I../native
#-I/usr/local/include/opencv -I/usr/aarch64-linux-gnu/
#
#
#-L. -llbf_

output:
	g++ make.cpp -I../src/ -lrt  -pthread  $(CFLAGS) -o make -O3 -I/usr/lib -L. -llibpico -llib7000 -lliblinear  -llibfacedetection $(OPENCV)		#pico
	#g++ src.cpp -fPIC -shared -o lib***.so
