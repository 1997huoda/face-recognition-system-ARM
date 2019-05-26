
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "align.hpp"
float getticks()
{
	struct timespec ts;
	if(clock_gettime(CLOCK_MONOTONIC, &ts) < 0)
		return -1.0f;
	return ts.tv_sec + 1e-9f*ts.tv_nsec;
}
dlib::shape_predictor sp;               // dlib shape predictor
vector<Mat> alignment_face_recall;

void MyGammaCorrection(Mat& src, Mat& dst, float fGamma)
{
	CV_Assert(src.data);
	// accept only char type matrices
	CV_Assert(src.depth() != sizeof(uchar));
	// build look up table
	unsigned char lut[256];
	for( int i = 0; i < 256; i++ )
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f);
	}
	dst = src.clone();
	const int channels = dst.channels();
	switch(channels)
	{
		case 1:
			{
				MatIterator_<uchar> it, end;
				for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )
					//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;
					*it = lut[(*it)];
				break;
			}
		case 3: 
			{
				MatIterator_<Vec3b> it, end;
				for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )
				{
					//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;
					//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;
					//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;
					(*it)[0] = lut[((*it)[0])];
					(*it)[1] = lut[((*it)[1])];
					(*it)[2] = lut[((*it)[2])];
				}
				break;
			}
	}
}
void face_alignment(Mat image_roi){
	//equalizeHist
	cv::cvtColor(image_roi, image_roi, CV_BGR2GRAY);
	MyGammaCorrection(image_roi,image_roi,1.5f);
	equalizeHist(image_roi,image_roi);
	//dlib::cv_image<dlib::rgb_pixel> img(image_roi);  
	dlib::cv_image<unsigned char> img(image_roi);  	
	std::vector<dlib::full_object_detection> shapes;//shape的向量
	dlib::array<dlib::array2d<dlib::rgb_pixel> > face_chips;//图像的向量	dlib::rgb_pixel 用来存储对齐之后的人脸
	dlib::rectangle dlibRect(0, 0, image_roi.cols, image_roi.rows);
	float t = getticks();
	dlib::full_object_detection shape = sp(img, dlibRect);
    t = getticks() - t;
    if(t!=0)    cout<<" face feature point time     "<<t*1000<<"ms"<<endl;
// shapes[0].part(i).x(), shapes[0].part(i).y()         //shape[0]是第一个人 第i个点的xy坐标
	shapes.push_back(shape);
	 t = getticks();
	dlib::extract_image_chips(img, dlib::get_face_chip_details(shapes), face_chips);
	t = getticks() - t;
    if(t!=0)    cout<<" face align    time     "<<t*1000<<"ms"<<endl;
	//dlib::array2d<dlib::rgb_pixel> equ;//图像格式
	//dlib::equalize_histogram(face_chips[0], equ);
	//Mat eve = dlib::toMat(equ);
	//cv::cvtColor(eve, eve, CV_RGB2BGR);
	Mat eve = dlib::toMat(face_chips[0]);
	//cvtColor(eve, eve, CV_RGB2GRAY);
	alignment_face_recall.push_back(eve.clone());
}
