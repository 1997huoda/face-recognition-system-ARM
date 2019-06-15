#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>  

#include <stdio.h>
#include<pthread.h>
#include<math.h>
#include "lbf.hpp"
#include "test.hpp"
#include "facedetectcnn.h"

#include <dirent.h>
using namespace std; 
using namespace cv;
using namespace lbf;
cv::Size size_box(100,100);//标准化输出尺寸

int main(int argc, char* argv[])
{
    global_init();
    string path="/home/huoda/Desktop/1w_10photos";
    
    struct dirent *ptr,*ptr1;    
	DIR *dir,*dir1;
    cout<<"path      "<<path.c_str()<<endl;
	dir=opendir(path.c_str());//path如果是文件夹 返回NULL
	while((ptr=readdir(dir))!=NULL)//读取列表
	{        
        cout<<"ptr      "<<ptr->d_name<<endl;
		if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db")		//去掉当前文件夹目录和 Thumbs.db这个windows下保存图片就会产生的文件
			continue;
		string ss=path+'/'+ptr->d_name;//二级文件夹目录   //这TM有问题 path后面少了一个'/'
		cout<<"ss      "<<ss<<endl;
		dir1=opendir(ss.c_str());
        int to_num=0;
		while((ptr1=readdir(dir1))!=NULL)
		{
            cout<<"ptr1      "<<ptr1->d_name<<endl;
			if(ptr1->d_name[0] == '.'||ptr1->d_name=="Thumbs.db")
				continue;
			string sss=ss+'/'+ptr1->d_name;		//获得地址开始人脸检测和矫正
			cout<<"sss      "<<sss<<endl;
            string s2="/home/huoda/Desktop/new1w";                      //   "/home/huoda/Desktop/1w"
            string s3=".jpg";
            s2=s2+'/'+ptr->d_name+'/'+to_string(to_num)+s3;
            to_num++;   
            cout<<"s2      "<<s2<<endl;
            
        final_location.clear();
        alignment_face_recall.clear();
        alignment_shapes.clear();
            
            Mat pic=imread(sss);if(pic.empty()){cout<<"pic empty"<<endl;continue;}
            
            start_4thread(pic);
            
            for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
                if(iter+1==final_location.end())break;
                for(vector<location>::iterator  it = iter+1;it!=final_location.end();){
                    if((*it)<(*iter)){
                        it=final_location.erase(it);
                        iter=final_location.begin();
                        cout<<"     这里有重复人脸框"<<endl;
                    }
                    else{
                        it++;
                    }
                        
                }
            }
            
            sort(final_location.begin(),final_location.end(),big);//从大到小
            cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
            if(final_location.size()==0)continue;
            
//             for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
            //只要最大的
                vector<location>::iterator  iter = final_location.begin();
                float x=(*iter).x;float y = (*iter).y;float w = (*iter).w;float h = (*iter).h;
                /***为了更好的检测到嘴巴*******/
//                 x-=3;if(x<0)x=0;
//                 y-=3;if(y<0)y=0;
//                 w+=6;if(x+w>pic.cols)w=pic.cols-x;
//                 h+=6;if(y+h>pic.rows)h=pic.rows-y;
                /*********/
                Rect rect(x,y,w,h);
                Mat image2=(pic(rect));
                cvtColor(image2, image2, CV_BGR2GRAY);
                resize(image2,image2,cv::Size(100,100),0,0,INTER_LINEAR);
//                 face_alignment(image2);
//             }  
//                 Mat to_save=(*alignment_face_recall.begin());
//                 cvtColor(to_save, to_save, CV_BGRA2GRAY);
                if(!image2.empty())
                imwrite(s2,image2);
		}
		closedir(dir1);
    }
    closedir(dir);
    
    cout<<"getFiles train   end"<<endl;
    
}
