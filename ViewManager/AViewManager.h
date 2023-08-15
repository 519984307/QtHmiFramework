#ifndef AVIEWMANAGER_H
#define AVIEWMANAGER_H

#include <QObject>
#include <QStack>
#include "AView.h"
class AViewManager: public QObject
{
    Q_OBJECT
public:
    explicit AViewManager(QObject *parent = nullptr);
    virtual ~AViewManager(){};

    virtual AView* createView(const S_VIEW_INFORMATION *view) = 0;
    virtual void pushEnter(const S_VIEW_INFORMATION* view) = 0;
    virtual void popExit() = 0;

    inline int history(uint32_t key) { return m_view_history[key]; }

    inline int increaseHistory(uint32_t key) { return ++m_view_history[key]; }

    inline int decreaseHistory(uint32_t key)
    {
        --m_view_history[key];
        if(m_view_history[m_last_view->info()->id] < 1)
        {
            m_view_history[m_last_view->info()->id] = 0;
        }
        return m_view_history[key];
    }
    inline AView* readCache(uint32_t key) const { return m_view_cached[key]; }
    inline void writecache(uint32_t key, AView* val) { m_view_cached[key] = val; }
    inline E_CACHE_STATUS cacheStatus(const uint32_t key)
    {
        if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
        return (m_view_cached[key] != nullptr)
                   ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
    }

    inline bool isValidLastId() { return m_view_cached[m_last_view->info()->id] != nullptr; }


    AView *last_view() const;

signals:
    void signalPushEnter(AView*);

protected:
    QHash<uint32_t, AView*>         m_view_cached;
    QHash<uint32_t, int>            m_view_history;
    AView                          *m_last_view                     = nullptr;
};

#endif // AVIEWMANAGER_H
