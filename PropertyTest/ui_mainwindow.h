/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *TipsLabel;
    QListWidget *list;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *name;
    QLineEdit *propertyEdit;
    QPushButton *updateBtn;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *newEdit;
    QComboBox *typeBox;
    QPushButton *newBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(532, 713);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        TipsLabel = new QLabel(widget);
        TipsLabel->setObjectName("TipsLabel");

        verticalLayout->addWidget(TipsLabel);

        list = new QListWidget(widget);
        list->setObjectName("list");

        verticalLayout->addWidget(list);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        name = new QLabel(widget_2);
        name->setObjectName("name");
        name->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(name);

        propertyEdit = new QLineEdit(widget_2);
        propertyEdit->setObjectName("propertyEdit");

        horizontalLayout->addWidget(propertyEdit);

        updateBtn = new QPushButton(widget_2);
        updateBtn->setObjectName("updateBtn");

        horizontalLayout->addWidget(updateBtn);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newEdit = new QLineEdit(widget_3);
        newEdit->setObjectName("newEdit");

        horizontalLayout_2->addWidget(newEdit);

        typeBox = new QComboBox(widget_3);
        typeBox->setObjectName("typeBox");

        horizontalLayout_2->addWidget(typeBox);

        newBtn = new QPushButton(widget_3);
        newBtn->setObjectName("newBtn");

        horizontalLayout_2->addWidget(newBtn);


        verticalLayout_2->addWidget(widget_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 532, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        TipsLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        name->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        updateBtn->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        newBtn->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
