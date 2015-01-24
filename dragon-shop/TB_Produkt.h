#ifndef TB_PRODUKT_H
#define TB_PRODUKT_H
#include "IDataTable.h"

class TB_Produkt : public IDataTable
{
    public:
        enum CIP {CIP_ID, CIP_NAME, CIP_UNIT, CIP_TERM, CIP_PHOTO};
        TB_Produkt(std::string name, std::string unit,  int term, std::string nameFile,  TypeStorage typeStorage);
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
        std::string m_nameFile;
        TypeStorage m_typeStorage;
};

#endif // TB_PRODUKT_H
