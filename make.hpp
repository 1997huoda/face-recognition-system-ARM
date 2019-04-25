#ifndef _MAKEH
#define _MAKE_H

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

#endif /* _MAKE_H */