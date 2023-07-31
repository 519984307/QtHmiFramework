#ifndef IVIEWMANAGER_H
#define IVIEWMANAGER_H

#include <QObject>
#include <QHash>
#include "Common.h"

class IViewManager
{
public:
    virtual void pushEnter(const S_VIEW_INFORMATION* nextView) = 0;
    virtual void popExit()                                     = 0;

    inline const S_VIEW_INFORMATION *lastView() const
    {
        return m_lastView;
    }

    inline void setLastView(const S_VIEW_INFORMATION *newLastView)
    {
        m_lastView = newLastView;
    }

    inline bool isValidDepth()
    {
        return m_depth > 1;
    }

    inline int depth() const
    {
        return m_depth;
    }

    inline int increaseDepth(uint8_t step = 1)
    {
        m_depth += step;
        return m_depth;
    }

    inline int decreaseDepth(uint8_t step = 1)
    {
        m_depth -= step;
        if(m_depth < 0) m_depth = 0;
        return m_depth;
    }


private:
    const S_VIEW_INFORMATION    *m_lastView;
    int                          m_depth{0};
};


#endif // IVIEWMANAGER_H
