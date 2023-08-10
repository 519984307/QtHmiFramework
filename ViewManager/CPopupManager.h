#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QStack>
#include "AViewManager.h"
#include "CPopup.h"

class CPopupManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    explicit CPopupManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView()
    {
        if(m_views.isEmpty()) return nullptr;
        return m_views.top();
    };
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();


private:
    QStack<CPopup*>                           m_views;
};

#endif // CPOPUPMANAGER_H
