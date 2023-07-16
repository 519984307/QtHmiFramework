#ifndef CPOPUPOBJECT_H
#define CPOPUPOBJECT_H

#include <QQmlComponent>
#include <QTimer>
#include "IViewObject.h"
#include "CommonStructs.h"

class CPopupObject : public QQmlComponent, public IViewObject
{
    Q_OBJECT
public:
    explicit CPopupObject(const S_VIEW_INFORMATION *view, QQmlApplicationEngine *ngin, QObject *parent = nullptr);
    ~CPopupObject();

private:
    QTimer                      *m_timer;
    const S_VIEW_INFORMATION    *m_info;


};

#endif // CPOPUPOBJECT_H
