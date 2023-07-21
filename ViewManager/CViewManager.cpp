#include "CViewManager.h"
#include "Utils.h"
#include <QGuiApplication>

CViewManager::CViewManager(QQmlApplicationEngine *ngin, QObject *parent)
    : QObject{parent}
{
    m_ngin = ngin;
    m_base = new QQmlComponent(m_ngin, this);

    initConnections();
}

CViewManager::~CViewManager()
{
    safeRelease(m_base);
}

const S_VIEW_INFORMATION *CViewManager::currentView() const
{
    return m_currentView;
}

uint8_t CViewManager::depth() const
{
    return m_depth;
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{
    // Log item to history
    if(!m_stack_history.key(view->id)) m_stack_history.insert(view->id, true);

    m_currentView = view;

    initComponent();
}

void CViewManager::popExit()
{
    // Check: if stack's depth less than 2 view
    if(m_depth < 2) return;
    // Remove item pushed
    if(m_stack_history.key(m_currentView->id)) m_stack_history.remove(m_currentView->id);

    destroyComponent();
}

void CViewManager::onStatusChanged(QQmlComponent::Status status)
{
    switch (status) {
    case QQmlComponent::Null:
        qInfo() << "This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.";
        break;
    case QQmlComponent::Ready:
    {
        m_stack.push({currentView(), new QQuickItem()});

        m_stack.top().item = qobject_cast<QQuickItem*>(m_base->create(m_rootCtx));
        m_stack.top().item->setParentItem(m_window->contentItem());

        qvariant_cast<QObject*>(m_stack.top().item->property("anchors"))->setProperty(m_currentView->type == E_VIEW_TYPE::SCREEN_TYPE? "fill":"centerIn",
                                                                                      QVariant::fromValue(m_window->contentItem()));

        m_currentView->fnEntry();
        break;
    }
    case QQmlComponent::Loading:
        qInfo() << "This QQmlComponent is loading network data.";
        break;
    case QQmlComponent::Error:
        qInfo() << "An error has occurred. Call errors() to retrieve a list of errors.";
        break;
    default:
        break;
    }
}

void CViewManager::onProgressChanged(qreal progress)
{
    qInfo() << progress;
}

void CViewManager::initConnections()
{
    connect(m_base, &QQmlComponent::statusChanged, this, &CViewManager::onStatusChanged);
}

void CViewManager::initComponent()
{
    m_window = qobject_cast<QQuickWindow*>(m_ngin->rootObjects().at(0));
    if (m_window == nullptr)
      return;

    if(m_depth > 1)
    {
        if(m_stack.top().item != nullptr)
        {
          m_stack.top().item->setProperty("enabled", false);
          m_stack.top().item->setProperty("visible", false);
        }
    }

    m_base->loadUrl(QUrl(m_currentView->path), QQmlComponent::PreferSynchronous);

    ++m_depth;
    emit depthChanged();
}

void CViewManager::destroyComponent()
{
    m_stack.top().info->fnExit();
    m_stack.pop().item->deleteLater();

    m_currentView = m_stack.top().info;
    m_stack.top().item->setProperty("enabled", true);
    m_stack.top().item->setProperty("visible", true);


    --m_depth;
    emit depthChanged();
}
