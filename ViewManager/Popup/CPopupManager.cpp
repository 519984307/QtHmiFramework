#include "CPopupManager.h"

CPopupManager::CPopupManager(QObject *parent)
    : AViewManager{parent}
{

}

void CPopupManager::signalInvisible()
{
    if(this->sender() == nullptr) return;
    CPopup *obj = reinterpret_cast<CPopup*>(this->sender());
    obj->hide();
    safeRelease(obj);
    int idx = indexOfView(obj->info()->id);
    m_views.removeAt(idx);
    updateDepth();
}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    CPopup* newView = new CPopup(nextView, this);
    m_last_view = newView;
    m_views.push_back(newView);
    connect((CPopup*)newView, &CPopup::signalWaittingForTimeout,this, &CPopupManager::signalInvisible);
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

int CPopupManager::indexOfView(const uint32_t &id)
{
    QList<CPopup*>::iterator it = m_views.begin();
    while(it != m_views.end())
    {
        if((*it)->info()->id == id)
        {
            return (int)(it - m_views.begin());
        }
        ++it;
    }
    return -1;
}
