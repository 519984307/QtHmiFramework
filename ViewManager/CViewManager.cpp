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
    // Log item is pushed to history
    increaseStackHistoryCnt(view->id);

    m_currentView = view;

    initComponent();
}

void CViewManager::popExit()
{
    // Check: if stack's depth less than 2 view
    if(m_depth < 2) return;
    // Log item is pop to history
    decreaseStackHistoryCnt(m_currentView->id);;

    // Remove item is cached
    if(m_viewCached[m_currentView->id] != nullptr) m_viewCached.remove(m_currentView->id);

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
        qInfo() << "This QQmlComponent is ready and create() may be called.";
        m_stack.push({currentView(), new QQuickItem});
        qInfo() << m_stack.top().item;
        m_stack.top().item = qobject_cast<QQuickItem*>(m_base->create(m_rootCtx));
        m_stack.top().item->setParentItem(m_window->contentItem());

        qvariant_cast<QObject*>(m_stack.top().item->property("anchors"))->setProperty(m_currentView->type == E_VIEW_TYPE::SCREEN_TYPE? "fill":"centerIn",
                                                                                      QVariant::fromValue(m_window->contentItem()));

        m_currentView->fnEntry();

        m_viewCached[m_currentView->id] = &m_stack.top();
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
    // Check: if stack's depth greater than 1 then hide last item and push new item
    if(m_depth > 1)
    {
        if(m_stack.top().item != nullptr)
        {
          m_stack.top().hide();
        }
    }

    // Check: if view is cacked then push new item to stack and show without call loadUrl() function
    if(m_viewCached[m_currentView->id] != nullptr)
    {
        m_stack.push({m_currentView, m_viewCached[m_currentView->id]->item});
        m_stack.top().show();
    }
    else
    {
        m_window = qobject_cast<QQuickWindow*>(m_ngin->rootObjects().at(0));
        if (m_window == nullptr)
          return;
        m_base->loadUrl(QUrl(m_currentView->path), QQmlComponent::Asynchronous);
    }

    ++m_depth;
    emit depthChanged();
}

void CViewManager::destroyComponent()
{
    if(m_depth > 1)
    {
        qInfo() <<m_currentView->path << m_stackHistory[m_currentView->id];
        if(m_stackHistory[m_currentView->id] == 1)
        {
          m_stack.pop().destroy();
        }
        else if(m_stackHistory[m_currentView->id] > 1)
        {
          m_stack.pop().info->fnExit();
        }

        m_currentView = m_stack.top().info;
        m_stack.top().show();

        --m_depth;
        emit depthChanged();
    }
}

void CViewManager::increaseStackHistoryCnt(const uint32_t &id)
{
    ++m_stackHistory[id];
}

void CViewManager::decreaseStackHistoryCnt(const uint32_t &id)
{
    --m_stackHistory[id];
    if(m_stackHistory[id] < 1)
    {
        m_stackHistory[id] = 1;
    }
}
