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

    inline E_CACHE_STATUS cacheStatus(const uint32_t &key)
    {
        return (E_CACHE_STATUS)(m_view_cached.contains(key) && m_view_cached[key] != nullptr);
    }
private:
    QStack<CScreen*>                    m_views;
    QHash<uint32_t, CScreen*>           m_view_cached;



};

#endif // CSCREENMANAGER_H
