#ifndef TB_ZAKUP_H
#define TB_ZAKUP_H
#include "IDataTable.h"

class TB_Zakup : public IDataTable
{
    public:
        enum CIZ { CIZ_ID, CIZ_ID_FIRMA, CIZ_ID_ODDZIAL, CIZ_ID_PRODUKT, CIZ_CENA, CIZ_ILOSC, CIZ_DATA_WAZNOSCI, CIZ_DATA_ZAKUPU};
        enum CIZC { CIZC_NAZWA_FIRMY, CIZC_NAZWA_ODDZIALU, CIZC_NAZWA_PRODUKTU, CIZC_CENA, CIZC_ILOSC, CIZC_DATA_WAZNOSCI, CIZC_DATA_ZAKUPU };
        TB_Zakup(int id_firmy, int id_oodizalu, int id_produktu, float cena, float ilosc, std::string data_waznosci, std::string data_zakupu, TypeStorage typeStorage) :
            m_id_firmy(id_firmy),
            m_id_oddzial(id_oodizalu),
            m_id_produkt(id_produktu),
            m_cena(cena),
            m_ilosc(ilosc),
            m_data_waznosci(data_waznosci),
            m_data_zakupu(data_zakupu),
            m_typeStorage(typeStorage)
            {

            }
        virtual ~TB_Zakup();
        static std::string createTableStr(TypeStorage typeStorage);
        static std::string getAllRow(TypeStorage typeStorage);
        static std::string getCompactAllRow(TypeStorage typeStorage);
        std::string addRow();
        std::string removeRow(int id);
    protected:
    private:
        int m_id_firmy;
        int m_id_oddzial;
        int m_id_produkt;
        float m_cena;
        float m_ilosc;
        std::string m_data_waznosci;
        std::string m_data_zakupu;
        int m_produkt_nazwa_paragon;
        TypeStorage m_typeStorage;
};

#endif // TB_ZAKUP_H
