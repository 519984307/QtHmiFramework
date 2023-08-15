#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include "AViewManager.h"

class CPopupManager : public AViewManager
{
public:
    explicit CPopupManager(QObject *parent = nullptr);

    // AViewManager interface
public:
    virtual AView *createView(const S_VIEW_INFORMATION *view) override;
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;
};

#endif // CPOPUPMANAGER_H
