#include "CPopupManager.h"

CPopupManager::CPopupManager(QObject *parent)
    : QObject{parent}
{

}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    CPopup *comp = new CPopup;
    comp->setInfo(nextView);
    m_event_view_change_cb();
    m_views.push(comp);
    increaseDepth();
}

void CPopupManager::popExit()
{
    m_views.top()->hide();
    safeRelease(m_views.top());
    m_views.pop();
    if(!m_views.empty())
    {
        m_views.top()->show();
    }

    decreaseDepth();
}
