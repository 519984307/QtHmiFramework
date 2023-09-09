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

void CToastManager::pushEnter(const S_VIEW_INFORMATION *view)
{
    if(view == nullptr) return;
    CToast *newView = new CToast(view, this);
    m_last_view = newView;
    m_views.push_back(newView);
    connect((CToast*)newView, &CToast::signalWaittingForTimeout,this, &CToastManager::onSignalInvisible, Qt::DirectConnection);
    emit signalPushEnter(newView);
    updateDepth();
    CPP_LOG_INFO("Load TOAST [%s]", newView->info()->path)
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
