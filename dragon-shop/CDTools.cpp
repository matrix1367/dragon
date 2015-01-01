#include "CDTools.h"
#include <cstdio>

std::string intToString(int i)
{
    std::ostringstream ss;
    ss << i;
    return ss.str();
}

int stringToInt(std::string str)
{
    int numb = -999;
    std::istringstream ( str ) >> numb;
    return numb;
}

void printTB(TB_Result result)
{
    for(TB_Result::iterator it = result.begin(); it != result.end(); it++)
    {
        for(TB_Row::iterator iit = it->begin(); iit != it->end(); iit++)
        {
            printf(" %s |", (*iit).c_str());
        }
        printf("\n");
    }
}
