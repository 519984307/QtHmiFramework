#include "CPopupManager.h"

namespace HmiNgin
{
    CPopupManager::CPopupManager()
    {
        m_initQmlEventPayload.cb = std::bind(&CPopupManager::loadNewQmFromCallback, this, std::placeholders::_1);
    }

    CPopupManager::~CPopupManager()
    {
    }

    void CPopupManager::attach(const S_VIEW_INFORMATION *info)
    {
        CPP_LOG_DEBUG("Load POPUP from path [%s]", info->path);

        m_initQmlEventPayload.info = info;
        CEventManager::instance()->dispatchEvent(E_EVENT_LOAD_QML, &m_initQmlEventPayload);
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

        m_view = next;

        CPP_LOG_DEBUG("[Exit]")
    }

} // namespace HmiNgin
