#include "elm.hpp"
#include "lbf.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>  

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
