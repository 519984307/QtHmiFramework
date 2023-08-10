#include "CViewManager.h"
#include "ViewManagerDefines.h"
#include "Logger/LoggerDefines.h"
#include "Utils.h"

CViewManager::CViewManager(QQmlApplicationEngine *ngin, QObject *parent)
    : QObject{parent}
{
    m_ngin = ngin;
    m_base = new QQmlComponent(m_ngin, this);

    m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]   = &m_screen_manager;
    m_view_managers[E_VIEW_TYPE::POPUP_TYPE]    = &m_popup_manager;
    m_view_managers[E_VIEW_TYPE::TOAST_TYPE]    = &m_toast_manager;
    m_view_managers[E_VIEW_TYPE::NOTIFY_TYPE]   = &m_notify_manager;


    QHash<E_VIEW_TYPE, AViewManager*>::iterator it = m_view_managers.begin();
    while (it != m_view_managers.end())
    {
        (*it)->registerViewChangeEventCallBack(
            std::bind(&CViewManager::listenViewChangeEventCallBack, this));
        ++it;
    }

    initConnections();
}

CViewManager::~CViewManager()
{
    safeRelease(m_base);
}

CComponent *CViewManager::currentView()
{
    return m_view_managers[m_last_view_type]->lastView();
}

int CViewManager::depth() const { return m_depth; }

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{
    m_last_view_type = view->type;
    m_view_managers[m_last_view_type]->pushEnter(view);
    updateDepth();
}

void CViewManager::popExit()
{
    if(m_last_view_type == E_VIEW_TYPE::NONE_TYPE) return;

    m_last_view_type = E_VIEW_TYPE::SCREEN_TYPE;
    if(m_view_managers[E_VIEW_TYPE::POPUP_TYPE]->isValidDepth())
    {
        m_last_view_type = E_VIEW_TYPE::POPUP_TYPE;
    }
    m_view_managers[m_last_view_type]->popExit();
    updateDepth();
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
        m_qml_parent = m_window->contentItem();
    }
}

void CViewManager::onProgressChanged(qreal progress)
{
    CPP_LOG_INFO("%d", progress);
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

        QQuickItem *item = qobject_cast<QQuickItem*>(m_base->create());
        item->setParentItem(m_qml_parent);

        currentView()->setProperty("anchors", qvariant_cast<QObject*>(item->property("anchors")));

        if(currentView()->info()->type == E_VIEW_TYPE::SCREEN_TYPE)
        {
            currentView()->properties().value("anchors")->setProperty("fill", QVariant::fromValue(m_qml_parent));
        }
        else if(currentView()->info()->type == E_VIEW_TYPE::POPUP_TYPE)
        {
            currentView()->properties().value("anchors")->setProperty("centerIn", QVariant::fromValue(m_qml_parent));
        }
        else if(currentView()->info()->type == E_VIEW_TYPE::TOAST_TYPE)
        {
            currentView()->properties().value("anchors")->setProperty("horizontalCenter", QVariant::fromValue(m_qml_parent->property("horizontalCenter")));
            currentView()->properties().value("anchors")->setProperty("bottom", QVariant::fromValue(m_qml_parent->property("bottom")));
            currentView()->properties().value("anchors")->setProperty("bottomMargin", TOAST_MARGIN_BOTTOM);
        }
        else if(currentView()->info()->type == E_VIEW_TYPE::NOTIFY_TYPE)
        {
            currentView()->properties().value("anchors")->setProperty("horizontalCenter", QVariant::fromValue(m_qml_parent->property("horizontalCenter")));
            currentView()->properties().value("anchors")->setProperty("top", QVariant::fromValue(m_qml_parent->property("top")));
            currentView()->properties().value("anchors")->setProperty("topMargin", NOTIFY_MARGIN_TOP);
        }

        currentView()->setItem(item);

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

void CViewManager::listenViewChangeEventCallBack()
{
    if(currentView() == nullptr) return;
    CPP_LOG_DEBUG("Path %s", currentView()->info()->path.toStdString().c_str());
    m_base->loadUrl(QUrl(currentView()->info()->path), QQmlComponent::Asynchronous);
}

void CViewManager::updateDepth()
{
    resetDepth();
    QHash<E_VIEW_TYPE, AViewManager*>::iterator it = m_view_managers.begin();
    while(it != m_view_managers.end())
    {
        m_depth += (*it)->depth();
        ++it;
    }
    emit depthChanged();
}

void CViewManager::resetDepth()
{
    m_depth = 0;
    emit depthChanged();
}
