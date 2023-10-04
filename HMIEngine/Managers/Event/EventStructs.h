#ifndef __EVENTSTRUCTS_H__
#define __EVENTSTRUCTS_H__

#include <functional>
#include "CommonStructs.h"
#include "CView.h"

class IEventPayload {};

namespace HmiNgin 
{
    struct SInitQmlEventPayload: public IEventPayload
    {
        const S_VIEW_INFORMATION*  info;
        const std::function<void(CView*)> *cb;
    };
}


#endif // __EVENTSTRUCTS_H__