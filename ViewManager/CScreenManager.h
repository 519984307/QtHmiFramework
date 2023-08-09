#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QStack>
#include "IViewManager.h"
#include "CScreen.h"


class CScreenManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CScreenManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView() {return m_views.top();};
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

    inline bool isValidDepth() { return depth() > 0; }
    inline bool isValidLastId() { return m_view_cached[m_last_view_id] != nullptr; }
    inline E_CACHE_STATUS cacheStatus(const uint32_t &key)
    {
        if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
        return (m_view_cached[key] != nullptr)
                   ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
    }
private:
    QStack<CScreen*>                    m_views;
    QHash<uint32_t, CScreen*>           m_view_cached;
    QHash<uint32_t, int>                m_view_history;
};

#endif // CSCREENMANAGER_H
