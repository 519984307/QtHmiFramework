#include "CViewManager.h"
#include "Utils.h"

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
    return m_stack.top();
}

uint8_t CViewManager::depth() const
{
    return m_depth;
}

void CViewManager::pushEnter(const S_VIEW_INFORMATION* view)
{
    // Log item to history
    if(!m_stack_history.key(view->id)) m_stack_history.insert(view->id, true);

    m_stack.push(view);
    m_stack.top()->fnEntry();

    ++m_depth;
    emit depthChanged();
}

void CViewManager::popExit()
{
    // Check: if stack's depth less than 2 view
    if(m_depth < 2) return;
    // Remove item pushed
    if(m_stack_history.key(m_stack.top()->id)) m_stack_history.remove(m_stack.top()->id);

    m_stack.pop()->fnExit();

    --m_depth;
    emit depthChanged();
}

void CViewManager::setRootObject(const QObject *root)
{
    m_root = root;
}
