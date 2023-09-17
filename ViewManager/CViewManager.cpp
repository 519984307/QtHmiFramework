#include "CViewManager.h"

CViewManager::CViewManager(QObject *parent) : QObject(parent)
{}

CViewManager::~CViewManager()
{}


int CViewManager::depth() const
{
    return m_views.length();
}

CView *CViewManager::lastView() const
{
    return m_views.last();
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    CPP_LOG_INFO("[Entry]")
    E_CACHE_STATUS status = cacheStatus(nextView->id);
    emit signalPushBack(nextView, status);
    CPP_LOG_INFO("[Exit]")
}

void CViewManager::popExit()
{
    CPP_LOG_INFO("[Entry]")
    emit signalPopBack();
    CPP_LOG_INFO("[Exit]")
}

void CViewManager::pushBack(CView *newView)
{
    CPP_LOG_INFO("[Entry]")
    m_views.push_back(newView);

    if (m_view_history[newView->id()] > 0)
    {
        m_view_history[newView->id()] += 1;
    }
    else
    {
        m_view_history[newView->id()] = 0;
    }

    emit depthChanged();
    CPP_LOG_INFO("[Exit]")
}

void CViewManager::popBack()
{
    CPP_LOG_INFO("[Entry]")

    CView *last = m_views.last();
    m_views.pop_back();

    m_view_history[last->id()]--;
    if (m_view_history[last->id()] < 0)
    {
        m_view_history[last->id()] = 0;
        writecache(last->id(), nullptr);
        safeRelease(last);
    }

    emit depthChanged();
    CPP_LOG_INFO("[Exit]")
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
