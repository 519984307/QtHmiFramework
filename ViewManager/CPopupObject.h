#ifndef CPOPUPOBJECT_H
#define CPOPUPOBJECT_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QTimer>
#include "CommonStructs.h"

class CPopupObject : public QObject
{
    Q_OBJECT
public:
    explicit CPopupObject(QObject *parent = nullptr);
    ~CPopupObject();

    void setData(const S_VIEW_INFORMATION*);
    void setDuration(uint32_t);
    void show();
    void close();

public slots:
    void onPopupTimeout();

signals:

private:
    QTimer                      *m_timer;
    const S_VIEW_INFORMATION    *m_info;

};

#endif // CPOPUPOBJECT_H
