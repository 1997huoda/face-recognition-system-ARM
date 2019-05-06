#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "test.hpp"
#include "facedetectcnn.h"
#define imshow imshow
#define waitKey waitKey

cv::Size size_box(100, 100);
cv::Size nor(160, 120);//160 120// 320 160 // 128 96 //

vector<location> final_location;
vector<Mat> alignment_face_recall;



// //define the buffer size. Do not change the size!
// #define DETECT_BUFFER_SIZE 0x20000

bool cmp(const location & m1, const location & m2){//按照x从小到大，的顺序
	return m1.x < m2.x;
}
bool big(const location & m1, const location & m2){//按照w从大到小，的顺序
	return m1.w > m2.w;
}
//重载< 用于remove location
bool location::operator<(location & a){
	int x = this->x + (this->w) / 2; int y = this->y + (this->h) / 2; int w = this->w; int h = this->h; int q = this->q;
	if((x < a.x + a.w) && (x > a.x) && (y < a.y + a.h) && (y > a.y) && (w <= a.w)) //&&(x!=a.x)&&(y!=a.y)&&(r!=a.r)
		return true;
	else
		return false;
}
void global_init(){
	init_face_detector_dlib();
	final_location.clear();
	alignment_face_recall.clear();
}
void face_alignment(Mat image_roi){
	//<dlib::rgb_pixel>                                 //彩色图
	//<dlib::bgr_pixel>		//才是mat的正确格式
	dlib::cv_image<unsigned char> img(image_roi);       //灰度图

	std::vector<dlib::full_object_detection> shapes;//shape的向量
	dlib::array<dlib::array2d<dlib::rgb_pixel> > face_chips;//图像的向量	用来存储对齐之后的人脸
	dlib::rectangle dlibRect(0, 0, image_roi.cols, image_roi.rows);

	TickMeter tm;
	tm.start();
	dlib::full_object_detection shape = sp(img, dlibRect);
	tm.stop();
	std::cout << "alignment 用时      " << tm.getTimeSec() * 1000 << "   ms" << endl;//输出是s
    // shapes[0].part(i).x(), shapes[0].part(i).y()         //shape[0]是第一个人 第i个点的xy坐标
	
	shapes.push_back(shape);
	dlib::extract_image_chips(img, dlib::get_face_chip_details(shapes), face_chips);
	dlib::array2d<dlib::rgb_pixel> equ;//图像格式
	
	dlib::equalize_histogram(face_chips[0], equ);
	// transform_image (equ,equ);
	Mat eve = dlib::toMat(equ);
	// Mat eve = dlib::toMat(face_chips[0]);

	alignment_face_recall.push_back(eve);

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
	TickMeter tm;
	tm.start();
	pResults = facedetect_cnn(pBuffer, (unsigned char *)(mat.ptr(0)), mat.cols, mat.rows, (int)mat.step);
	tm.stop();
	std::cout << "process_image 用时      " << tm.getTimeSec() * 1000 << "   ms" << endl;//输出是s
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
		int angle = p[5];
		if((((pResults ? *pResults : 0) > 1) && (neighbors < 90)) || (x < 0) || (y < 0) || (w <= 0) || (h <= 0) || (y + h >= mat.rows) || (x + w >= mat.cols)){//根源杜绝 mat超边界

		}else{
			location good = {x, y, w, h, neighbors};
			final_location.push_back(good);
		}
		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x, y, w, h, neighbors, angle);
	}
	free(pBuffer);
}

void process_webcam_frames()
{
	//定义一个Mat变量，用于存储每一帧的图像
	VideoCapture capture(0);
	if(!capture.isOpened()) //没有打开摄像头的话，就返回。
		return;
	while(true)
	{
		final_location.clear();
		alignment_face_recall.clear();
		Mat origin, frame, bak_gray; //定义一个Mat变量，用于存储每一帧的图像
		capture >> origin;
		if(origin.empty())
			break;
		//bak_gray为原图
		cvtColor(origin, bak_gray, CV_BGR2GRAY);
		// capture >> origin;
		resize(origin, frame, nor, 0, 0, INTER_LINEAR);//320 160//256 144 //192*172
		if(frame.empty())
			break;
		process_image(frame);
		//                  算法稳定仍然需要去重
		for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
			if(iter + 1 == final_location.end()) break;
			for(vector<location>::iterator it = iter + 1; it != final_location.end(); ){
				if((*it) < (*iter)){
					it = final_location.erase(it);
					iter = final_location.begin();
					cout << "     这里有重复人脸框" << endl;
				}
				else
					it++;
			}
		}

		sort(final_location.begin(), final_location.end(), cmp);//按照x从小到大排序
		cout << "检测到的人脸的个数    " << final_location.size() << "个" << endl;
		int x_b = cvRound(bak_gray.cols / nor.width); int y_b = cvRound(bak_gray.rows / nor.height);
		for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
			int x = cvRound(x_b * (*iter).x); int y = cvRound(y_b * (*iter).y); int w = cvRound(x_b * (*iter).w); int h = cvRound(y_b * (*iter).h);
//                 x-=0;if(x<0)x=0;
//                 y-=0;if(y<0)y=0;
//                 w+=0;if(x+w>bak_gray.cols)w=bak_gray.cols-x;
//                 h+=0;if(y+h>bak_gray.rows)h=bak_gray.rows-y;
			Rect rect(x, y, w, h);
			Mat image = (bak_gray(rect));
			//resize 将长方形的人脸 resize 成标准方形
			resize(image, image, size_box, 0, 0, INTER_LINEAR);
			face_alignment(image);
		}

		for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
			int x = (*iter).x; int y = (*iter).y; int w = (*iter).w; int h = (*iter).h;
			Rect rect(x, y, w, h);
			Point point(x, y + h);//左下角
			String text = to_string(iter - final_location.begin());
			int font_face = cv::FONT_HERSHEY_COMPLEX;
			double font_scale = 2;
			int thickness = 2;
			int baseline;
			cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
			rectangle(frame, rect, cv::Scalar(100, 0, 0), 1, 0);
			cv::putText(frame, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
		}


		for(vector<Mat>::iterator iter = alignment_face_recall.begin(); iter != alignment_face_recall.end(); iter++){
			imshow("show" + to_string(iter - alignment_face_recall.begin()), (*iter));
			imwrite("align" + to_string(iter - alignment_face_recall.begin()) + ".jpg", (*iter));
		}

		imwrite("save.jpg", frame);

		imshow("point", frame); //显示当前帧
		waitKey(5); //延时5ms
	}
}
void pic_scan(string pic_name){


}

void cap_save(Mat src, string out_name){
	for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
		float x = (*iter).x; float y = (*iter).y; float w = (*iter).w; float h = (*iter).h;
		x -= 12; y -= 12; w += 24; h += 24;
		if(x < 0) x = 0;
		if(y < 0) y = 0;
		if(x + w > src.cols) w = src.cols - x;
		if(y + h > src.rows) h = src.rows - y;

		Rect rect(x, y, w, h);
		Mat image2 = (src(rect));
		imwrite(out_name + to_string(iter - final_location.begin()) + ".jpg", image2);
	}
}

void init_face_detector_dlib(string face_landmark)
{
	detector = dlib::get_frontal_face_detector();
	dlib::deserialize(face_landmark) >> sp;
}


int main(int argc, char * argv[])
{
	printf("START OK  \n");
	int arg;
	char input[100];
	global_init();
	input[0] = 0;
	// parse command line arguments
	arg = 1;
	while(arg < argc)
	{

		if(0 == strcmp("-i", argv[arg]) || 0 == strcmp("--input", argv[arg]))
		{
			if(arg + 1 < argc)
			{
				sscanf(argv[arg + 1], "%s", input);
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
