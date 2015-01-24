#ifndef CDSETTINGDATA_H
#define CDSETTINGDATA_H
#include <CDStorageTools.h>
#include <string>
#include <windows.h>

class CDSettingData
{
    public:
        CDSettingData();
        virtual ~CDSettingData();
        char nameFileDB [MAX_PATH];
        int idDB;
        TypeStorage typeStorage;
    protected:
    private:
};

#endif // CDSETTINGDATA_H
