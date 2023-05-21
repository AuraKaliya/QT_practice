#include "slideblock.h"

slideBlock::slideBlock()
{
    m_isPressed=false;
}

void slideBlock::setRect(QRect rect)
{
    m_abRect=rect;
}

void slideBlock::mousePressEvent(QMouseEvent *e)
{
    m_isPressed=true;
    m_mouseStartPos=e->pos();
    qDebug()<<m_mouseStartPos;
    m_btnStarPos=this->frameGeometry().topLeft();

}

void slideBlock::mouseMoveEvent(QMouseEvent *e)
{
    if(m_isPressed&&(this->x()>=m_abRect.x()))
    {
       QPoint distance=e->pos()-m_mouseStartPos;
        //this->move((m_btnStarPos+distance).x(),m_btnStarPos.y());
       this->move(distance.x()+this->x(),m_btnStarPos.y());
        //this->move(e->pos().x()+this->x()-e->pos().x(),m_btnStarPos.y());
    }
}

void slideBlock::mouseReleaseEvent(QMouseEvent *e)
{
    m_isPressed=false;
    if(this->x()<m_abRect.x()+10)
    {
        this->move(m_abRect.x(),m_abRect.y());
        emit valueMax();
    }
    else
    {
        resetPos();
    }
}

void slideBlock::initPos()
{

}

void slideBlock::resetPos()
{
    move(fixPos);
}

void slideBlock::setMouseStartPos(QPoint newMouseStartPos)
{
   // m_mouseStartPos = newMouseStartPos;
    //m_mouseStartPos=QPoint(0,0);
    qDebug()<<m_mouseStartPos;
}

void slideBlock::setFixPos(QPoint newFixPos)
{
    fixPos = newFixPos;
}
