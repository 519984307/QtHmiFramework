#ifndef CPOPUPMANAGER_H
#define CPOPUPMANAGER_H

#include "CPopup.h"
#include "AViewManager.h"

class CPopupManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    explicit CPopupManager(QObject *parent = nullptr);

    inline int depth() const {return m_views.size(); }
    inline void updateDepth() { emit depthChanged(); }
    inline bool isValidDepth() { return depth() > 0; }

signals:
    void depthChanged();

public slots:
    void signalInvisible();

    // AViewManager interface
public:
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;
    virtual int  indexOfView(const uint32_t &) override;

private:
    QList<CPopup*>                  m_views;

};

#endif // CPOPUPMANAGER_H
