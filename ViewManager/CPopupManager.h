#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include "IViewManager.h"
#include "CPopup.h"

class CPopupManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CPopupManager(QObject *parent = nullptr);

    // IViewManager interface
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QHash<uint32_t, CPopup*>                  m_view;
};

#endif // CPOPUPMANAGER_H
