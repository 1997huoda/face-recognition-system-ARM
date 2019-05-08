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
#include <opencv2/opencv.hpp>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
using namespace Eigen;
using namespace cv;

extern int k;

// MatrixXd T;                           //存放训练集标签
extern int L;                           //隐层节点数
extern int m;                           //训练集以及测试集人数
extern int model_num;                     //子ELM模型的数量
//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
extern string trainfile_path; // = "../A";   // = "/home/huoda/Desktop/100"; //路径
// extern string testfile_path;  // = "/home/huoda/Desktop/50";

// extern vector<int> test_labels_ori;
// extern Mat trainingImages;
// extern Mat testingImages;
extern vector<int> trainingLabels;
// extern vector<int> testingLabels;
extern int N;
extern int n;
extern int N_test;
extern MatrixXd F, output, T/* , temp_T */;
//其他文件爱呢还想没有调用
// extern int flag;                          // 没有人脸?
// extern vector<int> train_labels_ori;

void init_stdio();                               //初始化IO
void ELM_in_ELM(MatrixXd & feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta/* ,MatrixXd & F, *//*  MatrixXd & output,  *//* int L, int m, int n, int N,int model_num */);            // ELM-in-ELM训练函数

int my_parse_args(int argc, char * argv[]); //设定初始参数函数

MatrixXd ELM_in_ELM_face_training_matrix_from_files(); //从文件夹中获取训练集矩阵
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(vector<Mat> mat_v);

MatrixXd generate_training_labels();                  //生成训练集标签
void ELM_training(MatrixXd feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta); // ELM-in-ELM训练函数
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b, MatrixXd * beta); // ELM-in-ELM测试函数


/* ----------------sample mian function:
        int main(int argc, char** argv)
   {
        init_stdio();
        int in=my_parse_args(argc,argv);
        if(argc<=1)
                cout<<"Using default settings!\n";
        cout_current_settings();
        if(in!=0)
                return 0;
        init_face_detector_dlib();
        //time
        MatrixXd W[model_num],b[model_num], beta[model_num];
        MatrixXd feature,feature1;
        feature=ELM_in_ELM_face_training_matrix_from_files();
        feature1=ELM_in_ELM_face_testing_matrix_from_files();
        T=generate_training_labels();
        ELM_training(feature,W,b,beta);
        ELM_testing(feature1,W,b,beta);
        show_testing_results();
        return 0;
   }
 */

#endif /* _ELM_H */
