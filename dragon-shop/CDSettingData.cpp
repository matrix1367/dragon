#include "CDSettingData.h"
#include <cstring>
#include <windows.h>
CDSettingData::CDSettingData()
{
    //nameFileDB = "db.dat";
    TCHAR Buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, Buffer);
    strcpy (nameFileDB, (std::string(Buffer) +"\\db.data").c_str());
    idDB = 1;
    typeStorage = TYPE_STORAGE_SQLITE3;
}

CDSettingData::~CDSettingData()
{

}
