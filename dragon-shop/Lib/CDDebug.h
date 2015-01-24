#ifndef CDDEBUG_H_INCLUDED
#define CDDEBUG_H_INCLUDED
#include <cstdio>
#include <string>

void LOG(std::string msg);

void LOG(std::string msg, int errorCode);

#endif // CDDEBUG_H_INCLUDED
