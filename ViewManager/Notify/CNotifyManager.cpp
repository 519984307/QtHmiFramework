#include "CNotifyManager.h"

CNotifyManager::CNotifyManager(QObject *parent)
    : AViewManager{parent}
{

}

void CNotifyManager::removeById(const uint32_t &id)
{
    int idx = indexOfViewByID<CNotify>(m_views, id);
    CNotify *obj = m_views.at(idx);
    m_views.removeAt(idx);
    updateDepth();
    safeRelease(obj);
}

void CNotifyManager::onSignalInvisible()
{
    if(this->sender() == nullptr) return;
    CNotify *obj = reinterpret_cast<CNotify*>(this->sender());
    obj->hide();
}

void CNotifyManager::pushEnter(const S_VIEW_INFORMATION *view)
{
    if(view == nullptr) return;
    CNotify *newView = new CNotify(view, this);
    m_views.insert(view->id, newView);
    connect((CNotify*)newView, &CNotify::signalWaittingForTimeout,this, &CNotifyManager::onSignalInvisible, Qt::DirectConnection);
    emit signalPushEnter(newView);
    updateDepth();
    CPP_LOG_INFO("Load NOTIFY [%s]", newView->info()->path);
}

void CNotifyManager::popExit()
{
    return;
}
