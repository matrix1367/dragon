#ifndef TB_ZAKUP_H
#define TB_ZAKUP_H
#include "IDataTable.h"

class TB_Zakup
{
    public:
        TB_Zakup();
        virtual ~TB_Zakup();
        static std::string createTableStr(TypeStorage typeStorage);
       static std::string getAllRow(TypeStorage typeStorage);
    protected:
    private:
};

#endif // TB_ZAKUP_H
