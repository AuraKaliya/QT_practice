#include "socketwidget.h"

SocketWidget::SocketWidget(QTcpSocket* socket,QWidget *parent)
    : QWidget{parent},m_socket(socket)
{
    m_label=new QLabel(this);
    m_label->setMinimumHeight(50);
    m_layout=new QHBoxLayout();
    m_layout->addWidget(m_label);
    this->setLayout(m_layout);
    if(m_socket!=nullptr)
    {
        m_label->setText("socket:"+QString::number(QRandomGenerator::global()->bounded(200)));
    }

}

void SocketWidget::setSocket(QTcpSocket *socket)
{
    m_socket=socket;
    if(m_socket!=nullptr)
    {
        m_label->setText("socket:"+QString::number(QRandomGenerator::global()->bounded(200)));
    }
}

QTcpSocket *SocketWidget::getSocket()
{
    return m_socket;
}

QString SocketWidget::getSocketName()
{
    return m_label->text();
}
