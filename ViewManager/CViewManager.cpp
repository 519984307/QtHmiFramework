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

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{


//    if(m_events_history[event]->type == E_VIEW_TYPE::POPUP_TYPE) // check if current view  is a popup
//    {
//        m_popupObjs.push(new CPopupObject(this));
//        m_popupObjs.top()->setData(m_events_history[event]);
//        m_popupObjs.top()->show();
//    }

    m_stack.push(view);
    m_stack.top()->fnEntry();
}

void CViewManager::popExit()
{
    if(m_stack.length() <= 1) return;
    m_stack.pop()->fnExit();
    m_stack.top()->fnEntry();
}
