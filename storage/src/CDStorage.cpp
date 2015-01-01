#include "CDStorage.h"
#include "DataBaseSQLite3.h"
#include <cstdio>

CDStorage::CDStorage(int id, std::string fileName, std::string URLDB, std::string User, std::string password, TypeStorage typeStorage): m_id(id), m_fileDB(fileName), m_URLDB(URLDB), m_UserDB(User), m_PasswordDB(password), m_typeStorage(typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        m_dataBase = new DataBaseSQLite3(fileName);
        printf("[CDStorage::CDStorage] typeStorage == TYPE_STORAGE_SQLITE3\n" );
    }
}

int CDStorage::GetDataBase(IDataBase* db)
{
    if(m_dataBase != NULL)
    {
        db = m_dataBase;
        return  MS_ERROR_CODE_OK;
    }
    else return MS_ERROR_CODE_NOT_OPEN_DB;
}

 int CDStorage::IsExistBD(bool& isExist)
 {
     if(m_dataBase == NULL)
     {
         isExist = false;
         printf("[CDStorage::IsExist]:%s, [IsExist]:%d\n",  m_fileDB.c_str(),isExist);
         return MS_ERROR_CODE_CLOSE_DB;
     }
     else
    {
        m_dataBase->IsExist(isExist);
        printf("[CDStorage::IsExist]:%s, [IsExist]:%d\n",  m_fileDB.c_str(),isExist);
        return MS_ERROR_CODE_OK;
    }
 }

 int CDStorage::IsFirstOpen(bool& isExist)
 {
     if(m_dataBase == NULL)
     {
         return MS_ERROR_CODE_CLOSE_DB;
     }
     else{
            isExist = m_dataBase->IsFirstOpen();
        return  MS_ERROR_CODE_OK;
     }
 }
