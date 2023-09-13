#include "CToastManager.h"

CToastManager::CToastManager(QObject *parent)
    : AViewManager{parent}
{

}

void CToastManager::removeById(const uint32_t &id)
{
    int idx = indexOfViewByID<CToast>(m_views, id);
    CToast *obj = m_views.at(idx);
    m_views.removeAt(idx);
    updateDepth();
    safeRelease(obj);
}

void CToastManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    emit signalPushEnter(nextView, E_CACHE_STATUS::MISS);
}

AViewManager *CToastManager::pushEnter(AView *newView)
{
    CPP_LOG_INFO("[Entry]")
    m_last_view = newView;
    CToast *obj = (CToast*)newView;
    m_views.push_back(obj);
    updateDepth();
    CPP_LOG_INFO("Load TOAST [%s]", obj->info()->path)
    connect(obj, &CToast::signalWaittingForTimeout,this, &CToastManager::onSignalInvisible, Qt::DirectConnection);
    CPP_LOG_INFO("[Exit]")
    return this;
}

void CToastManager::pushEnterExisted(const S_VIEW_INFORMATION *view)
{
    Q_UNUSED(view)
}

void CToastManager::popExit()
{
    return;
}

void CToastManager::onSignalInvisible()
{
    if(this->sender() == nullptr) return;
    CToast *obj = reinterpret_cast<CToast*>(this->sender());
    obj->hide();
    removeById(obj->info()->id);
}
