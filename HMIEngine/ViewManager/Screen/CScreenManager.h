#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QObject>
#include "CViewManager.h"
#include "Screen/CScreen.h"

class CScreenManager: public CViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CScreenManager(QObject *parent = nullptr);
    ~CScreenManager();

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION*) override;
    virtual void detach(const S_VIEW_INFORMATION*) override;

    int depth() const;

signals:
    void depthChanged();

protected:
    virtual void initConnections() override;
    virtual void loadQmlCallBack(CView*) override;

private:
    bool isValidDepth();
    int indexOf(CScreen *view);

private:
    QList<CScreen*>                         m_views;
};

#endif // CSCREENMANAGER_H
