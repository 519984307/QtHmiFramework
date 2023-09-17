#include "CNgin.h"
#include "Utils.h"
#include "Logger/LoggerDefines.h"
#include "Screen/CScreen.h"
#include "Popup/CPopup.h"
#include "Notify/CNotify.h"
#include "Toast/CToast.h"
#include "Screen/CScreenManager.h"
#include "Popup/CPopupManager.h"
//#include "Notify/CNotifyManager.h"
//#include "Toast/CToastManager.h"
#include "CViewEnums.h"

#define QML_BASE "qrc:/QML_RESOURCE//main.qml"

CNgin *CNgin::s_instance = nullptr;
CNgin *CNgin::instance()
{
    return s_instance = (s_instance == nullptr)? new CNgin(): s_instance;
}

CNgin::CNgin(QObject *parent)
    : QObject{parent}
{
    m_qml_ngin           = new QQmlApplicationEngine(this);
    m_qml_ctx            = m_qml_ngin->rootContext();
    m_qml_base           = new QQmlComponent(m_qml_ngin, this);

    m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]   = new CScreenManager(this);
    m_view_managers[E_VIEW_TYPE::POPUP_TYPE]    = new CPopupManager(this);
    //    m_view_managers[E_VIEW_TYPE::NOTIFY_TYPE]   = new CNotifyManager(this);
    //    m_view_managers[E_VIEW_TYPE::TOAST_TYPE]    = new CToastManager(this);


    m_view_types_dict[E_VIEW_TYPE::SCREEN_TYPE] = "Screen";
    m_view_types_dict[E_VIEW_TYPE::POPUP_TYPE]  = "Popup";

    initConnections();
}

CNgin::~CNgin()
{
    safeRelease(m_qml_ngin);
    safeRelease(m_qml_base);

    QHash<E_VIEW_TYPE, CViewManager*>::iterator it = m_view_managers.begin();
    while(it != m_view_managers.end())
    {
        safeRelease(it.value());
        ++it;
    }
}

void CNgin::initConnections()
{
    connect(this, &CNgin::signalCompleted, this, &CNgin::onCompleted);

    QHash<E_VIEW_TYPE, CViewManager*>::iterator it = m_view_managers.begin();
    while(it != m_view_managers.end())
    {
        connect(it.value(), &CViewManager::signalPushBack,
                this, &CNgin::onSignalPushBack, Qt::QueuedConnection);

        connect(it.value(), &CViewManager::signalPopBack,
                this, &CNgin::onSignalPopBack, Qt::QueuedConnection);
        ++it;
    }
}

void CNgin::updateLastViewType(E_VIEW_TYPE type)
{
    m_last_view_type = type;
}

void CNgin::initialize(QGuiApplication&app, const uint32_t &screenWidth, const uint32_t &screenHeight, const uchar &event)
{
    const QUrl url(QStringLiteral(QML_BASE));

    QObject::connect(m_qml_ngin, &QQmlApplicationEngine::objectCreated,
        &app, [event, url, this](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
            {
                QCoreApplication::exit(-1);
            }
            else
            {
                emit signalCompleted(event);
            }
        }, Qt::QueuedConnection);


    if(screenHeight * screenHeight > 0)
    {
        setCtxProperty("QmlRootScreenWidth", screenWidth);
        setCtxProperty("QmlRootScreenHeight", screenHeight);
    }

    // set context
    setCtxProperty("QmlNgin", QVariant::fromValue(this));
    setCtxProperty("QmlScreenManager", QVariant::fromValue(m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]));
    setCtxProperty("QmlPopupManager", QVariant::fromValue(m_view_managers[E_VIEW_TYPE::POPUP_TYPE]));



    // register QML types and other types
    qmlRegisterType<CViewEnums>("VIEWENUMS", 1, 0, "EVT");

    qmlRegisterType<CScreen>("Common.Qml", 1, 0, "QmlScreen");
    qmlRegisterType<CPopup>("Common.Qml", 1, 0, "QmlPopup");
    qmlRegisterType<CNotify>("Common.Qml", 1, 0, "QmlNotify");
    qmlRegisterType<CToast>("Common.Qml", 1, 0, "QmlToast");

    // do other things
}

void CNgin::completed()
{
    if(m_qml_ngin != nullptr)
    {
        m_qml_ngin->load(QML_BASE);
    }
}

void CNgin::setCtxProperty(QString label, QVariant value)
{
    if(m_qml_ctx != nullptr)
    {
        m_qml_ctx->setContextProperty(label, value);
    }
}

void CNgin::registerViews(const S_VIEW_INFORMATION *views, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        m_infos.append(&views[i]);
    }
}

void CNgin::registerEvents(const S_VIEW_EVENT *events, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        m_events.append(&events[i]);
    }
}

void CNgin::setLastViewType(const E_VIEW_TYPE &type)
{
    if(m_last_view_type == type)
    {
        return;
    }

    m_last_view_type = type;
    emit signalOnTopChanged(m_last_view_type);
}

void CNgin::sendEvent(const uchar &evtId)
{
    //    if(m_last_event != 0 && m_last_event == evtId)
    //    {
    //        CPP_LOG_WARN("The current Event [%u] the last Event", evtId);
    //        return;
    //    }

    //    CPP_LOG_WARN("The Event [%u] [%s] processing", evtId, m_event_is_processing? "is":"is not");
    //    if(m_event_is_processing)
    //    {
    //        m_events_queue.enqueue(evtId);
    //        return;
    //    }

    const QList<uint32_t> anyId = {E_SCREEN_ID::E_SCREEN_ANY_ID, E_POPUP_ID::E_POPUP_ANY_ID};
    const S_VIEW_EVENT* evt = findEventByID(evtId);
    const S_VIEW_INFORMATION* info = findViewByID(evt->view);

    if(evt == nullptr)
    {
        CPP_LOG_WARN("Event with ID [%u] has not been defined!!!", evtId)
        return;
    }

    setLastViewType(info->type);

    m_last_event = evt->event; // event id
    evt->fn();

    if(anyId.contains(evt->destination))
    {
        m_view_managers[m_last_view_type]->popExit();
    }
    else
    {
        info = findViewByID(evt->destination);
        if(info == nullptr)
        {
            CPP_LOG_WARN("View with ID [%u] not found!!!", evt->destination)
            return;
        }

        setLastViewType(info->type);

        m_view_managers[m_last_view_type]->pushEnter(info);
    }
}

void CNgin::onCompleted(const uchar& event)
{
    // [INITIALIZE]
    {
        m_root_object = m_qml_ngin->rootObjects().at(0);
        if (m_root_object == nullptr) return;
        if (m_qml_window == nullptr)
        {
            m_qml_window = qobject_cast<QQuickWindow*>(m_root_object);
            m_qml_parent = m_qml_window->contentItem();
        }
    }

    // [AFTER ALL INITIALIZED]
    {
        if (m_root_object == nullptr || m_qml_window == nullptr || m_qml_base == nullptr) return;
        CNgin::instance()->sendEvent(event);
    }
}

void CNgin::onSignalPushBack(const S_VIEW_INFORMATION *nextView, E_CACHE_STATUS status)
{
    CPP_LOG_DEBUG("Path %s", nextView->path);
    CView *obj = nullptr;
    if(status == E_CACHE_STATUS::HIT)
    {
        CPP_LOG_INFO("Load SCREEN [%s] from cache memory", nextView->path);
        obj = m_view_managers[m_last_view_type]->findViewObjectByID(nextView->id);
        if(obj == nullptr) return;

        m_view_managers[m_last_view_type]->views().last()->hide();
    }
    else if(status == E_CACHE_STATUS::MISS)
    {
        if(nextView == nullptr || m_last_view_type == E_VIEW_TYPE::NONE_TYPE) return;
        m_qml_base->loadUrl(QUrl(nextView->path), QQmlComponent::PreferSynchronous);
        switch (m_qml_base->status()) {
        case QQmlComponent::Null:
            CPP_LOG_INFO("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.")

            break;
        case QQmlComponent::Ready:
        {
            CPP_LOG_INFO("This QQmlComponent is ready and create() may be called.")
            obj = qobject_cast<CView*>(m_qml_base->create());
            obj->initialize(nextView, m_qml_parent);
            m_view_managers[m_last_view_type]->writecache(nextView->id, obj);
            break;
        }
        case QQmlComponent::Loading:
            CPP_LOG_INFO("This QQmlComponent is loading network data.")

            break;
        case QQmlComponent::Error:
            CPP_LOG_INFO("An error has occurred. Call errors() to retrieve a list of errors.")

            break;
        default:
            break;
        }
    }

    if(obj == nullptr) return;
//    if(obj->type() == E_VIEW_TYPE::POPUP_TYPE)
//    {
//        m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]
//            ->views().last()
//            ->setProperty("enabled", false);
//    }

    obj->show();
    m_view_managers[m_last_view_type]->pushBack(obj);

}

void CNgin::onSignalPopBack()
{
    CPP_LOG_INFO("[Entry")
    CViewManager *manager   = m_view_managers[m_last_view_type];
    CView        *lastView  = manager->lastView();

    if(!manager->isValidDepth()) return;
    if(lastView == nullptr) return;

    lastView->hide();
    manager->popBack();

    if(manager->views().isEmpty()) return;
    manager->lastView()->show();
    CPP_LOG_INFO("[Exit")
}

const S_VIEW_INFORMATION *CNgin::findViewByID(const uint32_t &id)
{
    if(m_info_cached[id] != nullptr)
    {
        return m_info_cached[id];
    }

    QList<const S_VIEW_INFORMATION*>::iterator it = m_infos.begin();
    while(it != m_infos.end())
    {
        if(id == (*it)->id)
        {
            m_info_cached[id] =  (*it);
            return (*it);
        }
        ++it;
    }
    return nullptr;
}

const S_VIEW_EVENT *CNgin::findEventByID(const uchar &id)
{
    if(m_event_cached[id] != nullptr)
    {
        return m_event_cached[id];
    }

    QList<const S_VIEW_EVENT*>::iterator it = m_events.begin();
    while(it != m_events.end())
    {
        if(id == (*it)->event)
        {
            m_event_cached[id] =  (*it);
            return (*it);
        }
        ++it;
    }
    return nullptr;
}
