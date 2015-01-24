#include "TB_Lokalizacja.h"

TB_Lokalizacja::TB_Lokalizacja(std::string ulica ,std::string nr, std::string kod, std::string miasto, TypeStorage typeStorage) : m_ulica(ulica), m_nr(nr), m_kod(kod), m_miasto(miasto), m_typestorage(typeStorage)
{
    //ctor
}

TB_Lokalizacja::~TB_Lokalizacja()
{
    //dtor
}

std::string TB_Lokalizacja::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
         return "CREATE TABLE Lokalizacja(id INTEGER PRIMARY KEY AUTOINCREMENT, ulica TEXT, nr_domu TEXT, kod TEXT, miasto TEXT)";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Lokalizacja::createTable()
{
    if (m_typestorage == TYPE_STORAGE_SQLITE3)
    {
         return "CREATE TABLE Lokalizacja(id INTEGER PRIMARY KEY AUTOINCREMENT, ulica TEXT, nr_domu TEXT, kod TEXT, miasto TEXT)";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Lokalizacja::addRow()
{
    if (m_typestorage == TYPE_STORAGE_SQLITE3)
    {
         return "INSERT INTO Lokalizacja (ulica, nr_domu, kod, miasto) VALUES('" + m_ulica +"' , '" + m_nr+ "' , '" + m_kod +"', '"+ m_miasto + "')";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Lokalizacja::addRow(IDataTable* table)
{
    if (m_typestorage == TYPE_STORAGE_SQLITE3)
    {
        return "";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Lokalizacja::removeRow(int id)
{
    if (m_typestorage == TYPE_STORAGE_SQLITE3)
    {
        return "";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}
std::string TB_Lokalizacja::getAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Lokalizacja";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Lokalizacja::getUniqueCity(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select DISTINCT miasto FROM Lokalizacja  ORDER BY miasto ASC;";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}


