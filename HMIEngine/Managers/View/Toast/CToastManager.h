#ifndef CTOASTMANAGER_H
#define CTOASTMANAGER_H

#include <AViewManager.h>
#include <QObject>

BEGIN_NAMESPACE(HmiNgin)
    class CToastManager : public QObject, public AViewManager
    {
        Q_OBJECT
    public:
        CToastManager();

        // CViewManager interface
    public:
        virtual void attach(const S_VIEW_INFORMATION *) override;
        virtual void detach(const S_VIEW_INFORMATION *) override;
    };
END_NAMESPACE

#endif // CTOASTMANAGER_H
