#include "CScreenManager.h"

CScreenManager::CScreenManager()
{}

CScreenManager::~CScreenManager()
{

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

    E_CACHE_STATUS status = m_cache_manager.cacheStatus(info->id);
    if(status == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_DEBUG("Load SCREEN [%s] from cache memory", info->path);

        next = m_cache_manager.readCache<CScreen>(info->id);
        next->show();

        m_freq_table.increase(info->id);

        m_views.push_back(next);
        emit depthChanged();
    }
    else if(status == E_CACHE_STATUS::MISS)
    {
        CPP_LOG_DEBUG("Load SCREEN from path [%s]", info->path);        
        m_load_qml_payload.info = info;
        m_load_qml_payload.cb   = &m_load_qml_cb;
        CEventManager::instance()->dispatchEvent(E_EVENT_LOAD_QML, &m_load_qml_payload);
    }
}

void CScreenManager::detach(const S_VIEW_INFORMATION *info)
{
    CScreen *last = nullptr;
    last = m_cache_manager.readCache<CScreen>(info->id);
    if(last == nullptr) return;
    if(!isValidDepth()) return;

    m_freq_table.append(info->id, 0);

    last->hide();

    int index = -1;
    index = indexOf(last);
    m_views.removeAt(index);

    m_freq_table.reduce(info->id);

    if(m_views.isEmpty()) return;
    m_views.last()->show();

    emit depthChanged();
}

void CScreenManager::initConnections()
{

}

void CScreenManager::loadNewQmFromCallback(CView *view)
{
    CPP_LOG_DEBUG("[Entry] %s", view->path())

    if(view == nullptr) return;

    CScreen* next = (CScreen*)view;
    next->show();

    m_cache_manager.writecache(view->id(), next);
    m_freq_table.increase(view->id());

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
