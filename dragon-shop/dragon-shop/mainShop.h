#ifndef MAINSHOP_H_INCLUDED
#define MAINSHOP_H_INCLUDED
#include <windows.h>
#include <string>


bool GetTextFromEdit(HWND hwnd, int editID, std::string& text)
{
    int len = GetWindowTextLength(GetDlgItem(hwnd, editID));
    if (len <= 0)
    {
        return false;
    }
    else
    {
        char * buf;
        buf = (char*)GlobalAlloc(GPTR, len+1);
        GetDlgItemText(hwnd, editID, buf, len +1);
        text.append(buf);
        GlobalFree((HANDLE)buf);
        return true;
    }
}


bool GetIndexFromCombo(HWND hwnd, int editID, int& index)
{
    HWND HWNDcombo = GetDlgItem(hwnd, editID);
    index = SendMessage(HWNDcombo , CB_GETCURSEL, 0, 0 );
    return true;
}


#endif // MAINSHOP_H_INCLUDED
