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
    connect(newView, &CView::signalVisibleTimeout, this, [&](){
        this->popOne(newView);
    });

    ++m_view_history[newView->id()];

    emit depthChanged();
    CPP_LOG_INFO("[Exit]")
}

void CViewManager::popBack()
{
    CPP_LOG_INFO("[Entry]")
    if(m_views.isEmpty()) return;

    CView *view = m_views.last();
    popOne(view);

    CPP_LOG_INFO("[Exit]")
}

void CViewManager::popOne(CView *view)
{
    CPP_LOG_INFO("[Entry]")

    if(view == nullptr) return;

    removeOne(view);
    emit depthChanged();

    --m_view_history[view->id()];
    if (m_view_history[view->id()] < 1)
    {
        CPP_LOG_INFO("Release [%s]", view->c_strType())
        writecache(view->id(), nullptr);
        m_view_history[view->id()] = 0;
        safeRelease(view);
    }


    CPP_LOG_INFO("[Exit]")
}

void CViewManager::popOne(const uint32_t &id)
{
    CPP_LOG_INFO("[Entry]")

    CView *view = findViewObjectByID(id);
    popOne(view);

    CPP_LOG_INFO("[Exit]")
}

void CViewManager::removeOne(CView *view)
{
    CPP_LOG_INFO("[Entry]")

    int index  = indexOf(view);
    m_views.removeAt(index);

    CPP_LOG_INFO("[Exit]")
}

void CViewManager::removeOne(const uint32_t &id)
{
    CPP_LOG_INFO("[Entry]")

    CView *obj = findViewObjectByID(id);
    removeOne(obj);

    CPP_LOG_INFO("[Exit]")
}

int CViewManager::indexOf(CView *view)
{
    int index = -1;
    for(CView *e: m_views)
    {
        index++;
        if(e->id() == view->id())
        {
            break;
        }
    }
    return index;
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
