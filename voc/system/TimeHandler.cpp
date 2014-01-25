#include "TimeHandler.h"

unsigned int CTimeHandler::getRealTime()
{
    timeval tv;
    gettimeofday(&tv, 0);
    return (unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

