#ifndef TB_ODDZIAL_H
#define TB_ODDZIAL_H
#include "IDataTable.h"

class TB_Oddzial : public IDataTable
{
    public:
        enum CICO { CICO_NAZWA_FIRMY, CICO_NAZWA_ODDZ, CICO_MIASTO_LOK, CICO_ULICA_LOK, CICO_NR_LOK };

        TB_Oddzial(int id_firmy, std::string name, int id_lokalizacja, TypeStorage typeStorage);
        virtual ~TB_Oddzial();
        static std::string createTableStr(TypeStorage typeStorage);
        static std::string getAllRow(TypeStorage typeStorage);
        static std::string getCompactAllRow(TypeStorage typeStorage);
        std::string addRow();
        std::string removeRow(int id);
    protected:
    private:
        int m_id;
        int m_id_firmy;
        std::string m_name;
        int m_id_lokalizacja;
        TypeStorage m_typeStorage;
};

#endif // TB_ODDZIAL_H
