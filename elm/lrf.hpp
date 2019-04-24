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

std::vector<float> get_feature(Mat img);

void LRF_train(MatrixXd feature,MatrixXd T,MatrixXd beta);
void LRF_train(MatrixXd feature,MatrixXd beta,MatrixXd output);



#endif /* _LRF_H */
