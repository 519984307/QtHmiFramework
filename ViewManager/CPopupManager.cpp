#include "CPopupManager.h"
#include "CPopup.h"

CPopupManager::CPopupManager(QObject *parent)
    : AViewManager{parent}
{

}

AView *CPopupManager::createView(const S_VIEW_INFORMATION *view)
{
    return new CPopup(view);
}

void CPopupManager::pushEnter(const S_VIEW_INFORMATION *view)
{
    Q_UNUSED(view)
}

void CPopupManager::popExit()
{

}
