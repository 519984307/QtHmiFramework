#ifndef CCACHEMANAGER_H
#define CCACHEMANAGER_H

#include "CView.h"

class CCacheManager
{
public:
    static CCacheManager *instance();

    template<typename T>
    T* readCache(uint32_t key) const
    {
        return dynamic_cast<T*>(m_view_cached[key]);
    }

    void writecache(uint32_t key, CView* view);
    E_CACHE_STATUS cacheStatus(const uint32_t key);

private:
    CCacheManager();
    static CCacheManager *s_instance;

private:
    QHash<uint32_t, CView*>                 m_view_cached;
};

#endif // CCACHEMANAGER_H
