#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QHash>
#include <QTimer>
#include <QStack>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQmlComponent>
#include "CComponent.h"
#include "CommonStructs.h"

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
    void onVisibleTimeout();

signals:
    void depthChanged();

private:
    void initConnections();
    void initComponent(const S_VIEW_INFORMATION *view = nullptr);
    void destroyComponent(const S_VIEW_INFORMATION *view = nullptr);
    void increaseImpressions(const S_VIEW_INFORMATION *view = nullptr);
    void decreaseImpressions(const S_VIEW_INFORMATION *view = nullptr);
    void increaseDepth();
    void decreaseDepth();
    void removeInValidView();

private:
    QQmlApplicationEngine                              *m_ngin                          = nullptr;
    const S_VIEW_INFORMATION                           *m_current_view                  = nullptr;
    QQuickWindow                                       *m_window                        = nullptr;
    QQmlComponent                                      *m_base                          = nullptr;
    QQmlContext                                        *m_root_ctx                      = nullptr;
    QUrl                                                m_url;
    QStack<CComponent*>                                 m_stack;
    QHash<uint32_t, CComponent*>                        m_view_cached;
    QHash<uint32_t, int>                                m_stack_history;
    uint8_t                                             m_depth{0};
};

#endif // CVIEWMANAGER_H
