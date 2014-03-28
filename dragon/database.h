#ifndef DATABASE_H
#define DATABASE_H

#include<QtSql/QSqlDatabase>

class Database
{
public:
    Database();
    virtual ~Database();
    virtual bool connect(const char * nameDB);
    virtual bool disconect();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
