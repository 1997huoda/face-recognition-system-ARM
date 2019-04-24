#ifndef _ELM_H
#define _ELM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <opencv2/opencv.hpp>
#include<opencv2/core/eigen.hpp>
#include<algorithm>
#include <dirent.h>
#include <time.h>

using namespace std;
using namespace Eigen;
using namespace cv;

	int k=1;   //程序参数个数
	int flag=0;        // 没有人脸?
	MatrixXd T;	//存放训练集标签  //目标矩阵
	int L = 100;     //隐层节点数   //单个图像  随机权重  特征矩阵 的 个数
	// m 可以设置为文件夹的个数
	int m = 100;      //训练集以及测试集   人数    

	int training_face_num_per_person=7; //训练集中每个人的人脸数
	int testing_face_num_per_person=3;  // 测试集中每个人的人脸数
	string trainfile_path="/home/huoda/Desktop/test100"; //路径
	string testfile_path="/home/huoda/Desktop/sh";
	vector<int> train_labels_ori;
	vector<int> test_labels_ori;
	Mat trainingImages;
    Mat testingImages;
	vector<int> trainingLabels;
	vector<int> testingLabels;    
    
	int N;
// 	int n; //特征值的数量
	int N_test;
	MatrixXd T,beta,output;

	std::vector<float> extract_feature_LBP(Mat src, int src_rows, int src_cols) ;
	std::vector<float> extract_feature(Mat src) ;
	void getFiles_train( string path, vector<string>& files ) ; //从路径中获取训练集图像的路径
	void getFiles_test( string path, vector<string>& files ) ; //从路径中获取测试集图像的路径
	void getFaces_train(string filePath, Mat& trainingImages, vector<int>& trainingLabels); //获取训练集图像
	void getFaces_test(string filePath, Mat& testingImages, vector<int>& testingLabels);  //获取测试集图像
	void init_stdio() ; //初始化IO
	void pr(string msg, MatrixXd &T); //输出MatrixXd
	void pr(string msg, VectorXd &T) ;//输出VectorXd
	void print_matrix(MatrixXd &T);    //输出矩阵
	int my_parse_args(int argc, char* argv[]);  //设定初始参数函数
	void cout_current_settings(); //输出使用中的参数信息
	MatrixXd ELM_in_ELM_face_training_matrix_from_files(); //从文件夹中获取训练集矩阵
	MatrixXd ELM_in_ELM_face_testing_matrix_from_files(); //从文件夹中获取测试集矩阵
	MatrixXd generate_training_labels(); //生成训练集标签
	void show_testing_results();    //显示测试结果
	
	/*----------------sample mian function:
		int main(int argc, char** argv)
	{
		int in=my_parse_args(argc,argv);
		if(argc<=1)
			cout<<"Using default settings!\n";
		cout_current_settings();
		if(in!=0)
			return 0;
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

cv::Mat face_align(const char* filename);
	

#endif /* _TEST_H */

	
