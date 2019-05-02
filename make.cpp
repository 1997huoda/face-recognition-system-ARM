#include "make.hpp"
// int main(int argc, char* argv[])
// {
//  return 0;
// }

int main(){
	eve_init();
	// main 函数变量		MatrixXd
	MatrixXd W[model_num], b[model_num], beta[model_num];
	//应该首先开机训练 50人 训练4s 写参数txt 14s	就不需要读取参数了
	//也就不用写参数了
	train_elm(W, b, beta);

	cout << "init--OK" << endl;
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);
	std::cout << "waiting connetting" << std::endl;
	socket.connect("tcp://localhost:5555");

	zmq::message_t msg;
	zmq::message_t received;

	send_msg(socket, "xxxx");

	while(true){
		//接收命令
		command = recv_msg(socket);
		cout << "command : 	" << command << endl;
		if(!strcmp(command.c_str(), "send_picture")){
			//清空输出name字符串
			name.clear();
			//单次人脸识别
			Mat frame = process_once();
			// alignment-->string name
			if(alignment_face_recall.size() != 0)
				test_elm(alignment_face_recall, W, b, beta);

			//发人脸数量
			send_msg(socket, to_string(face_num));
			socket.recv(&received);

			//发人脸名字
			send_msg(socket, name);
			cout << "name:" << name << endl;
			socket.recv(&received);

			//摄像头 图像
			send_pic(socket, frame);
			socket.recv(&received);

			// face_num个人脸的图像
			int x_b = cvRound(origin.cols / nor.width);
			int y_b = cvRound(origin.rows / nor.height);
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

			//备用发送 未测试
			// for(vector<location>::iterator iter =
			// alignment_face_recall.begin(); iter !=
			// alignment_face_recall.end(); iter++){    send_pic(socket,
			// (*iter);     socket.recv(&received);
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

			//收照片名字        好像不需要了
			// socket.recv(&received);
			// std::string picture_name = std::string((char *)received.data(),
			// received.size());

			// std::string picture_name = recv_msg(socket);
			// tmp = "received_picture_name";
			// send_msg(socket, tmp);

			//收图
			socket.recv(&received);
			std::vector<uchar> img_data(received.size());
			memcpy(img_data.data(), received.data(), received.size());
			rec_img = cv::imdecode(img_data, cv::IMREAD_COLOR);
			cvtColor(rec_img, rec_img, COLOR_BGR2GRAY);
			alignment_face_recall.clear();
			face_alignment(rec_img);
			int N64 =rand()+rand();
			// int NN64 = rng.next();
			string sss = trainfile_path + "/" + human_name + "/" + to_string(N64) + ".jpg";
			imwrite(sss, alignment_face_recall[0]);
			tmp = "received_picture";
			send_msg(socket, tmp);
			// alignment_face_recall.clear();

		} else {
			std::cout << "GGGGGGGGGGGGGGGGGGGG" << std::endl;
		}
	}

	return 0;
}
