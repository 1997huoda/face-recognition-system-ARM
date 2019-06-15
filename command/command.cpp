#include "command.hpp"

float getticks()
{
	struct timespec ts;
	if(clock_gettime(CLOCK_MONOTONIC, &ts) < 0)
		return -1.0f;
	return ts.tv_sec + 1e-9f*ts.tv_nsec;
}

// MatrixXd W[model_num], b[model_num], beta[model_num];
string ip1;
//摄像头类
VideoCapture capture;
//摄像头帧
Mat origin;

//发送人脸数量
int face_num;
//人 名字 标签
vector<string> names;
//识别结果
std::string name;

//收到的人的名称
std::string human_name;
//收到的照片名称
std::string picture_name;
//收到的图
Mat rec_img;

int read_arg(int argc, char * argv[]){
	int arg = 1;
	while(arg < argc)
	{

        if (strncmp(argv[arg], "-ip=", 4) == 0)
        {
            ip1 = &argv[arg][4];
        }
        arg++;
	}
	return 0;
}

void get_filename(string path, vector<string> &names) {
	names.clear();
	// if(names.size()!=0){
		// vector <string>().swap(names);
	// }
    
    struct dirent *ptr, *ptr1;
    DIR *dir, *dir1;
    dir = opendir(path.c_str()); // path如果是文件夹 返回NULL
    if (!dir) {
        cout << "dir fail" << endl;
        return;
    }
    while ((ptr = readdir(dir)) != NULL) //读取列表
    {
        if (ptr->d_name[0] == '.') //去掉本级目录	去掉上级目录 || ptr->d_name ==  "Thumbs.db"
            continue;
        if (ptr->d_type == DT_DIR) { // DT_DIR目录    DT_REG常规文件
            string ss = ptr->d_name; //+ '/'; //二级文件夹目录   //这TM有问题
                                     //path后面少了一个'/'
            string path_ss = path + '/' + ss;
            dir1 = opendir(path_ss.c_str());
            int exit_flag = 0;
            while ((ptr1 = readdir(dir1)) != NULL) {
                if (ptr1->d_name[0] == '.' ) //去掉本级目录	去掉上级目录//|| ptr1->d_name ==  "Thumbs.db"
                {
                    continue;
                } else {
                    exit_flag = 1;
                    break;
                }
            }
            closedir(dir1);
            if (exit_flag == 1) {
                cout << "push_back" << ss << endl;
                names.push_back(ss);
            }
        }
    }
    closedir(dir);
}
void train_elm(MatrixXd *W, MatrixXd *b, MatrixXd *beta) {
    //训练参数  W b beta
    MatrixXd feature;
    feature = ELM_in_ELM_face_training_matrix_from_files();
    T = generate_training_labels();
    ELM_training(feature, W, b, beta);
    cout << "train elm-in-elm end\n";
    get_filename(trainfile_path, names);
    cout << "update file name \n";
}

string show_once() {
    string output_name="";
    for (int i = 0; i < N_test; i++) {
        int /* ii, */ jj;
        // cout<<"i"<<i<<endl;
        // cout<<output.row(i)<<endl;
        float truth = (output.row(i)).maxCoeff(&jj);
        output_name += names[jj]+"\n"+to_string(truth)  + "/";
        // cout <<"ii:"<<ii<<"  jj:"<< jj <<"   name:"<<names[jj]<< "   truth:"<<truth<<endl;
    }
	cout<<output_name<<endl;
    return output_name;
}

void test_elm(vector<Mat> mat_v, MatrixXd *W, MatrixXd *b, MatrixXd *beta) {
    MatrixXd /* feature, */ feature1;
    feature1 = ELM_in_ELM_face_testing_matrix_from_files(mat_v);
    ELM_testing(feature1, W, b, beta);
    name = show_once();
}


void mkdir_human_name(string human_name) {
    string filename = trainfile_path + "/" + human_name;
    DIR *dir;
    dir = opendir(filename.c_str());
    if (!dir) {
        mode_t mode = umask(0);
        if (0 == mkdir(filename.c_str(), 0777))
            // cout << filename << "  mkdir OK!" << endl;
        umask(mode);
        cout << "创建" << filename << "成功\n";
        return;
    } else {
        cout << filename << "已经存在\n";
    }
}



Mat process_once() {
    if (!capture.isOpened())
        capture.open(0);
    if (!capture.isOpened()) //没有打开摄像头的话，就返回。
        cout << "failed open capture" << endl;

    //将识别结果清空f
    final_location.clear();
    alignment_face_recall.clear();
    name.clear();
    origin.release();

    Mat frame;//, bak_gray; //定义一个Mat变量，用于存储每一帧的图像
	float t_c = getticks();
	// capture.set(CAP_PROP_FRAME_WIDTH, 1280);
	// capture.set(CAP_PROP_FRAME_HEIGHT, 720);
    capture >> origin;
	t_c = getticks() - t_c;
    if(t_c!=0)    cout<<" cap    time     "<<t_c*1000<<"ms"<<endl;
    //ARM
	// flip(origin, origin, -1);//当参数flipCode=0时，将对矩阵沿X轴方向翻转；当flipCode>0时，将对矩阵沿Y轴方向翻转；当flipCode<0时，将对矩阵沿XY轴方向翻转。

    if (origin.empty()){
        cout << "cap empty" << endl;
        face_num=0;
        capture.release();
        return process_once();
        // return cv::Mat::zeros(nor, CV_8UC3);
    }else{
        
    }
    resize(origin, frame, nor, 0, 0, INTER_LINEAR);
    if (frame.empty())
        cout << "frame empty" << endl;

    process_image(frame);

    //                  算法稳定仍然需要去重
    for (vector<location>::iterator iter = final_location.begin();  iter != final_location.end(); iter++) {
        if (iter + 1 == final_location.end())
            break;
        for (vector<location>::iterator it = iter + 1;  it != final_location.end();) {
            if ((*it) < (*iter)) {
                it = final_location.erase(it);
                iter = final_location.begin();
                cout << "     这里有重复人脸框" << endl;
            } else
                it++;
        }
    }

    sort(final_location.begin(), final_location.end(), cmp); //按照x从小到大排序

    cout << "检测到的人脸的个数    " << final_location.size() << "个" << endl;
    /*********face_num***************/
    face_num = final_location.size();

    float x_b = (origin.cols / nor.width);
    float y_b = (origin.rows / nor.height);
    for (vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++) {

        int x = cvRound(x_b * (*iter).x);
        int y = cvRound(y_b * (*iter).y);
        int w = cvRound(x_b * (*iter).w);
        int h = cvRound(y_b * (*iter).h);

        Rect rect(x, y, w, h);
        Mat image = (origin(rect));

        // resize 将长方形的人脸 resize 成标准方形
        resize(image, image, size_box, 0, 0, INTER_LINEAR);
        face_alignment(image);
    }

    for (vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++) {
        int x = (*iter).x;
        int y = (*iter).y;
        int w = (*iter).w;
        int h = (*iter).h;
        Rect rect(x, y, w, h);
        rectangle(frame, rect, cv::Scalar(100, 0, 0), 1, 0);
    }
    return frame;
}

