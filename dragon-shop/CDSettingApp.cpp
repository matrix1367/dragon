#include "CDSettingApp.h"
#include "CDSerialize.h"


CDSettingApp::CDSettingApp()
{
    Load();
}

CDSettingApp::CDSettingApp(CDSettingApp const &)
{

}

CDSettingApp::~CDSettingApp()
{

}

int CDSettingApp::Save()
{
    CDSerialize<CDSettingData> serialzer("dragon_setting.dat");
    serialzer.Write(settingData);
    return 0;
}

int CDSettingApp::Load()
{
    CDSerialize<CDSettingData> serialzer("dragon_setting.dat");
    serialzer.Read(settingData);
    //printf("Load setting [idBD: %d, nameFileDB: %s, typeStorage: %d]"  , settingData.idDB, settingData.nameFileDB.c_str(), settingData.typeStorage);
    printf("Load setting [idBD: %d, nameFileDB: %s, typeStorage: %d]\n"  , settingData.idDB, settingData.nameFileDB, settingData.typeStorage);
    return 0;
}
