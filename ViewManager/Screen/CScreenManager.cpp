#include "CScreenManager.h"
#include "CScreen.h"

CScreenManager::CScreenManager(QObject *parent) : AViewManager(parent)
{}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    E_CACHE_STATUS status = cacheStatus(nextView->id);
    m_last_view = new CScreen(nextView);
    emit signalPushEnter(nextView, status);
}

AViewManager *CScreenManager::pushEnter(AView *newView)
{
    CPP_LOG_INFO("[Entry]")
    CScreen *obj = (CScreen*)newView;
    obj->setInfo(m_last_view->info());
    m_last_view = obj;
    uint32_t id = obj->info()->id;
    writecache(id, obj);
    m_views.push(obj);
    updateDepth();
    increaseHistory(id);
    CPP_LOG_INFO("Load SCREEN [%s]", newView->info()->path);
    CPP_LOG_INFO("[Exit]")
    return this;
}

void CScreenManager::pushEnterExisted(const S_VIEW_INFORMATION* nextView)
{
    CPP_LOG_INFO("Load SCREEN [%s] from cache memory", readCache(nextView->id)->info()->path);
    if(isValidDepth()) m_views.top()->hide();
    m_views.push(readCache(nextView->id));
    m_views.top()->show();
    m_last_view = m_views.top();
    updateDepth();
    increaseHistory(nextView->id);
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

