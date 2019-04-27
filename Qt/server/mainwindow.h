#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<qt/QtCore/QCoreApplication>
#include <string>
#include<QTimer>
#include "libzmq.hpp"
#include<QThread>

//using namespace std;
extern std::string command;
extern  zmq::socket_t socket;
extern zmq::message_t reply;
extern zmq::message_t request;


class thr : public QThread
{
    void run() override {
        while(1){

        
    cout<<"hello"<<endl;
    std::cout << "command: " << command << std::endl;
    send_msg(socket, command);
    if (!strcmp(command.c_str(), "send_picture")) {
        //下位机发图，上位机收图
        //收人脸数
        socket.recv(&request);
        int face_num =
            std::stoi(std::string((char *)request.data(), request.size()));
        send_msg(socket, "received_face_num");
        //人脸名字
        socket.recv(&request);
        std::string name =   std::string((char *)request.data(), request.size());
        send_msg(socket, "received_face_name");
        //收图片
        cv::Mat img;

        socket.recv(&request);
        std::vector<uchar> img_data(request.size());
        memcpy(img_data.data(), request.data(), request.size());
        img = cv::imdecode(img_data, cv::IMREAD_COLOR);
        imwrite("cap.jpg", img);
        send_msg(socket, "reveice_picture_i");

        for (int i = 0; i < face_num; i++) {
            socket.recv(&request);
            std::vector<uchar> img_data(request.size());
            memcpy(img_data.data(), request.data(), request.size());
            img = cv::imdecode(img_data, cv::IMREAD_COLOR);
            imwrite("face" + to_string(i) + ".jpg", img);
            send_msg(socket, "reveice_picture_i");
        }
        socket.recv(&request);
    } else if (!strcmp(command.c_str(), "none")) {
        socket.recv(&request);
    } else if (!strcmp(command.c_str(), "start_traning") ) {
        //收
        socket.recv(&request);
    } else if (!strcmp(command.c_str(), "change_train_set")) {
        socket.recv(&request);
        //发人名
        std::string human_name = "hhh";
        send_msg(socket, human_name);
        //收
        socket.recv(&request);
        //发照片名字
//             std::string picture_name = "1.jpg";
//             send_msg(socket, picture_name);
        //收
//             socket.recv(&request);
        //发送图片
        send_pic(socket, "../pic/1.png");
        //收
        socket.recv(&request);
    } else {
        std::cout << "GGGGGGGGGGGGGGGGGGGGGGGGGG" << std::endl;
    }
        }
    // run();

     
    }
};












namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timerUpdate();
    void on_cmd_1_clicked();

    void on_cmd_2_clicked();

    void on_cmd_3_clicked();

    void on_cmd_4_clicked();

    void on_cmd_connect_clicked();


private:
    Ui::MainWindow *ui;
    thr t;
 
};




#endif // MAINWINDOW_H
