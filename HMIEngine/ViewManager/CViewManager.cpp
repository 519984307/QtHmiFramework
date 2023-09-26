#include "CViewManager.h"

CViewManager::CViewManager(QObject *parent) : QObject(parent)
{
    m_cacheManager      = CCacheManager::instance();
    m_freqTable    = CFreqTable::instance();
}

CViewManager::~CViewManager()
{}
