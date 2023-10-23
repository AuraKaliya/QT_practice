#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;

    virtual void SetImage(QString imageUrl);
    virtual void resetImage();

signals:
    void me(ClickLabel*);
    void clicked();

protected:

    QString  m_imageUrl;
};

#endif // CLICKLABEL_H
