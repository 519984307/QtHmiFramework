#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QStack>
#include "IViewManager.h"
#include "CPopup.h"

class CPopupManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CPopupManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView() {return m_views.top();};
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

    inline E_CACHE_STATUS cacheStatus(const uint32_t &key)
    {
        return (E_CACHE_STATUS)(m_view_cached.contains(key) && m_view_cached[key] != nullptr);
    }
private:
    QStack<CPopup*>                           m_views;
    QHash<uint32_t, CPopup*>                  m_view_cached;
};

#endif // CPOPUPMANAGER_H
