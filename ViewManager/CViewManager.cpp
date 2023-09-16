#include "CViewManager.h"

CViewManager::CViewManager(QObject *parent) : QObject(parent)
{}

CViewManager::~CViewManager()
{}


int CViewManager::depth() const
{
    return m_views.length();
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    E_CACHE_STATUS status = cacheStatus(nextView->id);
    emit signalPushBack(nextView, status);
}

void CViewManager::popExit()
{
    emit signalPopBack();
}

void CViewManager::pushBack(CView *newView)
{
    m_views.push_back(newView);
    emit depthChanged();
}

void CViewManager::popBack()
{
    m_views.pop_back();
    emit depthChanged();
}

CView *CViewManager::findViewObjectByID(const uint32_t &id)
{
    QList<CView*>::iterator it = m_views.begin();
    while(it != m_views.end())
    {
        if((*it)->id() == id)
        {
            return (*it);
        }
        ++it;
    }
    return nullptr;
}

QList<CView *> CViewManager::views() const
{
    return m_views;
}

void CViewManager::initConnections()
{
}
