#include "DataBaseSQLite3.h"
#include "CDStorageTools.h"
#include <cstdio>
#include <Shlwapi.h>
#include "CDDebug.h"

DataBaseSQLite3::DataBaseSQLite3(const std::string nameFile) : m_nameFile(nameFile)
{
    m_firstOpen = true;
    IsExist(m_firstOpen);
    m_firstOpen=!m_firstOpen;
    int res = Open();
    if (res)
    {
         LOG("Open data base failed, error code: %d!\n" , res);
    }
}

DataBaseSQLite3::~DataBaseSQLite3()
{
    Close();
}

int DataBaseSQLite3::Open()
{
    int rc = sqlite3_open(m_nameFile.c_str(), &db);
    if (rc)
    {
        printf("Open data base: %s failed, error code: %d!\n" , m_nameFile.c_str(), rc);
        return MS_ERROR_CODE_NOT_OPEN_DB;
    }
    return MS_ERROR_CODE_OK;
}

int DataBaseSQLite3::Close()
{
    int result = sqlite3_close(db);
    if(result)
    {
        return MS_ERROR_CODE_CLOSE_DB;
    }
    return MS_ERROR_CODE_OK;
}

int DataBaseSQLite3::Query(const std::string query, std::vector< std::vector < std::string > >& results)
{
    sqlite3_stmt *statement;


    int res = sqlite3_prepare(db, query.c_str(),  - 1, &statement, 0);
	if( res == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
			{
				std::vector<std::string> values;
				for(int col = 0; col < cols; col++)
				{
				    std::string value="";
				    char* ptr = (char*)sqlite3_column_text(statement, col);
				    if (ptr)
                    {
                        value = std::string(ptr);
                    }

					values.push_back(value);
					//printf("add vector: %s\n",value.c_str());
				}
				results.push_back(values);
			}
			else if (result == SQLITE_DONE) {
                break;
            } else if (result == SQLITE_ERROR)
			{
			    printf("failed!\n");
				break;
			} else
			{
                printf("ERROR : %d!\n", result);
			    break;
			}
		}

		sqlite3_finalize(statement);
	} else {
        printf("[SQL] sqlite3_prepare(...), Error sql %d\n", res);
	}

	std::string error = sqlite3_errmsg(db);
	if(error != "not an error")
    {
        printf("[SQL]:%s, [ERROR]:%s\n",  query.c_str(), error.c_str());
        return MS_ERROR_CODE_QUERY;
	}
	else
    {
        printf("[SQL]:%s\n", query.c_str());
	}
    return MS_ERROR_CODE_OK;
}

int DataBaseSQLite3::IsExist(bool& isExist)
{
   isExist =  PathFileExists(m_nameFile.c_str());
   printf("[SQL::IsExist]:%s, [IsExist]:%d\n",  m_nameFile.c_str(),isExist);
   return MS_ERROR_CODE_OK;
}
