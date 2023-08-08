#include "CScreenManager.h"

CScreenManager::CScreenManager(QObject *parent)
    : QObject{parent}
{

}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;

    ++m_view_history[nextView->id];

    E_CACHE_STATUS cached = cacheStatus(nextView->id);
    if(cached == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", m_view_cached[nextView->id]->info()->path.toStdString().c_str());
        if(isValidDepth()) {m_view_cached[m_last_view_id]->hide(); }
        if(m_last_view_id != nextView->id)
        {
            m_views.push(m_view_cached[nextView->id]);
            m_views.top()->show();
        }
        else
        {
            return;
        }
    }
    else if(cached == E_CACHE_STATUS::MISS)
    {
        CScreen *comp = new CScreen;
        comp->setInfo(nextView);
        m_event_view_change_cb(comp);
        m_views.push(comp);
        m_view_cached[nextView->id] = comp;
    }


    m_last_view_id = nextView->id;

    increaseDepth();
    qInfo() << m_views;
}

void CScreenManager::popExit()
{
    if(!isValidDepth()) return;
    m_views.top()->hide();
    --m_view_history[m_last_view_id];
    if(m_view_history[m_last_view_id] < 1)
    {
        m_view_history.remove(m_last_view_id);
        m_view_cached.remove(m_last_view_id);
        safeRelease(m_view_cached[m_last_view_id]);
    }
    m_views.pop();

    m_views.top()->show();
    m_last_view_id = m_views.top()->info()->id;

    decreaseDepth();
    qInfo() << m_views;
}
