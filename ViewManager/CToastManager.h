#ifndef CTOASTMANAGER_H
#define CTOASTMANAGER_H

#include "AViewManager.h"
#include "CToast.h"

class CToastManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    explicit CToastManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView() {return m_views[m_last_view_id];};
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QHash<uint32_t, CToast*>                  m_views;
};

#endif // CTOASTMANAGER_H
