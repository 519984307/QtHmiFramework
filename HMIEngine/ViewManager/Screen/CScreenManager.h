#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QObject>
#include "CViewManager.h"
#include "Screen/CScreen.h"

class CScreenManager: public CViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CScreenManager(QObject *parent = nullptr);
    ~CScreenManager();

    CScreen* readCache(uint32_t key) const;
    void writecache(uint32_t key, CScreen* view);
    E_CACHE_STATUS cacheStatus(const uint32_t key);

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION*) override;
    virtual void detach(const S_VIEW_INFORMATION*) override;

    int depth() const;

signals:
    void depthChanged();

protected:
    virtual void initConnections() override;
    virtual void loadQmlCallBack(CView*) override;

private:
    bool isValidDepth();
    int indexOf(CScreen *view);

private:
    QList<CScreen*>                         m_views;
    QHash<uint32_t, CScreen*>               m_view_cached;
    QHash<uint32_t, int>                    m_view_history;
};

#endif // CSCREENMANAGER_H
