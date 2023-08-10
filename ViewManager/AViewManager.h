#ifndef AVIEWMANAGER_H
#define AVIEWMANAGER_H

#include <QObject>
#include <QQmlComponent>
#include <QQuickItem>
#include <QHash>
#include <functional>
#include "CComponent.h"
#include "Common.h"
#include "Logger/LoggerDefines.h"

class AViewManager
{
public:
    virtual ~AViewManager(){}
    virtual CComponent *lastView()                             = 0;
    virtual void pushEnter(const S_VIEW_INFORMATION* nextView) = 0;
    virtual void popExit()                                     = 0;

    typedef std::function<void()> ViewChangeEventCallBack;

    void registerViewChangeEventCallBack(ViewChangeEventCallBack cb)
    {
        m_event_view_change_cb = cb;
    }

    inline int history(uint32_t key) { return m_view_history[key]; }

    inline int increaseHistory(uint32_t key) { return ++m_view_history[key]; }

    inline int decreaseHistory(uint32_t key)
    {
        --m_view_history[key];
        if(m_view_history[m_last_view_id] < 1)
        {
            m_view_history[m_last_view_id] = 0;
        }
        return m_view_history[key];
    }

    template<class T>
    inline T *readCache(uint32_t key) { return (T*)m_view_cached[key];}

    template<class T>
    inline void writeCache(uint32_t key, CComponent *comp) { m_view_cached[key] = (T*)comp; }

    inline int depth() const { return m_depth; }

    inline int increaseDepth(uint8_t step = 1)
    {
        m_depth += step;
        return m_depth;
    }

    inline int decreaseDepth(uint8_t step = 1)
    {
        m_depth -= step;
        if(m_depth < 1) m_depth = 0;
        return m_depth;
    }

    inline E_CACHE_STATUS cacheStatus(const uint32_t key)
    {
        if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
        return (m_view_cached[key] != nullptr)
                   ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
    }

    inline bool isValidDepth() { return depth() > 0; }

    inline bool isValidLastId() { return m_view_cached[m_last_view_id] != nullptr; }

protected:
    uint32_t                               m_last_view_id;
    ViewChangeEventCallBack                m_event_view_change_cb;

private:
    int                          m_depth{0};
    QHash<uint32_t, CComponent*> m_view_cached;
    QHash<uint32_t, int>         m_view_history;

};


#endif // AVIEWMANAGER_H
