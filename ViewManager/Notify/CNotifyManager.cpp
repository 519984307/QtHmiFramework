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

void CNotifyManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    emit signalPushEnter(nextView, E_CACHE_STATUS::MISS);
}

AViewManager *CNotifyManager::pushEnter(AView *newView)
{
    CPP_LOG_INFO("[Entry]")
    m_last_view = newView;
    CNotify *obj = (CNotify*)newView;
    m_views.push_back(obj);
    updateDepth();
    CPP_LOG_INFO("Load NOTIFY [%s]", obj->info()->path)
    connect(obj, &CNotify::signalWaittingForTimeout,this, &CNotifyManager::onSignalInvisible, Qt::DirectConnection);
    CPP_LOG_INFO("[Exit]")
    return this;
}

void CNotifyManager::pushEnterExisted(const S_VIEW_INFORMATION *view)
{
    Q_UNUSED(view)
}

void CNotifyManager::popExit()
{
    return;
}
