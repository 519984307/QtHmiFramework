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
    m_views.push(comp);
    m_event_view_change_cb();

    if(m_last_view_id != nextView->id)
    {
        m_last_view_id = nextView->id;
    }
    increaseDepth();
}

void CPopupManager::popExit()
{
    if(m_views.isEmpty()) return;
    m_views.top()->hide();
    safeRelease(m_views.top());
    m_views.pop();

    if(m_views.isEmpty()) return;

    m_views.top()->show();
    m_last_view_id = m_views.top()->info()->id;

    decreaseDepth();
}
