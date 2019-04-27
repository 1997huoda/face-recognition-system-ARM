#ifndef _LIBZMQ_H
#define _LIBZMQ_H

#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <zmq.hpp>

using namespace std;
using namespace cv;

extern std::string command;

void send_msg(zmq::socket_t & socket, std::string str);

std::string recv_msg(zmq::socket_t & socket);

void send_pic(zmq::socket_t & socket, cv::Mat img);

void send_pic(zmq::socket_t & socket, std::string path);



#endif /* _LIBZMQ_H */
