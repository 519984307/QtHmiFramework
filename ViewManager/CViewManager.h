#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QObject>
#include <QStack>
#include <functional>
#include "CView.h"

class CViewManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CViewManager(QObject *parent = nullptr);
    virtual ~CViewManager();


    virtual E_CACHE_STATUS hasCached(const uint32_t&) { return E_CACHE_STATUS::MISS; }

    int depth() const;
    inline bool isValidDepth() { return m_is_valid_depth; }
    inline CView* readCache(uint32_t key) const { return m_view_cached[key]; }
    inline void writecache(uint32_t key, CView* view) { m_view_cached[key] = view; }
    inline E_CACHE_STATUS cacheStatus(const uint32_t key)
    {
        if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
        return (m_view_cached[key] != nullptr)
                   ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
    }

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

    void pushBack(QQmlComponent *, QQuickItem *, const S_VIEW_INFORMATION*);
    void popBack();

signals:
    void signalPushBack();
    void signalPopBack();
    void depthChanged();

public slots:
    void onStatusChanged(QQmlComponent::Status);
    void onProgressChanged(qreal);

protected:
    template<class AT>
    int indexOfViewByID(QList<AT*> &views, const uint32_t &id)
    {
        int index = -1;
        for(AT *e: views)
        {
            index++;
            if(e->info()->id == id)
            {
                break;
            }
        }
        return index;
    }


    QList<CView*>                           m_views;
    bool                                    m_is_valid_depth{false};

private:
    void initConnections();

private:
    QHash<uint32_t, CView*>                 m_view_cached;
    QHash<uint32_t, int>                    m_view_history;
    QQmlComponent                          *m_qml_base          = nullptr;
    QQuickItem                             *m_qml_parent        = nullptr;
    CView                                  *m_last_view         = nullptr;
    const S_VIEW_INFORMATION               *m_next_view_info    = nullptr;

};


#endif // CVIEWMANAGER_H
