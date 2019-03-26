#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>  
#include <stdio.h>
#include<opencv2/opencv.hpp>   
#include<pthread.h>
#include<math.h>
#include "lbf.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "test.hpp"
#include "facedetectcnn.h"
#define imshow imshow

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace std; 
using namespace cv;
using namespace lbf;

cv::Size size_box(50,50);//标准化输出尺寸
bool cmp(const location &m1,const location &m2){//按照x从小到大，的顺序
    return m1.x<m2.x;
}
//重载< 用于remove location
bool location::operator<(location& a){
    int x=this->x+(this->w)/2;int y=this->y+(this->h)/2;int w=this->w;int h=this->h;int q=this->q;
    if((x<a.x+a.w)&&(x>a.x)&&(y<a.y+a.h)&&(y>a.y)&&(w<=a.w))//&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
        return true;
    else
        return false;
}
void global_init_(){
    final_location.clear();
    alignment_face_recall.clear();
	//*******************lbf_cascador init**********************/
	const char *model_name = "./lfpw.model";//lfpw	helen	
    FILE *model = fopen(model_name, "rb");
    if(!model) {        fprintf(stderr, "Could not load lbf model %s\n", model_name);}
    lbf_cascador.Read(model);
    fclose(model);
}
void face_alignment(Mat image_roi){	
		double bbox[4];//x1 y1 x2 y2
		double point_ab[4]={0};
		Mat shape;
		bbox[0] = 0;//x
		bbox[1] = 0;//y
		bbox[2] = image_roi.cols;//r
		bbox[3] = image_roi.rows;//r
		BBox bbox_(bbox[0], bbox[1], bbox[2], bbox[3]);
		double t,fps;
		t = getticks();
		shape = lbf_cascador.Predict(image_roi, bbox_);
		t = getticks() - t;
		if(t!=0){
		printf("#box	alignment time 	%fms\n",t*1000);}
		double* P_36 =shape.ptr<double>(36);
		point_ab[0]=P_36[0];//x1
		point_ab[1]=P_36[1];//y1
		double* P_45 =shape.ptr<double>(45);
		point_ab[2]=P_45[0];//x2
		point_ab[3]=P_45[1];//y2
		float du=atan2(point_ab[3]-point_ab[1],point_ab[2]-point_ab[0]);
		memset(point_ab,0,4*sizeof(double));
		if((du<=0.05)&&(du>=-0.05)){
			resize(image_roi,image_roi,size_box,0,0,INTER_LINEAR);
            alignment_face_recall.push_back(image_roi);
            alignment_shapes.push_back(shape);
		}
		else{
			cv::Size bigg(image_roi.cols,image_roi.rows);
			cv::Point2f center(image_roi.cols / 2., image_roi.rows / 2.);
			cv::Mat rot_mat = cv::getRotationMatrix2D(center, du*pi, 1.0);//旋转中心  角度 缩放倍数
			cv::warpAffine(image_roi, image_roi, rot_mat, bigg);
			resize(image_roi,image_roi,size_box,0,0,INTER_LINEAR);
            star_alignment_thread(image_roi);
		}
	}

void process_image(Mat mat)
{
    cout<<"     hello   "<<endl;
	int * pResults = NULL; 
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    if(!pBuffer)
    {
        fprintf(stderr, "Can not alloc buffer.\n");
        return ;
    }
	float t = getticks();
	pResults = facedetect_cnn(pBuffer, (unsigned char*)(mat.ptr(0)), mat.cols, mat.rows, (int)mat.step);
    t = getticks() - t;
    if(t!=0)    cout<<"     time     "<<t*1000<<"ms"<<endl;
    printf("%d faces detected.\n", (pResults ? *pResults : 0));
	
	//print the detection results
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+142*i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
// 		int angle = p[5];
        if((x<0)||(y<0)||(w<=0)||(h<=0)||(y+h>mat.rows)||(x+w>mat.cols)){//根源杜绝 mat超边界
            
        }else{
            location good={x,y,w,h,neighbors};
            final_location.push_back(good);    
        }
    
		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=\n", x,y,w,h,neighbors );
	}	
	    free(pBuffer);
}
//send a struct to arg
void *text(void *arg)
{
    struct val *v = (struct val *)arg;
    process_image(v->mat);
    //pthread_exit(NULL);
    return NULL;
}

void *text_alignment(void *arg)
{
    struct val *v = (struct val *)arg;
    face_alignment(v->mat);
//     pthread_exit(NULL);
    return NULL;
}

void star_alignment_thread(Mat edges){
    pthread_t t;
    
    struct val v;
    v.mat=edges;
    
    pthread_create(&t, NULL, text_alignment,(void *)&v);
   // 等待线程结束
    void * result;
    if(pthread_join(t, &result) == -1){
        puts("fail to recollect t\n");
        exit(1);
    }
}
void start_4thread(Mat edges){
    pthread_t t0;   
//     pthread_t t1;
//     pthread_t t2;
//     pthread_t t3;
    
    struct val v;
    v.mat=edges;
    if(edges.empty())return ;
    
    pthread_create(&t0, NULL, text,(void *)&v);
    
    
    
	 
    // 等待线程结束
    void * result;
    if(pthread_join(t0, &result) == -1){
        puts("fail to recollect t0\n");
        exit(1);
    }
//     pthread_create(&t1, NULL, text, (void *)&v);
//     if(pthread_join(t1, &result) == -1){
//         puts("fail to recollect t1\n");
//         exit(1);
//     }
//     pthread_create(&t2, NULL, text, (void *)&v);
//     if(pthread_join(t2, &result) == -1){
//         puts("fail to recollect t2\n");
//         exit(1);
//     }
//     pthread_create(&t3, NULL, text, (void *)&v);
//     if(pthread_join(t3, &result) == -1){
//         puts("fail to recollect t3\n");
//         exit(1);
//     }
    
}
void process_webcam_frames()
{
	//定义一个Mat变量，用于存储每一帧的图像
	VideoCapture capture(0);
	if (!capture.isOpened())//没有打开摄像头的话，就返回。
		return;

	while(true)
	{	
        final_location.clear();
        alignment_face_recall.clear();
        alignment_shapes.clear();
		Mat frame; //定义一个Mat变量，用于存储每一帧的图像  
		capture>>frame;
		if (frame.empty())
			break;         
		resize(frame,frame,cv::Size(320,160),0,0,INTER_LINEAR);//320 160//256 144 //192*172
		start_4thread(frame);
        
//                  算法稳定仍然需要去重
// 		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
//             if(iter+1==final_location.end())break;
//             for(vector<location>::iterator  it = iter+1;it!=final_location.end();){
//                 if((*it)<(*iter)){
//                     it=final_location.erase(it);
//                     iter=final_location.begin();
//                     cout<<"     这里有重复人脸框"<<endl;
//                 }
//                 else
//                     it++;
//             }
// 		}
        
		sort(final_location.begin(),final_location.end(),cmp);//按照x从小到大排序
        
        cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            float x=(*iter).x;float y = (*iter).y;float w = (*iter).w;float h = (*iter).h;  
            Rect rect(x,y,w,h);
            Mat image2=(frame(rect));
            Mat image=image2.clone();
            cvtColor(image, image, CV_BGR2GRAY);
            resize(image,image,cv::Size(100,100),0,0,INTER_LINEAR);//320 160//256 144
            star_alignment_thread(image);//没有灰度处理
            
            Point point(x,y+h);//左下角
            String text=to_string(iter-final_location.begin());
            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 2;
            int thickness = 2;
            int baseline;
            cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
            rectangle(frame,rect,cv::Scalar(100, 0, 0),-1,0);
            cv::putText(frame, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
        }
        

        for(vector<Mat>::iterator iter = alignment_face_recall.begin();iter!=alignment_face_recall.end();iter++){
            imshow("show"+to_string(iter-alignment_face_recall.begin()),(*iter));
        }
//     	imwrite("save.jpg",frame);

		imshow("point", frame); //显示当前帧  
		waitKey(5); //延时5ms 

	}
}
void pic_scan(string pic_name){
    cout<<pic_name<<endl;
    Mat pic=imread(pic_name);
    if(pic.empty()){
        cout<<"pic_scan open error "<<endl;
    }

    final_location.clear();
    alignment_face_recall.clear();
    alignment_shapes.clear();
    start_4thread(pic);
    
    sort(final_location.begin(),final_location.end(),cmp);//按照x从小到大排序
    cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
    
    for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
        float x=(*iter).x;float y = (*iter).y;float w = (*iter).w;float h = (*iter).h;
        Rect rect(x,y,w,h);
        
        

        Mat image2=(pic(rect));
        Mat image=image2.clone();
//         cvtColor(image, image, CV_BGR2GRAY);
        resize(image,image,cv::Size(100,100),0,0,INTER_LINEAR);//320 160//256 144
        star_alignment_thread(image);//没有灰度处理

        Point point(x,y+h);//左下角
        String text=to_string(iter-final_location.begin());
        int font_face = cv::FONT_HERSHEY_COMPLEX;
        double font_scale = 2;
        int thickness = 2;
        int baseline;
        cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
        rectangle(pic,rect,cv::Scalar(100, 0, 0),-1,0);
        cv::putText(pic, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
    }
        
    for(vector<Mat>::iterator iter = alignment_face_recall.begin();iter!=alignment_face_recall.end();iter++){
        imwrite(""+to_string(iter-alignment_face_recall.begin())+".jpg",(*iter));
    }
    imwrite("result.jpg",pic);

}
int main(int argc, char* argv[])
{
	printf("START OK  \n");
	int arg;
	char input[100];
	global_init_();
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
		process_webcam_frames();
	}
	else{
        pic_scan(input);
    }
	return 0;
}
