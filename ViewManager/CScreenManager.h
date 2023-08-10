#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QStack>
#include "AViewManager.h"
#include "CScreen.h"


class CScreenManager : public QObject, public AViewManager
{
    Q_OBJECT
public:
    explicit CScreenManager(QObject *parent = nullptr);

    // IViewManager interface
    CComponent *lastView()
    {
        if(m_views.isEmpty()) return nullptr;
        return m_views.top();
    };
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();



private:
    QStack<CScreen*>                    m_views;

};

#endif // CSCREENMANAGER_H
