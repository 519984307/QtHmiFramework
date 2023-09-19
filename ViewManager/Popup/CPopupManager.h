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
};

#endif // CPOPUPMANAGER_H
