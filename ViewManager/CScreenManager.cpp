#include "CScreenManager.h"
#include "CScreen.h"

CScreenManager::CScreenManager(QObject *parent) : AViewManager(parent)
{}

AView *CScreenManager::createView(const S_VIEW_INFORMATION *view)
{
    return new CScreen(view);
}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{

    if(nextView == nullptr)
    {
        CPP_LOG_INFO("");
        return;
    }
    E_CACHE_STATUS cached = cacheStatus(nextView->id);
    if(cached == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", readCache(nextView->id)->info()->path);
        if(isValidDepth() && isValidLastId()) m_view.top()->hide();
        m_view.push(readCache(nextView->id));
        m_view.top()->show();
    }
    else if(cached == E_CACHE_STATUS::MISS)
    {
        AView* newView = createView(nextView);
        writecache(nextView->id, newView);
        m_view.push(newView);
        emit signalPushEnter(newView);
        CPP_LOG_INFO("Load SCREEN [%s]", newView->info()->path);
    }

    m_last_view = m_view.top();

    increaseHistory(m_last_view->info()->id);
    increaseDepth();
}

void CScreenManager::popExit()
{
    if(!isValidDepth()) return;

    readCache(m_last_view->info()->id)->hide();
    if(history(m_last_view->info()->id) < 1)
    {
        writecache(m_last_view->info()->id, nullptr);
        safeRelease(readCache(m_last_view->info()->id));
    }

    decreaseHistory(m_last_view->info()->id);
    decreaseDepth();
    m_view.pop();

    m_view.top()->show();
    m_last_view = m_view.top();
}

int CScreenManager::depth() const
{
    return m_depth;
}

