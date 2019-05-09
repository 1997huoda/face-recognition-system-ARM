#ifndef _ELM_H
#define _ELM_H

// #define DLIB_JPEG_SUPPORT
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <algorithm>
#include <dirent.h>
// #include <dlib/image_io.h>
// #include <dlib/image_processing.h>
// #include <dlib/image_processing/frontal_face_detector.h>
// #include <dlib/image_processing/render_face_detections.h>
// #include <dlib/image_transforms.h>
// #include <dlib/opencv.h>
#include <fstream>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/objdetect.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <time.h>
#include <vector>
#include "new.hpp"

using namespace std;
using namespace Eigen;
using namespace cv;


//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
extern string trainfile_path; // = "../A";   // = "/home/huoda/Desktop/100"; //路径

extern vector<int> trainingLabels;


extern int N_test;


MatrixXd ELM_in_ELM_face_training_matrix_from_files(); //从文件夹中获取训练集矩阵
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(vector<Mat> mat_v);

MatrixXd generate_training_labels();                  //生成训练集标签
void ELM_training(MatrixXd feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta); // ELM-in-ELM训练函数
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b, MatrixXd * beta); // ELM-in-ELM测试函数


#endif /* _ELM_H */
