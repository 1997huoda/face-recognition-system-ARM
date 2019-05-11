#include "make.hpp"
void eve_init() {
    std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
    //修改全局变量
	dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
    trainfile_path = "../A";
	ip1="localhost";
    // ip1="localhost";
    // global_init();
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
	send_msg(socket, "0");	 //这样崩溃的时候少一次启动
	while(true){
		//接收命令
		command = recv_msg(socket);
		cout << "command : 	" << command << endl;
		if(!strcmp(command.c_str(), "send_picture")){
			//清空输出name字符串
			// name.clear();//在process——once里面写了清空
			//单次人脸识别
			Mat frame = process_once();
			// alignment-->string name
			if(final_location.size() == 0)
				name="空/空/空/空/空/空/";
			if(alignment_face_recall.size() != 0){
				test_elm(alignment_face_recall, W, b, beta);
			}
			//发人脸数量
			send_msg(socket, to_string(face_num));
			socket.recv(&received);

			//发人脸名字
			send_msg(socket, name);
			// cout << "name:" << name << endl;
			socket.recv(&received);

			if(origin.empty()){
				frame=imread("none.bmp");
			}
			//摄像头 图像
			send_pic(socket, frame);
			socket.recv(&received);

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
				resize(origin, frame, size_box, 0, 0, INTER_LINEAR);
				send_pic(socket, send);
				socket.recv(&received);
			}

			//备用发送 未测试	//仅供测试使用 否则与u实际逻辑冲突 ***能用 但是 不推荐***
			// for(vector<Mat>::iterator iter =alignment_face_recall.begin(); iter !=	alignment_face_recall.end(); iter++){
			// 	Mat send=(*iter);
			// 	send_pic(socket,(*iter)); 
			// 	socket.recv(&received);
			// }

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

			//收照片名字        不需要了

			//收图
			rec_img = receive_pic(socket);
			cvtColor(rec_img, rec_img, COLOR_BGR2GRAY);
			alignment_face_recall.clear();
			face_alignment(rec_img);
			int N64 =rand();
			// int NN64 = rng.next();
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
