#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>
#include <QStack>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQmlComponent>
#include "CommonStructs.h"

struct S_COMPONENT
{
    const S_VIEW_INFORMATION    *info;
    QObject                     *item = new QQuickItem;

    inline void destroy()
    {
        hide();
        info->fnExit();
        delete item;
        item = nullptr;
    }

    inline void show(){item->setProperty("visible", true);}
    inline void hide(){item->setProperty("visible", false);}
};

class CViewManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint8_t depth READ depth NOTIFY depthChanged)
public:
    explicit CViewManager(QQmlApplicationEngine *ngin, QObject *parent = nullptr);
    ~CViewManager();
    const S_VIEW_INFORMATION *currentView() const;
    uint8_t depth() const;
    void pushEnter(const S_VIEW_INFORMATION*);
    void popExit();

public slots:
    void onCompleted();
    void onStatusChanged(QQmlComponent::Status);
    void onProgressChanged(qreal);

signals:
    void depthChanged();

private:
    void initConnections();
    void initComponent();
    void destroyComponent();
    void increaseStackHistoryCnt();
    void decreaseStackHistoryCnt();
private:
    QQmlApplicationEngine                              *m_ngin                          = nullptr;
    const S_VIEW_INFORMATION                           *m_current_view                   = nullptr;
    QQuickWindow                                       *m_window                        = nullptr;
    QQmlComponent                                      *m_base                          = nullptr;
    QQmlContext                                        *m_root_ctx                       = nullptr;
    QUrl                                                m_url;
    QStack<S_COMPONENT*>                                m_stack;
    QHash<uint32_t, S_COMPONENT*>                       m_view_cached;
    QHash<uint32_t, int>                                m_stack_history;
    uint8_t                                             m_depth{0};
};

#endif // CVIEWMANAGER_H
