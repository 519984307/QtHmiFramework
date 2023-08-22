#include "CPopupManager.h"
#include "CPopup.h"

CPopupManager::CPopupManager(QObject *parent)
    : AViewManager{parent}
{

}

void CPopupManager::signalInvisible()
{
    AView *obj = reinterpret_cast<AView*>(this->sender());
    m_views.removeOne(obj);
    safeRelease(this->sender());
    updateDepth();
}

AView *CPopupManager::createView(const S_VIEW_INFORMATION *view)
{
    return new CPopup(view);
}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    if(m_last_view != nullptr) m_last_view->hide();
    if(m_views.size() > 5)
    {
        m_views.front()->hide();
        safeRelease(m_views.front());
        m_views.pop_front();
    }

    AView* newView = createView(nextView);
    connect(newView, &AView::signalInvisible,this, &CPopupManager::signalInvisible);
    m_views.push_back(newView);
    m_last_view = m_views.last();
    updateDepth();

    emit signalPushEnter(m_last_view);
    CPP_LOG_INFO("Load POPUP [%s]", newView->info()->path);
}

void CPopupManager::popExit()
{
    if(m_views.size() < 1) return;
    m_last_view->hide();
    m_last_view->disconnect();
    safeRelease(m_last_view);
    m_views.pop_back();

    if(!m_views.isEmpty())
    {
        m_last_view = m_views.last();
        m_last_view->show();
        updateDepth();
    }
    qInfo() << m_views;

    CPP_LOG_INFO("%d", m_views.size());
}
