#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include <QObject>
#include <AViewManager.h>

namespace HmiNgin
{
    class CNotifyManager : public QObject, public AViewManager
    {
        Q_OBJECT
    public:
        CNotifyManager();

        // CViewManager interface
    public:
        virtual void attach(const S_VIEW_INFORMATION *) override;
        virtual void detach(const S_VIEW_INFORMATION *) override;
    };
} // namespace HmiNgin

#endif // CNOTIFYMANAGER_H
