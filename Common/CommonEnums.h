#ifndef COMMONENUMS_H
#define COMMONENUMS_H

#include <cstdint>

enum E_CACHE_STATUS: bool
{
    HIT = true,
    MISS = false
};

enum E_DURATION: uint8_t
{
    NONE                    = 0x0,
    IN_5_SECS               = 0x5,
    IN_10_SECS              = 0xA,
    IN_15_SEC               = 0xE,
    IN_30_SEC               = 0x1E
};

enum E_VIEW_TYPE: uint8_t
{
    SCREEN_TYPE = 0x0,
    POPUP_TYPE  = 0x1,
    TOAST_TYPE  = 0x2,
    NOTIFY_TYPE = 0x3
};

enum E_LOGGER_FLAG: uint64_t
{
    NOFLAG                  = 0x4E4F464C4147,
    QML                     = 0x514D4C,
    CPP                     = 0x435050
};

enum E_LOGGER_FLAG_COLOR: uint64_t
{

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

enum E_LOGGER_LEVEL_COLOR: uint64_t
{

};


#endif // COMMONENUMS_H
