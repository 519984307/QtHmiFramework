#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QObject>
#include "AViewManager.h"
#include "Screen/CScreen.h"

BEGIN_NAMESPACE(HmiNgin)
class CScreenManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    CScreenManager();
    ~CScreenManager();

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION *) override;
    virtual void detach(const S_VIEW_INFORMATION *) override;

protected:
    virtual void initConnections() override;
    virtual void loadNewQmFromCallback(CView *) override;

private:
    bool isValidDepth();
    int indexOf(CScreen *view);

private:
    QList<CScreen *> m_views;
};

END_NAMESPACE

#endif // CSCREENMANAGER_H
