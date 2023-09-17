#include "CPopupManager.h"

CPopupManager::CPopupManager(QObject *parent) : CViewManager(parent)
{}

CPopupManager::~CPopupManager()
{

}

bool CPopupManager::isValidDepth()
{
    return depth() > 0;
}
