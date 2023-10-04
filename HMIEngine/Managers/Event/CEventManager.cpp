#include "Logger/LoggerDefines.h"

#include "CEventManager.h"
#include "CommonDefine.h"

namespace HmiNgin
{
    CEventManager *CEventManager::s_instance = nullptr;
    CEventManager::CEventManager()
    {
    }

    CEventManager::~CEventManager()
    {
    }

    CEventManager *CEventManager::instance()
    {
        return s_instance = (s_instance == nullptr ? new CEventManager() : s_instance);
    }

    void CEventManager::registerListener(E_EVENT_ID eventID, EventCallBack &listener)
    {
        m_cb_dict[eventID].push_back(listener);
    }

    void CEventManager::dispatchEvent(E_EVENT_ID eventID, IEventPayload *payload)
    {
        if (m_cb_dict[eventID].size() < 1)
            return;
        std::vector<EventCallBack>::iterator it = m_cb_dict[eventID].begin();
        while (it != m_cb_dict[eventID].end())
        {
            (*it)(payload);
            ++it;
        }
    }

    void CEventManager::dispatchEvent(E_EVENT_ID eventID)
    {
        dispatchEvent(eventID, nullptr);
    }
} // namespace HmiNgin

