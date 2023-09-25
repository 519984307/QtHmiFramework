#include "CScreenManager.h"


CScreenManager::CScreenManager(QObject *parent) : CViewManager(parent)
{}

CScreenManager::~CScreenManager()
{

}

CScreen *CScreenManager::readCache(uint32_t key) const
{
    return m_view_cached[key];
}

void CScreenManager::writecache(uint32_t key, CScreen *view)
{
    m_view_cached[key] = view;
}

E_CACHE_STATUS CScreenManager::cacheStatus(const uint32_t key)
{
    if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
    return (m_view_cached[key] != nullptr)
               ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
}

void CScreenManager::attach(const S_VIEW_INFORMATION *info)
{
    CScreen *last = nullptr;
    CScreen *next = nullptr;

    if(!m_views.isEmpty())
    {
        last = m_views.last();
    }

    if(last != nullptr)
    {
        last->hide();
    }

    E_CACHE_STATUS status = cacheStatus(info->id);
    if(status == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_DEBUG("Load SCREEN [%s] from cache memory", info->path);

        next = readCache(info->id);
        next->show();

        m_view_history[next->id()]++;
        m_views.push_back(next);
        emit depthChanged();
    }
    else if(status == E_CACHE_STATUS::MISS)
    {
        CPP_LOG_DEBUG("Load SCREEN from path [%s]", info->path);
        emit signalLoadQml(info, m_load_qml_cb);
    }
}

void CScreenManager::detach(const S_VIEW_INFORMATION *info)
{
    CScreen *last = nullptr;
    last = readCache(info->id);
    if(last == nullptr) return;
    if(!isValidDepth()) return;

    last->hide();

    int index = -1;
    index = indexOf(last);
    m_views.removeAt(index);

    m_view_history[info->id]--;


    if(m_views.isEmpty()) return;
    m_views.last()->show();

    emit depthChanged();
}

void CScreenManager::initConnections()
{

}

void CScreenManager::loadQmlCallBack(CView *view)
{
    CPP_LOG_DEBUG("[Entry]", view)

    if(view == nullptr) return;

    CScreen* next = (CScreen*)view;
    next->show();

    writecache(view->id(), next);
    m_view_history[view->id()]++;
    m_views.push_back(next);
    emit depthChanged();

    CPP_LOG_DEBUG("[Exit]")
}

bool CScreenManager::isValidDepth()
{
    return depth() > 1;
}

int CScreenManager::indexOf(CScreen *view)
{
    int index = -1;
    QList<CScreen*>::iterator it = m_views.end();
    while(it != m_views.begin())
    {
        --it;
        if((*it)->id() == view->id())
        {
            index = (it - m_views.begin());
            break;
        }
        index = 0;
    }
    return index;
}

int CScreenManager::depth() const
{
    return m_views.count();
}
