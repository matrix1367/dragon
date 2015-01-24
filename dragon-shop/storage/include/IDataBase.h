#ifndef IDATABASE_H_INCLUDED
#define IDATABASE_H_INCLUDED

#include <string>
#include <vector>

class IDataBase
{
public :
    virtual int Open() = 0;
    virtual int Close() = 0;
    virtual int Query(const std::string msq, std::vector< std::vector < std::string > > & result) = 0;
    virtual int Query(const std::string msq, const std::string nameFile, std::vector< std::vector < std::string > > & result) = 0;
    virtual int IsExist(bool& isExist) = 0;
    virtual bool IsFirstOpen() = 0;
};

#endif // IDATABASE_H_INCLUDED
