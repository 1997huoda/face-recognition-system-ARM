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
// 	return 0;
// }

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    std::cout << "waiting connetting" << std::endl;
    socket.connect("tcp://localhost:5555");

    // cv::Mat img = cv::imread("../pic/1.png");
    zmq::message_t msg;
    zmq::message_t received;
    std::string command;
    send_msg(socket, "none");

    while (true) {
        //接收命令
        command = recv_msg(socket);
        if (command == "send_picture") {
            //单次人脸识别
            Mat frame=process_once();

            //发人脸数量
            // std::string face_num = std::to_string(1);
            // int face_num = 1;
            send_msg(socket, to_string(face_num));
            socket.recv(&received);

            //发人脸名字

            // std::string name = "dada";
            send_msg(socket, name);
            socket.recv(&received);

            //发图片
            //摄像头 带标记图像
            send_pic(socket, frame);
            socket.recv(&received);

            //face_num个人脸的图像
            VideoCapture capture(0);
            Mat next;
            capture>>next;
            int x_b=cvRound(next.cols/nor.width);int y_b=cvRound(next.rows/nor.height);
            for(vector<location>::iterator iter=final_location.begin();iter!=final_location.end();iter++){                
                int x=cvRound(x_b*(*iter).x);int y = cvRound(y_b*(*iter).y);
                int w =cvRound(x_b* (*iter).w);int h =cvRound( y_b*(*iter).h); 
                Rect rect(x,y,w,h);
                Mat send=(next(rect));
                send_pic(socket, send);
                socket.recv(&received);
            }

            std::string tmp = "send_picture_done";
            send_msg(socket, tmp);

        } else if (command == "none") {
            std::string tmp = "none";
            send_msg(socket, tmp);
        } else if (command == "start_traning") {
            train_elm();
            std::string tmp = "start_training";
            send_msg(socket, tmp);
        } else if (command == "change_train_set") {
            std::string tmp = "change_train_set";
            send_msg(socket, tmp);
            //收人名
            // socket.recv(&received);
            // std::string human_name =    std::string((char *)received.data(), received.size());
            human_name = recv_msg(socket);
            //检测文件夹是否存在 没有就创建一个
            mkdir_human_name( human_name ,names);


            tmp = "received_human_name";
            send_msg(socket, tmp);

            //收照片名字        好像不需要了
            // socket.recv(&received);
            // std::string picture_name = std::string((char *)received.data(), received.size());
            std::string picture_name = recv_msg(socket);
            tmp = "received_picture_name";
            send_msg(socket, tmp);

            //收图
            socket.recv(&received);
            std::vector<uchar> img_data(received.size());
            memcpy(img_data.data(), received.data(), received.size());
            rec_img = cv::imdecode(img_data, cv::IMREAD_COLOR);
            string sss=trainfile_path+"/"+human_name+".jpg";
            imwrite(sss, rec_img);
            tmp = "received_picture";
            send_msg(socket, tmp);

        } else {
            std::cout << "GGGGGGGGGGGGGGGGGGGG" << std::endl;
        }
    }

    return 0;
}
