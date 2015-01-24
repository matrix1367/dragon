#ifndef TB_LOKALIZACJA_H
#define TB_LOKALIZACJA_H
#include "IDataTable.h"

class TB_Lokalizacja : public  IDataTable
{
    public:
        enum ColumnIndexLokalizacja {CIL_ID, CIL_ULICA , CIL_NR, CIL_KOD, CIL_MIASTO };

        TB_Lokalizacja(std::string ulica ,std::string nr, std::string kod, std::string miasto, TypeStorage typeStorage);
        virtual ~TB_Lokalizacja();
        static std::string createTableStr(TypeStorage typeStorage);
        static std::string getAllRow(TypeStorage typeStorage);
        static std::string getUniqueCity(TypeStorage typestorage);
        std::string createTable();
        std::string addRow();
        std::string addRow(IDataTable * table);
        std::string removeRow(int id);
    protected:
    private:

      int m_id;
      std::string m_ulica;
      std::string m_nr;
      std::string m_kod;
      std::string m_miasto;
      TypeStorage m_typestorage;
};

#endif // TB_LOKALIZACJA_H
