#ifndef CDTOOLS_H_INCLUDED
#define CDTOOLS_H_INCLUDED
#include <string>
#include <sstream>
#include <stdlib.h>
#include "Until_TB.h"

std::string intToString(int i);
int stringToInt(std::string str);
float stringToFloat(std::string str);
std::string floatToString(float i);
void printTB(TB_Result result);


#endif // CDTOOLS_H_INCLUDED
