#include "CScreenManager.h"

CScreenManager::CScreenManager(QObject *parent) : CViewManager(parent)
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

    E_CACHE_STATUS status = m_cacheManager->cacheStatus(info->id);
    if(status == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_DEBUG("Load SCREEN [%s] from cache memory", info->path);

        next = m_cacheManager->readCache<CScreen>(info->id);
        next->show();

        m_freqTable->increase(info->id);

        m_views.push_back(next);
        emit depthChanged();
    }
    else if(status == E_CACHE_STATUS::MISS)
    {
        CPP_LOG_DEBUG("Load SCREEN from path [%s]", info->path);
        m_freqTable->append(info->id, 0);
        emit signalLoadQml(info, m_load_qml_cb);
    }
}

void CScreenManager::detach(const S_VIEW_INFORMATION *info)
{
    CScreen *last = nullptr;
    last = m_cacheManager->readCache<CScreen>(info->id);
    if(last == nullptr) return;
    if(!isValidDepth()) return;

    last->hide();

    int index = -1;
    index = indexOf(last);
    m_views.removeAt(index);

    m_freqTable->reduce(info->id);


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

    m_cacheManager->writecache(view->id(), next);
    m_freqTable->increase(view->id());

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
