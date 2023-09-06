#include "CScreenManager.h"
#include "CScreen.h"

CScreenManager::CScreenManager(QObject *parent) : AViewManager(parent)
{}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
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
        CScreen* newView = new CScreen(nextView, this);
        writecache(nextView->id, newView);
        m_views.push(newView);
        emit signalPushEnter(newView);
        CPP_LOG_INFO("Load SCREEN [%s]", newView->info()->path);
    }

    updateDepth();
    increaseHistory(nextView->id);
    m_last_view = m_views.top();
}

void CScreenManager::popExit()
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

    m_last_view = m_views.top();
    m_last_view->show();
    updateDepth();
}

