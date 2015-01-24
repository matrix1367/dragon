#ifndef DATABASESQLITE3_H
#define DATABASESQLITE3_H
#include "sqlite3.h"
#include "IDataBase.h"


class DataBaseSQLite3 : public IDataBase
{
    public:
        DataBaseSQLite3(const std::string fileNme);
        virtual ~DataBaseSQLite3();
        int Open() ;
        int Close() ;
        int Query(const std::string msq, std::vector< std::vector < std::string > > & result) ;
        int Query(const std::string msq, const std::string nameFile, std::vector< std::vector < std::string > > & result);
        int IsExist(bool& isExist);
        bool IsFirstOpen() { return m_firstOpen; }
    protected:
    private:
        std::string m_nameFile;
        bool m_firstOpen;
        sqlite3 *db;
};

#endif // DATABASESQLITE3_H
