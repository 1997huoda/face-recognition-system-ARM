/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *cmd_connect;
    QLabel *cap;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *cmd_1;
    QPushButton *cmd_2;
    QPushButton *cmd_3;
    QPushButton *cmd_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *cmd_state;
    QLabel *label_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *face_1;
    QLabel *face_2;
    QLabel *face_3;
    QLabel *face_4;
    QLabel *face_5;
    QLabel *face_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *name_1;
    QLabel *name_2;
    QLabel *name_3;
    QLabel *name_4;
    QLabel *name_5;
    QLabel *name_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 515);
        MainWindow->setMinimumSize(QSize(840, 515));
        MainWindow->setMaximumSize(QSize(840, 515));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        cmd_connect = new QPushButton(centralwidget);
        cmd_connect->setObjectName(QString::fromUtf8("cmd_connect"));
        cmd_connect->setGeometry(QRect(360, 20, 80, 20));
        cap = new QLabel(centralwidget);
        cap->setObjectName(QString::fromUtf8("cap"));
        cap->setGeometry(QRect(60, 60, 320, 240));
        cap->setMinimumSize(QSize(320, 240));
        cap->setMaximumSize(QSize(320, 240));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(420, 60, 160, 184));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cmd_1 = new QPushButton(verticalLayoutWidget);
        cmd_1->setObjectName(QString::fromUtf8("cmd_1"));

        verticalLayout->addWidget(cmd_1);

        cmd_2 = new QPushButton(verticalLayoutWidget);
        cmd_2->setObjectName(QString::fromUtf8("cmd_2"));

        verticalLayout->addWidget(cmd_2);

        cmd_3 = new QPushButton(verticalLayoutWidget);
        cmd_3->setObjectName(QString::fromUtf8("cmd_3"));

        verticalLayout->addWidget(cmd_3);

        cmd_4 = new QPushButton(verticalLayoutWidget);
        cmd_4->setObjectName(QString::fromUtf8("cmd_4"));

        verticalLayout->addWidget(cmd_4);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(600, 70, 221, 82));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(20);
        label_2->setFont(font);

        verticalLayout_3->addWidget(label_2);

        cmd_state = new QLabel(verticalLayoutWidget_2);
        cmd_state->setObjectName(QString::fromUtf8("cmd_state"));
        cmd_state->setFont(font);

        verticalLayout_3->addWidget(cmd_state);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(210, 490, 251, 291));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 340, 751, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        face_1 = new QLabel(horizontalLayoutWidget);
        face_1->setObjectName(QString::fromUtf8("face_1"));
        face_1->setMinimumSize(QSize(100, 100));
        face_1->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_1);

        face_2 = new QLabel(horizontalLayoutWidget);
        face_2->setObjectName(QString::fromUtf8("face_2"));
        face_2->setMinimumSize(QSize(100, 100));
        face_2->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_2);

        face_3 = new QLabel(horizontalLayoutWidget);
        face_3->setObjectName(QString::fromUtf8("face_3"));
        face_3->setMinimumSize(QSize(100, 100));
        face_3->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_3);

        face_4 = new QLabel(horizontalLayoutWidget);
        face_4->setObjectName(QString::fromUtf8("face_4"));
        face_4->setMinimumSize(QSize(100, 100));
        face_4->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_4);

        face_5 = new QLabel(horizontalLayoutWidget);
        face_5->setObjectName(QString::fromUtf8("face_5"));
        face_5->setMinimumSize(QSize(100, 100));
        face_5->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_5);

        face_6 = new QLabel(horizontalLayoutWidget);
        face_6->setObjectName(QString::fromUtf8("face_6"));
        face_6->setMinimumSize(QSize(100, 100));
        face_6->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(face_6);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(50, 470, 751, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        name_1 = new QLabel(horizontalLayoutWidget_2);
        name_1->setObjectName(QString::fromUtf8("name_1"));

        horizontalLayout_2->addWidget(name_1);

        name_2 = new QLabel(horizontalLayoutWidget_2);
        name_2->setObjectName(QString::fromUtf8("name_2"));

        horizontalLayout_2->addWidget(name_2);

        name_3 = new QLabel(horizontalLayoutWidget_2);
        name_3->setObjectName(QString::fromUtf8("name_3"));

        horizontalLayout_2->addWidget(name_3);

        name_4 = new QLabel(horizontalLayoutWidget_2);
        name_4->setObjectName(QString::fromUtf8("name_4"));

        horizontalLayout_2->addWidget(name_4);

        name_5 = new QLabel(horizontalLayoutWidget_2);
        name_5->setObjectName(QString::fromUtf8("name_5"));

        horizontalLayout_2->addWidget(name_5);

        name_6 = new QLabel(horizontalLayoutWidget_2);
        name_6->setObjectName(QString::fromUtf8("name_6"));

        horizontalLayout_2->addWidget(name_6);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        cmd_connect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        cap->setText(QApplication::translate("MainWindow", "cap", nullptr));
        cmd_1->setText(QApplication::translate("MainWindow", "\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
        cmd_2->setText(QApplication::translate("MainWindow", "\350\256\255\347\273\203\346\250\241\345\236\213", nullptr));
        cmd_3->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260\345\233\276\347\211\207", nullptr));
        cmd_4->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "command:", nullptr));
        cmd_state->setText(QApplication::translate("MainWindow", "tmp", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        face_1->setText(QApplication::translate("MainWindow", "face_1", nullptr));
        face_2->setText(QApplication::translate("MainWindow", "face_2", nullptr));
        face_3->setText(QApplication::translate("MainWindow", "face_3", nullptr));
        face_4->setText(QApplication::translate("MainWindow", "face_4", nullptr));
        face_5->setText(QApplication::translate("MainWindow", "face_5", nullptr));
        face_6->setText(QApplication::translate("MainWindow", "face_6", nullptr));
        name_1->setText(QApplication::translate("MainWindow", "name_1", nullptr));
        name_2->setText(QApplication::translate("MainWindow", "name_2", nullptr));
        name_3->setText(QApplication::translate("MainWindow", "name_3", nullptr));
        name_4->setText(QApplication::translate("MainWindow", "name_4", nullptr));
        name_5->setText(QApplication::translate("MainWindow", "name_5", nullptr));
        name_6->setText(QApplication::translate("MainWindow", "name_6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
