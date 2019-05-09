#ifndef _TEST_H
#define _TEST_H

#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <time.h>
#include "facedetectcnn.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>

#include <dlib/image_processing.h>
#include <dlib/image_transforms.h>
#include <dlib/opencv.h>

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace std;
using namespace cv;
// using namespace dlib;

//标准化输出尺寸    //alignment 输出大小 设置为50*50减小内存损耗
extern cv::Size size_box;
extern cv::Size nor;//160 120// 320 160 // 128 96 //


struct location {
	int x, y, w, h, q;
	bool operator<(location & a);    // <号重载
};
extern vector<location> final_location;
extern vector<Mat> alignment_face_recall;

void global_init();//参数初始化 模型加载

void face_alignment(Mat image_roi);//人脸矫正 直到误差小于等于3度 最后结果标准化输出
void process_image(Mat mat);//角度检测函数

bool cmp(const location & m1, const location & m2);
bool big(const location & m1, const location & m2);

static dlib::shape_predictor sp;               // dlib shape predictor

#endif /* _TEST_H */
