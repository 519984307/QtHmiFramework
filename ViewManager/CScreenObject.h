#ifndef CSCREENOBJECT_H
#define CSCREENOBJECT_H

#include <QObject>
#include <QQmlComponent>
#include "IViewObject.h"

class CScreenObject : public QQmlComponent, public IViewObject
{
    Q_OBJECT
public:
    explicit CScreenObject(const S_VIEW_INFORMATION *view, QQmlApplicationEngine *ngin, QObject *parent = nullptr);
    ~CScreenObject();
};

#endif // CSCREENOBJECT_H
