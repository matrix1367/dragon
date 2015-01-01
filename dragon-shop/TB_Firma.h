#ifndef TB_FIRMA_H
#define TB_FIRMA_H
#include <CDStorageTools.h>
#include "IDataTable.h"

class TB_Firma : public IDataTable
{
    public:
        enum CIF {CIF_ID, CIF_NAZWA, CIF_DES, CIF_NIP,  CIF_ID_LOKALIZACJA };

        TB_Firma(int ID_Lokalizacja, std::string name, std::string nip, std::string des, TypeStorage typeStorage);

        virtual ~TB_Firma();
        static std::string createTableStr(TypeStorage typeStorage);
        static std::string getAllRow(TypeStorage typeStorage);
        std::string addRow();
        std::string removeRow(int id);

    protected:
    private:
        int m_ID;
        int m_ID_Lokalizacja;
        std::string m_name;
        std::string m_nip;
        std::string m_des;
        TypeStorage m_typestorage;
};

#endif // TB_FIRMA_H
