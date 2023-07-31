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
    explicit CComponent(QObject *parent = nullptr);
    ~CComponent();

    inline void show()
    {
        if(m_item == nullptr) return;
        m_item->setProperty("visible", true);
    }
    inline void hide()
    {
        if(m_item == nullptr) return;
        m_item->setProperty("visible", false);
    }

    const S_VIEW_INFORMATION *info() const;

    void setInfo(const S_VIEW_INFORMATION*);

    QQuickItem *item() const;

    void setItem(QQuickItem*);

    QHash<QString, QObject *> properties() const;

    void setProperty(QString, QObject*);

private:
    const S_VIEW_INFORMATION    *m_info;
    QQuickItem                  *m_item         = nullptr;
    QHash<QString, QObject*>     m_properties   = {{"anchors", nullptr}};
};


#endif // CCOMPONENT_H
