#ifndef IDATATABLE_H
#define IDATATABLE_H
#include "CDStorageTools.h"
#include <string>

class IDataTable
{
    public:
        IDataTable();
        virtual ~IDataTable();
        virtual std::string addRow() = 0;
        virtual std::string removeRow(int id) =0;
    protected:

    private:
};

#endif // IDATATABLE_H
