#ifndef CNGIN_H
#define CNGIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QTimer>
#include <QQueue>
#include <vector>
#include "CViewManager.h"

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

public slots:

signals:
    void initCompleted();

private:
    explicit CNgin(QObject *parent = nullptr);
    ~CNgin();

    const S_VIEW_INFORMATION* findViewByID(const uint32_t&);
    const S_VIEW_EVENT* findEventByID(const uchar&);
    void initConnections();
    void loadQML(QString, const QString&);

private:
    static CNgin                                            *s_instance;
    QQmlApplicationEngine                                   *m_qml_ngin           = nullptr;
    QQmlContext                                             *m_qml_ctx            = nullptr;
    QObject                                                 *m_root_object        = nullptr;
    CViewManager                                            *m_view_manager       = nullptr;
    QHash<uchar, const S_VIEW_EVENT*>                        m_event_cached;
    QHash<uint32_t, const S_VIEW_INFORMATION*>               m_info_cached;
    QList<const S_VIEW_INFORMATION*>                         m_infos{};
    QList<const S_VIEW_EVENT*>                               m_events{};
    QQueue<uchar>                                            m_events_queue;
    uchar                                                    m_last_event{0};
    bool                                                     m_event_is_processing{false};

};

#endif // CNGIN_H
