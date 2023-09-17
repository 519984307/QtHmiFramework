#include "CScreenManager.h"


CScreenManager::CScreenManager(QObject *parent) : CViewManager(parent)
{}

CScreenManager::~CScreenManager()
{

}

bool CScreenManager::isValidDepth()
{
    return depth() > 1;
}
