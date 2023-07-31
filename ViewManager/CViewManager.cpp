#include "CViewManager.h"
#include "Utils.h"
#include "ViewManagerDefines.h"
#include "Logger/LoggerDefines.h"

CViewManager::CViewManager(QQmlApplicationEngine *ngin, QObject *parent)
    : QObject{parent}
{
    m_ngin = ngin;
    m_base = new QQmlComponent(m_ngin, this);

    m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]   = &m_screen_manager;
    m_view_managers[E_VIEW_TYPE::POPUP_TYPE]    = &m_popup_manager;
    m_view_managers[E_VIEW_TYPE::TOAST_TYPE]    = &m_toast_manager;
    m_view_managers[E_VIEW_TYPE::NOTIFY_TYPE]   = &m_notify_manager;

    initConnections();
}

CViewManager::~CViewManager()
{
    safeRelease(m_base);
}

const S_VIEW_INFORMATION *CViewManager::currentView() const
{
    return m_view_managers[m_last_view_type]->lastView();
}

uint8_t CViewManager::depth() const
{
    return m_depth;
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{
    m_last_view_type = view->type;
    m_view_managers[m_last_view_type]->pushEnter(view);
}

void CViewManager::popExit()
{
    if(m_last_view_type == E_VIEW_TYPE::NONE_TYPE) return;
    m_view_managers[m_last_view_type]->popExit();
}

void CViewManager::initConnections()
{
    connect(m_base, &QQmlComponent::statusChanged, this, &CViewManager::onStatusChanged);
}

void CViewManager::onCompleted()
{
    if (m_window == nullptr)
    {
        m_window = qobject_cast<QQuickWindow*>(m_ngin->rootObjects().at(0));
    }
}

void CViewManager::onStatusChanged(QQmlComponent::Status status)
{
    switch (status) {
    case QQmlComponent::Null:
        CPP_LOG_INFO("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.");
        break;
    case QQmlComponent::Ready:
    {
        CPP_LOG_INFO("This QQmlComponent is ready and create() may be called.");
        break;
    }
    case QQmlComponent::Loading:
        CPP_LOG_INFO("This QQmlComponent is loading network data.");
        break;
    case QQmlComponent::Error:
        CPP_LOG_INFO("An error has occurred. Call errors() to retrieve a list of errors.");
        break;
    default:
        break;
    }
}

void CViewManager::onProgressChanged(qreal progress)
{
    CPP_LOG_INFO("%d", progress);
}
