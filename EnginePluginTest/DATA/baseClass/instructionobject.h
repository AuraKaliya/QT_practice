#ifndef INSTRUCTIONOBJECT_H
#define INSTRUCTIONOBJECT_H

#include <QObject>
#include "../instructioncontext.h"
#include <QVector>
class InstructionObject : public QObject
{
    Q_OBJECT
public:
    explicit InstructionObject(QObject *parent = nullptr);
    QString getInsName();
    InstructionContext* getInsContext() ;
    void setInsContext(const InstructionContext& ins);
    void setInsName(const QString &newInsName);

protected:
    QString m_insName;
    InstructionContext m_insContext;
signals:
    void finished();
public slots:
    virtual void solution(InstructionContext insContext=InstructionContext());
};

#endif // INSTRUCTIONOBJECT_H
