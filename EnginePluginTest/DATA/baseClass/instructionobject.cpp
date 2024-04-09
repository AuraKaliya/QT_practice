#include "instructionobject.h"

InstructionObject::InstructionObject(QObject *parent)
    : QObject{parent}
{

}

QString InstructionObject::getInsName()
{
    return m_insName;
}

InstructionContext* InstructionObject::getInsContext()
{
    return &m_insContext;
}

void InstructionObject::setInsContext(const InstructionContext & ins)
{
    m_insContext=ins;
}

void InstructionObject::setInsName(const QString &newInsName)
{
    m_insName = newInsName;
}

void InstructionObject::solution(InstructionContext insContext)
{
    emit finished();
}


