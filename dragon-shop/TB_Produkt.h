#ifndef TB_PRODUKT_H
#define TB_PRODUKT_H
#include "IDataTable.h"

class TB_Produkt : public IDataTable
{
    public:
        TB_Produkt(std::string name, std::string unit,  int term,  TypeStorage typeStorage);
        virtual ~TB_Produkt();
        static std::string createTableStr(TypeStorage typeStorage);
        static std::string getAllRow(TypeStorage typeStorage);
        std::string addRow();
        std::string removeRow(int id);
    protected:
    private:
        int m_id;
        std::string m_name;
        std::string m_unit;
        int m_term;
        TypeStorage m_typeStorage;
};

#endif // TB_PRODUKT_H
