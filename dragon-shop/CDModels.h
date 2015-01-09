#ifndef MODULS_H
#define MODULS_H
#include <windows.h>
#include <IDataTable.h>
#include <CDStorage.h>
#include "Until_TB.h"

class CDModels
{
    public:
        static CDModels& getInstance()
        {
            static CDModels instance;
            return instance;
        }

        int Init();
        bool AddDataToTable(IDataTable* dataTable);
        bool GetAllRow(Tabels table, TB_Result& result);
        int ConvertIndexCBToId(int indexCB, Tabels table);
        bool GetCompactLocation(std::vector<std::string> & result);
        bool GetCompactFirmy(TB_Row & row);
        bool GetCompactOddzial(int id_firmy, TB_Row & row);
        bool GetCompactProdukt(TB_Row & row);
        bool GetCompactProdukt(int id_product,  TB_Row & row);
        bool GetUniqueCity(std::vector< std::string> & result);
        bool SetDataInTable(HWND hwndDlg, Tabels table);
        void OnExit();
    protected:
    private:
        CDModels();
        CDModels(CDModels const &);
        void operator=(CDModels const &);
        virtual ~CDModels();

        CDStorage* m_storage;
};

#endif // MODULS_H
