#ifndef __EVENTDEFINES_H__
#define __EVENTDEFINES_H__

#include <functional>
#include "CommonStructs.h"
#include "IEvent.h"
#include "CView.h"

struct s_load_qml_cb_param: public IEvent
{
    const S_VIEW_INFORMATION* info;
    const std::function<void(CView*)> *cb;
};

#endif // __EVENTDEFINES_H__