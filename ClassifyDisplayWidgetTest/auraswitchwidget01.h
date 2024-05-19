#ifndef AURASWITCHWIDGET01_H
#define AURASWITCHWIDGET01_H

#include <QWidget>


#include "clicklabel.h"


class AuraSwitchWidget01 : public QWidget
{
    Q_OBJECT
public:
    explicit AuraSwitchWidget01(QWidget *parent = nullptr);
    void initWidget();


    void addLabel(ClickLabel* label);
    ClickLabel* getLabel(int index);
    int nowIndex() const;
    void setNowIndex(int newNowIndex);
    void updateLabelState();
    void updateLayout();

protected:
    void resizeEvent(QResizeEvent* e)override;
private:
    QVector<ClickLabel*> m_labelList;
    int m_nowIndex;
    int m_preIndex;

signals:
    void nowIndexChanged(int);
};

#endif // AURASWITCHWIDGET01_H
