#include "CViewManager.h"
#include "Utils.h"

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
    return m_current_view;
}

uint8_t CViewManager::depth() const
{
    return m_depth;
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{
    if(view == nullptr) return;
    m_current_view = view;
    initComponent();
}

void CViewManager::popExit()
{
    if(m_current_view == nullptr) return;
    destroyComponent();
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
        qInfo() << "This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.";
        break;
    case QQmlComponent::Ready:
    {
        qInfo() << "This QQmlComponent is ready and create() may be called.";

        S_COMPONENT *comp = new S_COMPONENT{m_current_view};
        QQuickItem *item = qobject_cast<QQuickItem*>(m_base->create());
        QQuickItem *parent = m_window->contentItem();
        item->setParentItem(parent);

        comp->properties.insert("anchors", qvariant_cast<QObject*>(item->property("anchors")));
        comp->properties.value("anchors")->setProperty("fill", QVariant::fromValue(parent));

        m_stack.push(comp);
        m_stack.top()->item = item;

        m_current_view->fnEntry();
        m_view_cached[m_current_view->id] = new S_COMPONENT{m_current_view, m_stack.top()->item};

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
        if(m_current_view->type == E_VIEW_TYPE::SCREEN_TYPE)
        {
            m_stack.top()->hide();
        }
    }

    // Check: if view is cacked then push new item to stack and show without call loadUrl() function
    if(m_view_cached.contains(m_current_view->id) && m_view_cached[m_current_view->id] != nullptr)
    {
        qInfo() << QString("Load [%1] from cache memory").arg(m_view_cached[m_current_view->id]->info->path);
        m_stack.push(m_view_cached[m_current_view->id]);
        m_stack.top()->show();
        qInfo() << QString("View [%1] has visible [%2]").arg(m_stack.top()->info->path).arg(m_stack.top()->item->property("visible").toBool());
    }
    else
    {
        m_base->loadUrl(QUrl(m_current_view->path), QQmlComponent::Asynchronous);
    }

    increaseImpressions();

    ++m_depth;
    emit depthChanged();
}

void CViewManager::destroyComponent()
{
    // Check: if stack's depth less than 2 view
    if(m_depth < 2) return;
    if(m_stack_history[m_current_view->id] == 1)
    {
        m_stack.top()->destroy();
    }
    else
    {
        m_stack.top()->hide();
    }

    m_stack.pop();

    decreaseImpressions();

    m_current_view = m_stack.top()->info;
    m_stack.top()->show();

    --m_depth;
    emit depthChanged();
}

void CViewManager::increaseImpressions()
{
    ++m_stack_history[m_current_view->id];
}

void CViewManager::decreaseImpressions()
{
    --m_stack_history[m_current_view->id];
    if(m_stack_history[m_current_view->id] < 1)
    {
        m_stack_history[m_current_view->id] = 1;
    }
}
