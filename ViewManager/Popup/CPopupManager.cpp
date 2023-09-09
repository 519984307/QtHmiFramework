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
    CPopup* newView = new CPopup(nextView, this);
    m_last_view = newView;
    m_views.push_back(newView);
    connect((CPopup*)newView, &CPopup::signalWaittingForTimeout,this, &CPopupManager::onSignalInvisible);
    emit signalPushEnter(newView);
    updateDepth();
    CPP_LOG_INFO("Load POPUP [%s]", newView->info()->path);
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
