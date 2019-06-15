#ifndef _ALIGN_H
#define _ALIGN_H


#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

#include <dlib/image_processing.h>
#include <dlib/image_transforms.h>
#include <dlib/opencv.h>

#include<ctime>

using namespace std;
using namespace cv;

extern vector<Mat> alignment_face_recall;
extern  dlib::shape_predictor sp;               // dlib shape predictor

void face_alignment(Mat image_roi);//人脸矫正 直到误差小于等于3度 最后结果标准化输出


#endif /* _TEST_H */