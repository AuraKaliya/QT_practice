#ifndef SOURCEMETADATA_H
#define SOURCEMETADATA_H

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QDebug>
class SourceMetaData : public QObject
{
    Q_OBJECT
public:
    explicit SourceMetaData(QObject *parent = nullptr);
    int Gid=-1;
    QPixmap* Icon=nullptr;
    QString Name="";
    QString Information="";
    QString Class="";

    void operator=(const SourceMetaData& it)
    {
        Gid=it.Gid;
        Icon=it.Icon;
        Name=it.Name;
        Information=it.Information;
        Class=it.Class;
    }

    void show();


signals:

};

#endif // SOURCEMETADATA_H
