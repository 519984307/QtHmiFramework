#include "CScreenManager.h"

CScreenManager::CScreenManager(QObject *parent)
    : QObject{parent}
{

}

void CScreenManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    if(nextView == nullptr) return;
    setLastView(nextView);
}

void CScreenManager::popExit()
{
    if(!isValidDepth()) return;
    m_views.pop();
}
