#ifndef LOGER_H
#define LOGER_H
#include <QString>



class TypeLog {
public:
    static QString FATAL_STR;
    const QString MINOR_STR;
    const QString MAJOR_STR;
    const QString DEBUG_STR;
    const QString INFO_STR;
    static int FATAL;
    const int MINOR;
    const int MAJOR;
    const int DEBUG;
    const int INFO;
};

class Loger
{
public:
    LevelLog m_levelLog;
    static Loger & getInstance();
    void write(LevelLog typeMsg, QString msg);
protected:
private:
    Loger();
    Loger(const Loger &);
    Loger& operator = (const Loger &);
    ~Loger();
    QString createMsg(LevelLog typeMsg, QString msg);
};

#endif // LOGER_H
