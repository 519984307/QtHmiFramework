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
    virtual bool isValidDepth() override;
    virtual void popExit() override;
};

#endif // CNOTIFYMANAGER_H
