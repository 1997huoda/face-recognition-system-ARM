#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    MainWindow window;
    MainWindow.show();
    qDebug() << "hello qt!";
    app.exec();
    return 0;
}
