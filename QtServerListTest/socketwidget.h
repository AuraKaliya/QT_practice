#ifndef SOCKETWIDGET_H
#define SOCKETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QRandomGenerator>
class SocketWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SocketWidget(QTcpSocket* socket,QWidget *parent = nullptr);
    void setSocket(QTcpSocket* socket);
    QTcpSocket* getSocket();
    QString getSocketName();
signals:
private:
    QTcpSocket * m_socket=nullptr;
    QLabel * m_label;
    QHBoxLayout * m_layout;
};

#endif // SOCKETWIDGET_H
