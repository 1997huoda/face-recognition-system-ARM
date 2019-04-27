#ifndef _SERVER_H
#define _SERVER_H
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <zmq.hpp>
using namespace std;

void send_msg(zmq::socket_t &socket, std::string str);
std::string recv_msg(zmq::socket_t &socket) ;
void send_pic(zmq::socket_t &socket, cv::Mat img);
void send_pic(zmq::socket_t &socket, std::string path);
int run();

 std::string command;

#endif /* _SERVER_H */