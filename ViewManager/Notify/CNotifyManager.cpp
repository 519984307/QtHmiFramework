#include "CNotifyManager.h"

CNotifyManager::CNotifyManager(QObject *parent)
    : CViewManager{parent}
{

}

bool CNotifyManager::isValidDepth()
{
    return true;
}

void CNotifyManager::popExit()
{
    return;
}
