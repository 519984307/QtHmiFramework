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

enum E_VIEW_TYPE: uint8_t
{
    SCREEN_TYPE = 0,
    POPUP_TYPE,
    TOAST_TYPE,
    NOTIFY_TYPE
};

enum E_LOGGER_FLAG: uint32_t
{
    QML = 0x514D4C,
    CPP = 0x435050
};

enum E_LOGGER_LEVEL: uint64_t
{
    FATAL   = 0X464154414C,
    INFO    = 0x494E464F,
    WARN    = 0x5741524E,
    DEBUG   = 0x4445425547,
    TRACE   = 0x5452414345,
    ERROR   = 0x4552524F52
};


#endif // COMMONENUMS_H
