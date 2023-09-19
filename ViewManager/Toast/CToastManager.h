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
    virtual bool isValidDepth() override;

};

#endif // CTOASTMANAGER_H
