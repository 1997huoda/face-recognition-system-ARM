#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "libzmq.hpp"
#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QTimer>
#include <qt/QtCore/QCoreApplication>
#include <string>

// using namespace std;
//command in libzmq
extern std::string command;

extern zmq::socket_t socket;
extern zmq::message_t reply;
extern zmq::message_t request;

extern string name;
extern string human_name;
extern Mat change_mat;
// extern bool flag;
extern Mat recieve_mat[];
extern Mat cap;
// human_name = qstr.toStdString();
// QString qstr;
// qstr = QString::fromStdString(str);

class thr : public QThread {
    Q_OBJECT
signals:
    void update_signal();
    void cmd_st();
    void get_text();
    void change_over();
    void stop_sig();
    void after();
    void check_cmd_st();

public:
    void run() override {
        while (1) {
            this->check_cmd_st();
            // if (flag) {
            //     sleep(100);
            //     continue;
            // }

            cout << "hello" << endl;
            std::cout << "command: " << command << std::endl;
            send_msg(socket, command);
            this->cmd_st();
            if (!strcmp(command.c_str(), "send_picture")) {
                //下位机发图，上位机收图
                //收人脸数
                socket.recv(&request);
                int face_num = std::atoi( std::string((char *)request.data(), request.size()).c_str());
                send_msg(socket, "received_face_num");
                //人脸名字
                socket.recv(&request);
                name = std::string((char *)request.data(), request.size());
                send_msg(socket, "received_face_name");
                //收图片
                cap=receive_pic(socket);
                send_msg(socket, "reveice_picture_i");

                for (int i = 0; i < face_num; i++) {
                    if(i>5)
                        continue;   
                    recieve_mat[i] = receive_pic(socket);
                    resize( recieve_mat[i],  recieve_mat[i], cv::Size(100, 100), 0, 0, INTER_LINEAR);
                    send_msg(socket, "reveice_picture_i");
                }
                this->update_signal();
                socket.recv(&request);

            } else if (!strcmp(command.c_str(), "none")) {
                socket.recv(&request);
            } else if (!strcmp(command.c_str(), "start_traning")) {
                //收
                socket.recv(&request);

                //只执行一次命令 自动切换
                // flag=true;
                command="send_picture";
                // this->after();
            } else if (!strcmp(command.c_str(), "change_train_set")) {
                socket.recv(&request);
                //发人名
                //                human_name = "hhh";
                send_msg(socket, human_name);
                //收
                socket.recv(&request);

                //发送图片
                send_pic(socket, change_mat);
                //收
                socket.recv(&request);

                this->change_over();

                //防止重复发送 执行完change_train_set 下一个命令自己切换
                // flag =true;
                command = "send_picture";
                // command="send_picture";
                // this->after();
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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    void LabelDisplayMat(QLabel *label, cv::Mat &mat);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    

private slots:
    void timerUpdate();
    void on_cmd_1_clicked();

    void on_cmd_2_clicked();

    void on_cmd_3_clicked();

    void on_cmd_4_clicked();
    void stop_after();
    void on_cmd_connect_clicked();

    void update_ui();
    void cmd_up();
    void change_send_success();

    void on_change_7_clicked();

    void on_change_8_clicked();

    void on_change_9_clicked();

    void on_change_10_clicked();

    void on_change_11_clicked();

    void on_change_12_clicked();

private:
    Ui::MainWindow *ui;
    thr t;
};

#endif // MAINWINDOW_H
