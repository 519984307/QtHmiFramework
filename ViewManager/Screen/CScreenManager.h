#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QObject>
#include <CViewManager.h>

class CScreenManager: public CViewManager
{
    Q_OBJECT
public:
    CScreenManager(QObject *parent = nullptr);
    ~CScreenManager();
    // CViewManager interface
public:
    virtual bool isValidDepth() override;
    //    virtual void pushEnter(const S_VIEW_INFORMATION *) override;
    //    virtual void popExit() override;
};

#endif // CSCREENMANAGER_H
