#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "libzmq.hpp"

zmq::context_t context(3);
zmq::socket_t socket(context, ZMQ_REP);
zmq::message_t reply;
zmq::message_t request;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void run(){
    // command = read_command();
    std::cout << "command: " << command << std::endl;
    send_msg(socket, command);
    if (command == "send_picture") {
        //下位机发图，上位机收图
        //收人脸数
        socket.recv(&request);
        int face_num =
            std::stoi(std::string((char *)request.data(), request.size()));
        send_msg(socket, "received_face_num");
        //人脸名字
        socket.recv(&request);
        std::string name =
            std::string((char *)request.data(), request.size());
        send_msg(socket, "received_face_name");
        //收图片
        cv::Mat img;
        for (int i = 0; i <= face_num; i++) {
            socket.recv(&request);
            std::vector<uchar> img_data(request.size());
            memcpy(img_data.data(), request.data(), request.size());
            img = cv::imdecode(img_data, cv::IMREAD_COLOR);
            imwrite("face" + to_string(i) + ".jpg", img);
            send_msg(socket, "reveice_picture_i");
        }
        socket.recv(&request);
    } else if (command == "none") {
        socket.recv(&request);
    } else if (command == "start_traning") {
        //收
        socket.recv(&request);
    } else if (command == "change_train_set") {
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
void MainWindow::on_cmd_1_clicked()
{
    //日常人脸识别 ARM发送识别信息
     command="send_picture";
     run();
}

void MainWindow::on_cmd_2_clicked()
{
    //开始ELMInELM训练 参数保存在本地txt中
    command="start_traning";
    run();
}

void MainWindow::on_cmd_3_clicked()
{
    //改变训练集 PC传参数
    command="change_train_set";
    run();
}

void MainWindow::on_cmd_4_clicked()
{
    //空
    command="none";
    run();
}

void MainWindow::on_cmd_connect_clicked()
{
     socket.bind("tcp://*:5555");
     socket.recv(&request);
}

void MainWindow::InitTimer()
{
   if(NULL == m_timer)
       m_timer = new QTimer;
   //设置定时器是否为单次触发。默认为 false 多次触发
   m_timer->setSingleShot(false);
   //启动或重启定时器, 并设置定时器时间：毫秒
   m_timer->start(2000);
   //定时器触发信号槽
   connect(m_timer, SIGNAL(timeout()), this, SLOT(ImageTimerTimeout()));
}

void MainWindow::TimerTimeOut()
{
    //判断定时器是否运行
    if(m_timer->isActive())
        m_timer->stop();   //停止定时器
    //执行定时器触发时需要处理的业务
}

