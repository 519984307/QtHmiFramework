#ifndef __EVENTDEFINES_H__
#define __EVENTDEFINES_H__

#include <functional>
#include "EventStructs.h"

namespace HmiNgin
{
    typedef std::function<void(IEventPayload*)> EventCallBack;
} 


#endif // __EVENTDEFINES_H__