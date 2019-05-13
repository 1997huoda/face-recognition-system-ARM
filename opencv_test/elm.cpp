#include <fstream>
#include <algorithm>
#include <dirent.h>
#include <iostream>
// #include <opencv2/core/eigen.hpp>

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
using namespace cv;


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

cv::Mat logTransform3(Mat srcImage, float c)  
{  
    // 输入图像判断
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;
    // cv::Mat resultImage =     cv::Mat::zeros(srcImage.size(), srcImage.type());  
		Mat resultImage =srcImage.clone();
    resultImage.convertTo(resultImage,CV_32F);
    resultImage = resultImage + 1;
    cv::log(resultImage,resultImage);
    resultImage = c * resultImage; 
		// resultImage = resultImage-c; //灰度图 0是黑色 255是白色
    cv::normalize(resultImage,resultImage,0,255,cv::NORM_MINMAX);
		// equalizeHist(resultImage, resultImage);
    cv::convertScaleAbs(resultImage,resultImage);
		// resultImage.convertTo(resultImage,CV_8U);
    return resultImage; 
}

int main(int argc, char * * argv){
/* 	VideoCapture capture;
	    if (!capture.isOpened())
        capture.open(0);
    if (!capture.isOpened()) //没有打开摄像头的话，就返回。
        cout << "failed open capture" << endl;
				 */
				Mat origin;
				origin=imread("../2.jpg");
    // capture >> origin;
	imwrite("origin.jpg",origin);
	Mat gray=origin.clone();
	cvtColor(gray,gray,COLOR_BGR2GRAY);
	imwrite("gray.jpg",gray);
	Mat equ=gray.clone();
	equalizeHist(gray,equ);
	imwrite("equalize.jpg",equ);
	Mat g4=gray.clone();
	MyGammaCorrection(g4,g4,0.4f);
	imwrite("gamma0.4.jpg",g4);
	Mat g15=gray.clone();
	MyGammaCorrection(g15,g15,1.5f);
	imwrite("gamma1.5.jpg",g15);
	Mat l=gray.clone();
	l=logTransform3(l,3.0f);
	imwrite("log.jpg",l);


/* 	vector<float> xy;
	xy.push_back(1);
	xy.push_back(2);
	xy.push_back(4);
	xy.push_back(8);
	xy.push_back(16);
	xy.push_back(32);
	xy.push_back(64);
	xy.push_back(128);
	Mat yy=Mat(xy,true);
	cout<<"yy:"<<endl;
	cout<<yy<<endl;
		// Mat SrcImage1 = Mat(feature, true);
	// TickMeter tm;
	// tm.start();
	PCA pca(yy,Mat(),CV_PCA_DATA_AS_COL,8);//按照圆的面积参数应该是0.785 
	Mat get_back = pca.project(yy);//映射新空间
	cout<<"get_back:"<<endl;
	cout<<get_back<<endl;
	// tm.stop();
	// std::cout << "PCA time:    " << tm.getTimeSec() *1000<< "  ms" << endl;
	// std::vector<float> back = convertMat2Vector<float>(get_back);
	// std::vector<float> back = convertMat2Vector<float>(SrcImage1);
	// return back; */

}
