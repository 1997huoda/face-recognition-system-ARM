
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "align.hpp"

 dlib::shape_predictor sp;               // dlib shape predictor
 vector<Mat> alignment_face_recall;
 
void face_alignment(Mat image_roi){
	//<dlib::rgb_pixel>                                 //彩色图
	//<dlib::bgr_pixel>		//才是mat的正确格式
	// dlib::cv_image<unsigned char> img(image_roi);       //灰度图
	dlib::cv_image<dlib::bgr_pixel> img(image_roi);   

	std::vector<dlib::full_object_detection> shapes;//shape的向量
	dlib::array<dlib::array2d<dlib::bgr_pixel> > face_chips;//图像的向量	用来存储对齐之后的人脸
	dlib::rectangle dlibRect(0, 0, image_roi.cols, image_roi.rows);

	// TickMeter tm;
	// tm.start();
	dlib::full_object_detection shape = sp(img, dlibRect);
	// tm.stop();
	// std::cout << "alignment 用时      " << tm.getTimeSec() * 1000 << "   ms" << endl;//输出是s
    // shapes[0].part(i).x(), shapes[0].part(i).y()         //shape[0]是第一个人 第i个点的xy坐标
	
	shapes.push_back(shape);
	dlib::extract_image_chips(img, dlib::get_face_chip_details(shapes), face_chips);
	dlib::array2d<dlib::bgr_pixel> equ;//图像格式
	dlib::equalize_histogram(face_chips[0], equ);

	Mat eve = dlib::toMat(equ);

	alignment_face_recall.push_back(eve.clone());
}
