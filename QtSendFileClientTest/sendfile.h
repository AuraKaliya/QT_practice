#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>
#pragma execution_character_set("utf-8")
class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port,QString ip);

    //发送文件
    void sendFile(QString path);
signals:
    void linked();
    void disLinked();
    void curPercent(int );
private:
    QTcpSocket * m_socket=nullptr;

};

#endif // SENDFILE_H
