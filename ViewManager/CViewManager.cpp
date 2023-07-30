#include "CViewManager.h"
#include "Utils.h"
#include "ViewManagerDefines.h"
#include "Logger/LoggerDefines.h"

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

//    removeInValidView();
    initComponent();
}

void CViewManager::popExit()
{
    if(m_current_view == nullptr) return;
//    removeInValidView();
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
        CPP_LOG_INFO("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.");
        break;
    case QQmlComponent::Ready:
    {
        CPP_LOG_INFO("This QQmlComponent is ready and create() may be called.");

        CComponent *comp = new CComponent(m_current_view, nullptr, this);
        QQuickItem *item = qobject_cast<QQuickItem*>(m_base->create());
        QQuickItem *parent = m_window->contentItem();
        item->setParentItem(parent);

        comp->setProperty("anchors", qvariant_cast<QObject*>(item->property("anchors")));

        if(m_current_view->type == E_VIEW_TYPE::SCREEN_TYPE)
        {
            comp->properties().value("anchors")->setProperty("fill", QVariant::fromValue(parent));
        }
        else if(m_current_view->type == E_VIEW_TYPE::POPUP_TYPE)
        {
            comp->properties().value("anchors")->setProperty("centerIn", QVariant::fromValue(parent));
        }
        else if(m_current_view->type == E_VIEW_TYPE::TOAST_TYPE)
        {
            comp->properties().value("anchors")->setProperty("horizontalCenter", QVariant::fromValue(parent->property("horizontalCenter")));
            comp->properties().value("anchors")->setProperty("bottom", QVariant::fromValue(parent->property("bottom")));
            comp->properties().value("anchors")->setProperty("bottomMargin", TOAST_MARGIN_BOTTOM);
        }
        else if(m_current_view->type == E_VIEW_TYPE::NOTIFY_TYPE)
        {
            comp->properties().value("anchors")->setProperty("horizontalCenter", QVariant::fromValue(parent->property("horizontalCenter")));
            comp->properties().value("anchors")->setProperty("top", QVariant::fromValue(parent->property("top")));
            comp->properties().value("anchors")->setProperty("topMargin", NOTIFY_MARGIN_TOP);
        }

        m_stack.push(comp);

        // required
        m_stack.top()->setItem(item);
//        m_stack.top()->setTimeOut();
//        connect(m_stack.top(), &CComponent::visibleTimeout, this, &CViewManager::onVisibleTimeout);
        // end required

        m_current_view->fnEntry();

        // cache view
        m_view_cached[m_current_view->id] = new CComponent(m_current_view, m_stack.top()->item(), this);

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

void CViewManager::onVisibleTimeout()
{
    CComponent *comp = reinterpret_cast<CComponent*>(sender());
    comp->hide();
    m_view_cached[comp->info()->id] = nullptr;
    decreaseImpressions(comp->info());
    decreaseDepth();

    // do it after all
    safeRelease(comp);
}

void CViewManager::initConnections()
{
    connect(m_base, &QQmlComponent::statusChanged, this, &CViewManager::onStatusChanged);
}

void CViewManager::initComponent(const S_VIEW_INFORMATION *view)
{
    if(view != nullptr) m_current_view = view;
    // Check: if stack's depth greater than 1 then hide last item and push new item
    if(m_depth > 1)
    {
        E_VIEW_TYPE lastType = m_stack.top()->info()->type;
        E_VIEW_TYPE nextType = m_current_view->type;
        if((lastType == E_VIEW_TYPE::SCREEN_TYPE && nextType == E_VIEW_TYPE::SCREEN_TYPE)
            || (lastType == E_VIEW_TYPE::POPUP_TYPE && nextType == E_VIEW_TYPE::POPUP_TYPE)
            || ((lastType == E_VIEW_TYPE::TOAST_TYPE || lastType == E_VIEW_TYPE::NOTIFY_TYPE)
                && (nextType == E_VIEW_TYPE::TOAST_TYPE || nextType == E_VIEW_TYPE::NOTIFY_TYPE)))
        {
            m_stack.top()->hide();
        }
    }

    // Check: if view is cacked then push new item to stack and show without call loadUrl() function
    if(m_view_cached.contains(m_current_view->id) && m_view_cached[m_current_view->id] != nullptr)
    {
        CPP_LOG_INFO("Load [%s] from cache memory", m_view_cached[m_current_view->id]->info()->path.toStdString().c_str());
        m_stack.push(m_view_cached[m_current_view->id]);
        m_stack.top()->show();
    }
    else
    {
        m_base->loadUrl(QUrl(m_current_view->path), QQmlComponent::Asynchronous);
    }

    increaseImpressions();
    increaseDepth();
}

void CViewManager::destroyComponent(const S_VIEW_INFORMATION *view)
{
    if(view != nullptr) m_current_view = view;
    // Check: if stack's depth less than 2 view
    if(m_depth == MINIMUM_NUM_OF_VIEWS) return;

    if(m_stack_history[m_current_view->id] < MINIMUM_NUM_OF_VIEWS)
    {
        m_stack.top()->hide();
        safeRelease(m_stack.top());
        m_view_cached[m_current_view->id] = nullptr;
    }
    else
    {
        m_stack.top()->hide();
    }

    m_stack.pop();

    m_current_view = m_stack.top()->info();
    m_stack.top()->show();

    decreaseImpressions();
    decreaseDepth();
}

void CViewManager::increaseImpressions(const S_VIEW_INFORMATION *view)
{
    if(view != nullptr) m_current_view = view;
    ++m_stack_history[m_current_view->id];
}

void CViewManager::decreaseImpressions(const S_VIEW_INFORMATION *view)
{
    if(view != nullptr) m_current_view = view;
    --m_stack_history[m_current_view->id];
    if(m_stack_history[m_current_view->id] < MINIMUM_NUM_OF_VIEWS)
    {
        m_stack_history[m_current_view->id] = 0;
    }
}

void CViewManager::increaseDepth()
{
    ++m_depth;
    emit depthChanged();
}

void CViewManager::decreaseDepth()
{
    --m_depth;
    emit depthChanged();
}

void CViewManager::removeInValidView()
{
    if(m_stack.isEmpty()) return;
    if (!m_stack.isEmpty()) {
        CPP_LOG_INFO("TINNE %p", m_stack.top());
//        decreaseImpressions(m_stack.top()->info());
//        decreaseDepth();
//        safeRelease(m_stack.top());
//        m_stack.pop();
    }
}
