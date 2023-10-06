#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include <QObject>
#include <AViewManager.h>

BEGIN_NAMESPACE(HmiNgin)
class CNotifyManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    CNotifyManager();

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION *) override;
    virtual void detach(const S_VIEW_INFORMATION *) override;
};
END_NAMESPACE

#endif // CNOTIFYMANAGER_H
