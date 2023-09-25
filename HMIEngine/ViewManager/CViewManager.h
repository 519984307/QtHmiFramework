#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QObject>
#include <QStack>
#include <functional>
#include "CView.h"

class CViewManager: public QObject
{
    Q_OBJECT
public:
    CViewManager(QObject *parent = nullptr);
    virtual ~CViewManager();

    void show(const S_VIEW_INFORMATION*);
    void hide(const S_VIEW_INFORMATION*);

    virtual void attach(const S_VIEW_INFORMATION*) = 0;
    virtual void detach(const S_VIEW_INFORMATION*) = 0;

protected:
    virtual void initConnections(){};
    virtual void loadQmlCallBack(CView*){};

protected:
    const std::function<void(CView*)>  m_load_qml_cb = std::bind(&CViewManager::loadQmlCallBack, this, std::placeholders::_1);

signals:
    void signalLoadQml(const S_VIEW_INFORMATION*, const std::function<void(CView*)>&);
};


#endif // CVIEWMANAGER_H
