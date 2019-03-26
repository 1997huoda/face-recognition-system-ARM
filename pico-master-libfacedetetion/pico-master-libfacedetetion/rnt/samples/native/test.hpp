#ifndef _TEST_H
#define _TEST_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <algorithm>    // std::sort
#include <vector>       // std::vector

using namespace std; 
using namespace cv;
using namespace lbf;

#ifdef __GNUC__
#include <time.h>
float getticks()
{
	struct timespec ts;
	if(clock_gettime(CLOCK_MONOTONIC, &ts) < 0)
		return -1.0f;
	return ts.tv_sec + 1e-9f*ts.tv_nsec;
}
#else
#include <windows.h>
float getticks()
{
	static double freq = -1.0;
	LARGE_intEGER lint;
	if(freq < 0.0)
	{
		if(!QueryPerformanceFrequency(&lint))
			return -1.0f;
		freq = lint.QuadPart;
	}
	if(!QueryPerformanceCounter(&lint))
		return -1.0f;
	return (float)( lint.QuadPart/freq );
}
#endif



struct val{
	Mat mat;
};
struct location{
    int x,y,w,h,q;
    bool operator<(location& a); //<号重载
};
vector<location> final_location;
vector<Mat> alignment_face_recall;
vector<Mat> alignment_shapes;


double pi = 57.29578;//180/pi 优化计算速度
LbfCascador lbf_cascador;

void global_init_();//参数初始化 模型加载
void start_4thread(Mat edges);//启动四线程 四角度人脸检测
void star_alignment_thread(Mat edges);//人脸矫正线程
void face_alignment(Mat image_roi);//人脸矫正 直到误差小于等于3度 最后结果标准化输出
void process_image(Mat mat);//角度检测函数
void process_webcam_frames();//演示函数
bool cmp(const location &m1,const location &m2);


#ifdef __cplusplus
}
#endif

#endif /* _TEST_H */
