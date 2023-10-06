#ifndef AVIEWMANAGER_H
#define AVIEWMANAGER_H

#include <functional>
#include "CView.h"
#include "CCacheManager.h"
#include "CFreqTable.h"
#include "CEventManager.h"
#include "EventStructs.h"

BEGIN_NAMESPACE(HmiNgin)
class AViewManager
{
public:
    virtual void attach(const S_VIEW_INFORMATION *) = 0;
    virtual void detach(const S_VIEW_INFORMATION *) = 0;

protected:
    virtual void initConnections(){};
    virtual void loadNewQmFromCallback(CView *){};

protected:
    CCacheManager           m_cache_manager;
    CFreqTable              m_freq_table;

    // payloads
    SInitQmlEventPayload    m_initQmlEventPayload;
};
END_NAMESPACE

#endif // AVIEWMANAGER_H
