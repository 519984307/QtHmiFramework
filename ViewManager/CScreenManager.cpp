#include "CScreenManager.h"

CScreenManager::CScreenManager(QObject *parent)
    : QObject{parent}
{

}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    E_CACHE_STATUS cached = cacheStatus(nextView->id);
    if(cached == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", readCache<CScreen>(m_last_view_id)->info()->path.toStdString().c_str());
        if(isValidDepth() && isValidLastId()) {readCache<CScreen>(m_last_view_id)->hide(); }
        m_views.push(readCache<CScreen>(nextView->id));
        m_views.top()->show();
    }
    else if(cached == E_CACHE_STATUS::MISS)
    {
        CScreen *comp = new CScreen;
        comp->setInfo(nextView);
        m_views.push(comp);
        writeCache(nextView->id, comp);
        m_event_view_change_cb();
        CPP_LOG_INFO("Load SCREEN [%s]", comp->info()->path.toStdString().c_str());
    }

    if(m_last_view_id != nextView->id)
    {
        m_last_view_id = nextView->id;
    }

    increaseHistory(m_last_view_id);
    increaseDepth();
}

void CScreenManager::popExit()
{
    readCache<CScreen>(m_last_view_id)->hide();
    if(history(m_last_view_id) < 1)
    {
        safeRelease(readCache<CScreen>(m_last_view_id));
    }
    m_views.pop();
    decreaseHistory(m_last_view_id);
    decreaseDepth();

    if(!isValidDepth()) return;
    m_views.top()->show();
    m_last_view_id = m_views.top()->info()->id;
}
