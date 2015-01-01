#include "TB_Oddzial.h"
#include "CDTools.h"

TB_Oddzial::TB_Oddzial(int id_firmy, std::string name, int id_lokalizacja, TypeStorage typeStorage) : m_id_firmy(id_firmy), m_name(name), m_id_lokalizacja(id_lokalizacja) , m_typeStorage(typeStorage)
{
    //empty
}

TB_Oddzial::~TB_Oddzial()
{
    //dtor
}

std::string TB_Oddzial::createTableStr(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "CREATE TABLE Oddzial(id INTEGER PRIMARY KEY AUTOINCREMENT, id_Firma INTEGER, nazwa TEXT, id_Lokalizacja INTEGER)";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Oddzial::getAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "Select * FROM Oddzial";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Oddzial::getCompactAllRow(TypeStorage typeStorage)
{
    if (typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "select Firma.nazwa, Oddzial.nazwa , Lokalizacja.miasto, Lokalizacja.ulica , Lokalizacja.nr_domu From Oddzial LEFT JOIN  Firma  ON  Firma.id = Oddzial.id_Firma LEFT JOIN Lokalizacja ON Lokalizacja.id = Oddzial.id_Lokalizacja;";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Oddzial::addRow()
{
    if (m_typeStorage == TYPE_STORAGE_SQLITE3)
    {
        return "INSERT INTO Oddzial (id_Firma, nazwa, id_Lokalizacja) VALUES("+ intToString(m_id_firmy)+ ", '" + m_name +"' ,"+ intToString(m_id_lokalizacja) + ")";
    }
    else
    {
        return "ERROR_TYPE_STORAGE";
    }
}

std::string TB_Oddzial::removeRow(int id)
{
     return "ERROR_TYPE_STORAGE";
}


