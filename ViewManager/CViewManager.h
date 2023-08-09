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
#include "IViewManager.h"
#include "CComponent.h"
#include "CScreenManager.h"
#include "CPopupManager.h"
#include "CToastManager.h"
#include "CNotifyManager.h"

class CViewManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    explicit CViewManager(QQmlApplicationEngine *ngin, QObject *parent = nullptr);
    ~CViewManager();
    CComponent *currentView();
    int depth() const;
    void updateDepth();
    void resetDepth();
    void pushEnter(const S_VIEW_INFORMATION*);
    void popExit();

    void listenViewChangeEventCallBack(CComponent*);
private:
    void initConnections();

public slots:
    void onCompleted();
    void onProgressChanged(qreal);
    void onStatusChanged(QQmlComponent::Status);

signals:
    void depthChanged();

private:
    QQmlApplicationEngine                              *m_ngin                          = nullptr;
    QQmlComponent                                      *m_base                          = nullptr;
    QQuickWindow                                       *m_window                        = nullptr;
    QQuickItem                                         *m_qml_parent                    = nullptr;
    QQmlContext                                        *m_root_ctx                      = nullptr;
    CScreenManager                                      m_screen_manager;
    CPopupManager                                       m_popup_manager;
    CToastManager                                       m_toast_manager;
    CNotifyManager                                      m_notify_manager;
    QHash<E_VIEW_TYPE, IViewManager*>                   m_view_managers;
    E_VIEW_TYPE                                         m_last_view_type{E_VIEW_TYPE::NONE_TYPE};
    int                                                 m_depth{0};

};

#endif // CVIEWMANAGER_H
