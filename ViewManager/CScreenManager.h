#ifndef CSCREENMANAGER_H
#define CSCREENMANAGER_H

#include <QStack>
#include "IViewManager.h"
#include "CScreen.h"

class CScreenManager : public QObject, public IViewManager
{
    Q_OBJECT
public:
    explicit CScreenManager(QObject *parent = nullptr);


    // IViewManager interface
    void pushEnter(const S_VIEW_INFORMATION *nextView);
    void popExit();

private:
    QStack<CScreen*>                    m_views;

};

#endif // CSCREENMANAGER_H
