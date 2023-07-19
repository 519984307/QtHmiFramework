#include "CViewManager.h"
#include "Utils.h"
#include <QGuiApplication>

CViewManager::CViewManager(QQmlApplicationEngine *ngin, QObject *parent)
    : QObject{parent}
{
    m_ngin = ngin;
}

CViewManager::~CViewManager()
{
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

    initView(view);
}

void CViewManager::popExit(const S_VIEW_INFORMATION* view)
{
    // Check: if stack's depth less than 2 view
    if(m_depth < 2) return;
    // Remove item pushed
    if(m_stack_history.key(view->id)) m_stack_history.remove(view->id);

    destroyView(view);
}

void CViewManager::initView(const S_VIEW_INFORMATION *view)
{
    m_rootObj = m_ngin->rootObjects().at(0);
    if (m_rootObj == nullptr)
      return;
    m_currentView = view;

    if(m_depth > 1)
    {
        if(m_stack.top() != nullptr) m_stack.top()->setProperty("visible", false);
    }

    m_rootCtx = m_ngin->rootContext();
    QQuickItem *container = m_rootObj->findChild<QQuickItem*>("qml_root_rect");
    QQmlComponent *comp = new QQmlComponent(m_ngin, QUrl(view->path), this);
    QObject *obj = comp->create(m_rootCtx);
    obj->setParent(container);
    obj->setProperty("anchors.centerIn", QVariant::fromValue(obj->parent()));

    m_stack.push(obj);
    view->fnEntry();

    ++m_depth;
    emit depthChanged();
}

void CViewManager::destroyView(const S_VIEW_INFORMATION *view)
{
    m_stack.top()->setProperty("visible", false);
    if(view == nullptr)
    {
        view = currentView();
    }

    safeRelease(m_stack.pop());
    view->fnExit();

    m_currentView = nullptr;

    --m_depth;
    emit depthChanged();
}
