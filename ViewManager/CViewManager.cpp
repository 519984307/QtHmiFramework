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
    if(nextView == nullptr) return;
    E_CACHE_STATUS status = cacheStatus(nextView->id);
    emit signalPushBack(nextView, status);
}

void CViewManager::popExit()
{
    emit signalPopBack();
}

void CViewManager::pushBack(CView *newView)
{
    if(newView == nullptr)
    {
        CPP_LOG_DEBUG("New View is NULL")
        return;
    }
    m_views.push_back(newView);
    connect(newView, &CView::signalVisibleTimeout, this, [&](){
        this->popOne(newView);
    });

    ++m_view_history[newView->id()];

    emit depthChanged();
}

void CViewManager::popBack()
{
    if(m_views.isEmpty())
    {
        CPP_LOG_DEBUG("View container is empty")
        return;
    }

    CView *view = m_views.last();
    popOne(view);

}

void CViewManager::popOne(CView *view)
{
    if(view == nullptr) return;

    removeOne(view);
    emit depthChanged();

    --m_view_history[view->id()];
    if (m_view_history[view->id()] < 1)
    {
        CPP_LOG_DEBUG("Release [%s]", view->c_strType())
        writecache(view->id(), nullptr);
        m_view_history[view->id()] = 0;
        safeRelease(view);
    }
}

void CViewManager::popOne(const uint32_t &id)
{
    CView *view = findViewObjectByID(id);
    popOne(view);
}

void CViewManager::removeOne(CView *view)
{
    if(view == nullptr) return;

    int index  = indexOf(view);
    m_views.removeAt(index);
}

void CViewManager::removeOne(const uint32_t &id)
{
    CView *obj = findViewObjectByID(id);
    removeOne(obj);
}

int CViewManager::indexOf(CView *view)
{
    int index = -1;
    QList<CView*>::iterator it = m_views.end();
    while(it != m_views.begin())
    {
        --it;
        if((*it)->id() == view->id())
        {
            return (it - m_views.begin());
        }
    }
    return index;
}

CView *CViewManager::findViewObjectByID(const uint32_t &id)
{
    QList<CView*>::iterator it = m_views.end();
    while(it != m_views.begin())
    {
        --it;
        if((*it)->id() == id)
        {
            return (*it);
        }
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
