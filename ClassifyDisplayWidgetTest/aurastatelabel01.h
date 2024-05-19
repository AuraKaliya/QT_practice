#ifndef AURASTATELABEL01_H
#define AURASTATELABEL01_H

#include <QWidget>

#include "UIStyle.hpp"

#include "clicklabel.h"

class AuraStateLabel01 : public ClickLabel
{
    Q_OBJECT
public:
    explicit AuraStateLabel01(QWidget *parent = nullptr);
    explicit AuraStateLabel01(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
protected:
    void paintEvent(QPaintEvent* e)override;
private:
    void preInit();
private:
    QColor m_nowColor;

signals:

};

#endif // AURASTATELABEL01_H
