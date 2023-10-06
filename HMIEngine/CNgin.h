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
#include <QSensor>
#include <vector>
#include "AViewManager.h"
#include "Common.h"
    
namespace HmiNgin
{
    class CNgin : public QObject
    {
        Q_OBJECT
    public:
        static CNgin* instance();

        void initialize(QGuiApplication&, const uint32_t&, const uint32_t&, const uchar&);
        void completed();
        void setCtxProperty(const QString&, QVariant);
        void registerViews(const S_VIEW_INFORMATION*, uint32_t);
        void registerEvents(const S_VIEW_EVENT*, uint32_t);


        inline QQmlApplicationEngine *qmlEngine() const { return m_qml_ngin; }
        inline QQmlComponent *qmlBase() const { return m_qml_base; }
        inline QQuickWindow *qmlWindow() const { return m_qml_window; }


        void setLastViewType(const E_VIEW_TYPE&);

    public:
        Q_INVOKABLE void sendEvent(const uchar&);


    signals:
        void signalCompleted(const uchar&);
        void signalOnTopChanged(const E_VIEW_TYPE&);

    private:
        explicit CNgin(QObject *parent = nullptr);
        ~CNgin();

        void initConnections();

    public slots:
        void onCompleted(const uchar&);

        void onLoadQml(IEventPayload*);

    private:
        const S_VIEW_INFORMATION* findViewByID(const uint32_t&);
        const S_VIEW_EVENT* findEventByID(const uchar&);

    private:
        static CNgin                                            *s_instance;
        QQmlApplicationEngine                                   *m_qml_ngin           = nullptr;
        QQmlContext                                             *m_qml_ctx            = nullptr;
        QObject                                                 *m_root_object        = nullptr;
        QQmlComponent                                           *m_qml_base           = nullptr;
        QQuickWindow                                            *m_qml_window         = nullptr;
        QQuickItem                                              *m_qml_parent         = nullptr;

        QHash<uint8_t, QString>                                  m_view_types_dict;
        QHash<uchar, const S_VIEW_EVENT*>                        m_event_cached;
        QHash<uint32_t, const S_VIEW_INFORMATION*>               m_info_cached;
        QList<const S_VIEW_INFORMATION*>                         m_infos{};
        QList<const S_VIEW_EVENT*>                               m_events{};
        QQueue<uchar>                                            m_events_queue;
        uchar                                                    m_last_event{0};
        bool                                                     m_event_is_processing{false};
        
        QHash<E_VIEW_TYPE, AViewManager*>                        m_view_managers;
        E_VIEW_TYPE                                              m_last_view_type{E_VIEW_TYPE::NONE_TYPE};

        EventCallBack                                            m_LoadQmlCallBack;
    };

} // namespace HmiNgin


#endif // CNGIN_H
