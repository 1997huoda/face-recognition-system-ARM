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
#include <QtWidgets/QTextEdit>
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
    QPushButton *cmd_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *cmd_state;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *name_1;
    QLabel *name_2;
    QLabel *name_3;
    QLabel *name_4;
    QLabel *name_5;
    QLabel *name_6;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *text_1;
    QTextEdit *text_2;
    QTextEdit *text_3;
    QTextEdit *text_4;
    QTextEdit *text_5;
    QTextEdit *text_6;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *change_7;
    QPushButton *change_8;
    QPushButton *change_9;
    QPushButton *change_10;
    QPushButton *change_11;
    QPushButton *change_12;
    QHBoxLayout *horizontalLayout;
    QLabel *face_1;
    QLabel *face_2;
    QLabel *face_3;
    QLabel *face_4;
    QLabel *face_5;
    QLabel *face_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 620);
        MainWindow->setMinimumSize(QSize(840, 620));
        MainWindow->setMaximumSize(QSize(840, 620));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        cmd_connect = new QPushButton(centralwidget);
        cmd_connect->setObjectName(QString::fromUtf8("cmd_connect"));
        cmd_connect->setGeometry(QRect(360, 20, 80, 20));
        cap = new QLabel(centralwidget);
        cap->setObjectName(QString::fromUtf8("cap"));
        cap->setGeometry(QRect(70, 50, 320, 240));
        cap->setMinimumSize(QSize(320, 240));
        cap->setMaximumSize(QSize(320, 240));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(420, 54, 381, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cmd_1 = new QPushButton(verticalLayoutWidget);
        cmd_1->setObjectName(QString::fromUtf8("cmd_1"));

        verticalLayout->addWidget(cmd_1);

        cmd_2 = new QPushButton(verticalLayoutWidget);
        cmd_2->setObjectName(QString::fromUtf8("cmd_2"));

        verticalLayout->addWidget(cmd_2);

        cmd_4 = new QPushButton(verticalLayoutWidget);
        cmd_4->setObjectName(QString::fromUtf8("cmd_4"));

        verticalLayout->addWidget(cmd_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(20);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_2);

        cmd_state = new QLabel(verticalLayoutWidget);
        cmd_state->setObjectName(QString::fromUtf8("cmd_state"));
        cmd_state->setFont(font);
        cmd_state->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(cmd_state);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(30, 320, 771, 269));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        name_1 = new QLabel(verticalLayoutWidget_3);
        name_1->setObjectName(QString::fromUtf8("name_1"));
        name_1->setMinimumSize(QSize(100, 50));
        name_1->setMaximumSize(QSize(100, 50));
        name_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_1);

        name_2 = new QLabel(verticalLayoutWidget_3);
        name_2->setObjectName(QString::fromUtf8("name_2"));
        name_2->setMinimumSize(QSize(100, 50));
        name_2->setMaximumSize(QSize(100, 50));
        name_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_2);

        name_3 = new QLabel(verticalLayoutWidget_3);
        name_3->setObjectName(QString::fromUtf8("name_3"));
        name_3->setMinimumSize(QSize(100, 50));
        name_3->setMaximumSize(QSize(100, 50));
        name_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_3);

        name_4 = new QLabel(verticalLayoutWidget_3);
        name_4->setObjectName(QString::fromUtf8("name_4"));
        name_4->setMinimumSize(QSize(100, 50));
        name_4->setMaximumSize(QSize(100, 50));
        name_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_4);

        name_5 = new QLabel(verticalLayoutWidget_3);
        name_5->setObjectName(QString::fromUtf8("name_5"));
        name_5->setMinimumSize(QSize(100, 50));
        name_5->setMaximumSize(QSize(100, 50));
        name_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_5);

        name_6 = new QLabel(verticalLayoutWidget_3);
        name_6->setObjectName(QString::fromUtf8("name_6"));
        name_6->setMinimumSize(QSize(100, 50));
        name_6->setMaximumSize(QSize(100, 50));
        name_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(name_6);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        text_1 = new QTextEdit(verticalLayoutWidget_3);
        text_1->setObjectName(QString::fromUtf8("text_1"));
        text_1->setMinimumSize(QSize(120, 50));
        text_1->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_1);

        text_2 = new QTextEdit(verticalLayoutWidget_3);
        text_2->setObjectName(QString::fromUtf8("text_2"));
        text_2->setMinimumSize(QSize(120, 50));
        text_2->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_2);

        text_3 = new QTextEdit(verticalLayoutWidget_3);
        text_3->setObjectName(QString::fromUtf8("text_3"));
        text_3->setMinimumSize(QSize(120, 50));
        text_3->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_3);

        text_4 = new QTextEdit(verticalLayoutWidget_3);
        text_4->setObjectName(QString::fromUtf8("text_4"));
        text_4->setMinimumSize(QSize(120, 50));
        text_4->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_4);

        text_5 = new QTextEdit(verticalLayoutWidget_3);
        text_5->setObjectName(QString::fromUtf8("text_5"));
        text_5->setMinimumSize(QSize(120, 50));
        text_5->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_5);

        text_6 = new QTextEdit(verticalLayoutWidget_3);
        text_6->setObjectName(QString::fromUtf8("text_6"));
        text_6->setMinimumSize(QSize(120, 50));
        text_6->setMaximumSize(QSize(120, 50));

        horizontalLayout_3->addWidget(text_6);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        change_7 = new QPushButton(verticalLayoutWidget_3);
        change_7->setObjectName(QString::fromUtf8("change_7"));

        horizontalLayout_6->addWidget(change_7);

        change_8 = new QPushButton(verticalLayoutWidget_3);
        change_8->setObjectName(QString::fromUtf8("change_8"));

        horizontalLayout_6->addWidget(change_8);

        change_9 = new QPushButton(verticalLayoutWidget_3);
        change_9->setObjectName(QString::fromUtf8("change_9"));

        horizontalLayout_6->addWidget(change_9);

        change_10 = new QPushButton(verticalLayoutWidget_3);
        change_10->setObjectName(QString::fromUtf8("change_10"));

        horizontalLayout_6->addWidget(change_10);

        change_11 = new QPushButton(verticalLayoutWidget_3);
        change_11->setObjectName(QString::fromUtf8("change_11"));

        horizontalLayout_6->addWidget(change_11);

        change_12 = new QPushButton(verticalLayoutWidget_3);
        change_12->setObjectName(QString::fromUtf8("change_12"));

        horizontalLayout_6->addWidget(change_12);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        face_1 = new QLabel(verticalLayoutWidget_3);
        face_1->setObjectName(QString::fromUtf8("face_1"));
        face_1->setMinimumSize(QSize(100, 100));
        face_1->setMaximumSize(QSize(100, 100));
        face_1->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_1);

        face_2 = new QLabel(verticalLayoutWidget_3);
        face_2->setObjectName(QString::fromUtf8("face_2"));
        face_2->setMinimumSize(QSize(100, 100));
        face_2->setMaximumSize(QSize(100, 100));
        face_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_2);

        face_3 = new QLabel(verticalLayoutWidget_3);
        face_3->setObjectName(QString::fromUtf8("face_3"));
        face_3->setMinimumSize(QSize(100, 100));
        face_3->setMaximumSize(QSize(100, 100));
        face_3->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_3);

        face_4 = new QLabel(verticalLayoutWidget_3);
        face_4->setObjectName(QString::fromUtf8("face_4"));
        face_4->setMinimumSize(QSize(100, 100));
        face_4->setMaximumSize(QSize(100, 100));
        face_4->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_4);

        face_5 = new QLabel(verticalLayoutWidget_3);
        face_5->setObjectName(QString::fromUtf8("face_5"));
        face_5->setMinimumSize(QSize(100, 100));
        face_5->setMaximumSize(QSize(100, 100));
        face_5->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_5);

        face_6 = new QLabel(verticalLayoutWidget_3);
        face_6->setObjectName(QString::fromUtf8("face_6"));
        face_6->setMinimumSize(QSize(100, 100));
        face_6->setMaximumSize(QSize(100, 100));
        face_6->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(face_6);


        verticalLayout_5->addLayout(horizontalLayout);

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
        cmd_4->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "cmd:", nullptr));
        cmd_state->setText(QApplication::translate("MainWindow", "cmd", nullptr));
        name_1->setText(QApplication::translate("MainWindow", "name_1", nullptr));
        name_2->setText(QApplication::translate("MainWindow", "name_2", nullptr));
        name_3->setText(QApplication::translate("MainWindow", "name_3", nullptr));
        name_4->setText(QApplication::translate("MainWindow", "name_4", nullptr));
        name_5->setText(QApplication::translate("MainWindow", "name_5", nullptr));
        name_6->setText(QApplication::translate("MainWindow", "name_6", nullptr));
        change_7->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        change_8->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        change_9->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        change_10->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        change_11->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        change_12->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271", nullptr));
        face_1->setText(QApplication::translate("MainWindow", "face_1", nullptr));
        face_2->setText(QApplication::translate("MainWindow", "face_2", nullptr));
        face_3->setText(QApplication::translate("MainWindow", "face_3", nullptr));
        face_4->setText(QApplication::translate("MainWindow", "face_4", nullptr));
        face_5->setText(QApplication::translate("MainWindow", "face_5", nullptr));
        face_6->setText(QApplication::translate("MainWindow", "face_6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
