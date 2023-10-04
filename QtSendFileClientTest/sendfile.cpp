#include "sendfile.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>
SendFile::SendFile(QObject *parent)
    : QObject{parent}
{

}

void SendFile::connectServer(unsigned short port, QString ip)
{
    if(m_socket==nullptr)
    {
        m_socket=new QTcpSocket;
        m_socket->connectToHost(QHostAddress(ip),port);
        connect(m_socket,&QTcpSocket::connected,this,[=](){
            emit linked();
        });
        connect(m_socket,&QTcpSocket::disconnected,this,[=](){
            m_socket->close();
            m_socket->deleteLater();
            m_socket=nullptr;
            emit disLinked();
        });

    }
}

void SendFile::sendFile(QString path)
{
    QFile file(path);
    QFileInfo info(path);
    int fileSize=info.size();
    QString fileName=info.fileName();
    fileName.resize(100,'\0');

    file.open(QFile::ReadOnly);

    m_socket->write(fileName.toUtf8(),100);
    m_socket->write((char*)&fileSize,4);

    int num=0;
    while(!file.atEnd())
    {

       QByteArray line= file.readLine();
        num+=line.size();
        int percent=(num*100/fileSize);
        emit curPercent(percent);
        m_socket->write(line);
    }
}
