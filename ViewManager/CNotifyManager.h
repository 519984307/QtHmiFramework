#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include "AViewManager.h"
#include "CNotify.h"


class CNotifyManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    explicit CNotifyManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView() {return m_views[m_last_view_id];};
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QHash<uint32_t, CNotify*>                 m_views;
};

#endif // CNOTIFYMANAGER_H
