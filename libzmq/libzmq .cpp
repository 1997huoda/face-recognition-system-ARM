

#include "libzmq.hpp"

std::string command;

void send_msg(zmq::socket_t &socket, std::string str) {
    zmq::message_t msg(str.size());
    memcpy(msg.data(), str.c_str(), str.size());
    socket.send(msg);
}
std::string recv_msg(zmq::socket_t &socket) {
    zmq::message_t received;
    socket.recv(received);
    return std::string((char *)received.data(), received.size());
}
void send_pic(zmq::socket_t &socket, cv::Mat img) {
    // cv::Mat img = cv::imread("../pic/1.png");
    std::vector<uchar> img_data;
    cv::imencode(".jpg", img, img_data);
    zmq::message_t pic(img_data.size());
    zmq::message_t msg(img_data.size());
    memcpy(pic.data(), img_data.data(), img_data.size());
    socket.send(pic);
}
void send_pic(zmq::socket_t &socket, std::string path) {
    cv::Mat img = cv::imread(path);
    send_pic(socket, img);
}
Mat receive_pic(zmq::socket_t &socket){
            Mat rec_img;
            zmq::message_t received;
            socket.recv(received);
			std::vector<uchar> img_data(received.size());
			memcpy(img_data.data(), received.data(), received.size());
			rec_img = cv::imdecode(img_data, cv::IMREAD_COLOR);
            return rec_img;
}

