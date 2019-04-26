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

static const int table[256] = {
	1,  2,  3,  4,  5,  0,  6,  7,  8, 0,  0,  0,  9,  0,  10, 11, 12, 0,  0,
	0,  0,  0,  0,  0,  13, 0,  0,  0, 14, 0,  15, 16, 17, 0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  18, 0,  0,  0,  0,  0,  0,  0,  19,
	0,  0,  0,  20, 0,  21, 22, 23, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  24, 0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  25, 0,
	0,  0,  0,  0,  0,  0,  26, 0,  0, 0,  27, 0,  28, 29, 30, 31, 0,  32, 0,
	0,  0,  33, 0,  0,  0,  0,  0,  0, 0,  34, 0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  35, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  36, 37, 38, 0,  39, 0,  0,  0, 40, 0,  0,  0,  0,  0,  0,  0,  41, 0,
	0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  42, 43, 44, 0,  45,
	0,  0,  0,  46, 0,  0,  0,  0,  0, 0,  0,  47, 48, 49, 0,  50, 0,  0,  0,
	51, 52, 53, 0,  54, 55, 56, 57, 58};

int k = 1;
int flag = 0;                         // 没有人脸?
MatrixXd T;                           //存放训练集标签
int L = 600;                          //隐层节点数
int m = 50;                           //训练集以及测试集人数
int model_num = 5;                    //子ELM模型的数量
int training_face_num_per_person = 7; //训练集中每个人的人脸数
int testing_face_num_per_person = 3;  // 测试集中每个人的人脸数
//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
string trainfile_path = "../A";   // = "/home/huoda/Desktop/100"; //路径
string testfile_path;  // = "/home/huoda/Desktop/50";
vector<int> train_labels_ori;
vector<int> test_labels_ori;
Mat trainingImages;
vector<int> trainingLabels;
Mat testingImages;
vector<int> testingLabels;
int N;
int n;
int N_test;
MatrixXd F, output;
MatrixXd temp_T;
// MatrixXd W[model_num],b[model_num], beta[model_num];
// static dlib::frontal_face_detector detector; // dlib face detector
// static dlib::shape_predictor sp;             // dlib shape predictor

void LBP81(const Mat & src, Mat & dst); // LBP_extractor
std::vector<float> extract_feature_LBP(Mat src, int src_rows, int src_cols);
std::vector<float> extract_feature(Mat src);

void read_parameter(string path, MatrixXd & in);
void write_parameter(string path, MatrixXd output);

// double difftimeval(const struct timeval *start,
//                    const struct timeval *end); //计算时间间隔
void getFiles_train(string path,
					vector<string> & files); //从路径中获取训练集图像的路径
void getFiles_test(string path, vector<string> & files); //从路径中获取测试集图像的路径
void getFaces_train(string filePath, Mat & trainingImages,
					vector<int> & trainingLabels); //获取训练集图像
void getFaces_test(string filePath, Mat & trainingImages,  vector<int> & trainingLabels); //获取测试集图像
void getFaces_test(Mat SrcImage, Mat & trainingImages, vector<int> & trainingLabels); //重载单个Mat
void getFaces_test(vector<Mat> mat_v, Mat & trainingImages);

void init_stdio();                               //初始化IO
void ELM_basic(MatrixXd & feature, MatrixXd & W, MatrixXd & b_1, MatrixXd & beta,
			   MatrixXd & output, int L, int m, int n, int N); //原始ELM训练函数
void ELM_in_ELM(MatrixXd & feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta,
				MatrixXd & F, MatrixXd & output, int L, int m, int n, int N,
				int model_num);            // ELM-in-ELM训练函数
void pr(string msg, MatrixXd & T);          //输出MatrixXd
void pr(string msg, VectorXd & T);          //输出VectorXd
void print_matrix(MatrixXd & T);            //输出矩阵
cv::Mat face_align(const char * filename);  //人脸对齐
int my_parse_args(int argc, char * argv[]); //设定初始参数函数
void cout_current_settings();              //输出使用中的参数信息
// void init_face_detector_dlib(    string face_landmark =    "shape_predictor_68_face_landmarks.dat"); //初始化dlib人脸检测器
MatrixXd ELM_in_ELM_face_training_matrix_from_files(); //从文件夹中获取训练集矩阵
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(); //从文件夹中获取测试集矩阵
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(Mat SrcImage);
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(vector<Mat> mat_v);

MatrixXd generate_training_labels();                  //生成训练集标签
void ELM_training(MatrixXd feature, MatrixXd * W, MatrixXd * b,
				  MatrixXd * beta); // ELM-in-ELM训练函数
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b,
				 MatrixXd * beta); // ELM-in-ELM测试函数
void show_testing_results();      //显示测试结果

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
