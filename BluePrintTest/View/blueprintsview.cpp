#include "blueprintsview.h"

BlueprintsView::BlueprintsView(QWidget *parent)
    : GridGraphicsView{parent}
{
    preInit();
}

BlueprintsView::BlueprintsView(QGraphicsScene *scene, QWidget *parent)
    : GridGraphicsView(scene,parent)
{
    preInit();
}

BezierCurveItem *BlueprintsView::addLinkLine(QPointF startPoint, QPointF endPoint)
{
    BezierCurveItem* linkLine=new BezierCurveItem(QPointF(),QPointF());
    scene()->addItem(linkLine);
    linkLine->setVisible(true);
    linkLine->UpdatePoint(startPoint,endPoint);
    linkLine->setLineColor(m_lineColor);
    return linkLine;
}

void BlueprintsView::mouseMoveEvent(QMouseEvent *e)
{
    m_currentPos=e->pos();

    m_endPos=m_currentPos;

    if(m_drawFlag)
    {
        m_previewLine->setVisible(true);
        QPointF startPoint(mapToScene(m_startPos));
        QPointF endPoint(mapToScene(m_endPos));
        m_previewLine->UpdatePoint(startPoint,endPoint);
        m_previewLine->setLineColor(m_lineColor);
    }

    GridGraphicsView::mouseMoveEvent(e);
}

void BlueprintsView::mousePressEvent(QMouseEvent *e)
{
    m_startPos=e->pos();
    m_currentPos=m_startPos;
    m_endPos=m_currentPos;
    // 为you键
    if(e->buttons()==Qt::RightButton)
    {
        //qDebug()<<"BlueprintsView::mousePressEvent | check m_startPos:"<<m_startPos;
        PortInfomation portInfo=NodeManager::getPortInfoByPos(this,m_startPos);

        if(!portInfo.isEmpty())
        {
            m_drawFlag=true;
            m_lineColor=portInfo.port()->getColorByDataType(portInfo.port()->portDataType());
            m_nowStartPort=portInfo.port();
        }

    }
    GridGraphicsView::mousePressEvent(e);
}

void BlueprintsView::mouseReleaseEvent(QMouseEvent *e)
{
    m_currentPos=e->pos();
    m_endPos=m_currentPos;
    m_previewLine->setVisible(false);

    //qDebug()<<"BlueprintsView::mouseReleaseEvent | check flag:"<<m_drawFlag << " e buttons:" <<(e->buttons() == Qt::RightButton) << "button:"<<e->button();
    if(m_drawFlag && e->button()==Qt::RightButton)
    {
        //qDebug()<<"BlueprintsView::mouseReleaseEvent | check m_endPos:"<<m_endPos;
        PortInfomation portInfo=NodeManager::getPortInfoByPos(this,m_endPos);

        if(!portInfo.isEmpty())
        {
            //qDebug()<<"BlueprintsView::mouseReleaseEvent | check  is not empty.";
            QPair<bool, PortObjectItem *> linkPair{false,nullptr};

            PortObjectItem * endPort=portInfo.port();

            //后续可进行优化
            if(m_nowStartPort->portType() == PortObjectItem::PortType::OutLink || m_nowStartPort->portType() ==PortObjectItem::PortType::Output)
            {
                //输入端口仅能连接一个输出端口
                if(!endPort->linkPortState())
                {
                    linkPair=NodeManager::checkLinkPort(m_nowStartPort,endPort);
                }
            }
            else
            {
                //输入端口仅能连接一个输出端口
                if(!m_nowStartPort->linkPortState())
                {
                    linkPair=NodeManager::checkLinkPort(endPort,m_nowStartPort);
                }
            }

            //可进行连接
            if(linkPair.first)
            {
                //添加连接线
                BezierCurveItem* linkLine=addLinkLine(mapToScene(m_startPos),mapToScene(m_endPos));

                //进行连接
                NodeManager::linkPort(m_nowStartPort,endPort,linkLine);
            }


        }
    }


    m_drawFlag=false;
    m_nowStartPort=nullptr;

    GridGraphicsView::mouseReleaseEvent(e);
}

void BlueprintsView::preInit()
{

    m_previewLine=new BezierCurveItem(QPointF(0,0),QPointF(0,0));
    m_previewLine->setVisible(false);

    m_drawFlag=false;
    //=========================初始化场景========================
    if(! scene())
    {
        BlueprintsScene *s=new BlueprintsScene();
        setScene(s);
        int maxSize=1000;
        setSceneRect(-maxSize,-maxSize,2*maxSize,2*maxSize);
    }
    scene()->addItem(m_previewLine);
    //=========================初始化场景========================
}
