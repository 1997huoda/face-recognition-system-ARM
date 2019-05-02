#include "command.hpp"

void eve_init(){
	//修改全局变量
	trainfile_path = "../A";
	global_init();
	//开启摄像头
	capture.open(0);
	if(!capture.isOpened()) //没有打开摄像头的话，就返回。
	{
		cout << "failed open capture" << endl;
		return;
	}else{
		cout << "open cap(0) -->" << endl;
	}
	// get_filename(trainfile_path, names);
}

void train_elm(MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	//训练参数  W b beta
	MatrixXd feature;
	feature = ELM_in_ELM_face_training_matrix_from_files();
	T = generate_training_labels();
	ELM_training(feature, W, b, beta);
	cout << "train elm-in-elm end\n";
	get_filename(trainfile_path, names);
	cout << "update file name \n";
}

void test_elm(vector<Mat> mat_v, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	//将整个 alignment vector送进来 产生测试数据集
	MatrixXd feature, feature1;
	feature1 = ELM_in_ELM_face_testing_matrix_from_files(mat_v);
	ELM_testing(feature1, W, b, beta);
	//name为识别结果字符串
	name = show_once();
}
string show_once(){
	string output_name;
	for(int i = 0; i < N_test; i++){
		int ii, jj;
		// cout << output.row(i).maxCoeff(&ii, &jj) << endl;
		std::string name_plus;
		double truth = output.row(i).maxCoeff(&ii, &jj);
		if(truth > 0.8){
			name_plus = "\n(similar)";
		}else if(truth > 0.6){
			name_plus = "\n(possible)";
		}else if(truth > 0.4){
			name_plus = "\n(doubtful)";
		}else if(truth > 0.2){
			name_plus = "\n(uncertain)";
		}else if(truth < 0.2){
			name_plus = "\n(unpredictable)";
		}
		output_name += names[jj] + name_plus + "/";
		cout << output_name << endl;
	}
	return output_name;
}

void mkdir_human_name(string human_name){
	string filename = trainfile_path + "/" +  human_name;
	DIR * dir;
	dir = opendir(filename.c_str());
	if(!dir)
	{
		mode_t mode = umask(0);
		if(0 == mkdir(filename.c_str(), 0777))
			cout << filename << "  mkdir OK!" << endl;
		umask(mode);
		cout << "创建" << filename << "成功\n";
		return;
	}else{
		cout << filename << "已经存在\n";
	}
}

void get_filename(string path, vector<string> & names){
	struct dirent * ptr, * ptr1;
	DIR * dir, * dir1;
	dir = opendir(path.c_str());         // path如果是文件夹 返回NULL
	if(!dir){
		cout << "dir fail" << endl;
		return;
	}
	while((ptr = readdir(dir)) != NULL)  //读取列表
	{
		if(strncmp(ptr->d_name, ".", 1) == 0)   //去掉本级目录	去掉上级目录	去掉隐藏文件
			continue;
		if(ptr->d_type == DT_DIR){       //DT_DIR目录    DT_REG常规文件
			string ss =  ptr->d_name; //+ '/'; //二级文件夹目录   //这TM有问题 path后面少了一个'/'
			string path_ss=path+'/'+ss;
			dir1 = opendir(path_ss.c_str());
			int exit_flag =0 ;
			while((ptr1 = readdir(dir1)) != NULL){
				if(strncmp(ptr1->d_name, ".", 1) == 0)   //去掉本级目录	去掉上级目录	去掉隐藏文件
					{continue;}
				else{
					exit_flag=1;
					break;
				}
			}
			if(exit_flag==1){
			cout << "push_back" << ss << endl;
			names.push_back(ss);
			}
		}
	}
	closedir(dir);
}

Mat process_once()
{
	// VideoCapture capture(0);
	// captrue.open(0);
	if(!capture.isOpened()) //没有打开摄像头的话，就返回。
		cout << "failed open capture" << endl;
	// return ;

	//将识别结果清空
	final_location.clear();
	alignment_face_recall.clear();
	name = "";

	Mat frame, bak_gray; //定义一个Mat变量，用于存储每一帧的图像
	capture >> origin;
	if(origin.empty())
		cout << "cap empty" << endl;
	// return ;
	//bak_gray为原图的灰度图
	cvtColor(origin, bak_gray, CV_BGR2GRAY);
	// capture >> frame;
	resize(origin, frame, nor, 0, 0, INTER_LINEAR);
	if(frame.empty())
		cout << "" << endl;

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
	/*********face_num***************/
	face_num = final_location.size();

	int x_b = cvRound(bak_gray.cols / nor.width); int y_b = cvRound(bak_gray.rows / nor.height);
	for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){

		int x = cvRound(x_b * (*iter).x); int y = cvRound(y_b * (*iter).y);
		int w = cvRound(x_b * (*iter).w); int h = cvRound(y_b * (*iter).h);

		Rect rect(x, y, w, h);
		Mat image = (bak_gray(rect));

		//resize 将长方形的人脸 resize 成标准方形
		resize(image, image, size_box, 0, 0, INTER_LINEAR);
		face_alignment(image);
	}

	for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
		int x = (*iter).x; int y = (*iter).y; int w = (*iter).w; int h = (*iter).h;
		Rect rect(x, y, w, h);
		// Point point(x, y );//左上角 //不影响截图
		// String text = to_string(iter - final_location.begin());
		// int font_face = cv::FONT_HERSHEY_COMPLEX;
		// double font_scale = 2;
		// int thickness = 2;
		// int baseline;
		// cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baselinebaseline);
		rectangle(frame, rect, cv::Scalar(100, 0, 0), 1, 0);
		//检测结果不用写在图上
		// cv::putText(frame, text, point, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
	}


	// for(vector<Mat>::iterator iter = alignment_face_recall.begin(); iter != alignment_face_recall.end(); iter++){
	//  imshow("show" + to_string(iter - alignment_face_recall.begin()), (*iter));
	//  imwrite("face" + to_string(iter - alignment_face_recall.begin()) + ".jpg", (*iter));
	// }

	// imshow("point", frame); //显示当前帧
	// waitKey(5); //延时5ms
	return frame;

}

int main(){
	return 0;
}
