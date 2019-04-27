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
    if(t.isRunning() == true)
        t.exit();
}

void MainWindow::timerUpdate()
{
    // cout<<"time up"<<endl;
    // run();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cmd_1_clicked()
{
    //日常人脸识别 ARM发送识别信息
     command="send_picture";
    //  run();
}

void MainWindow::on_cmd_2_clicked()
{
    //开始ELMInELM训练 参数保存在本地txt中
    command="start_traning";
    // run();
}

void MainWindow::on_cmd_3_clicked()
{
    //改变训练集 PC传参数
    command="change_train_set";
    // run();
}

void MainWindow::on_cmd_4_clicked()
{
    //空
    command="none";
    // run();
}

void MainWindow::on_cmd_connect_clicked()
{
    socket.bind("tcp://*:5555");
    socket.recv(&request);
    cout<<"连接成功"<<endl;
    ui->cmd_connect->setEnabled(false);

    // QTimer *timer = new QTimer(this);
    // connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    // timer->start(1000);
    t.start();
}



