#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include "AViewManager.h"

class CScreenManager : public AViewManager
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    CScreenManager(QObject *parent = nullptr);
    inline int increaseDepth(uint8_t step = 1)
    {
        m_depth += step;
        emit depthChanged();
        return m_depth;
    }

    inline int decreaseDepth(uint8_t step = 1)
    {
        m_depth -= step;
        if(m_depth < 1) m_depth = 0;
        emit depthChanged();
        return m_depth;
    }

    inline bool isValidDepth() { return m_depth > 1; }

signals:
    void depthChanged();



    // AViewManager interface
public:
    virtual AView *createView(const S_VIEW_INFORMATION *view) override;
    virtual void pushEnter(const S_VIEW_INFORMATION *view) override;
    virtual void popExit() override;


    int depth() const;

private:
    QStack<AView*>                  m_view;
    int                             m_depth{0};
};

#endif // CSCREENMANAGER_H
