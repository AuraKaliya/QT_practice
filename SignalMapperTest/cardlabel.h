#ifndef CARDLABEL_H
#define CARDLABEL_H

#include <QWidget>

#include "clicklabel.h"

class CardLabel : public ClickLabel
{
    Q_OBJECT
public:
    explicit CardLabel(int id,QWidget *parent = nullptr);

    unsigned int id() const;
    void setId(unsigned int newId);

protected:
    //暂 不用 重写的方法
private:
    unsigned int m_id;
signals:
    void clickedCard(int);
};

#endif // CARDLABEL_H
