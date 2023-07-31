#ifndef CTOASTMANAGER_H
#define CTOASTMANAGER_H

#include "IViewManager.h"
#include "CToast.h"

class CToastManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CToastManager(QObject *parent = nullptr);

    // IViewManager interface
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QHash<uint32_t, CToast*>                  m_views;
};

#endif // CTOASTMANAGER_H
