#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include <QObject>
#include <CViewManager.h>

class CNotifyManager : public CViewManager
{
    Q_OBJECT
public:
    explicit CNotifyManager(QObject *parent = nullptr);

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION*) override;
    virtual void detach(const S_VIEW_INFORMATION*) override;

};

#endif // CNOTIFYMANAGER_H
