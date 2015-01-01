#ifndef CDSTORAGE_H
#define CDSTORAGE_H
#include <string>
#include "CDStorageTools.h"
#include "IDataBase.h"

class CDStorage
{
public:

    CDStorage(int id, std::string fileName, std::string URLDB, std::string User, std::string password, TypeStorage typeStorage);
    CDStorage() {}
    int GetDataBase(IDataBase *db);
    inline int GetIdStorage() { return m_id; }
    inline std::string GetFileName() { return m_fileDB; }
    inline int QueryStorage(const std::string msq, TB_Result & result) { return m_dataBase->Query(msq, result);}
    int IsExistBD(bool & isExist);
    int IsFirstOpen(bool& isExist);
protected:
private:
    int m_id;
    std::string  m_fileDB;
    std::string  m_URLDB;
    std::string  m_UserDB;
    std::string  m_PasswordDB;
    TypeStorage  m_typeStorage;
    IDataBase*   m_dataBase;
};

#endif // CDSTORAGE_H
