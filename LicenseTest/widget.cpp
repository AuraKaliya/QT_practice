#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(int argc, char **argv, QWidget *parent)
    : QWidget(parent),ui(new Ui::Widget),m_argc(argc)
    , m_argv(argv)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_P)
    {
        //OpenSSL 加解密 RSA
        OpenSSLTest test;
        test.example();
    }
    if(e->key() == Qt::Key_O)
    {
        //OpenSSL 验证证书
        OpenSSLLicenseTest test;
        test.example(m_argc,m_argv);
    }

}

