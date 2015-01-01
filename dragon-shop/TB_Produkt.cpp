#include "TB_Produkt.h"
#include "CDTools.h"

TB_Produkt::TB_Produkt(std::string name, std::string unit, int term, TypeStorage typeStorage) : m_name(name), m_unit(unit), m_term(term), m_typeStorage(typeStorage)
{
    //ctor
}

TB_Produkt::~TB_Produkt()
{
    //dtor
}

std::string TB_Produkt::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "CREATE TABLE Produkt(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, unit TEXT, term INTEGER);";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Produkt::getAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Produkt";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Produkt::addRow()
{
    if (m_typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "INSERT INTO Produkt (name, unit, term) VALUES('" + m_name +"' , '" + m_unit+ "' , " + intToString(m_term) +")";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Produkt::removeRow(int id)
{
    if (m_typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Firma";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}
