#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "CDModels.h"
#include "mainShop.h"
#include "CDSettingApp.h"
#include "TB_Firma.h"
#include "TB_Lokalizacja.h"
#include "CDTools.h"

HINSTANCE hInst;

BOOL CALLBACK DlgFirmy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDodajFirmy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgOddzialy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDodajOddzialy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgLokalizacje(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDodajLokalizacje(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProdukty(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDodajProdukty(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgZakupy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDodajZakupy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case ID_MAINMENU_SHOP_EXIT:
            {
                 EndDialog(hwndDlg, 0);
                 break;
            }
        case ID_MAINMENU_SHOP_FIRMY:
            {
                DialogBox(hInst, MAKEINTRESOURCE(DLG_FIRMY), NULL, (DLGPROC)DlgFirmy);
                break;
            }
        case ID_MAINMENU_SHOP_ODDZIALY:
            {
                DialogBox(hInst, MAKEINTRESOURCE(DLG_ODDZIALY), NULL, (DLGPROC)DlgOddzialy);
                break;
            }
        case ID_MAINMENU_SHOP_LOKALIZACJE:
            {
                DialogBox(hInst, MAKEINTRESOURCE(DLG_LOKALIZACJE), NULL, (DLGPROC)DlgLokalizacje);
                break;
            }
        case ID_MAINMENU_SHOP_PRODUKTY:
            {
                break;
            }
        case ID_MAINMENU_SHOP_ZAKUPY:
            {
                break;
            }
        }
    }
    return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgFirmy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        HWND listview = GetDlgItem(hwndDlg, DLG_FIRMY_IDC_LIST1);

        //ustawianie komponentow do poprawnego wyswietlania
       // RECT rectFirmyWindow;
       // GetWindowRect(listview, &rectFirmyWindow);
       // SetWindowPos( hwndDlg, 0, rectFirmyWindow.top, rectFirmyWindow.left , rectFirmyWindow.right - rectFirmyWindow.left +100, rectFirmyWindow.bottom - rectFirmyWindow.top, SWP_SHOWWINDOW );
        //dodawanie kolumn do listview

        LVCOLUMN lvc;
        lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.iSubItem = 0;
        lvc.cx = 100;
        lvc.pszText = const_cast<char*>( "Nazwa firmy");
        ListView_InsertColumn(listview , 0, & lvc );

        lvc.iSubItem = 1;
        lvc.cx = 80;
        lvc.pszText = const_cast<char*>( "NIP");
        ListView_InsertColumn(listview , 1, & lvc );

        lvc.iSubItem = 2;
        lvc.cx = 200;
        lvc.pszText = const_cast<char*>( "Opis");
        ListView_InsertColumn(listview , 2, & lvc );
        CDModels::getInstance().SetDataInTable(hwndDlg,TB_FIRMA);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_SIZE:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_FIRMY_IDC_LIST1);
            SetWindowPos( listview, 0, 0, 0 , LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            //printf("w:%d , h: %d\n" ,  LOWORD( lParam ),  HIWORD( lParam ));
            break;
        }
        return TRUE;
    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {

        case ID_MAINMENU_FIRMY_EXIT:
            {
                 EndDialog(hwndDlg, 0);
                 break;
            }
        case ID_MAINMENU_FIRMY_DODAJ_FIRME:
            {
                int res = DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_FIRMY), NULL, (DLGPROC)DlgDodajFirmy);
                if (res == IDOK)
                {
                    CDModels::getInstance().SetDataInTable(hwndDlg,TB_FIRMA);
                }
                break;
            }

        }
    }
    return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgDodajFirmy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        TB_Row row;
        CDModels::getInstance().GetCompactLocation(row);
        if (row.size() > 0)
        {
            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_FIRMY_IDC_COMBO1);
            for(TB_Row::iterator it = row.begin(); it != row.end(); it++)
            {
                     SendMessage(HWNDcombo,
                                CB_ADDSTRING,
                                0,
                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
            }
            SendMessage(HWNDcombo, CB_SETCURSEL, 0 ,0);
        }
        else
            {
                MessageBox(hwndDlg, "Brak lokalizacji", "Błąd", 0);
                EndDialog(hwndDlg, IDCANCEL);
            }
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDCANCEL:
            {
                 EndDialog(hwndDlg, IDCANCEL);
                 break;
            }
        case IDOK:
            {
               std::string name;
               std::string nip;
               std::string des;
               std::string id_lokalizacaja;

               if(GetTextFromEdit(hwndDlg,DLG_DODAJ_FIRMY_IDC_EDIT1,name))
               {
                   GetTextFromEdit(hwndDlg,DLG_DODAJ_FIRMY_IDC_EDIT2,nip);
                   GetTextFromEdit(hwndDlg,DLG_DODAJ_FIRMY_IDC_EDIT3,des);
                   int indexSelectComboBox = -1;
                   GetIndexFromCombo(hwndDlg,DLG_DODAJ_FIRMY_IDC_COMBO1, indexSelectComboBox);

                   //GetTextFromEdit(hwndDlg,DLG_DODAJ_LOKALIZACJE_IDC_COMBO1,id_lokalizacaja);
                   printf("LOG index combo %d\n",indexSelectComboBox);
                   TB_Firma firma(CDModels::getInstance().ConvertIndexCBToId(indexSelectComboBox, TB_LOKALIZACJA),name,nip,des, CDSettingApp::getInstance().GetSettingData().typeStorage);
                   CDModels::getInstance().AddDataToTable(&firma);
                   EndDialog(hwndDlg, IDOK);
               }
                //CDModels::getInstance().

                break;
            }

        }
    }
    return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgOddzialy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_ODDZIALY_IDC_LIST1);

            LVCOLUMN lvc;
            lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.iSubItem = 0;
            lvc.cx = 150;
            lvc.pszText = const_cast<char*>( "Nazwa firmy");
            ListView_InsertColumn(listview , 0, & lvc );

            lvc.iSubItem = 1;
            lvc.cx = 120;
            lvc.pszText = const_cast<char*>( "Nazwa oddzialu");
            ListView_InsertColumn(listview , 1, & lvc );

            lvc.iSubItem = 2;
            lvc.cx = 150;
            lvc.pszText = const_cast<char*>( "Lokalizacja");
            ListView_InsertColumn(listview , 2, & lvc );
            CDModels::getInstance().SetDataInTable(hwndDlg,TB_ODDZIAL);
        }
        return TRUE;
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_ODDZIALY_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
                case IDM_DODAJ_ODDZIA_1:
                {
                    int res = DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_ODDZIAL), NULL, (DLGPROC)DlgDodajOddzialy);
                    if (res == IDOK)
                    {
                        CDModels::getInstance().SetDataInTable(hwndDlg,TB_ODDZIAL);
                    }
                    break;
                }
            }
        }
        return TRUE;

        case WM_SIZE:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_ODDZIALY_IDC_LIST1);
            SetWindowPos( listview, 0, 0, 0 , LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            break;
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgDodajOddzialy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        TB_Row row;
        CDModels::getInstance().GetCompactLocation(row);
        if (row.size() > 0)
        {
            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ODDZIAL_IDC_COMBO1);
            for(TB_Row::iterator it = row.begin(); it != row.end(); it++)
            {
                     SendMessage(HWNDcombo,
                                CB_ADDSTRING,
                                0,
                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
            }
            SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
        }
        else
        {
            MessageBox(hwndDlg, "Brak lokalizacji", "Błąd", 0);
            EndDialog(hwndDlg, IDCANCEL);
        }
        TB_Row row_firmy;
        CDModels::getInstance().GetCompactFirmy(row_firmy);
        if (row_firmy.size() > 0)
        {
            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ODDZIAL_IDC_COMBO2);
            for(TB_Row::iterator it = row_firmy.begin(); it != row_firmy.end(); it++)
            {
                     SendMessage(HWNDcombo,
                                CB_ADDSTRING,
                                0,
                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
            }
            SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
        }
        else
        {
            MessageBox(hwndDlg, "Brak firmy", "Błąd", 0);
            EndDialog(hwndDlg, IDCANCEL);
        }
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, IDCANCEL);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDCANCEL:
        {
             EndDialog(hwndDlg, IDCANCEL);
             break;
        }
        case IDOK:
            {
               std::string name;
               std::string id_lokalizacaja;

               if(GetTextFromEdit(hwndDlg,DLG_DODAJ_ODDZIAL_IDC_EDIT1,name))
               {
                   int indexSelectComboBox1 = -1;
                   GetIndexFromCombo(hwndDlg,DLG_DODAJ_ODDZIAL_IDC_COMBO1, indexSelectComboBox1);
                   int indexSelectComboBox2 = -1;
                   GetIndexFromCombo(hwndDlg,DLG_DODAJ_ODDZIAL_IDC_COMBO2, indexSelectComboBox2);

                  // printf("LOG odd index combo %d\n",indexSelectComboBox1);
                  // printf("LOG odd index combo %d\n",indexSelectComboBox2);
                   TB_Oddzial oddzial(CDModels::getInstance().ConvertIndexCBToId(indexSelectComboBox2, TB_FIRMA),
                                      name,
                                      CDModels::getInstance().ConvertIndexCBToId(indexSelectComboBox1, TB_LOKALIZACJA),
                                      CDSettingApp::getInstance().GetSettingData().typeStorage);

                   CDModels::getInstance().AddDataToTable(&oddzial);
                   EndDialog(hwndDlg, IDOK);
               }


                break;
            }

        }
    }
    return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgLokalizacje(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_LOKALIZACJE_IDC_LIST1);
            LVCOLUMN lvc;
            lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.iSubItem = 0;
            lvc.cx = 90;
            lvc.pszText = const_cast<char*>( "Miasto");
            ListView_InsertColumn(listview , 0, & lvc );

            lvc.iSubItem = 1;
            lvc.cx = 60;
            lvc.pszText = const_cast<char*>( "Kod");
            ListView_InsertColumn(listview , 1, & lvc );

            lvc.iSubItem = 2;
            lvc.cx = 150;
            lvc.pszText = const_cast<char*>( "Ulica");
            ListView_InsertColumn(listview , 2, & lvc );

            lvc.iSubItem = 3;
            lvc.cx = 60;
            lvc.pszText = const_cast<char*>( "Nr domu");
            ListView_InsertColumn(listview , 3, & lvc );

            CDModels::getInstance().SetDataInTable(hwndDlg,TB_LOKALIZACJA);

        }
        return TRUE;

        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_SIZE:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_LOKALIZACJE_IDC_LIST1);
            SetWindowPos( listview, 0, 0, 0 , LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            //printf("w:%d , h: %d\n" ,  LOWORD( lParam ),  HIWORD( lParam ));
            break;
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_LOKALIZACJE_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
                case ID_MAINMENU_LOKALIZACJE_DODAJ_LOK:
                {
                    int res =   DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_LOKALIZACJE), NULL, (DLGPROC)DlgDodajLokalizacje);
                    if (res == IDOK)
                    {
                        CDModels::getInstance().SetDataInTable(hwndDlg,TB_LOKALIZACJA);
                    }
                    break;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgDodajLokalizacje(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, IDCANCEL);
        }
        return TRUE;

        case WM_INITDIALOG:
        {
         //Pobranie wszystkich miast z lokalizacji i dodanie ich do combobox
            HWND HWNDcombo;
            TB_Row row;
            if(CDModels::getInstance().GetUniqueCity(row) && row.size() > 0)
            {
                HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_LOKALIZACJE_IDC_COMBO1);
                for(TB_Row::iterator it = row.begin(); it != row.end(); it++)
                {
                     SendMessage(HWNDcombo,
                                CB_ADDSTRING,
                                0,
                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                }
                SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
            }
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case IDCANCEL:
                {
                     EndDialog(hwndDlg, IDCANCEL);
                     break;
                }
                //dodanie lokalizacj do bazy danych
                case IDOK:
                {
                     std::string ulica ,miasto, nr, kod;
                     GetTextFromEdit(hwndDlg, DLG_DODAJ_LOKALIZACJE_IDC_EDIT1, ulica);
                     GetTextFromEdit(hwndDlg, DLG_DODAJ_LOKALIZACJE_IDC_EDIT2, nr);
                     GetTextFromEdit(hwndDlg, DLG_DODAJ_LOKALIZACJE_IDC_EDIT3, kod);
                     GetTextFromEdit(hwndDlg, DLG_DODAJ_LOKALIZACJE_IDC_COMBO1, miasto);
                     if (!ulica.empty() && !nr.empty() && !kod.empty() && !miasto.empty())
                     {
                         TB_Lokalizacja lokacja(ulica, nr, kod, miasto, CDSettingApp::getInstance().GetSettingData().typeStorage);
                         if(!CDModels::getInstance().AddDataToTable(&lokacja))  MessageBox(hwndDlg, "Wystąpił błąd podczas dodawania danych do BD.", "Błąd", 0);
                         EndDialog(hwndDlg, IDOK);
                     }
                     else{
                        MessageBox(hwndDlg, "Wypełnij wszystkie pola", "Błąd", 0);
                     }

                     break;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgProdukty(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_PRODUKTY_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgDodajProdukty(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_ZAKUPY_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
                case IDM_DODAJ_PRODUKT1:
                    {
                        break;
                    }
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgZakupy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_ZAKUPY_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
                case IDM_DODAJ_PRODUKT1:
                    {
                        break;
                    }
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CALLBACK DlgDodajZakupy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_MAINMENU_ZAKUPY_EXIT:
                {
                     EndDialog(hwndDlg, 0);
                     break;
                }
                case IDM_DODAJ_PRODUKT1:
                    {
                        break;
                    }
            }
        }
        return TRUE;
    }
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    CDModels::getInstance().Init();
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
