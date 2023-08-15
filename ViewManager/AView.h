#ifndef AVIEW_H
#define AVIEW_H

#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include <QHash>
#include "CommonStructs.h"
#include "CommonDefine.h"
#include "Logger/LoggerDefines.h"


class AView: public QObject
{
    Q_OBJECT
public:
    explicit AView(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
    ~AView();

    inline void show()
    {
        CPP_LOG_INFO("%s", m_info->path);
        if(m_item == nullptr) return;
        m_item->setProperty("visible", true);
    }
    inline void hide()
    {
        CPP_LOG_INFO("%s", m_info->path);
        if(m_item == nullptr) return;
        m_item->setProperty("visible", false);
    }

    const S_VIEW_INFORMATION *info() const
    {
        return m_info;
    }

    QQuickItem *parentItem() const;

    AView *initialize(QQuickItem*);


    virtual void customizeProperties() {};

private:
    void initConnections();
    void readProperties();

protected:
    const S_VIEW_INFORMATION    *m_info         = nullptr;
    QQuickItem                  *m_item         = nullptr;
    QHash<QString, QVariant>     m_properties;
};


#endif // AVIEW_H
