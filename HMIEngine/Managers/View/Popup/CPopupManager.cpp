#include "CPopupManager.h"

BEGIN_NAMESPACE(HmiNgin)
CPopupManager::CPopupManager()
{
    m_initQmlEventPayload.cb = std::bind(&CPopupManager::loadNewQmFromCallback, this, std::placeholders::_1);
}

CPopupManager::~CPopupManager()
{
}

void CPopupManager::attach(const S_VIEW_INFORMATION *info)
{
    if(info == nullptr) return;
    if(m_view != nullptr) m_view->hide();

    CPP_LOG_DEBUG("Load POPUP from path [%s]", info->path);

    E_CACHE_STATUS status = m_cache_manager.cacheStatus(info->id);
    if (status == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_DEBUG("Load SCREEN [%s] from cache memory", info->path);

        if(m_view != nullptr) m_view->hide();

        m_view = m_cache_manager.readCache<CPopup>(info->id);
        m_view->show();
    }
    else if (status == E_CACHE_STATUS::MISS)
    {
        CPP_LOG_DEBUG("Load SCREEN from path [%s]", info->path);
        m_initQmlEventPayload.info = info;
        CEventManager::instance()->dispatchEvent(E_EVENT_LOAD_QML, &m_initQmlEventPayload);
    }
}

void CPopupManager::detach(const S_VIEW_INFORMATION *info)
{
    Q_UNUSED(info);
    m_view->hide();
}

void CPopupManager::loadNewQmFromCallback(CView *view)
{
    CPP_LOG_DEBUG("[Entry]")

    if (view == nullptr)
        return;

    CPopup *next = (CPopup *)view;
    next->show();

    m_cache_manager.writecache(view->id(), next);

    m_view = next;

    CPP_LOG_DEBUG("[Exit]")
}

END_NAMESPACE
