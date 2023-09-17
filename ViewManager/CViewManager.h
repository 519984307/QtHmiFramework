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
    inline CView* readCache(uint32_t key) const { return m_view_cached[key]; }
    inline void writecache(uint32_t key, CView* view) { m_view_cached[key] = view; }
    inline E_CACHE_STATUS cacheStatus(const uint32_t key)
    {
        if(m_view_cached.isEmpty()) return E_CACHE_STATUS::MISS;
        return (m_view_cached[key] != nullptr)
                   ? E_CACHE_STATUS::HIT:E_CACHE_STATUS::MISS;
    }

    virtual bool isValidDepth() = 0;
    virtual void pushEnter(const S_VIEW_INFORMATION*);
    virtual void popExit();

    // start encapsulate
    int depth() const;
    CView *lastView() const;
    // end encapsulate

    void pushBack(CView*);
    void popBack();

    CView *findViewObjectByID(const uint32_t &id);

    QList<CView *> views() const;

signals:
    void signalPushBack(const S_VIEW_INFORMATION*, E_CACHE_STATUS);
    void signalPopBack();

    void depthChanged();

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
    QHash<uint32_t, CView*>                 m_view_cached;
    QHash<uint32_t, int>                    m_view_history;

private:
    void initConnections();

};


#endif // CVIEWMANAGER_H
