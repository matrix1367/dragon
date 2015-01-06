#include "CDDebug.h"

void LOG(std::string msg)
{
    printf("[LOG]:%s", msg.c_str() );
}

void LOG(std::string msg, int errorCode)
{
    printf("[LOG]:%s [ERROR_CODE]:%d", msg.c_str(), errorCode );
}
