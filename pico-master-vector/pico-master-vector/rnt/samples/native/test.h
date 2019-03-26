#ifndef _TEST_H
#define _TEST_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <algorithm>    // std::sort
#include <vector>       // std::vector

#define MAXNDETECTIONS 400

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
float GL_angle[4]={0.125f,0.0416667f,0.9583333f,0.875f};
unsigned int GL_angle_i=0;

struct val{
	Mat mat;
};
struct location{
    float x,y,r,q;
    bool operator<(location& a);
    bool operator==(location a);
};
vector<location> final_location;
vector<Mat> alignment_face_recall;

//******************pico settings init********************************/节省时间**底层代码优化
unsigned int minsize=100;
unsigned int maxsize=800;
float scalefactor =1.2f;//#第一个1.1增加可以减少检测次数移动设备建议1.2
float stridefactor= 0.06f;//#第二个1.0  ->增大可以减少检测次数 ->想要更高的召回率可以设置为0.05
float qthreshold= 8.0f;//检验图像质量 默认5.0
/********************************************************************/

double pi = 3.1415926535;
LbfCascador lbf_cascador;
void* cascade = 0;

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
