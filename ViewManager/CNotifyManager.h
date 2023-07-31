#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include "IViewManager.h"
#include "CNotify.h"


class CNotifyManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CNotifyManager(QObject *parent = nullptr);

    // IViewManager interface
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QHash<uint32_t, CNotify*>                 m_views;

};

#endif // CNOTIFYMANAGER_H
