#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include "AViewManager.h"
#include "CScreenTransitions.h"

class CScreenManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CScreenManager(QObject *parent = nullptr);

    inline int depth() const {return m_views.size(); }
    inline void updateDepth() { emit depthChanged(); }
    inline bool isValidDepth() { return depth() > 1; }

signals:
    void depthChanged();



    // AViewManager interface
public:
    virtual AView *createView(const S_VIEW_INFORMATION *view) override;
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;


private:
    QStack<AView*>                  m_views;
    CScreenTransitions              m_transitions;

};

#endif // CSCREENMANAGER_H
