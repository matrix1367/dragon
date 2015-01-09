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

#define ID_TRAY1 99
#define CMSG_TRAY1 98

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
BOOL CALLBACK DlgDodajZakupyMulti(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (LPARAM)IDI_ICON1);
        SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)IDI_ICON1);

        LPSTR sTip = "Dragon-shop";
        NOTIFYICONDATA nid;

        nid.cbSize = sizeof( NOTIFYICONDATA );
        nid.hWnd = hwndDlg;
        nid.uID = ID_TRAY1;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        nid.uCallbackMessage = CMSG_TRAY1;
        nid.hIcon = (HICON)LoadIcon( hInst, MAKEINTRESOURCE( IDI_ICON1 ) );
        lstrcpy( nid.szTip, sTip );

        BOOL r;
        r = Shell_NotifyIcon( NIM_ADD, & nid );
        if( !r ) MessageBox( hwndDlg, "No niestety, z ikonki nici...", "Łeeee...", MB_ICONEXCLAMATION );
    }
    return TRUE;

    case WM_SIZE:
    {
        if( wParam == SIZE_MINIMIZED )
        {
            ShowWindow( hwndDlg, SW_HIDE );
            // 1
        }
        else
        {
            ShowWindow( hwndDlg, SW_SHOW );
            // 2
        }
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case CMSG_TRAY1:
      if(lParam == WM_LBUTTONDOWN)
      {
         ShowWindow( hwndDlg, SW_RESTORE );
        break;
      }
    return TRUE;

    case WM_DESTROY:
    {
        NOTIFYICONDATA nid;
        nid.cbSize = sizeof( NOTIFYICONDATA );
        nid.hWnd = hwndDlg;
        nid.uID = ID_TRAY1;
        nid.uFlags = 0;
        Shell_NotifyIcon( NIM_DELETE, & nid );

        PostQuitMessage( 0 );
    }

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
                DialogBox(hInst, MAKEINTRESOURCE(DLG_PRODUKTY), NULL, (DLGPROC)DlgProdukty);
                break;
            }
        case ID_MAINMENU_SHOP_ZAKUPY:
            {
                DialogBox(hInst, MAKEINTRESOURCE(DLG_ZAKUPY), NULL, (DLGPROC)DlgZakupy);
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
        case WM_INITDIALOG:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_PRODUKT_IDC_LIST1);
            LVCOLUMN lvc;
            lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.iSubItem = 0;
            lvc.cx = 200;

            lvc.pszText = const_cast<char*>( "Nazwa");
            ListView_InsertColumn(listview , 0, & lvc );

            lvc.iSubItem = 1;
            lvc.cx = 100;
            lvc.pszText = const_cast<char*>( "Jednostka");
            ListView_InsertColumn(listview , 1, & lvc );

            lvc.iSubItem = 2;
            lvc.cx = 50;
            lvc.pszText = const_cast<char*>( "Termin");
            ListView_InsertColumn(listview , 2, & lvc );

            CDModels::getInstance().SetDataInTable(hwndDlg,TB_PRODUKT);
        }
        return true;

        case WM_SIZE:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_PRODUKT_IDC_LIST1);
            SetWindowPos( listview, 0, 0, 0 , LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            break;
        }

        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
            break;
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
                case IDM_DODAJ_PRODUKT1:
                    {
                        int res =   DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_PRODUKT), NULL, (DLGPROC)DlgDodajProdukty);
                        if (res == IDOK)
                        {
                            CDModels::getInstance().SetDataInTable(hwndDlg,TB_PRODUKT);
                        }
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
        case WM_INITDIALOG:
        {
            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_PRODUKT_IDC_COMBO1);

            SendMessage(HWNDcombo,  CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)("kg")));
            SendMessage(HWNDcombo,  CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)("sztuk")));
            SendMessage(HWNDcombo,  CB_SETCURSEL, 0, 0);
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
                    std::string jednostka;

                    if (GetTextFromEdit(hwndDlg,  DLG_DODAJ_PRODUKT_IDC_EDIT1, name))
                    {
                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_PRODUKT_IDC_COMBO1, jednostka);
                        HWND checkBox = GetDlgItem(hwndDlg, DLG_DODAJ_PRODUKT_IDC_CHECKBOX1);
                        int dwPos = SendMessage(checkBox, BM_GETCHECK, 0, 0);
                        TB_Produkt produkt(name, jednostka , dwPos, CDSettingApp::getInstance().GetSettingData().typeStorage);
                        CDModels::getInstance().AddDataToTable(&produkt);
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

BOOL CALLBACK DlgZakupy(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            {

            HWND listview = GetDlgItem(hwndDlg, DLG_ZAKUPY_ID_LISTVIEW1);
            LVCOLUMN lvc;
            lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.iSubItem = 0;
            lvc.cx = 100;

            lvc.pszText = const_cast<char*>( "Firma");
            ListView_InsertColumn(listview , 0, & lvc );

            lvc.iSubItem = 1;
            lvc.cx = 50;
            lvc.pszText = const_cast<char*>( "Oddzial");
            ListView_InsertColumn(listview , 1, & lvc );

            lvc.iSubItem = 2;
            lvc.cx = 250;
            lvc.pszText = const_cast<char*>( "Produkt");
            ListView_InsertColumn(listview , 2, & lvc );

            lvc.iSubItem = 3;
            lvc.cx = 50;
            lvc.pszText = const_cast<char*>( "Cena");
            ListView_InsertColumn(listview , 3, & lvc );

            lvc.iSubItem = 4;
            lvc.cx = 50;
            lvc.pszText = const_cast<char*>( "Ilosc");
            ListView_InsertColumn(listview , 4, & lvc );

            lvc.iSubItem = 5;
            lvc.cx = 70;
            lvc.pszText = const_cast<char*>( "Data waznosci");
            ListView_InsertColumn(listview , 5, & lvc );

            lvc.iSubItem = 6;
            lvc.cx = 70;
            lvc.pszText = const_cast<char*>( "Data zakupu");
            ListView_InsertColumn(listview , 6, & lvc );

            CDModels::getInstance().SetDataInTable(hwndDlg,TB_ZAKUPY);
            break;
            }
            return TRUE;

        case WM_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_SIZE:
        {
            HWND listview = GetDlgItem(hwndDlg, DLG_ZAKUPY_ID_LISTVIEW1);
            SetWindowPos( listview, 0, 0, 0 , LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            break;
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
                case IDM_DODAJ_ZAKUP1:
                    {
                        int res =   DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_ZAKUP), NULL, (DLGPROC)DlgDodajZakupy);
                        if (res == IDOK)
                        {
                            CDModels::getInstance().SetDataInTable(hwndDlg,TB_ZAKUPY);
                        }
                        break;
                    }
                case ID_MAINMENU_ZAKUPY_DODAJ_ZAKUPY:
                    {
                        int res =   DialogBox(hInst, MAKEINTRESOURCE(DLG_DODAJ_ZAKUP1), NULL, (DLGPROC)DlgDodajZakupyMulti);
                        if (res == IDOK)
                        {
                            CDModels::getInstance().SetDataInTable(hwndDlg,TB_ZAKUPY);
                        }
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
        case WM_INITDIALOG:
            {
                    TB_Row row_firmy;
                    CDModels::getInstance().GetCompactFirmy(row_firmy);
                    if (row_firmy.size() > 0)
                    {
                        HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_FIRMA);
                        for(TB_Row::iterator it = row_firmy.begin(); it != row_firmy.end(); it++)
                        {
                                 SendMessage(HWNDcombo,
                                            CB_ADDSTRING,
                                            0,
                                            reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                        }
                        SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);

                        TB_Row row_oddzial;
                        CDModels::getInstance().GetCompactOddzial(CDModels::getInstance().ConvertIndexCBToId(0,TB_FIRMA), row_oddzial);
                        if (row_oddzial.size() > 0)
                        {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_ODDZIAL);
                            for(TB_Row::iterator it = row_oddzial.begin(); it != row_oddzial.end(); it++)
                            {
                                     SendMessage(HWNDcombo,
                                                CB_ADDSTRING,
                                                0,
                                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                            }
                            SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
                        }

                    }
                    else
                    {
                        MessageBox(hwndDlg, "Brak firmy", "Błąd", 0);
                        EndDialog(hwndDlg, IDCANCEL);
                    }

                    TB_Row tb_result_produkt;
                    CDModels::getInstance().GetCompactProdukt(tb_result_produkt);
                    if ( tb_result_produkt.size() > 0 )
                    {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_PRODUKT);
                            for(TB_Row::iterator it = tb_result_produkt.begin(); it != tb_result_produkt.end(); it++)
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
                        MessageBox(hwndDlg, "Brak produktow", "Błąd", 0);
                        EndDialog(hwndDlg, IDCANCEL);
                    }
                break;
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
            case DLG_DODAJ_ZAKUP_COMBOBOX_FIRMA:
                {
                    switch(HIWORD(wParam))
                    {
                    case CBN_CLOSEUP:
                        {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_ODDZIAL);
                            SendMessage(HWNDcombo, CB_RESETCONTENT,  0, 0 );
                            int indexComboFirma  = -1;
                            GetIndexFromCombo(hwndDlg,DLG_DODAJ_ZAKUP_COMBOBOX_FIRMA, indexComboFirma);
                            printf("index : %d\n" , indexComboFirma );
                            TB_Row row_oddzial;
                            CDModels::getInstance().GetCompactOddzial(CDModels::getInstance().ConvertIndexCBToId(indexComboFirma,TB_FIRMA), row_oddzial);
                            if (row_oddzial.size() > 0)
                            {
                                HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_ODDZIAL);
                                for(TB_Row::iterator it = row_oddzial.begin(); it != row_oddzial.end(); it++)
                                {
                                         SendMessage(HWNDcombo,
                                                    CB_ADDSTRING,
                                                    0,
                                                    reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                                }
                                SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
                case IDCANCEL:
                {
                     EndDialog(hwndDlg, IDCANCEL);
                     break;
                }
                case IDOK:
                    {
                        int id_firmy = 0;
                        int id_oddzialu = 0;
                        int id_produktu = 0;
                        std::string cena = "";
                        std::string ilosc = "" ;
                        std::string data_waznosci = "";
                        std::string data_zakupu = "";

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_FIRMA, id_firmy);
                        id_firmy =  CDModels::getInstance().ConvertIndexCBToId(id_firmy,TB_FIRMA);

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_ODDZIAL, id_oddzialu);
                        id_oddzialu = CDModels::getInstance().ConvertIndexCBToId(id_oddzialu , TB_ODDZIAL);

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP_COMBOBOX_PRODUKT, id_produktu);
                        id_produktu = CDModels::getInstance().ConvertIndexCBToId(id_produktu, TB_PRODUKT);

                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP_EDIT_CENA, cena);
                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP_EDIT_ILOSC, ilosc);

                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP_DATA_WAZNOSCI, data_waznosci);
                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP_DATA_ZAKUPU, data_zakupu);

                        printf("firma %d, oddzial %d, produkt %d" , id_firmy, id_oddzialu , id_produktu);
                        printf("cena %s , ilosc %s , waznosc %s , zakup %s" , cena.c_str() , ilosc.c_str() , data_waznosci.c_str() , data_zakupu.c_str());
                        //TB_Zakup(int id_firmy, int id_oodizalu, int id_produktu, float cena, float ilosc, std::string data_waznosci, std::string data_zakupu, TypeStorage typeStorage)
                        TB_Zakup zakup(id_firmy, id_oddzialu, id_produktu, stringToFloat(cena), stringToFloat(ilosc) , data_waznosci , data_zakupu, CDSettingApp::getInstance().GetSettingData().typeStorage);
                        CDModels::getInstance().AddDataToTable(&zakup);
                        EndDialog(hwndDlg, IDOK);
                        break;
                    }
            }
        }
        return TRUE;
    }
    return FALSE;
}

std::vector<TB_Zakup> listaZakupow;

BOOL CALLBACK DlgDodajZakupyMulti(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            {

                HWND listview = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_LISTVIEW);
                LVCOLUMN lvc;
                lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                lvc.iSubItem = 0;
                lvc.cx = 200;

                lvc.pszText = const_cast<char*>( "Nazwa produktu");
                ListView_InsertColumn(listview , 0, & lvc );

                lvc.iSubItem = 1;
                lvc.cx = 50;
                lvc.pszText = const_cast<char*>( "Ilosc");
                ListView_InsertColumn(listview , 1, & lvc );

                lvc.iSubItem = 2;
                lvc.cx = 50;
                lvc.pszText = const_cast<char*>( "Cena");
                ListView_InsertColumn(listview , 2, & lvc );

                lvc.iSubItem = 3;
                lvc.cx = 90;
                lvc.pszText = const_cast<char*>( "Data waznosci");
                ListView_InsertColumn(listview , 3, & lvc );

                    listaZakupow.clear();

                    TB_Row row_firmy;
                    CDModels::getInstance().GetCompactFirmy(row_firmy);
                    if (row_firmy.size() > 0)
                    {
                        HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_FIRMA);
                        for(TB_Row::iterator it = row_firmy.begin(); it != row_firmy.end(); it++)
                        {
                                 SendMessage(HWNDcombo,
                                            CB_ADDSTRING,
                                            0,
                                            reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                        }
                        SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);

                        TB_Row row_oddzial;
                        CDModels::getInstance().GetCompactOddzial(CDModels::getInstance().ConvertIndexCBToId(0,TB_FIRMA), row_oddzial);
                        if (row_oddzial.size() > 0)
                        {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_ODDZIAL);
                            for(TB_Row::iterator it = row_oddzial.begin(); it != row_oddzial.end(); it++)
                            {
                                     SendMessage(HWNDcombo,
                                                CB_ADDSTRING,
                                                0,
                                                reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                            }
                            SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
                        }

                    }
                    else
                    {
                        MessageBox(hwndDlg, "Brak firmy", "Błąd", 0);
                        EndDialog(hwndDlg, IDCANCEL);
                    }

                    TB_Row tb_result_produkt;
                    CDModels::getInstance().GetCompactProdukt(tb_result_produkt);
                    if ( tb_result_produkt.size() > 0 )
                    {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_PRODUKT);
                            for(TB_Row::iterator it = tb_result_produkt.begin(); it != tb_result_produkt.end(); it++)
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
                        MessageBox(hwndDlg, "Brak produktow", "Błąd", 0);
                        EndDialog(hwndDlg, IDCANCEL);
                    }
                break;
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
            case DLG_DODAJ_ZAKUP1_COMBOBOX_FIRMA:
                {
                    switch(HIWORD(wParam))
                    {
                    case CBN_CLOSEUP:
                        {
                            HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_ODDZIAL);
                            SendMessage(HWNDcombo, CB_RESETCONTENT,  0, 0 );
                            int indexComboFirma  = -1;
                            GetIndexFromCombo(hwndDlg,DLG_DODAJ_ZAKUP1_COMBOBOX_FIRMA, indexComboFirma);
                            printf("index : %d\n" , indexComboFirma );
                            TB_Row row_oddzial;
                            CDModels::getInstance().GetCompactOddzial(CDModels::getInstance().ConvertIndexCBToId(indexComboFirma,TB_FIRMA), row_oddzial);
                            if (row_oddzial.size() > 0)
                            {
                                HWND HWNDcombo = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_ODDZIAL);
                                for(TB_Row::iterator it = row_oddzial.begin(); it != row_oddzial.end(); it++)
                                {
                                         SendMessage(HWNDcombo,
                                                    CB_ADDSTRING,
                                                    0,
                                                    reinterpret_cast<LPARAM>((LPCTSTR)(*it).c_str()));
                                }
                                SendMessage(HWNDcombo, CB_SETCURSEL, 0, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
                case IDCANCEL:
                {
                     EndDialog(hwndDlg, IDCANCEL);
                     break;
                }
                case IDOK:
                    {
                        for (std::vector<TB_Zakup>::iterator it = listaZakupow.begin() ; it != listaZakupow.end() ; it ++)
                        {
                            CDModels::getInstance().AddDataToTable(&(*it));
                        }
                        EndDialog(hwndDlg, IDOK);
                        break;
                    }
                case DLG_DODAJ_ZAKUP1_BUTTON_USUN:
                    {
                        HWND hListView = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_LISTVIEW);
                        int iPos = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                        while (iPos != -1) {
                            SendMessage(hListView,LVM_DELETEITEM,iPos,0);
                            listaZakupow.erase(listaZakupow.begin()+iPos);
                            iPos = ListView_GetNextItem(hListView, iPos, LVNI_SELECTED);
                        }
                        break;
                    }
                case DLG_DODAJ_ZAKUP1_BUTTON_DODAJ:
                    {
                        int id_firmy = 0;
                        int id_oddzialu = 0;
                        int id_produktu = 0;
                        std::string cena = "";
                        std::string ilosc = "" ;
                        std::string data_waznosci = "";
                        std::string data_zakupu = "";

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_FIRMA, id_firmy);
                        id_firmy =  CDModels::getInstance().ConvertIndexCBToId(id_firmy,TB_FIRMA);

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_ODDZIAL, id_oddzialu);
                        id_oddzialu = CDModels::getInstance().ConvertIndexCBToId(id_oddzialu , TB_ODDZIAL);

                        GetIndexFromCombo(hwndDlg, DLG_DODAJ_ZAKUP1_COMBOBOX_PRODUKT, id_produktu);
                        id_produktu = CDModels::getInstance().ConvertIndexCBToId(id_produktu, TB_PRODUKT);

                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP1_EDIT_CENA, cena);
                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP1_EDIT_ILOSC, ilosc);

                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP1_DATA_WAZNOSCI, data_waznosci);
                        GetTextFromEdit(hwndDlg,  DLG_DODAJ_ZAKUP1_DATA_ZAKUPU, data_zakupu);

                        printf("firma %d, oddzial %d, produkt %d" , id_firmy, id_oddzialu , id_produktu);
                        printf("cena %s , ilosc %s , waznosc %s , zakup %s" , cena.c_str() , ilosc.c_str() , data_waznosci.c_str() , data_zakupu.c_str());
                        //TB_Zakup(int id_firmy, int id_oodizalu, int id_produktu, float cena, float ilosc, std::string data_waznosci, std::string data_zakupu, TypeStorage typeStorage)
                        TB_Zakup zakup(id_firmy, id_oddzialu, id_produktu, stringToFloat(cena), stringToFloat(ilosc) , data_waznosci , data_zakupu, CDSettingApp::getInstance().GetSettingData().typeStorage);
                        listaZakupow.push_back(zakup);


                        HWND listview = GetDlgItem(hwndDlg, DLG_DODAJ_ZAKUP1_LISTVIEW);
                        LVITEM lvi;
                        lvi.mask = LVIF_TEXT;
                        int indexItem = ListView_GetItemCount(listview);
                        std::string name = "not name";
                        TB_Row row;
                        CDModels::getInstance().GetCompactProdukt( id_produktu , row);
                        if (row.size() > 0 )
                        {
                            name = row[0];
                        }
                        lvi.pszText = const_cast<char*>(name.c_str());
                        lvi.iItem = indexItem;
                        lvi.iSubItem = 0;
                        ListView_InsertItem( listview, & lvi );
                        ListView_SetItemText( listview, indexItem, 1, const_cast<char*>(ilosc.c_str()));
                        ListView_SetItemText( listview, indexItem, 2, const_cast<char*>(cena.c_str()));
                        ListView_SetItemText( listview, indexItem, 3, const_cast<char*>(data_waznosci.c_str()));



                        //CDModels::getInstance().AddDataToTable(&zakup);
                        //EndDialog(hwndDlg, IDOK);
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
