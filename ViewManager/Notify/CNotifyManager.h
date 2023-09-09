#ifndef CNOTIFYMANAGER_H
#define CNOTIFYMANAGER_H

#include "CNotify.h"
#include <AViewManager.h>
class CNotifyManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    explicit CNotifyManager(QObject *parent = nullptr);

    inline int depth() const {return m_views.size(); }
    inline void updateDepth() { emit depthChanged(); }

    void removeById(const uint32_t&);

    // AViewManager interface
public:
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;

public slots:
    void onSignalInvisible();

signals:
    void depthChanged();

private:
    QList<CNotify*>                  m_views;

};

#endif // CNOTIFYMANAGER_H
