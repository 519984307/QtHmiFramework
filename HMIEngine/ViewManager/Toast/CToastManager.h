#ifndef CTOASTMANAGER_H
#define CTOASTMANAGER_H

#include <CViewManager.h>
#include <QObject>

class CToastManager : public CViewManager
{
    Q_OBJECT
public:
    explicit CToastManager(QObject *parent = nullptr);

    // CViewManager interface
public:
    virtual void attach(const S_VIEW_INFORMATION*) override;
    virtual void detach(const S_VIEW_INFORMATION*) override;

};

#endif // CTOASTMANAGER_H
