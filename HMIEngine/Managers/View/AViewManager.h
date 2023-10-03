#ifndef AVIEWMANAGER_H
#define AVIEWMANAGER_H

#include <functional>
#include "CView.h"
#include "CCacheManager.h"
#include "CFreqTable.h"
#include "CEventManager.h"
#include "EventDefines.h"

class AViewManager
{
public:
    virtual void attach(const S_VIEW_INFORMATION*) = 0;
    virtual void detach(const S_VIEW_INFORMATION*) = 0;

protected:
    virtual void initConnections(){};
    virtual void loadNewQmFromCallback(CView*){};

protected:
    s_load_qml_cb_param                 m_load_qml_payload;
    std::function<void(CView*)>         m_load_qml_cb = std::bind(&AViewManager::loadNewQmFromCallback, this, std::placeholders::_1);
    CCacheManager                       m_cache_manager;
    CFreqTable                          m_freq_table;

};


#endif // AVIEWMANAGER_H
