#ifndef IVIEWMANAGER_H
#define IVIEWMANAGER_H

#include <QObject>
#include <QQmlComponent>
#include <QHash>
#include <functional>
#include "Logger/LoggerDefines.h"
#include "CComponent.h"
#include "Common.h"

class IViewManager
{
public:
    virtual ~IViewManager(){}
    virtual inline E_CACHE_STATUS cacheStatus(const uint32_t &key)
    {
        Q_UNUSED(key)
        return E_CACHE_STATUS::MISS;
    }
    virtual CComponent *lastView()                             = 0;
    virtual void pushEnter(const S_VIEW_INFORMATION* nextView) = 0;
    virtual void popExit()                                     = 0;

    typedef std::function<void(CComponent*)> ViewChangeEventCallBack;

    void registerViewChangeEventCallBack(ViewChangeEventCallBack cb)
    {
        m_event_view_change_cb = cb;
    }

    inline bool isValidDepth() { return depth() > 0; }
    inline int history(uint32_t &key) { return m_history[key]; }

    inline void setHistory(uint32_t &key, int value) { m_history[key] = value; }

    inline int depth() const { return m_depth; }

    inline int increaseDepth(uint8_t step = 1)
    {
        m_depth += step;
        return m_depth;
    }

    inline int decreaseDepth(uint8_t step = 1)
    {
        if(m_depth < 0) m_depth = 0;
        else m_depth -= step;
        return m_depth;
    }

protected:
    uint32_t                               m_last_view_id;
    ViewChangeEventCallBack                m_event_view_change_cb;

private:
    QHash<uint32_t, int>         m_history;
    int                          m_depth{0};
};


#endif // IVIEWMANAGER_H
