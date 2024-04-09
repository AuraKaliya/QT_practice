#ifndef INSTRUCTIONCONTEXT_H
#define INSTRUCTIONCONTEXT_H

#include <QString>
#include <QVariant>
#include <QVector>
class InsPacketData;
class InstructionContext
{
public:
    InstructionContext();
    QString  insPermission;
    QString  insDemo;
    QString  insModel;
    QVector<InsPacketData> insPacket;
};

class InsPacketData
{
public:
    InsPacketData();
    int insIndex;
    QString insName;
    int ObjectIndex;
    QVariant value;
    int link;
    bool delay;
    bool soluteState;
};


#endif // INSTRUCTIONCONTEXT_H
