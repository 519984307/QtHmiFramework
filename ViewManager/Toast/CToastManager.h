#ifndef CTOASTMANAGER_H
#define CTOASTMANAGER_H

#include "CToast.h"
#include "AViewManager.h"

class CToastManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    explicit CToastManager(QObject *parent = nullptr);
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
    QList<CToast*>                  m_views;
};

#endif // CTOASTMANAGER_H
