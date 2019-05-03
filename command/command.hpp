#ifndef _COMMAND_H
#define _COMMAND_H

#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <time.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/image_transforms.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

#include <Eigen/Dense>
#include <Eigen/SVD>
#include <dirent.h>

#include <fstream>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <string>

#include "test.hpp"
#include "elm.hpp"
#include "libzmq.hpp"

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
using namespace Eigen;
using namespace cv;

// MatrixXd W[model_num], b[model_num], beta[model_num];
string ip1,ip2;
//摄像头类
VideoCapture capture;
//摄像头帧
Mat origin;

//发送人脸数量
int face_num;
//人 名字 标签
vector<string> names;
//识别结果
std::string name;


//收到的人的名称
std::string human_name;
//收到的照片名称
std::string picture_name;
//收到的图
Mat rec_img;
int read_arg(int argc, char * argv[]);
void eve_init();

Mat process_once();
void train_elm(MatrixXd * W, MatrixXd * b, MatrixXd * beta);

void test_elm(vector<Mat> mat_v, MatrixXd * W, MatrixXd * b, MatrixXd * beta);
string show_once();
void mkdir_human_name(string human_name);
void get_filename(string path, vector<string> & names);



#endif /* _COMMAND_H */
