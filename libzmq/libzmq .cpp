

#include "libzmq.hpp"

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

