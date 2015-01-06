#include "TB_Zakup.h"
#include "CDTools.h"

TB_Zakup::~TB_Zakup()
{
    //dtor
}

std::string TB_Zakup::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "CREATE TABLE Zakup(id INTEGER PRIMARY KEY AUTOINCREMENT, id_Firmy INTEGER, id_Oddzial INTEGER, id_produkt INTEGER, cena_jednostkowa INTEGER, ilosc INTEGER, data_przydatnosci DATETIME, data_zakupu DATETIME)";
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
        return "Select * FROM Zakup";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Zakup::getCompactAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select Firma.nazwa, Oddzial.nazwa, Produkt.name, Zakup.cena_jednostkowa, Zakup.ilosc, Zakup.data_przydatnosci, Zakup.data_zakupu From Zakup Left JOIN Produkt ON Zakup.id_produkt = Produkt.id Left Join Firma ON Firma.id = Zakup.id_Firmy LEFT JOIN Oddzial ON Oddzial.id = Firma.id";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }

}

std::string TB_Zakup::addRow()
{
    if (m_typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "INSERT INTO Zakup (id_Firmy, id_Oddzial, id_produkt, cena_jednostkowa, ilosc, data_przydatnosci, data_zakupu ) VALUES("
            +  intToString(m_id_firmy) + ", " + intToString(m_id_oddzial) + ", " + intToString(m_id_produkt) + ", " + floatToString(m_cena) + ", " + floatToString(m_ilosc) + ", '" + m_data_waznosci +"' , '" + m_data_zakupu +"')";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Zakup::removeRow(int id)
{
    if (m_typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Zakup";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}
