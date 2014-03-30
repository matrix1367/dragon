#include "database.h"

Database::Database()
{
}

Database::~Database()
{

}

bool Database::connect(const char *nameDB)
{
    db = QSqlDatabase::addDatabase(nameDB);
    return db.open();
}

bool Database::disconect()
{
    db.close();
    return true;
}
