#ifndef COMMONENUMS_H
#define COMMONENUMS_H

#include <cstdint>

enum E_CACHE_STATUS: bool
{
    HIT = true,
    MISS = false
};

enum E_DURATION: uint32_t
{
    NONE                    = 0,
    IN_5_SECS               = 5,
    IN_10_SECS              = 10,
    IN_15_SEC               = 15,
    IN_30_SEC               = 30
};

enum E_VIEW_TYPE
{
    SCREEN_TYPE,
    POPUP_TYPE,
    TOAST_TYPE,
    NOTIFY_TYPE
};


#endif // COMMONENUMS_H
