#include "CToastManager.h"

CToastManager::CToastManager(QObject *parent)
    : CViewManager{parent}
{

}

bool CToastManager::isValidDepth()
{
    return true;
}
