#include "CNotifyManager.h"

CNotifyManager::CNotifyManager(QObject *parent)
    : QObject{parent}
{

}

void CNotifyManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    Q_UNUSED(nextView)
}

void CNotifyManager::popExit()
{

}
