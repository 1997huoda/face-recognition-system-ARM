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

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "facedetectcnn.h"

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;

int main(int argc, char* argv[])
{
    VideoCapture capture(0);
	if (!capture.isOpened())//没有打开摄像头的话，就返回。
		return 0;
    while(1){
        

	//load an image and convert it to gray (single-channel)
	Mat image ;
    capture>>image;
	if(image.empty())
	{
		fprintf(stderr, "Can not load the image file %s.\n", argv[1]);
		return -1;
	}
	resize(image,image,cv::Size(256,144),0,0,INTER_LINEAR);//320 160//256 144

	int * pResults = NULL; 
    //pBuffer is used in the detection functions.
    //If you call functions in multiple threads, please create one buffer for each thread!
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if(!pBuffer)
    {
        fprintf(stderr, "Can not alloc buffer.\n");
        return -1;
    }
	

	///////////////////////////////////////////
	// CNN face detection 
	// Best detection rate
	//////////////////////////////////////////
	//!!! The input image must be a RGB one (three-channel)
	//!!! DO NOT RELEASE pResults !!!
	float t = getticks();
	pResults = facedetect_cnn(pBuffer, (unsigned char*)(image.ptr(0)), image.cols, image.rows, (int)image.step);
    t = getticks() - t;
    if(t!=0)    cout<<"     time     "<<t*1000<<"ms"<<endl;
    printf("%d faces detected.\n", (pResults ? *pResults : 0));
	Mat result_cnn = image.clone();
	//print the detection results
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+142*i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];

		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);
        printf("\n");
		rectangle(result_cnn, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
	}
	imshow("result_cnn", result_cnn);

 	waitKey(5);

    //release the buffer
    free(pBuffer);
    }
	return 0;
}
