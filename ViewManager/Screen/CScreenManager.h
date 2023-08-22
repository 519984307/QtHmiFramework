#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include "AViewManager.h"
#include "CScreenTransitions.h"

class CScreenManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CScreenManager(QObject *parent = nullptr);

    inline int depth() const {return m_views.size(); }
    inline void updateDepth() { emit depthChanged(); }
    inline bool isValidDepth() { return depth() > 1; }

    inline int history(uint32_t key) { return m_view_history[key]; }
    inline int increaseHistory(uint32_t key) { return ++m_view_history[key]; }
    inline int decreaseHistory(uint32_t key)
    {
        --m_view_history[key];
        if(m_view_history[key] < 1)
        {
            m_view_history[key] = 0;
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

signals:
    void depthChanged();



    // AViewManager interface
public:
    virtual AView *createView(const S_VIEW_INFORMATION *view) override;
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;


private:
    QStack<AView*>                  m_views;
    QHash<uint32_t, AView*>         m_view_cached;
    QHash<uint32_t, int>            m_view_history;
    CScreenTransitions              m_transitions;

};

#endif // CSCREENMANAGER_H
