#ifndef _NEW_H
#define _NEW_H

#include <Eigen/Dense>
#include <Eigen/SVD>
#include <algorithm>
#include <dirent.h>
using namespace std;
using namespace Eigen;


extern int n;
extern int L;                           //隐层节点数
extern int N;
extern MatrixXd F, output, T;
extern int m;                           //训练集以及测试集人数
extern int model_num;                     //子ELM模型的数量

void ELM_in_ELM(MatrixXd & feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta);   

#endif /* _NEW_H */