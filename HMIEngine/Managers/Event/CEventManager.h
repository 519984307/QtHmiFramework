#ifndef __CEVENTMANAGER_H__
#define __CEVENTMANAGER_H__

#include <stdint.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include "EventEnums.h"
#include "IEvent.h"

typedef std::function<void(IEvent*)> EventCallBack;

class CEventManager
{
private:
    static CEventManager                                         *s_instance;
    std::unordered_map<E_EVENT_ID, std::vector<EventCallBack>>    m_cb_dict;

private:
    CEventManager();
    ~CEventManager();

public:
    static CEventManager *instance();

    void registerListener(E_EVENT_ID eventID, EventCallBack &listener);
    void dispatchEvent(E_EVENT_ID eventID, IEvent *payload);

};

#endif // __CEVENTMANAGER_H__