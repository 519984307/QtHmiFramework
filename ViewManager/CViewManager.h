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
    QQuickItem                  *item;
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
    void popExit(const S_VIEW_INFORMATION *view = nullptr);

public slots:
    void onStatusChanged(QQmlComponent::Status);
    void onProgressChanged(qreal);

signals:
    void depthChanged();

private:
    void initConnections();
    void initView(const S_VIEW_INFORMATION*);
    void destroyView(const S_VIEW_INFORMATION*);
private:
    QQmlApplicationEngine                              *m_ngin                          = nullptr;
    const S_VIEW_INFORMATION                           *m_currentView                   = nullptr;
    QQuickWindow                                       *m_window                        = nullptr;
    QQmlComponent                                      *m_base                          = nullptr;
    QQmlContext                                        *m_rootCtx                       = nullptr;
    QUrl                                                m_url;
    QStack<S_COMPONENT>                                 m_stack;
    QHash<uint32_t, bool>                               m_stack_history;
    uint8_t                                             m_depth{0};
};

#endif // CVIEWMANAGER_H
