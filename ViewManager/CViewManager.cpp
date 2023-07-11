#include "CViewManager.h"
#include "Utils.h"
CViewManager::CViewManager(QObject *parent)
    : QObject{parent}
{
}

CViewManager::~CViewManager()
{
}

const S_VIEW_INFORMATION *CViewManager::currentView() const
{
    return m_stack.top();
}

void CViewManager::addView(const S_VIEW_INFORMATION *view)
{
    m_views.push_back(view);
}

void CViewManager::addEvents(const S_VIEW_EVENT *event)
{
    m_events.push_back(event);
}

void CViewManager::pushViewByEvt(uchar &event)
{
    QList<const S_VIEW_EVENT*>::iterator evtIt = m_events.begin();
    QList<const S_VIEW_INFORMATION*>::iterator infoIt = m_views.begin();

    // Check if event was ever sent
    if(m_event_history[event] == nullptr)
    {
        for(; evtIt != m_events.end(); evtIt++)
        {
            if(event == (*evtIt)->event)
            {
                break;
            }
        }

        while(infoIt != m_views.end())
        {
            if((*evtIt)->destination != (*infoIt)->id)
            {
                ++infoIt;
                continue;
            }

            m_event_history[event] = (*infoIt);
            break;
        }
    }


    if(m_event_history[event]->type == E_VIEW_TYPE::POPUP_TYPE)
    {

    }


    m_event_history[event]->fnEntry();

    if(m_stack.length() > 0)
    {
        // [1] check if top of the stack is a popup -> pop stack & got into fnExit()
        if(m_stack.top()->type == E_VIEW_TYPE::POPUP_TYPE)
        {
            m_stack.pop();
        }

        m_stack.top()->fnExit();
    }

    m_stack.push(m_event_history[event]);
    qInfo() << m_stack;
}

void CViewManager::popLastView()
{
    if(m_stack.length() <= 1) return;
    m_stack.pop()->fnExit();
    m_stack.top()->fnEntry();
}
