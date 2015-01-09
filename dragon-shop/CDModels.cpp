#include <windows.h>
#include <Commctrl.h>
#include "CDModels.h"
#include "CDSettingApp.h"
#include "CDDebug.h"
#include "Until_TB.h"
#include "CDTools.h"
#include "resource.h"


CDModels::CDModels()
{
    //ctor
}

CDModels::~CDModels()
{
    //dtor
}

void CDModels::OnExit()
{
    CDSettingApp::getInstance().Save();
}

int CDModels::Init()
{
//      printf("lll %d\n", StorageOp(5,6));



    CDSettingApp::getInstance().Load();
    //(int id, std::string fileName, std::string URLDB, std::string User, std::string password, TypeStorage typeStorage)
    m_storage = new CDStorage(CDSettingApp::getInstance().GetSettingData().idDB,
                              CDSettingApp::getInstance().GetSettingData().nameFileDB,
                              "",
                              "",
                              "",
                              CDSettingApp::getInstance().GetSettingData().typeStorage);

    bool isExist = false;
    m_storage->IsFirstOpen(isExist);
    if (isExist)
    {
        LOG("baza nie istnieje, tworzenie bazy..\n");
        TB_Result res;
        m_storage->QueryStorage(TB_Firma::createTableStr(CDSettingApp::getInstance().GetSettingData().typeStorage), res);
        m_storage->QueryStorage(TB_Lokalizacja::createTableStr(CDSettingApp::getInstance().GetSettingData().typeStorage), res);
        m_storage->QueryStorage(TB_Oddzial::createTableStr(CDSettingApp::getInstance().GetSettingData().typeStorage), res);
        m_storage->QueryStorage(TB_Produkt::createTableStr(CDSettingApp::getInstance().GetSettingData().typeStorage), res);
        m_storage->QueryStorage(TB_Zakup::createTableStr(CDSettingApp::getInstance().GetSettingData().typeStorage), res);

        m_storage->QueryStorage("INSERT INTO Lokalizacja (ulica, nr_domu, kod, miasto) VALUES ('Wagrowskiego', '13', '89-410', 'Wicbork');",res);
        m_storage->QueryStorage("INSERT INTO Lokalizacja (ulica, nr_domu, kod, miasto) VALUES ('Marceliñska', '23', '60-801', 'Poznañ');",res);
        m_storage->QueryStorage("INSERT INTO Lokalizacja (ulica, nr_domu, kod, miasto) VALUES ('Maltañska', '1', '61-131', 'Poznañ');",res);

        m_storage->QueryStorage("INSERT INTO Firma (nazwa, opis, nip, id_lokalizacja) VALUES('Piotr i Pawel Plus', 'supermarket', '779-21-34-078', 2);",res);

        m_storage->QueryStorage("INSERT INTO Oddzial (id_Firma, nazwa, id_Lokalizacja) VALUES(1, 'supermarket - Galeria malta',  3);",res);
        m_storage->QueryStorage("INSERT INTO Produkt (name, unit, term) VALUES('Napoj garden 2L', 'sztuk', 1);",res);
        m_storage->QueryStorage("INSERT INTO Produkt (name, unit, term) VALUES('Syrop malinowy 750ML', 'sztuk', 1);",res);
        m_storage->QueryStorage("INSERT INTO Produkt (name, unit, term) VALUES('Obieraczka do jerzyn 1', 'sztuk', 0);",res);

        m_storage->QueryStorage("INSERT INTO Zakup (id_Firmy, id_Oddzial, id_produkt, cena_jednostkowa, ilosc, data_przydatnosci, data_zakupu ) VALUES(1, 1, 1, 3, 1, '2015-05-01', '2015-01-01');",res);

    }
    return 0;
}

bool CDModels::AddDataToTable(IDataTable * dataTable)
{
    TB_Result result;
    if(m_storage != NULL)
    {
        m_storage->QueryStorage(dataTable->addRow(), result);
        return true;
    }
    return false;
}

CDModels::CDModels(CDModels const&)
{

}

bool CDModels::GetAllRow(Tabels table, TB_Result& result)
{
    if(m_storage != NULL)
    {
        switch(table)
        {
        case TB_FIRMA:
            {
                m_storage->QueryStorage(TB_Firma::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                return true;
            }
        case TB_LOKALIZACJA:
            {
                m_storage->QueryStorage(TB_Lokalizacja::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                return true;
            }
        case TB_ODDZIAL:
            {
                m_storage->QueryStorage(TB_Oddzial::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                return true;
            }
        case TB_PRODUKT:
            {
                m_storage->QueryStorage(TB_Produkt::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                return true;
            }
        case TB_ZAKUPY:
            {
                m_storage->QueryStorage(TB_Zakup::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                return true;
            }
        default:
            return true;
        }
    }
    else
    {
        return false;
    }
}

int CDModels::ConvertIndexCBToId(int indexCB, Tabels table)
{
    if(m_storage != NULL)
    {
        TB_Result result;
        GetAllRow(table,result);
        if (result.size() >= (unsigned int)indexCB)
        {
            //printf("index z tabeli : %s\n", (result[indexCB][0]).c_str());
            //int iTmp = stringToInt(result[indexCB][0]);
            //printf("index z tabeli po konwersi : %d\n",  stringToInt(result[indexCB][0]));
            return  stringToInt(result[indexCB][0]);
        } else return -1;
    } else return -1;

}


bool CDModels::GetCompactLocation(std::vector<std::string> & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        GetAllRow(TB_LOKALIZACJA, tb_result);
        if (tb_result.size() > 0)
        {
            for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
            {
                result.push_back((*it)[4] + " "+ (*it)[1] + " " + (*it)[2] );
            }
        }

        return true;

    }
    else
    {
        return false;
    }
}

bool CDModels::GetCompactFirmy(TB_Row & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        GetAllRow(TB_FIRMA, tb_result);
        if (tb_result.size() > 0)
        {
            for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
            {
                result.push_back((*it)[TB_Firma::CIF_NAZWA] + ", "+ (*it)[TB_Firma::CIF_NIP]);
            }
        }

        return true;

    }
    else
    {
        return false;
    }
}

bool CDModels::GetCompactOddzial(int id_firmy, TB_Row & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        m_storage->QueryStorage(TB_Oddzial::getAllRowIdFirmy(id_firmy, CDSettingApp::getInstance().GetSettingData().typeStorage), tb_result);
        for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
        {
           result.push_back((*it)[2]);
        }
        return true;
    }
    else{return false;}
}

bool CDModels::GetCompactProdukt(TB_Row & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        m_storage->QueryStorage(TB_Produkt::getAllRow( CDSettingApp::getInstance().GetSettingData().typeStorage), tb_result);
        for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
        {
           result.push_back((*it)[TB_Produkt::CIP_NAME]);
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool CDModels::GetCompactProdukt(int id_produkt, TB_Row & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        m_storage->QueryStorage(TB_Produkt::getAllRow( CDSettingApp::getInstance().GetSettingData().typeStorage), tb_result);
        for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
        {
           if (id_produkt == stringToInt((*it)[TB_Produkt::CIP_ID])) result.push_back((*it)[TB_Produkt::CIP_NAME]);
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool CDModels::GetUniqueCity(std::vector< std::string> & result)
{
    if(m_storage != NULL)
    {
        TB_Result tb_result;
        m_storage->QueryStorage(TB_Lokalizacja::getUniqueCity(CDSettingApp::getInstance().GetSettingData().typeStorage),tb_result);
          for (TB_Result::iterator it= tb_result.begin(); it != tb_result.end(); it++)
          {
               result.push_back((*it)[0]);
          }
        return true;
    }

    return false;
}


bool CDModels::SetDataInTable(HWND hwndDlg, Tabels table)
{
     if(m_storage != NULL)
    {
        TB_Result result;
        HWND listview;
        switch(table)
        {
        case TB_FIRMA:
            {
                m_storage->QueryStorage(TB_Firma::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                listview = GetDlgItem(hwndDlg, DLG_FIRMY_IDC_LIST1);
                ListView_DeleteAllItems(listview);
                if (result.size()>0)
                {
                    LVITEM lvi;
                    lvi.mask = LVIF_TEXT;
                    int indexItem = 0;
                    for (TB_Result::iterator it = result.begin(); it != result.end(); it++)
                    {
                        lvi.pszText = const_cast<char*>(((*it)[TB_Firma::CIF_NAZWA]).c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(((*it)[TB_Firma::CIF_NIP]).c_str()));
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(((*it)[TB_Firma::CIF_DES]).c_str()));
                        indexItem++;
                    }
                }
                return true;
            }
        case TB_LOKALIZACJA:
            {
                m_storage->QueryStorage(TB_Lokalizacja::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                listview = GetDlgItem(hwndDlg, DLG_LOKALIZACJE_IDC_LIST1);
                ListView_DeleteAllItems(listview);
                if(result.size() > 0)
                {
                    LVITEM lvi;
                    lvi.mask = LVIF_TEXT;
                    int indexItem = 0;
                    for (TB_Result::iterator it = result.begin(); it != result.end(); it++)
                    {
                        lvi.pszText = const_cast<char*>(((*it)[TB_Lokalizacja::CIL_MIASTO]).c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(((*it)[TB_Lokalizacja::CIL_KOD]).c_str()));
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(((*it)[TB_Lokalizacja::CIL_ULICA]).c_str()));
                        ListView_SetItemText( listview, indexItem, 3, const_cast<char*>(((*it)[TB_Lokalizacja::CIL_NR]).c_str()));
                        indexItem++;
                    }
                }
                return true;
            }
        case TB_ODDZIAL:
            {
                m_storage->QueryStorage(TB_Oddzial::getCompactAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                printTB(result);
                listview = GetDlgItem(hwndDlg, DLG_ODDZIALY_IDC_LIST1);
                ListView_DeleteAllItems(listview);
                if(result.size()>0)
                {
                    LVITEM lvi;
                    lvi.mask = LVIF_TEXT;
                    int indexItem = 0;
                    for (TB_Result::iterator it = result.begin(); it != result.end(); it++)
                    {
                        lvi.pszText = const_cast<char*>(((*it)[TB_Oddzial::CICO_NAZWA_FIRMY]).c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(((*it)[TB_Oddzial::CICO_NAZWA_ODDZ]).c_str()));
                        std::string lokalizacjaTmp = (*it)[TB_Oddzial::CICO_MIASTO_LOK] + ", " + (*it)[TB_Oddzial::CICO_ULICA_LOK] + " " + (*it)[TB_Oddzial::CICO_NR_LOK] ;
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(lokalizacjaTmp.c_str()));
                        indexItem++;
                    }
                }
                return true;
            }
        case TB_PRODUKT:
            {
                m_storage->QueryStorage(TB_Produkt::getAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                listview = GetDlgItem(hwndDlg, DLG_PRODUKT_IDC_LIST1);
                ListView_DeleteAllItems(listview);

                if(result.size()>0)
                {
                    LVITEM lvi;
                    lvi.mask = LVIF_TEXT;
                    int indexItem = 0;
                    for (TB_Result::iterator it = result.begin(); it != result.end(); it++)
                    {
                        lvi.pszText = const_cast<char*>(((*it)[TB_Produkt::CIP_NAME]).c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(((*it)[TB_Produkt::CIP_UNIT]).c_str()));
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(((*it)[TB_Produkt::CIP_TERM]).c_str()));
                        indexItem++;
                    }
                }

                return true;
            }
        case TB_ZAKUPY:
            {
                m_storage->QueryStorage(TB_Zakup::getCompactAllRow(CDSettingApp::getInstance().GetSettingData().typeStorage),result);
                listview = GetDlgItem(hwndDlg, DLG_ZAKUPY_ID_LISTVIEW1);
                ListView_DeleteAllItems(listview);

                if(result.size()>0)
                {
                    LVITEM lvi;
                    lvi.mask = LVIF_TEXT;
                    int indexItem = 0;
                    for (TB_Result::iterator it = result.begin(); it != result.end(); it++)
                    {
                        lvi.pszText = const_cast<char*>(((*it)[TB_Zakup::CIZC_NAZWA_FIRMY]).c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(((*it)[TB_Zakup::CIZC_NAZWA_ODDZIALU]).c_str()));
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(((*it)[TB_Zakup::CIZC_NAZWA_PRODUKTU]).c_str()));
                        ListView_SetItemText( listview, indexItem, 3, const_cast<char*>(((*it)[TB_Zakup::CIZC_CENA]).c_str()));
                        ListView_SetItemText( listview, indexItem, 4, const_cast<char*>(((*it)[TB_Zakup::CIZC_ILOSC]).c_str()));
                        ListView_SetItemText( listview, indexItem, 5, const_cast<char*>(((*it)[TB_Zakup::CIZC_DATA_WAZNOSCI]).c_str()));
                        ListView_SetItemText( listview, indexItem, 6, const_cast<char*>(((*it)[TB_Zakup::CIZC_DATA_ZAKUPU]).c_str()));
                        indexItem++;
                    }
                }
                return true;
            }
        default:
            return true;
        }
    }
    else
    {
        return false;
    }
}
