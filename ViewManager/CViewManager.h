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

#include "CScreenManager.h"
#include "CPopupManager.h"
#include "CToastManager.h"
#include "CNotifyManager.h"

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

private:
    void initConnections();

public slots:
    void onCompleted();
    void onStatusChanged(QQmlComponent::Status);
    void onProgressChanged(qreal);

signals:
    void depthChanged();

private:
    QQmlApplicationEngine                              *m_ngin                          = nullptr;
    QQmlComponent                                      *m_base                          = nullptr;
    QQuickWindow                                       *m_window                        = nullptr;
    QQmlContext                                        *m_root_ctx                      = nullptr;
    const S_VIEW_INFORMATION                           *m_current_view                  = nullptr;
    CScreenManager                                      m_screen_manager;
    CPopupManager                                       m_popup_manager;
    CToastManager                                       m_toast_manager;
    CNotifyManager                                      m_notify_manager;
    QHash<uint32_t, int>                                m_stack_history;
    QHash<uint8_t, IViewManager*>                       m_view_managers;
    QHash<uint32_t, CComponent*>                        m_view_cached;
    uint8_t                                             m_last_view_type{E_VIEW_TYPE::NONE_TYPE};
    uint8_t                                             m_depth{0};
};

#endif // CVIEWMANAGER_H
