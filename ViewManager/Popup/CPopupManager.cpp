#include "CPopupManager.h"

CPopupManager::CPopupManager(QObject *parent) : CViewManager(parent)
{
    m_is_valid_depth = depth() > 0;
}

CPopupManager::~CPopupManager()
{

}
