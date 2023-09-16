#include "CViewManager.h"

CViewManager::CViewManager(QObject *parent) : QObject(parent)
{}

CViewManager::~CViewManager()
{}


int CViewManager::depth() const
{
    return m_views.length();
}

void CViewManager::pushBack(QQmlComponent *qmlBase, QQuickItem *parentItem, const S_VIEW_INFORMATION *nextView)
{
    CPP_LOG_INFO("[Entry]")

    m_qml_base          = qmlBase;
    m_qml_parent        = parentItem;
    m_next_view_info    = nextView;

    connect(m_qml_base, &QQmlComponent::progressChanged, this, &CViewManager::onProgressChanged);
    connect(m_qml_base, &QQmlComponent::statusChanged, this, &CViewManager::onStatusChanged);


    E_CACHE_STATUS status = cacheStatus(nextView->id);

    if(status == E_CACHE_STATUS::HIT)
    {
        m_last_view = readCache(nextView->id);
        m_last_view->hide();
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", m_last_view->path());
        m_last_view->show();
        m_views.push_back(m_last_view);
        increaseHistory(m_last_view->id());
        emit depthChanged();
    }
    else if(status == E_CACHE_STATUS::MISS)
    {
        CPP_LOG_DEBUG("Path %s", nextView->path);
        qmlBase->loadUrl(QUrl(nextView->path), QQmlComponent::Asynchronous);
    }

    CPP_LOG_INFO("[Exit]")

}

void CViewManager::popBack()
{
    CPP_LOG_INFO("[Entry]")

    if(!isValidDepth()) return;
    m_last_view->hide();
    decreaseHistory(m_last_view->id());
    if(history(m_last_view->id()) == 0)
    {
        writecache(m_last_view->id(), nullptr);
        safeRelease(m_last_view);
    }

    m_views.pop_back();

    m_last_view = m_views.last();
    m_last_view->show();
    emit depthChanged();

    CPP_LOG_INFO("[Exit]")
}

void CViewManager::onStatusChanged(QQmlComponent::Status status)
{
    switch (status) {
    case QQmlComponent::Null:
        CPP_LOG_INFO("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.")
        break;
    case QQmlComponent::Ready:
    {
        CPP_LOG_INFO("This QQmlComponent is ready and create() may be called.")
        m_last_view = qobject_cast<CView*>(m_qml_base->create());
        m_last_view->initialize(m_next_view_info, m_qml_parent);
        m_last_view->show();
        m_views.push_back(m_last_view);
        increaseHistory(m_last_view->id());
        writecache(m_last_view->id(), m_last_view);
        CPP_LOG_INFO("Load SCREEN [%s]", m_next_view_info->path);
        emit depthChanged();

        break;
    }
    case QQmlComponent::Loading:
        CPP_LOG_INFO("This QQmlComponent is loading network data.")
        break;
    case QQmlComponent::Error:
        CPP_LOG_INFO("An error has occurred. Call errors() to retrieve a list of errors.")
        break;
    default:
        break;
    }
}

void CViewManager::onProgressChanged(qreal progress)
{
    CPP_LOG_INFO("Loaded %f", progress);
}

void CViewManager::initConnections()
{

}
