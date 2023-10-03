#include "CPopupManager.h"

CPopupManager::CPopupManager()
{}

CPopupManager::~CPopupManager()
{

}

void CPopupManager::attach(const S_VIEW_INFORMATION *info)
{
    CPP_LOG_DEBUG("Load POPUP from path [%s]", info->path);
    // emit signalLoadQml(info, m_load_qml_cb);
}

void CPopupManager::detach(const S_VIEW_INFORMATION *info)
{
    Q_UNUSED(info);
    m_view->hide();
}

void CPopupManager::loadNewQmFromCallback(CView *view)
{
    CPP_LOG_DEBUG("[Entry]")

    if(view == nullptr) return;

    CPopup* next = (CPopup*)view;
    next->show();

    m_view = next;

    CPP_LOG_DEBUG("[Exit]")
}
