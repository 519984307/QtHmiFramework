#include "CPopupManager.h"

CPopupManager::CPopupManager(QObject *parent)
    : AViewManager{parent}
{

}

void CPopupManager::onSignalInvisible()
{
    if(this->sender() == nullptr) return;
    CPopup *obj = reinterpret_cast<CPopup*>(this->sender());
    obj->hide();
    int idx = indexOfViewByID<CPopup>(m_views, obj->info()->id);
    m_views.removeAt(idx);
    updateDepth();
    safeRelease(obj);
}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    emit signalPushEnter(nextView, E_CACHE_STATUS::MISS);
}

AViewManager *CPopupManager::pushEnter(AView *newView)
{
    CPP_LOG_INFO("[Entry]")
    m_last_view = newView;
    CPopup *obj = (CPopup*)newView;
    m_views.push_back(obj);
    updateDepth();
    CPP_LOG_INFO("Load POPUP [%s]", obj->info()->path);
    connect(obj, &CPopup::signalWaittingForTimeout,this, &CPopupManager::onSignalInvisible);
    CPP_LOG_INFO("[Exit]")
    return this;
}

void CPopupManager::pushEnterExisted(const S_VIEW_INFORMATION *view)
{
    Q_UNUSED(view)
}

void CPopupManager::popExit()
{
    qInfo() << m_views;
    if(!isValidDepth()) return;
    if(m_views.last() == nullptr) return;
    m_last_view = m_views.last();
    m_last_view->hide();
    safeRelease(m_last_view);
    m_views.pop_back();
    updateDepth();

    if(!m_views.isEmpty())
    {
        m_last_view = m_views.last();

        m_last_view->show();

    }
}
