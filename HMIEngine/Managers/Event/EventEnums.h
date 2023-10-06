#ifndef __EVENTID_H__
#define __EVENTID_H__

#include <stdint.h>

BEGIN_NAMESPACE(HmiNgin)

enum E_EVENT_ID : uint32_t
{
    E_EVENT_ID_MIN = 0,
    E_EVENT_LOAD_QML,
    E_EVENT_ID_MAX
};

END_NAMESPACE

#endif // __EVENTID_H__