#include "CLRUCache.h"

template<class T>
CLRUCache<T>::CLRUCache()
{

}

template<class T>
CLRUCache<T>::~CLRUCache()
{

}

template<class T>
E_CACHE_STATUS CLRUCache<T>::status() const
{
    return E_CACHE_STATUS::MISS;
}

template<class T>
T* CLRUCache<T>::get(uint32_t key)
{
    return nullptr;
}

template<class T>
void CLRUCache<T>::put(uint32_t key, T* value)
{
    if(m_cache.size() == m_maxSize)
    {
    }
}
