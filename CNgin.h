#ifndef CNGIN_H
#define CNGIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QTimer>
#include <QQueue>
#include <vector>
#include "AViewManager.h"
#include "Common.h"

class CNgin : public QObject
{
    Q_OBJECT
public:
    static CNgin* instance();

    void initialize(QGuiApplication&, uint32_t, uint32_t, uchar);
    void completed();
    void setCtxProperty(QString, QVariant);
    void registerViews(const S_VIEW_INFORMATION*, uint32_t);
    void registerEvents(const S_VIEW_EVENT*, uint32_t);

    Q_INVOKABLE void sendEvent(uchar);

signals:
    void initCompleted();

private:
    explicit CNgin(QObject *parent = nullptr);
    ~CNgin();

    void initConnections();

public slots:
    void onCompleted();
    void onProgressChanged(qreal);
    void onStatusChanged(QQmlComponent::Status);
    void onSignalPushEnter(AView*);

private:
    const S_VIEW_INFORMATION* findViewByID(const uint32_t&);
    const S_VIEW_EVENT* findEventByID(const uchar&);
    void pushEnter(const S_VIEW_INFORMATION*);
    void popExit();

private:
    static CNgin                                            *s_instance;
    QQmlApplicationEngine                                   *m_qml_ngin           = nullptr;
    QQmlContext                                             *m_qml_ctx            = nullptr;
    QObject                                                 *m_root_object        = nullptr;
    QQmlComponent                                           *m_base               = nullptr;
    QQuickWindow                                            *m_window             = nullptr;
    QQuickItem                                              *m_qml_parent         = nullptr;
    QQmlContext                                             *m_root_ctx           = nullptr;
    QHash<uchar, const S_VIEW_EVENT*>                        m_event_cached;
    QHash<uint32_t, const S_VIEW_INFORMATION*>               m_info_cached;
    QList<const S_VIEW_INFORMATION*>                         m_infos{};
    QList<const S_VIEW_EVENT*>                               m_events{};
    QQueue<uchar>                                            m_events_queue;
    uchar                                                    m_last_event{0};
    bool                                                     m_event_is_processing{false};
    QHash<E_VIEW_TYPE, AViewManager*>                        m_view_managers;
    E_VIEW_TYPE                                              m_last_view_type{E_VIEW_TYPE::NONE_TYPE};
};

#endif // CNGIN_H
