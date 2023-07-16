#ifndef IVIEWOBJECT_H
#define IVIEWOBJECT_H

#include <QQmlApplicationEngine>
#include "CommonStructs.h"

class IViewObject
{
public:
    const S_VIEW_INFORMATION* info()
    {
        return m_info;
    }

    QQmlApplicationEngine* engine()
    {
        return m_ngin;
    }
protected:
    const S_VIEW_INFORMATION                    *m_info;
    QQmlApplicationEngine                       *m_ngin;
};

#endif // IVIEWOBJECT_H
