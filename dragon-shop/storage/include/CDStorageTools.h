#ifndef CDSTORAGETOOLS_H_INCLUDED
#define CDSTORAGETOOLS_H_INCLUDED
#include <vector>
#include <string>

typedef  std::vector< std::vector < std::string> > TB_Result;
typedef std::vector< std::string > TB_Row;

enum TypeStorage  { TYPE_STORAGE_SQLITE3 };

enum MenagerStorage_Error_code {
    MS_ERROR_CODE_OK,
    MS_ERROR_CODE_EXIST,
    MS_ERROR_CODE_NOT_OPEN_DB,
    MS_ERROR_CODE_CLOSE_DB,
    MS_ERROR_CODE_QUERY
};


#endif // CDSTORAGETOOLS_H_INCLUDED
