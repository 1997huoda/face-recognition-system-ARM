#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "libzmq.hpp"

zmq::context_t context(3);
zmq::socket_t socket(context, ZMQ_REP);
zmq::message_t reply;
zmq::message_t request;

string name;
string human_name;
Mat change_mat;
bool flag;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QObject::connect(&t, &thr::update_signal, this, &MainWindow::update_ui);
    QObject::connect(&t, &thr::cmd_st, this, &MainWindow::cmd_up);
    QObject::connect(&t, &thr::change_over, this,   &MainWindow::change_send_success);
    QObject::connect(&t, &thr::stop_sig, this, &MainWindow::on_cmd_4_clicked);

    flag = false;
    if (t.isRunning() == true)
        t.exit();
}

void MainWindow::timerUpdate() {
    // cout<<"time up"<<endl;
    // run();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_cmd_1_clicked() {
    //日常人脸识别 ARM发送识别信息
    command = "send_picture";
    //  run();
}

void MainWindow::on_cmd_2_clicked() {
    //开始ELMInELM训练 参数保存在本地txt中
    command = "start_traning";
    // run();
}

void MainWindow::on_cmd_3_clicked() {
    //改变训练集 PC传参数
    command = "change_train_set";
    // run();
    TickMeter tm;
    tm.start();
    int xxx = 1e9;
    while (--xxx)
        ;
    tm.stop();
    std::cout << "xxx 用时      " << tm.getTimeSec() * 1000 << "   ms"
              << endl; //输出是s
}

void MainWindow::on_cmd_4_clicked() {
    //空
    if(flag){
        command = "send_picture";
    }else {
        command = "none";
    }
    flag = !flag;
    if(!flag){
        ui->cmd_4->setText(QString::fromStdString("暂停"));
    }else{
        //
        ui->cmd_4->setText(QString::fromStdString("继续"));
    }
    
    // run();
}

void MainWindow::on_cmd_connect_clicked() {
    socket.bind("tcp://*:5555");
    socket.recv(&request);
    cout << "连接成功" << endl;
    ui->cmd_connect->setEnabled(false);

    // QTimer *timer = new QTimer(this);
    // connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    // timer->start(1000);
    t.start();
}
void MainWindow::cmd_up() {
    ui->cmd_state->setText(QString::fromStdString(command));
}
void MainWindow::update_ui() {
    QPixmap cap("cap.jpg");
    ui->cap->setPixmap(cap);
    ui->cap->show();
    QPixmap face1("face0.jpg");
    ui->face_1->setPixmap(face1);
    ui->face_1->show();
    QPixmap face2("face1.jpg");
    ui->face_2->setPixmap(face2);
    ui->face_2->show();
    QPixmap face3("face2.jpg");
    ui->face_3->setPixmap(face3);
    ui->face_3->show();
    QPixmap face4("face3.jpg");
    ui->face_4->setPixmap(face4);
    ui->face_4->show();
    QPixmap face5("face4.jpg");
    ui->face_5->setPixmap(face5);
    ui->face_5->show();
    QPixmap face6("face5.jpg");
    ui->face_6->setPixmap(face6);
    ui->face_6->show();

    vector<string> name_label;
    //    string receive = "lajfl/asjdflkjdsf/ajkflsdfjs/gbhg/renming/";
    string tmp;
    for (int i = 0; i < name.size(); i++) {
        if (name[i] != '/') {
            tmp.push_back(name[i]);
        } else {
            name_label.push_back(tmp);
            tmp.clear();
        }
    }
    if (name_label.size() >= 1)
        ui->name_1->setText(QString::fromStdString(name_label[0]));
    if (name_label.size() >= 2)
        ui->name_2->setText(QString::fromStdString(name_label[1]));
    if (name_label.size() >= 3)
        ui->name_3->setText(QString::fromStdString(name_label[2]));
    if (name_label.size() >= 4)
        ui->name_4->setText(QString::fromStdString(name_label[3]));
    if (name_label.size() >= 5)
        ui->name_5->setText(QString::fromStdString(name_label[4]));
    if (name_label.size() >= 6)
        ui->name_6->setText(QString::fromStdString(name_label[5]));
}

void MainWindow::on_change_7_clicked() {
    QString qstr = ui->text_1->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face0.jpg");
    command = "change_train_set";
}

void MainWindow::on_change_8_clicked() {
    QString qstr = ui->text_2->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face1.jpg");
    command = "change_train_set";
}

void MainWindow::on_change_9_clicked() {
    QString qstr = ui->text_3->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face2.jpg");
    command = "change_train_set";
}

void MainWindow::on_change_10_clicked() {
    QString qstr = ui->text_4->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face3.jpg");
    command = "change_train_set";
}

void MainWindow::on_change_11_clicked() {
    QString qstr = ui->text_5->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face4.jpg");
    command = "change_train_set";
}

void MainWindow::on_change_12_clicked() {
    QString qstr = ui->text_6->toPlainText();
    if (qstr.isEmpty()) {
        QMessageBox::critical(this, "ERROR", "更改后的名字不能为空",
                              QMessageBox::Yes);
        return;
    }
    human_name = qstr.toStdString();
    change_mat = imread("face5.jpg");
    command = "change_train_set";
}
void MainWindow::change_send_success() {
    QString qstr = ui->text_1->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_1->setText(qstr);
        ui->text_1->setText(QString::fromStdString(""));
    }
    qstr = ui->text_2->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_2->setText(qstr);
        ui->text_2->setText(QString::fromStdString(""));
    }
    qstr = ui->text_3->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_3->setText(qstr);
        ui->text_3->setText(QString::fromStdString(""));
    }
    qstr = ui->text_4->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_4->setText(qstr);
        ui->text_4->setText(QString::fromStdString(""));
    }
    qstr = ui->text_5->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_5->setText(qstr);
        ui->text_5->setText(QString::fromStdString(""));
    }
    qstr = ui->text_6->toPlainText();
    if (!qstr.isEmpty()) {
        ui->name_6->setText(qstr);
        ui->text_6->setText(QString::fromStdString(""));
    }
}
