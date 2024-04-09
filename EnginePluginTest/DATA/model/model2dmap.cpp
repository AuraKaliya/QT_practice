#include "model2dmap.h"

//Model2DMap::Model2DMap(QObject *parent)
//    : ComponentObject{parent}
//{
//    setObjectName("Model2DMap");
//}

//void Model2DMap::tick()
//{
//    //输出可达矩阵信息
//    qDebug()<<"MotaMap---";
//    for(const auto &h:m_MapMatrix)
//    {
//        QString tmp="";
//        for(auto w:h)
//        {
//            tmp+=QString::number(w);
//            tmp+=" ";
//        }
//        qDebug()<<tmp;
//    }
//    qDebug()<<"MotaMap---end";
//}

//void Model2DMap::setMapSize(const unsigned int& width,const unsigned int& height)
//{
//    /*
//        vector的内容复习
//    */

//    m_mapSize=QPair<int,int>(width,height);
//    m_valiedMatrix.resize(height);
//    for(auto it:m_valiedMatrix)
//    {
//        it.resize(width);
//    }
//    emit mapSizeChanged();

//}

//void Model2DMap::setMapSize(QPair<int, int> newMapSize)
//{
//    m_mapSize=newMapSize;
//    m_valiedMatrix.resize(newMapSize.second);
//    for(auto it:m_valiedMatrix)
//    {
//        it.resize(newMapSize.first);
//    }
//    emit mapSizeChanged();

//}

//void Model2DMap::setValiedErea(const QVector<QVector<bool> > &valiedMatrix)
//{
//    /*
//        性能优化考虑
//    */
//    m_valiedMatrix.clear();
//    for(const auto &it:valiedMatrix)
//    {
//        m_valiedMatrix.append(it);
//    }

//}



//bool Model2DMap::pointIsActived(const int &x, const int &y)
//{
//    //检查是否合法。

//    //返回查询结果
//    return m_valiedMatrix[y][x];
//}

//void Model2DMap::setMapMatrix(const QVector<QVector<int> > &mapMatrix)
//{
//    m_MapMatrix.clear();
//    for(const auto& it:mapMatrix)
//    {
//        m_MapMatrix.append(it);
//    }

//}

//void Model2DMap::updateValiedEreaByMap()
//{

//}

//void Model2DMap::changeElement(int x, int y, int newIndex, bool valied)
//{
//    m_MapMatrix[y][x]=newIndex;
//    m_valiedMatrix[y][x]=valied;
//}

//QVector<QVector<int> > Model2DMap::getMapMatrix()
//{
//    //qDebug()<<"Model2DMap::getMapMatrix()  ---tick!";
//    //qDebug()<<"Model2DMap::getMapMatrix()  ---tick!end";
//    return m_MapMatrix;
//}

//QVector<QVector<bool> > Model2DMap::getValiedMatrix() const
//{
//    return m_valiedMatrix;
//}

//void Model2DMap::setValiedMatrix(const QVector<QVector<bool> > &newValiedMatrix)
//{
//    if (m_valiedMatrix == newValiedMatrix)
//        return;
//    m_valiedMatrix = newValiedMatrix;
//    emit valiedMatrixChanged();
//}


//QPair<int, int> Model2DMap::getMapSize() const
//{
//    return m_mapSize;
//}

//int Model2DMap::getMapWidth() const
//{
//    return m_mapWidth;
//}

//void Model2DMap::setMapWidth(int newMapWidth)
//{
//    if (m_mapWidth == newMapWidth)
//        return;
//    m_mapWidth = newMapWidth;
//    emit mapWidthChanged();
//}

//int Model2DMap::getMapHeight() const
//{
//    return m_mapHeight;
//}

//void Model2DMap::setMapHeight(int newMapHeight)
//{
//    if (m_mapHeight == newMapHeight)
//        return;
//    m_mapHeight = newMapHeight;
//    emit mapHeightChanged();
//}

//int Model2DMap::getMapDeFault() const
//{
//    return m_mapDeFault;
//}

//void Model2DMap::setMapDeFault(int newMapDeFault)
//{
//    if (m_mapDeFault == newMapDeFault)
//        return;
//    m_mapDeFault = newMapDeFault;
//    emit mapDeFaultChanged();
//}






















































Model2DMap::Model2DMap(QObject *parent):ComponentObject{parent}
{
    setObjectName("Model2DMap");
}

void Model2DMap::tick()
{
    qDebug()<<"---Model2DMap::tick---";
    qDebug()<<m_mapMatrix;
    qDebug()<<"---Model2DMap::tick---end";
}

int Model2DMap::getMapWidth() const
{
    return m_mapWidth;
}

void Model2DMap::setMapWidth(int newMapWidth)
{
    if (m_mapWidth == newMapWidth)
        return;
    m_mapWidth = newMapWidth;
    emit mapWidthChanged();
}

int Model2DMap::getMapHeight() const
{
    return m_mapHeight;
}

void Model2DMap::setMapHeight(int newMapHeight)
{
    if (m_mapHeight == newMapHeight)
        return;
    m_mapHeight = newMapHeight;
    emit mapHeightChanged();
}

int Model2DMap::getMapRealWidth() const
{
    return m_mapRealWidth;
}

void Model2DMap::setMapRealWidth(int newMapRealWidth)
{
    if (m_mapRealWidth == newMapRealWidth)
        return;
    m_mapRealWidth = newMapRealWidth;
    emit mapRealWidthChanged();
}

int Model2DMap::getMapRealHeight() const
{
    return m_mapRealHeight;
}

void Model2DMap::setMapRealHeight(int newMapRealHeight)
{
    if (m_mapRealHeight == newMapRealHeight)
        return;
    m_mapRealHeight = newMapRealHeight;
    emit mapRealHeightChanged();
}

bool Model2DMap::elementIsValied(int x, int y)
{
    //！warning！
    //有越界风险
    if(m_initFlag)
    {
        if(x>-1&&y>-1&&x<m_valiedMatrix.size()&&y<m_valiedMatrix[x].size())
        {
            //qDebug()<<"check:elementIsValied:"<<x<<y;
            //qDebug()<<"check:elementIsValied:"<<m_valiedMatrix;
            //qDebug()<<"check: valied"<<m_valiedMatrix[y][x];
            return m_valiedMatrix[y][x];
        }
        else
        {
            qDebug()<<"Model2DMap::elementIsValied: xy error"<<x<<y;
            return false;
        }
    }
    else
    {
        qDebug()<<"Model2DMap::elementIsValied: NO HAVE INIT";
    }
    return false;
}

void Model2DMap::setElement(int x, int y, int value)
{
    //！warning！
    //有越界风险
    if(m_initFlag)
    {
        m_mapMatrix[x][y]=value;
    }
    else
    {
        qDebug()<<"Model2DMap::setElement: NO HAVE INIT";
    }
}

void Model2DMap::setElementValied(int x, int y, bool valied)
{
    //！warning！
    //有越界风险
    if(m_initFlag)
    {
        m_valiedMatrix[x][y]=valied;
    }
    else
    {
        qDebug()<<"Model2DMap::setElementValied: NO HAVE INIT";
    }

}

void Model2DMap::initMap(int w, int h, int rw, int rh, QVector<QVector<int> > mapMatrix, QVector<QVector<bool> > valiedMatrix)
{
    setMapWidth(w);
    setMapHeight(h);
    setMapRealWidth(rw);
    setMapRealHeight(rh);

    perElementSizeW=rw/w;
    perElementSizeH=rh/h;

    m_mapMatrix=mapMatrix;
    m_valiedMatrix=valiedMatrix;

    m_initFlag=true;
}

QVector<QVector<bool> > Model2DMap::getValiedMatrix() const
{
    return m_valiedMatrix;
}

QVector<QVector<int> > Model2DMap::getMapMatrix() const
{
    return m_mapMatrix;
}

QPoint Model2DMap::getElementPoint(int x, int y)
{
    return QPoint(x*perElementSizeW,y*perElementSizeH);
}

QPair<int, int> Model2DMap::getPerElementSize()
{
    return QPair<int,int>(perElementSizeW,perElementSizeH);
}
