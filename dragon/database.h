#ifndef DATABASE_H
#define DATABASE_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>

class Database
{
public:
    Database();
    virtual ~Database();
protected:
    QSqlDatabase db;

    bool connect(const char * nameDB);
    bool disconect();
    virtual bool createTable() = 0;
private:

};

#endif // DATABASE_H
