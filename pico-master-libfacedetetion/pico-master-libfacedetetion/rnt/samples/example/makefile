OPENCV = -I/usr/lib \
-I/usr/include/opencv4 \
-I/usr/local/include -L/usr/local/lib \
-lopencv_dnn -lopencv_ml -lopencv_objdetect \
-lopencv_shape -lopencv_stitching -lopencv_superres \
-lopencv_videostab -lopencv_calib3d -lopencv_features2d \
-lopencv_highgui -lopencv_video -lopencv_photo -lopencv_imgproc \
-lopencv_flann -lopencv_core  -lopencv_ml -lopencv_imgcodecs \
 -lopencv_imgproc -lopencv_videoio \
 
output:
	g++  main.cpp -I../src/ -lrt  -lpthread -o pico -O3 -I/usr/lib -L. -lfacedetection  $(OPENCV)	
