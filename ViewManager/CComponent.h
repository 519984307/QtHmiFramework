#ifndef CCOMPONENT_H
#define CCOMPONENT_H

#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include <QHash>
#include "CommonStructs.h"
#include "CommonDefine.h"

class CComponent: public QObject
{
    Q_OBJECT
public:
    explicit CComponent(const S_VIEW_INFORMATION *info, QQuickItem *item, QObject *parent = nullptr);
    ~CComponent();

    inline bool hasTimeOut() {return m_info->duration > 0; }

    inline void setTimeOut()
    {
        if(hasTimeOut() && !m_timer->isActive())
        {
            m_timer->setSingleShot(true);
            m_timer->start(m_info->duration * ONE_SEC);
            return;
        }
        m_timer->stop();
    }

    inline void unsetTimeOut()
    {
        if(hasTimeOut() && m_timer->isActive())
        {
            m_timer->stop();
        }
    }

    inline void show()
    {
        if(m_item == nullptr) return;
        m_item->setProperty("visible", true);
        setTimeOut();
    }
    inline void hide()
    {
        if(m_item == nullptr) return;
        m_item->setProperty("visible", false);
        unsetTimeOut();
    }

    const S_VIEW_INFORMATION *info() const;

    QQuickItem *item() const;

    void setItem(QQuickItem*);

    QHash<QString, QObject *> properties() const;

    void setProperty(QString, QObject*);

public slots:
    void onVisibleTimeout();

signals:
    void visibleTimeout();

private:
    const S_VIEW_INFORMATION    *m_info;
    QQuickItem                  *m_item         = nullptr;
    QTimer                      *m_timer        = nullptr;
    QHash<QString, QObject*>     m_properties   = {{"anchors", nullptr}};
};


#endif // CCOMPONENT_H
