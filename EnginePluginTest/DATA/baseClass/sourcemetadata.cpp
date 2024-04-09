#include "sourcemetadata.h"

SourceMetaData::SourceMetaData(QObject *parent)
    : QObject{parent}
{

}

void SourceMetaData::show()
{

    qDebug()<<"----now Show SourceMetaData information----";
    qDebug()<<" GID: "<<Gid;
    qDebug()<<" Icon: "<<Icon;
    qDebug()<<" Name: "<<Name;
    qDebug()<<" Info: "<<Information;
    qDebug()<<" Class: "<<Class;
    qDebug()<<"----now Show SourceMetaData information----end ";
}
