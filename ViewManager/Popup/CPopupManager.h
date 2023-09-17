#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include <QObject>
#include <CViewManager.h>

class CPopupManager : public CViewManager
{
    Q_OBJECT
public:
    CPopupManager(QObject *parent = nullptr);
    ~CPopupManager();

    // CViewManager interface
public:
    virtual bool isValidDepth() override;
//    virtual void pushEnter(const S_VIEW_INFORMATION *) override;
//    virtual void popExit() override;
};

#endif // CPOPUPMANAGER_H
