#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include<QTimer>
#include "libzmq.hpp"

//using namespace std;
extern std::string command;
extern  zmq::socket_t socket;
extern zmq::message_t reply;
extern zmq::message_t request;

void run();

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
    void on_cmd_1_clicked();

    void on_cmd_2_clicked();

    void on_cmd_3_clicked();

    void on_cmd_4_clicked();

    void on_cmd_connect_clicked();

    void TimerTimeOut();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    void InitTimer();
};

#endif // MAINWINDOW_H
