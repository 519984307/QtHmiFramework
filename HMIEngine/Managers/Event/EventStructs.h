#ifndef __EVENTSTRUCTS_H__
#define __EVENTSTRUCTS_H__

#include <functional>
#include "CommonStructs.h"
#include "CView.h"

class IEventPayload {};

BEGIN_NAMESPACE(HmiNgin)

struct SInitQmlEventPayload: public IEventPayload
{
    const S_VIEW_INFORMATION*  info;
    std::function<void(CView*)> cb;
};

END_NAMESPACE


#endif // __EVENTSTRUCTS_H__