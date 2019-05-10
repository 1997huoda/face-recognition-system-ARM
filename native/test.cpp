#include <iostream>
#include <stdio.h>
#include <math.h>
#include "test.hpp"
#include "facedetectcnn.h"


cv::Size size_box(100, 100);
cv::Size nor(320, 160);//160 120// 320 160 // 128 96 //

vector<location> final_location;


// //define the buffer size. Do not change the size!
// #define DETECT_BUFFER_SIZE 0x20000

bool cmp(const location & m1, const location & m2){//按照x从小到大，的顺序
	return m1.x < m2.x;
}
// bool big(const location & m1, const location & m2){//按照w从大到小，的顺序
// 	return m1.w > m2.w;
// }

//重载< 用于remove location
bool location::operator<(location & a){
	int x = this->x + (this->w) / 2; int y = this->y + (this->h) / 2; int w = this->w; int h = this->h; int q = this->q;
	if((x < a.x + a.w) && (x > a.x) && (y < a.y + a.h) && (y > a.y) && (w <= a.w)) //&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
		return true;
	else
		return false;
}


void process_image(Mat mat)
{
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if(!pBuffer)
	{
		fprintf(stderr, "Can not alloc buffer.\n");
		return;
	}
clock_t start,end;
start=clock();	
	pResults = facedetect_cnn(pBuffer, (unsigned char *)(mat.ptr(0)), mat.cols, mat.rows, (int)mat.step);
end=clock();
double endtime=(double)(end-start)/CLOCKS_PER_SEC;
cout<<"detect time:		"<<endtime*1000<<"ms"<<endl;		//s为单位
//     printf("%d faces detected.\n", (pResults ? *pResults : 0));

	//print the detection results
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short *)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		// int angle = p[5];
		if((((pResults ? *pResults : 0) > 1) && (neighbors < 90)) || (x < 0) || (y < 0) || (w <= 0) || (h <= 0) || (y + h >= mat.rows) || (x + w >= mat.cols)){//根源杜绝 mat超边界

		}else{
			location good = {x, y, w, h, neighbors};
			final_location.push_back(good);
		}
		// printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=\n", x, y, w, h, neighbors);
	}
	free(pBuffer);
}
