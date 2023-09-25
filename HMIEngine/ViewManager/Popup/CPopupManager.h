#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QObject>
#include "CViewManager.h"
#include "Popup/CPopup.h"
class CPopupManager : public CViewManager
{
    Q_OBJECT
public:
    CPopupManager(QObject *parent = nullptr);
    ~CPopupManager();

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION*) override;
    virtual void detach(const S_VIEW_INFORMATION*) override;

private:
    CPopup                  *m_view;

};

#endif // CPOPUPMANAGER_H
