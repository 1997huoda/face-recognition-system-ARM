#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <zmq.hpp>

using namespace std;
using namespace cv;
void send_msg(zmq::socket_t &socket, std::string str) {
    zmq::message_t msg(str.size());
    memcpy(msg.data(), str.c_str(), str.size());
    socket.send(msg);
}
std::string recv_msg(zmq::socket_t &socket) {
    zmq::message_t received;
    socket.recv(&received);
    return std::string((char *)received.data(), received.size());
}
void send_pic(zmq::socket_t &socket, cv::Mat img) {
    // cv::Mat img = cv::imread("../pic/1.png");
    std::vector<uchar> img_data;
    cv::imencode(".png", img, img_data);
    zmq::message_t pic(img_data.size());
    zmq::message_t msg(img_data.size());
    memcpy(pic.data(), img_data.data(), img_data.size());
    socket.send(pic);
}
void send_pic(zmq::socket_t &socket, std::string path) {
    cv::Mat img = cv::imread(path);
    send_pic(socket, img);
}

enum status { none, send_picture, start_traning, change_train_set };
int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    std::cout << "waiting connetting" << std::endl;
    socket.connect("tcp://localhost:5555");

    cv::Mat img = cv::imread("../pic/1.png");
    zmq::message_t msg;
    zmq::message_t received;
    std::string command;
    send_msg(socket, "none");

    while (true) {
        //接收命令
        command = recv_msg(socket);
        if (command == "send_picture") {
            //发人脸数量
            // std::string face_num = std::to_string(1);
            int face_num = 1;
            send_msg(socket, to_string(face_num));
            socket.recv(&received);

            //发人脸名字
            std::string name = "dada";
            send_msg(socket, name);
            socket.recv(&received);
            //发图片
            send_pic(socket, img);
            socket.recv(&received);
            for (int i = 0; i < face_num; i++) {
                send_pic(socket, img);
                socket.recv(&received);
            }
            std::string tmp = "send_picture_done";
            send_msg(socket, tmp);

        } else if (command == "none") {
            std::string tmp = "none";
            send_msg(socket, tmp);
        } else if (command == "start_traning") {
            std::string tmp = "start_training";
            send_msg(socket, tmp);
        } else if (command == "change_train_set") {
            std::string tmp = "change_train_set";
            send_msg(socket, tmp);
            //收人名
            socket.recv(&received);
            std::string human_name =
                std::string((char *)received.data(), received.size());
            tmp = "received_human_name";
            send_msg(socket, tmp);

            //收照片名字
            socket.recv(&received);
            std::string picture_name =
                std::string((char *)received.data(), received.size());
            tmp = "received_picture_name";
            send_msg(socket, tmp);

            //收图
            socket.recv(&received);
            std::vector<uchar> img_data(received.size());
            memcpy(img_data.data(), received.data(), received.size());
            img = cv::imdecode(img_data, cv::IMREAD_COLOR);
            imwrite("a.jpg", img);
            tmp = "received_picture";
            send_msg(socket, tmp);

        } else {
            std::cout << "GGGGGGGGGGGGGGGGGGGG" << std::endl;
        }
    }

    return 0;
}
