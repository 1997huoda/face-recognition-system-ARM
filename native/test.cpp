#include <iostream>
#include <stdio.h>
#include <math.h>
#include "test.hpp"
#include "facedetectcnn.h"


cv::Size size_box(100, 100);
cv::Size nor(160, 120);//160 120// 320 160 // 128 96 //

vector<location> final_location;
vector<Mat> alignment_face_recall;

// //define the buffer size. Do not change the size!
// #define DETECT_BUFFER_SIZE 0x20000

bool cmp(const location & m1, const location & m2){//按照x从小到大，的顺序
	return m1.x < m2.x;
}
bool big(const location & m1, const location & m2){//按照w从大到小，的顺序
	return m1.w > m2.w;
}
//重载< 用于remove location
bool location::operator<(location & a){
	int x = this->x + (this->w) / 2; int y = this->y + (this->h) / 2; int w = this->w; int h = this->h; int q = this->q;
	if((x < a.x + a.w) && (x > a.x) && (y < a.y + a.h) && (y > a.y) && (w <= a.w)) //&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
		return true;
	else
		return false;
}
// void global_init(){
// 	// init_face_detector_dlib();
// 	dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
// 	final_location.clear();
// 	alignment_face_recall.clear();
// }



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

void process_image(Mat mat)
{
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if(!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return;
	}
	// TickMeter tm;
	// tm.start();
	pResults = facedetect_cnn(pBuffer, (unsigned char *)(mat.ptr(0)), mat.cols, mat.rows, (int)mat.step);
	// tm.stop();
	// std::cout << "process_image 用时      " << tm.getTimeSec() * 1000 << "   ms" << endl;//输出是s
//     printf("%d faces detected.\n", (pResults ? *pResults : 0));

	//print the detection results
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short *)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		// int angle = p[5];
		if((((pResults ? *pResults : 0) > 1) && (neighbors < 90)) || (x < 0) || (y < 0) || (w <= 0) || (h <= 0) || (y + h >= mat.rows) || (x + w >= mat.cols)){//根源杜绝 mat超边界

		}else{
			location good = {x, y, w, h, neighbors};
			final_location.push_back(good);
		}
		// printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=\n", x, y, w, h, neighbors);
	}
	free(pBuffer);
}
