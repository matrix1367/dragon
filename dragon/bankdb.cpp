#include "bankdb.h"

BankDB::BankDB()
{
}

BankDB::~BankDB()
{

}

/*
 *  Acount
        int ID;
        QString name;
        QString number;
        float value;
 */

bool BankDB::createTable()
{
    if (!db.isOpen()) if(!connect("bank.db")) return false;


    QSqlQuery query(db);
    bool result = true;

        result = query.exec("CREATE TABLE IF NOT EXISTS Account ( ID INTEGER PRIMARY KEY, name TEXT , number TEXT, value REAL");


    return false;
}

bool BankDB::addAccount(Account account)
{
    return true;
}

bool BankDB::addLocation(Location location)
{
    return true;
}

bool BankDB::addSubject(Subject subiect)
{
    return true;
}

bool BankDB::addTransaction(Transaction transaction)
{
    return true;
}

bool BankDB::selectAccount(Account * accounts)
{
    QSqlQuery gry(db);
    qry.prepare( "SELECT * FROM Account" );
     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
     {
       qDebug( "Selected!" );

       QSqlRecord rec = qry.record();

       int cols = rec.count();

       for( int c=0; c<cols; c++ )
         qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) );

       for( int r=0; qry.next(); r++ )
         for( int c=0; c<cols; c++ )
           qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
     }
    return true;
}
