#ifndef _LRF_H
#define _LRF_H

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
using namespace Eigen;


MatrixXd get_beta(MatrixXd feature,MatrixXd T);
Mat get_feature(Mat img,int L,int e);
MatrixXd LRF_train(MatrixXd feature,MatrixXd T);
MatrixXd LRF_test(MatrixXd feature,MatrixXd beta);



#endif /* _LRF_H */
