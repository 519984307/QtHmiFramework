#include "CToastManager.h"

CToastManager::CToastManager(QObject *parent)
    : QObject{parent}
{

}

void CToastManager::pushEnter(const S_VIEW_INFORMATION *nextView)
{
    Q_UNUSED(nextView)
}

void CToastManager::popExit()
{

}
