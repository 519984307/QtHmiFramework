#include "CCacheManager.h"

CCacheManager::CCacheManager()
{
}

void CCacheManager::writecache(uint32_t key, CView *view)
{
    m_view_cached[key] = view;
}

E_CACHE_STATUS CCacheManager::cacheStatus(const uint32_t key)
{
    if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
    return (m_view_cached[key] != nullptr)
               ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
}
