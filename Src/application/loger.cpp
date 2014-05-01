#include "loger.h"
#include <QDebug>


 TypeLog::FATAL = 0;
 TypeLog::MINOR = 1;


 Loger &Loger::getInstance()
{
    static Loger instanc;
    return instanc;
 }

 void Loger::write(TypeLog typeMsg, QString msg)
 {
     if (typeMsg <= m_levelLog)
     {
         qDebug() << createMsg(typeMsg , msg);
     }
 }

Loger::Loger() : m_levelLog(FATAL)
{

}

Loger::Loger(const Loger &) : m_levelLog(FATAL)
{

}

Loger::~Loger()
{

}

QString Loger::createMsg(LevelLog typeMsg, QString msg)
{
    return "[" +
}
