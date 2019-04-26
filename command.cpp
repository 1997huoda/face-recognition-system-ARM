#include "make.hpp"

void mkdir_human_name(string human_name,vector<string> & names){

}

void get_filename(string path, vector<string> & names){

	struct dirent * ptr;
	DIR * dir;
	dir = opendir(path.c_str());         // path如果是文件夹 返回NULL
	while((ptr = readdir(dir)) != NULL)  //读取列表
	{
		if(ptr->d_name[0] == '..' ||ptr->d_name[0] == '.' ||  ptr->d_name ==  "Thumbs.db")      //去掉当前文件夹目录和
			                 // Thumbs.db这个windows下保存图片就会产生的文件
			continue;
        if(ptr->d_type== DT_DIR){       //DT_DIR目录    DT_REG常规文件
      		string ss = path + '/' + ptr->d_name ;//+ '/'; //二级文件夹目录   //这TM有问题 path后面少了一个'/'
           names.push_back(ss);      
        }
	}
	closedir(dir);
}

void process_once()
{
	VideoCapture capture(0);
	if (!capture.isOpened())//没有打开摄像头的话，就返回。
		return;

    final_location.clear();
    alignment_face_recall.clear();
    
    Mat frame,bak_gray; //定义一个Mat变量，用于存储每一帧的图像  
    capture>>frame;
    if (frame.empty())
        break;          
    //bak_gray为原图的灰度图
    cvtColor(frame, bak_gray, CV_BGR2GRAY);
    capture>>frame;
    resize(frame,frame,nor,0,0,INTER_LINEAR);

    process_image(frame);

    //                  算法稳定仍然需要去重
    for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
        if(iter+1==final_location.end())break;
        for(vector<location>::iterator  it = iter+1;it!=final_location.end();){
            if((*it)<(*iter)){
                it=final_location.erase(it);
                iter=final_location.begin();
                cout<<"     这里有重复人脸框"<<endl;
            }
            else
                it++;
        }
    }
    
    sort(final_location.begin(),final_location.end(),cmp);//按照x从小到大排序
    
    cout<<"检测到的人脸的个数    "<<final_location.size()<<"个"<<endl;
    /*********face_num***************/
    face_num=final_location.size();
    
    int x_b=cvRound(bak_gray.cols/nor.width);int y_b=cvRound(bak_gray.rows/nor.height);
    for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
        
        int x=cvRound(x_b*(*iter).x);int y = cvRound(y_b*(*iter).y);
        int w =cvRound(x_b* (*iter).w);int h =cvRound( y_b*(*iter).h); 

        Rect rect(x,y,w,h);
        Mat image=(bak_gray(rect));
        
        //resize 将长方形的人脸 resize 成标准方形
        resize(image,image,size_box,0,0,INTER_LINEAR);
        face_alignment(image);
    }
    
    for(vector<location>::iterator  iter = final_location.begin();iter!=final_location.end();iter++){
        int x=(*iter).x;int y = (*iter).y;int w = (*iter).w;int h = (*iter).h; 
        Rect rect(x,y,w,h);
        Point point(x,y+h);//左下角
        String text=to_string(iter-final_location.begin());
        int font_face = cv::FONT_HERSHEY_COMPLEX;
        double font_scale = 2;
        int thickness = 2;
        int baseline;
        cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
        rectangle(frame,rect,cv::Scalar(100, 0, 0),1,0);
        cv::putText(frame, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
    }


    for(vector<Mat>::iterator iter = alignment_face_recall.begin();iter!=alignment_face_recall.end();iter++){
        imshow("show"+to_string(iter-alignment_face_recall.begin()),(*iter));
        imwrite("align"+to_string(iter-alignment_face_recall.begin())+".jpg",(*iter));
    }

    imshow("point", frame); //显示当前帧  
    waitKey(5); //延时5ms 
	
}