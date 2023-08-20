#include "CPopupManager.h"
#include "CPopup.h"

CPopupManager::CPopupManager(QObject *parent)
    : AViewManager{parent}
{

}

AView *CPopupManager::createView(const S_VIEW_INFORMATION *view)
{
    return new CPopup(view);
}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;

    E_CACHE_STATUS cached = cacheStatus(nextView->id);
    if(cached == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", readCache(nextView->id)->info()->path);
        if(isValidDepth()) m_views.top()->hide();
        m_views.push(readCache(nextView->id));
        m_views.top()->show();
    }
    else if(cached == E_CACHE_STATUS::MISS)
    {
        AView* newView = createView(nextView);
        writecache(nextView->id, newView);
        m_views.push(newView);
        CPP_LOG_INFO("Load SCREEN [%s]", newView->info()->path);
        emit signalPushEnter(newView);
    }

    updateDepth();
    increaseHistory(nextView->id);
    m_last_view = m_views.top();
}

void CPopupManager::popExit()
{
    if(!isValidDepth()) return;
    m_last_view->hide();
    decreaseHistory(m_last_view->info()->id);
    if(history(m_last_view->info()->id) == 0)
    {
        writecache(m_last_view->info()->id, nullptr);
        safeRelease(m_last_view);
    }

    m_views.pop();
    if(depth() > 0)
    {
        m_last_view = m_views.top();
        m_last_view->show();
        updateDepth();
    }
}
