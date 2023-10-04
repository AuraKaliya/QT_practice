#include "recvfile.h"

#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QString>
RecvFile::RecvFile(QTcpSocket* socket,QObject *parent)
    : QThread{parent},m_socket(socket)
{
    m_fileName="receiveFile.txt";

}

void RecvFile::setFileName(QString fileName)
{
    m_fileName=fileName;
}

void RecvFile::linkSocket(QTcpSocket *socket)
{
    m_socket=socket;
}


void RecvFile::run()
{
    if(m_socket!=nullptr)
    {

        connect(m_socket,&QTcpSocket::readyRead,this,[=](){
            static QFile *file=nullptr;
            static int count=0;
            static int total=0;
            if(count == 0)
            {
                QString fileName(m_socket->read(100));
                fileName.truncate(fileName.indexOf(QChar::Null));
                m_socket->read((char*)&total,4);
                file=new QFile(fileName);
                file->open(QFile::WriteOnly);
            }

            QByteArray all=m_socket->readAll();
            count+=all.size();
            file->write(all);
            if(count==total)
            {
                m_socket->close();
                m_socket->deleteLater();
                m_socket=nullptr;
                file ->close();
                file->deleteLater();
                emit over();
            }

        });
    }

    //进入阻塞状态等待事件到达（进入事件循环）
    exec();

}
