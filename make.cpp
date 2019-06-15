#include "make.hpp"
void eve_init() {
    std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
    //修改全局变量
	dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
    trainfile_path = "/home/huoda/Desktop/pico/A";				//后面不要有'/'
	// ip1="172.20.10.13";
    ip1="localhost";
    // global_init();
	for( int i = 0; i < 256; i++ )
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), 1.5f) * 255.0f);
	}
    //开启摄像头
    if (!capture.isOpened())
        capture.open(0);
    if (!capture.isOpened()) //没有打开摄像头的话，就返回。
    {
        cout << "failed open capture" << endl;
        return;
    } else {
        cout << "open cap(0) -->" << endl;
    }    
}

int main(int argc, char* argv[]){
	//先参数初始化
	eve_init();
	//再修改参数
	int in = read_arg(argc, argv);
	if(in==1){
		cout<<"input error\n";
	}else if(in==0){
	}
	if(argc <= 1){
		cout << "Using default settings!\n";
	}
	// main 函数变量		MatrixXd
	MatrixXd W[model_num], b[model_num], beta[model_num];
	train_elm(W, b, beta);
	cout << "init--OK" << endl;
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	std::cout << "waiting connetting" << std::endl;
	socket.connect("tcp://"+ip1+":5555");
	zmq::message_t msg;
	zmq::message_t received;
	send_msg(socket, "0");	 
	while(true){
		//接收命令
		command = recv_msg(socket);
		cout << "command : 	" << command << endl;
		if(!strcmp(command.c_str(), "send_picture")){

			float t_o = getticks();
			//单次人脸识别
			Mat frame = process_once();
			if(final_location.size() == 0)
				name="空/空/空/空/空/空/";
			if(alignment_face_recall.size() != 0){
				test_elm(alignment_face_recall, W, b, beta);
			}
			t_o = getticks() - t_o;
			if(t_o!=0)    cout<<" # 	process    time     "<<t_o*1000<<"ms"<<endl;

			//发人脸数量
			send_msg(socket, to_string(face_num));
			cout<<to_string(face_num)<<endl;
			recv_msg(socket);

			//发人脸名字
			send_msg(socket, name);
			recv_msg(socket);

			if(origin.empty()){
				frame=imread("none.bmp");
			}
			//摄像头 图像
			// resize(frame, frame, cv::Size(120,90), 0, 0, INTER_LINEAR);//减小传输数据	//120	90
			send_pic(socket, frame);
			recv_msg(socket);

			// face_num个人脸的图像
			float x_b = (origin.cols / nor.width);
			float y_b = (origin.rows / nor.height);
			for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
				int x = cvRound(x_b * (*iter).x);
				int y = cvRound(y_b * (*iter).y);
				int w = cvRound(x_b * (*iter).w);
				int h = cvRound(y_b * (*iter).h);

				Rect rect(x, y, w, h);
				Mat send = (origin(rect));
				resize(send, send, size_box, 0, 0, INTER_LINEAR);//减小传输数据
				imshow("???",send);
				send_pic(socket, send);
				recv_msg(socket);
			}


			std::string tmp = "send_picture_done";
			send_msg(socket, tmp);

		} else if(!strcmp(command.c_str(), "none")){
			std::string tmp = "none";
			send_msg(socket, tmp);
		} else if(!strcmp(command.c_str(), "start_traning")){
			train_elm(W, b, beta);
			std::string tmp = "start_training";
			send_msg(socket, tmp);
		} else if(!strcmp(command.c_str(), "change_train_set")){
			std::string tmp = "change_train_set";
			send_msg(socket, tmp);
			//收人名
			human_name = recv_msg(socket);
			//检测文件夹是否存在 没有就创建一个
			mkdir_human_name(human_name);

			tmp = "received_human_name";
			send_msg(socket, tmp);

			//收图
			rec_img = receive_pic(socket);
			//cvtColor(rec_img, rec_img, COLOR_BGR2GRAY);
			alignment_face_recall.clear();
			face_alignment(rec_img);
			int N64 =rand();
			string sss = trainfile_path + "/" + human_name + "/" + to_string(N64) + ".jpg";
			Mat every=alignment_face_recall[0];
			imwrite(sss, every);
			tmp = "received_picture";
			send_msg(socket, tmp);

		} else {
			std::cout << "GGGGGGGGGGGGGGGGGGGG" << std::endl;
		}
	}
	return 0;
}
