#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>
#include <QString>
#pragma execution_character_set("utf-8")
class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* socket,QObject *parent = nullptr);
    void setFileName(QString fileName);
    void linkSocket(QTcpSocket* socket);
protected:
    void run() override;
signals:
    void over();
private:
    QTcpSocket * m_socket=nullptr;
    QString m_fileName;
};

#endif // RECVFILE_H
