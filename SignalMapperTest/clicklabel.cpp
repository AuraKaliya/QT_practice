#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel{parent}
    //,
{
    preInit();
}

ClickLabel::ClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel{text,parent,f}
    //,m_entity(* new Entity())
{
    preInit();
}

void ClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
    emit clickedMe(this);
}

Entity &ClickLabel::entity()
{
    return m_entity ;
}

void ClickLabel::setDrawFunction(const std::function<void (QPainter *, ClickLabel *)> & newDrawFunction)
{
    m_drawFunction = newDrawFunction;
    drawFunctionFlag=true;
}

bool ClickLabel::isDrawFunctionEmpty()
{
    return drawFunctionFlag;
}

void ClickLabel::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    if(drawFunctionFlag)
    {
        m_drawFunction(&painter,this);
    }

    painter.end();
    QLabel::paintEvent(e);
}

void ClickLabel::preInit()
{
    drawFunctionFlag=false;
    m_entity=Entity();
}




