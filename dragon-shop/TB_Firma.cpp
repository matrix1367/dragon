#include "TB_Firma.h"
#include "CDTools.h"
#include <cstdio>

TB_Firma::TB_Firma(int ID_Lokalizacja, std::string name, std::string nip, std::string des, TypeStorage typeStorage) : m_ID_Lokalizacja(ID_Lokalizacja), m_name(name), m_nip(nip), m_des(des), m_typestorage(typeStorage)
{
    //ctor
    //printf("firma construktor : m_id_lokalizacje: %d\n" , m_ID_Lokalizacja);
     //printf("firma construktor : ID_Lokalizacja: %d\n" , ID_Lokalizacja);
}

TB_Firma::~TB_Firma()
{
    //dtor
}

std::string TB_Firma::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "CREATE TABLE Firma(id INTEGER PRIMARY KEY AUTOINCREMENT, nazwa TEXT, opis TEXT, nip TEXT, id_lokalizacja)";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Firma::addRow()
{
    if (m_typestorage == TYPE_STORAGE_SQLITE3)
    {
        return "INSERT INTO Firma (nazwa, opis, nip, id_lokalizacja) VALUES('" + m_name +"' , '" + m_des+ "' , '" + m_nip +"', "+ intToString(m_ID_Lokalizacja) + ")";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Firma::removeRow(int id)
{
    return "";
}

std::string TB_Firma::getAllRow(TypeStorage typeStorage)
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
