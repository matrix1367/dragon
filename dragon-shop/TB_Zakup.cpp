#include "TB_Zakup.h"

TB_Zakup::TB_Zakup()
{
    //ctor
}

TB_Zakup::~TB_Zakup()
{
    //dtor
}

std::string TB_Zakup::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "CREATE TABLE Zakup(id INTEGER PRIMARY KEY AUTOINCREMENT, id_produkt INTEGER, cena_jednostkowa REAL, ilosc REAL, data_zakupu TEXT)";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Zakup::getAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Firma";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}
