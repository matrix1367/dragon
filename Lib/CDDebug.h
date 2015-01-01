#ifndef CDDEBUG_H_INCLUDED
#define CDDEBUG_H_INCLUDED
#include <cstdio>

void LOG(std::string msg)
{
    printf("[LOG]:%s", msg.c_str() );
}

void LOG(std::string msg, int errorCode)
{
    printf("[LOG]:%s [ERROR_CODE]:%d", msg.c_str(), errorCode );
}

#endif // CDDEBUG_H_INCLUDED
