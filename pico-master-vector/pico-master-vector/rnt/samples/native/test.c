#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdio>
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
#include "test.h"

#include "../../picornt.h"
extern float GL_define_0_3f;//交集与并集的比值
using namespace std; 
using namespace cv;
using namespace lbf;

cv::Size size_box(50,50);//标准化输出尺寸
bool cmp(const location &m1,const location &m2){//按照x从小到大，的顺序
    return m1.x<m2.x;
}
//重载== 用于remove location
bool location::operator<(location& a){
    float x=this->x;float y=this->y;float r=this->r;
    if((x<a.x+a.r)&&(x>a.x-a.r)&&(y<a.y+a.r)&&(y>a.y-a.r)&&(r<a.r))//&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
        return true;
    else
        return false;
}
bool location::operator==(location a){
    float x=this->x;float y=this->y;float r=this->r;
    if((x<a.x+a.r)&&(x>a.x-a.r)&&(y<a.y+a.r)&&(y>a.y-a.r)&&(r<a.r))//&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
        return true;
    else
        return false;
}
void global_init_(){
    final_location.clear();
    alignment_face_recall.clear();
	//***************************pico cascade init*************************/
	int size;
	FILE* file;
	file = fopen("facefinder", "rb");
	if(!file){		printf("# cannot read cascade  \n");}
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	cascade = malloc(size);
	if(!cascade || size!=fread(cascade, 1, size, file))
		printf("#   cascade	error  \n");
	fclose(file);
	//*******************lbf_cascador init**********************/
	const char *model_name = "../model/lfpw.model";//lfpw	helen	
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
		}
		else{
			// resize(image_roi,image_roi,size_box,0,0,INTER_LINEAR);
			cv::Size bigg(image_roi.cols,image_roi.rows);
			cv::Point2f center(image_roi.cols / 2., image_roi.rows / 2.);
			cv::Mat rot_mat = cv::getRotationMatrix2D(center, du/pi*180, 1.0);//旋转中心  角度 缩放倍数
			cv::warpAffine(image_roi, image_roi, rot_mat, bigg);
			resize(image_roi,image_roi,size_box,0,0,INTER_LINEAR);
            star_alignment_thread(image_roi);
		}
	}

void process_image(Mat mat)
{
	unsigned int i, j;
	uint8_t* pixels;
	unsigned int nrows, ncols, ldim;
	unsigned int ndetections;
	float rcsq[4*MAXNDETECTIONS];
    float t;    
	pixels = (uint8_t*)mat.data;
	nrows = mat.rows;
	ncols = mat.cols;
	ldim = mat.step;
    t = getticks();
	ndetections = find_objects(rcsq, MAXNDETECTIONS, cascade, GL_angle[GL_angle_i], pixels, nrows, ncols, ldim, scalefactor, stridefactor, minsize, MIN(nrows, ncols));
	t = getticks() - t;
    ndetections = cluster_detections(rcsq, ndetections);
    if((t!=0)&&(ndetections!=0)){
    printf("#detect time    	%fms\n",t*1000);}
    
    for(i=0; i<ndetections; i++)
    {
        if(rcsq[4*i+3]>=qthreshold) // check the confidence threshold
        {
//             circle(mat, cvPoint(rcsq[4*i+1], rcsq[4*i+0]), rcsq[4*i+2]/2, Scalar(255), 2, 8, 0); 
            float x=rcsq[4*i+1];float y=rcsq[4*i+0];float r=rcsq[4*i+2]/2;float q=rcsq[4*i+3];
            location good={x,y,r,q};
            final_location.push_back(good);
            printf("%d					 %f      r-->%f\n",GL_angle_i,rcsq[4*i+3],rcsq[4*i+2]);//质量数//尺寸
        }
    }				
}
//send a struct to arg
void *text(void *arg)
{
    struct val *v = (struct val *)arg;
    GL_angle_i++;GL_angle_i%=4;
    process_image(v->mat);
    //pthread_exit(NULL);
    return NULL;
}

void *text_alignment(void *arg)
{
    struct val *v = (struct val *)arg;
    face_alignment(v->mat);
    // 	imshow("alignment",i);
    //pthread_exit(NULL);
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
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    
    struct val v;
    v.mat=edges;
    if(edges.empty())return ;
    
    pthread_create(&t0, NULL, text,(void *)&v);
    pthread_create(&t1, NULL, text, (void *)&v);
    pthread_create(&t2, NULL, text, (void *)&v);
    pthread_create(&t3, NULL, text, (void *)&v);
	 
    // 等待线程结束
    void * result;
    if(pthread_join(t0, &result) == -1){
        puts("fail to recollect t0\n");
        exit(1);
    }
    if(pthread_join(t1, &result) == -1){
        puts("fail to recollect t1\n");
        exit(1);
    }
    if(pthread_join(t2, &result) == -1){
        puts("fail to recollect t2\n");
        exit(1);
    }
    if(pthread_join(t3, &result) == -1){
        puts("fail to recollect t3\n");
        exit(1);
    }
}
void process_webcam_frames()
{
	Mat frame,edges,show;//定义一个Mat变量，用于存储每一帧的图像
	VideoCapture capture(0);
	if (!capture.isOpened())//没有打开摄像头的话，就返回。
		return;

	while(true)
	{	
        final_location.clear();
        alignment_face_recall.clear();
		Mat frame; //定义一个Mat变量，用于存储每一帧的图像  
		capture>>frame;
		if (frame.empty())
			break;         
		else
		{
			cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度  
			// equalizeHist(edges, edges);  //均衡化 直方图 
		}
		start_4thread(edges);
		vector<BBox> bboxes;
    	vector<Mat> shapes;
		double bbox[4];
		float t;
//         cout<<"检测到的人脸的个数1    "<<final_location.size()<<"个"<<endl;
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            for(vector<location>::iterator  it = final_location.begin();it<final_location.end();){
                if((*it)<(*iter)){
                    it=final_location.erase(it);
                    iter=final_location.begin();
                    cout<<"     这里有重复人脸框"<<endl;
                }
                else
                    it++;
            }
//             final_location.erase(remove(final_location.begin(),final_location.end(), (*iter)), final_location.end());//不能用 报错==
		}
		sort(final_location.begin(),final_location.end(),cmp);//按照x从小到大排序
        
        cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            float x=(*iter).x;float y = (*iter).y;float r = (*iter).r;float q = (*iter).q;
            Rect rect(x-r,y-r,r*2,r*2);
            Point point(x-r,y+r);
            String text=to_string(iter-final_location.begin());
            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 2;
            int thickness = 2;
            int baseline;
            cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
            rectangle(frame,rect,cv::Scalar(100, 0, 0),-1,0);
            cv::putText(frame, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
            
            Mat image=edges(rect);
            star_alignment_thread(image);
        }
        
		/*************演示用 标点用 无意义************/
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
			Mat shape;
    	    bbox[0] = (*iter).x-(*iter).r;
    	    bbox[1] = (*iter).y-(*iter).r;
            bbox[2] = (*iter).r*2;
    	    bbox[3] = (*iter).r*2;
    	    BBox bbox_(bbox[0], bbox[1], bbox[2], bbox[3]);
			shape = lbf_cascador.Predict(edges, bbox_);
    	    shapes.push_back(shape);
    	    bboxes.push_back(bbox_);
		}
		for(unsigned int i = 0; i < shapes.size(); i++) {
    	    frame = drawShapeInImage(frame, shapes[i], bboxes[i]);
    	}
    	/*******************以上************************/
		//imshow("point", frame); //显示当前帧  
		//waitKey(5); //延时5ms 

	}
}
void pic_scan(string pic_name){
	//******************pico settings init********************************/
	minsize = 10;
	maxsize = 200;
	scalefactor = 1.1f;//#第一个1.1增加可以减少检测次数移动设备建议1.2
	stridefactor = 0.05f;//#第二个增大0.1可以减少检测次数想要更高的召回率可以设置为0.05
	qthreshold = 8.0f;//检验图像质量 默认5.0
	
    cout<<pic_name<<endl;

    Mat pic=imread(pic_name,0);
    if(pic.empty()){
        cout<<"pic_scan open error "<<endl;
    }
    start_4thread(pic);
    final_location.clear();
    alignment_face_recall.clear();
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            for(vector<location>::iterator  it = final_location.begin();it<final_location.end();){
                if((*it)<(*iter)){
                    it=final_location.erase(it);
                    iter=final_location.begin();
                }
                else
                    it++;
            }
		}
		sort(final_location.begin(),final_location.end(),cmp);//按照x从小到大排序
        cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
		for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            float x=(*iter).x;float y = (*iter).y;float r = (*iter).r;float q = (*iter).q;
            Rect rect(x-r,y-r,r*2,r*2);
            Mat image=edges(rect);
            star_alignment_thread(image);
        }
        for(vector<Mat>::iterator iter = alignment_face_recall.begin();iter!=alignment_face_recall.end();iter++){
            imwrite(""+to_string(iter-alignment_face_recall.begin())+".jpg",(*iter));
        }

}
int main(int argc, char* argv[])
{
	printf("START OK  \n");
	int arg;
	char input[1024];
	global_init_();
	input[0] = 0;
	// parse command line arguments
	arg = 1;
	while(arg < argc)
	{
        if(0==strcmp("-m", argv[arg]) || 0==strcmp("--minsize", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%d", &minsize);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
		else if(0==strcmp("-i", argv[arg]) || 0==strcmp("--input", argv[arg]))
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
		else if(0==strcmp("-M", argv[arg]) || 0==strcmp("--maxsize", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%d", &maxsize);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
		else if(0==strcmp("-c", argv[arg]) || 0==strcmp("--scalefactor", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%f", &scalefactor);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
		else if(0==strcmp("-t", argv[arg]) || 0==strcmp("--stridefactor", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%f", &stridefactor);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
		else if(0==strcmp("-0.3", argv[arg]) || 0==strcmp("--0.3f", argv[arg]))//更改交集比上并集的比值 原比值为0.3 现比值为0.1 
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%f", &GL_define_0_3f);
				arg = arg + 2;
			}
			else
			{
				printf("# missing argument after '%s'\n", argv[arg]);
				return 1;
			}
		}
        else if(0==strcmp("-q", argv[arg]) || 0==strcmp("--qthreshold", argv[arg]))
		{
			if(arg+1 < argc)
			{
				sscanf(argv[arg+1], "%f", &qthreshold);
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
