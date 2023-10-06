#ifndef __EVENTDEFINES_H__
#define __EVENTDEFINES_H__

#include <functional>
#include "EventStructs.h"

BEGIN_NAMESPACE(HmiNgin)

typedef std::function<void(IEventPayload *)> EventCallBack;

END_NAMESPACE

#endif // __EVENTDEFINES_H__