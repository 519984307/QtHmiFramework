#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QObject>
#include "AViewManager.h"
#include "Popup/CPopup.h"

BEGIN_NAMESPACE(HmiNgin)
class CPopupManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    CPopupManager();
    ~CPopupManager();

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION *) override;
    virtual void detach(const S_VIEW_INFORMATION *) override;

    // CViewManager interface
protected:
    virtual void loadNewQmFromCallback(CView *) override;

private:
    CPopup *m_view;
};

END_NAMESPACE

#endif // CPOPUPMANAGER_H
