#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include<time.h>
#include "facedetectcnn.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>  

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
#include "facedetectcnn.h"
#include "elm.hpp"

using namespace std;
using namespace Eigen;
using namespace cv;

// extern void global_init();//参数初始化 模型加载
// extern void process_webcam_frames();//演示函数
// extern void pic_scan(string pic_name);
int main(int argc, char* argv[])
{
	printf("START OK  \n");
	int arg;
	char input[100];
	// global_init();
	input[0] = 0;
	// parse command line arguments
	arg = 1;
	while(arg < argc)
	{

		if(0==strcmp("-i", argv[arg]) || 0==strcmp("--input", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%s", input);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
		else
		{
			printf("# invalid command line argument '%s'\n", argv[arg]);
			return 1;
		}
	}
	if(0 == strlen(input))
	{
		// process_webcam_frames();
	}
	else{
        // pic_scan(input);
    }
	return 0;
}

