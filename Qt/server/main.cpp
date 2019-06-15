#include "mainwindow.h"
#include <QApplication>
//#include "libzmq.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    command="none";



    return a.exec();
}
