#include "CScreenManager.h"


CScreenManager::CScreenManager(QObject *parent) : CViewManager(parent)
{
    m_is_valid_depth = depth() > 1;
}

CScreenManager::~CScreenManager()
{

}
