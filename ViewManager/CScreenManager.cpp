#include "CScreenManager.h"

CScreenManager::CScreenManager(QObject *parent)
    : QObject{parent}
{

}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;

    if(cacheStatus(nextView->id) == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", m_view_cached[nextView->id]->info()->path.toStdString().c_str());
        if(isValidDepth()) { m_views.top()->hide(); }
        m_views.push(m_view_cached[nextView->id]);
        m_views.top()->show();
    }
    else if(cacheStatus(nextView->id) == E_CACHE_STATUS::MISS)
    {
        CScreen *comp = new CScreen;
        comp->setInfo(nextView);
        m_event_view_change_cb(comp);
        m_views.push(comp);
        m_view_cached[nextView->id] = comp;
    }

    m_last_view_id = nextView->id;

    increaseDepth();
}

void CScreenManager::popExit()
{
    if(!isValidDepth()) return;
    m_views.top()->hide();
    m_views.pop();

    m_views.top()->show();

    decreaseDepth();
}
