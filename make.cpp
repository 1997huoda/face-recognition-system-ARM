#include "make.hpp"
//研究思路 ::
//读取人脸识别参数  --<没有数据就训练-->训练参数写入txt
// 接受数据
//case1：更改训练数据  change_train_set:--> human_name  picture_name    img
//收到命令 再将命令字符串 返回发送到主机
//查找有无  human_name 文件夹，没有则创建
//将    picture_name.jpg    发送到  human_name
//case2：开始训练   start_traning :
//收到命令 再将命令字符串 返回发送到主机
//开始训练 训练结束后将参数写入txt

//case3：摄像头     send_picture:-->face_num    name    img
//收到命令 再将命令字符串 返回发送到主机
//摄像头
//得到人脸对齐之后的图像
//矩阵乘法 得到识别结果     -->需要数字标签与字符串对应关系获得预测结果
//发送结果


// int main(int argc, char* argv[])
// {
//  return 0;
// }

int main(){
	eve_init();
	//main 函数变量
	MatrixXd W[model_num], b[model_num], beta[model_num];
	//读取txt中的matrixxd
	if(model_num==5)
		read_Matrix((W,b,beta);

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
		cout << command << endl;
		if(!strcmp(command.c_str(), "send_picture")){

			//单次人脸识别
			Mat frame = process_once();
			//alignment-->string name
			// test_elm(alignment_face_recall,W,b,beta);

			//发人脸数量
			send_msg(socket, to_string(face_num));
			socket.recv(&received);

			//发人脸名字
			// std::string name = "dada";
			send_msg(socket, name);
			socket.recv(&received);

			//发图片
			//摄像头 
			send_pic(socket, frame);
			socket.recv(&received);

			//face_num个人脸的图像
			int x_b = cvRound(origin.cols / nor.width); int y_b = cvRound(origin.rows / nor.height);
			for(vector<location>::iterator iter = final_location.begin(); iter != final_location.end(); iter++){
				int x = cvRound(x_b * (*iter).x); int y = cvRound(y_b * (*iter).y);
				int w = cvRound(x_b * (*iter).w); int h = cvRound(y_b * (*iter).h);
				Rect rect(x, y, w, h);
				Mat send = (origin(rect));
				resize(origin, frame, size_box, 0, 0, INTER_LINEAR);
				send_pic(socket, send);
				socket.recv(&received);
			}
			//备用发送 未测试
			// for(vector<location>::iterator iter = alignment_face_recall.begin(); iter != alignment_face_recall.end(); iter++){
			// 	send_pic(socket, (*iter);
			// 	socket.recv(&received);
			// }

			std::string tmp = "send_picture_done";
			send_msg(socket, tmp);

		} else if(!strcmp(command.c_str(), "none")){
			std::string tmp = "none";
			send_msg(socket, tmp);
		} else if(!strcmp(command.c_str(), "start_traning")){
			train_elm(W,b,beta);
			std::string tmp = "start_training";
			send_msg(socket, tmp);
		} else if(!strcmp(command.c_str(), "change_train_set")){

			//收人名
			// socket.recv(&received);
			// std::string human_name =    std::string((char *)received.data(), received.size());
			human_name = recv_msg(socket);
			//检测文件夹是否存在 没有就创建一个
			mkdir_human_name(human_name, names);


			std::string tmp = "received_human_name";
			send_msg(socket, tmp);

			//收照片名字        好像不需要了
			// socket.recv(&received);
			// std::string picture_name = std::string((char *)received.data(), received.size());

			// std::string picture_name = recv_msg(socket);
			// tmp = "received_picture_name";
			// send_msg(socket, tmp);

			//收图
			socket.recv(&received);
			std::vector<uchar> img_data(received.size());
			memcpy(img_data.data(), received.data(), received.size());
			rec_img = cv::imdecode(img_data, cv::IMREAD_COLOR);
			string sss = trainfile_path + "/" + human_name + ".jpg";
			imwrite(sss, rec_img);
			tmp = "received_picture";
			send_msg(socket, tmp);

			tmp = "change_train_set";
			send_msg(socket, tmp);

		} else {
			std::cout << "GGGGGGGGGGGGGGGGGGGG" << std::endl;
		}
	}

	return 0;
}
