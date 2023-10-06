#include "CNgin.h"
#include "Utils.h"
#include "Logger/LoggerDefines.h"
#include "CViewEnums.h"

#include "Screen/CScreen.h"
#include "Popup/CPopup.h"
#include "Notify/CNotify.h"
#include "Toast/CToast.h"
#include "Screen/CScreenManager.h"
#include "Popup/CPopupManager.h"
#include "Notify/CNotifyManager.h"
#include "Toast/CToastManager.h"

#define QML_BASE "qrc:/QML/main.qml"

BEGIN_NAMESPACE(HmiNgin)

CNgin *CNgin::s_instance = nullptr;
CNgin *CNgin::instance()
{
    return s_instance = (s_instance == nullptr) ? new CNgin() : s_instance;
}

CNgin::CNgin(QObject *parent)
    : QObject{parent}
{
    m_qml_ngin = new QQmlApplicationEngine(this);
    m_qml_ctx = m_qml_ngin->rootContext();
    m_qml_base = new QQmlComponent(m_qml_ngin, this);

    m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]   = new CScreenManager();
    m_view_managers[E_VIEW_TYPE::POPUP_TYPE]    = new CPopupManager();
    m_view_managers[E_VIEW_TYPE::NOTIFY_TYPE]   = new CNotifyManager();
    m_view_managers[E_VIEW_TYPE::TOAST_TYPE]    = new CToastManager();

    m_view_types_dict[E_VIEW_TYPE::SCREEN_TYPE] = "Screen";
    m_view_types_dict[E_VIEW_TYPE::POPUP_TYPE] = "Popup";

    initConnections();
}

CNgin::~CNgin()
{
    safeRelease(m_qml_ngin);
    safeRelease(m_qml_base);
    safeRelease(m_qml_parent);
    safeRelease(m_qml_window);
    safeRelease(m_root_object);
    safeRelease(m_qml_ctx);

    QHash<E_VIEW_TYPE, AViewManager *>::iterator it = m_view_managers.begin();
    while (it != m_view_managers.end())
    {
        safeRelease((QObject *)(*it));
        ++it;
    }
}

void CNgin::initConnections()
{
    connect(this, &CNgin::signalCompleted, this, &CNgin::onCompleted);
    
    EVENT_REGISTER_LISTENER_1_ARG(CNgin, this, LoadQml, E_EVENT_LOAD_QML)
}

void CNgin::initialize(QGuiApplication &app, const char* appName, const uint32_t &screenWidth, const uint32_t &screenHeight, const uchar &event)
{
    CPP_LOG_DEBUG("[Entry]")
    const QUrl url(QStringLiteral(QML_BASE));

    QObject::connect(
        m_qml_ngin, &QQmlApplicationEngine::objectCreated,
        &app, [event, url, this](QObject *obj, const QUrl &objUrl)
        {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
        else
        {
            emit signalCompleted(event);
        } },
        Qt::QueuedConnection);

    if (screenHeight * screenHeight > 0)
    {
        setCtxProperty("QmlRootScreenWidth", screenWidth);
        setCtxProperty("QmlRootScreenHeight", screenHeight);
    }

    setCtxProperty("AppName", appName);

    // set context
    setCtxProperty("QmlNgin", QVariant::fromValue(this));
    setCtxProperty("QmlScreenManager", QVariant::fromValue((CScreenManager*)m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]));
    setCtxProperty("QmlPopupManager", QVariant::fromValue((CPopupManager*)m_view_managers[E_VIEW_TYPE::POPUP_TYPE]));

    // register QML types and other types
    qmlRegisterType<CViewEnums>("VIEWENUMS", 1, 0, "EVT");

    qmlRegisterType<CScreen>("Common.Qml", 1, 0, "QmlScreen");
    qmlRegisterType<CPopup>("Common.Qml", 1, 0, "QmlPopup");
    qmlRegisterType<CNotify>("Common.Qml", 1, 0, "QmlNotify");
    qmlRegisterType<CToast>("Common.Qml", 1, 0, "QmlToast");

    // do other things

    //
    CPP_LOG_DEBUG("[Exit]")
}

void CNgin::completed()
{
    CPP_LOG_DEBUG("[Entry]")
    if (m_qml_ngin != nullptr)
    {
        m_qml_ngin->load(QML_BASE);
    }
    CPP_LOG_DEBUG("[Exit]")
}

void CNgin::setCtxProperty(const QString &label, QVariant value)
{
    CPP_LOG_DEBUG("[Entry]")
    if (m_qml_ctx != nullptr)
    {
        m_qml_ctx->setContextProperty(label, value);
    }
    CPP_LOG_DEBUG("[Exit]")
}

void CNgin::registerViews(const S_VIEW_INFORMATION *views, uint32_t len)
{
    CPP_LOG_DEBUG("[Entry]")
    for (uint32_t i = 0; i < len; i++)
    {
        m_infos.append(&views[i]);
    }
    CPP_LOG_DEBUG("[Exit]")
}

void CNgin::registerEvents(const S_VIEW_EVENT *events, uint32_t len)
{
    CPP_LOG_DEBUG("[Entry]")
    for (uint32_t i = 0; i < len; i++)
    {
        m_events.append(&events[i]);
    }
    CPP_LOG_DEBUG("[Exit]")
}

void CNgin::setLastViewType(const E_VIEW_TYPE &type)
{
    if (m_last_view_type == type)
        return;
    m_last_view_type = type;
    emit signalOnTopChanged(m_last_view_type);
}

void CNgin::sendEvent(const uchar &evtId)
{
    const QList<uint32_t> anyId = {E_SCREEN_ID::E_SCREEN_ANY_ID, E_POPUP_ID::E_POPUP_ANY_ID};
    const S_VIEW_EVENT *evt = findEventByID(evtId);
    const S_VIEW_INFORMATION *info = findViewByID(evt->view);

    if (evt == nullptr)
    {
        CPP_LOG_WARN("Event with ID [%u] has not been defined!!!", evtId)
        return;
    }

    setLastViewType(info->type);

    if(m_last_view_type == E_VIEW_TYPE::NONE_TYPE) 
    {
        CPP_LOG_WARN("Current View Type: NONE")
        return;
    }

    m_last_event = evt->event; // event id
    evt->fn();

    if (anyId.contains(evt->destination))
    {   
        m_view_managers[m_last_view_type]->detach(info);
    }
    else
    {
        info = findViewByID(evt->destination);
        if (info == nullptr)
        {
            CPP_LOG_WARN("View with ID [%u] not found!!!", evt->destination)
            return;
        }

        setLastViewType(info->type);

        m_view_managers[m_last_view_type]->attach(info);
    }
}

void CNgin::onCompleted(const uchar &event)
{
    // [INITIALIZE]
    {
        m_root_object = m_qml_ngin->rootObjects().at(0);
        if (m_root_object == nullptr) return;
        if (m_qml_window == nullptr)
        {
            m_qml_window = qobject_cast<QQuickWindow *>(m_root_object);
            m_qml_parent = m_qml_window->contentItem();
        }
    }

    // [AFTER ALL INITIALIZED]
    {
        if (m_root_object == nullptr || m_qml_window == nullptr || m_qml_base == nullptr)
            return;
            
        CNgin::instance()->sendEvent(event);
    }
}

void CNgin::onLoadQml(IEventPayload *payload)
{
    HmiNgin::SInitQmlEventPayload *data = (HmiNgin::SInitQmlEventPayload *)payload;
    const S_VIEW_INFORMATION *info = data->info;
    const std::function<void(CView *)> &cb = data->cb;

    m_qml_base->loadUrl(QUrl(info->path), QQmlComponent::PreferSynchronous);
    switch (m_qml_base->status())
    {
    case QQmlComponent::Null:
        CPP_LOG_DEBUG("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.")
        break;
    case QQmlComponent::Ready:
    {
        CPP_LOG_DEBUG("This QQmlComponent is ready and create() may be called.")

        CView *obj = qobject_cast<CView *>(m_qml_base->create());
        obj->initialize(info, m_qml_parent);
        obj->completed();
        cb(obj);
        break;
    }
    case QQmlComponent::Loading:
        CPP_LOG_DEBUG("This QQmlComponent is loading network data.")

        break;
    case QQmlComponent::Error:
        CPP_LOG_DEBUG("An error has occurred. Call errors() to retrieve a list of errors.")

        break;
    default:
        break;
    }
}

const S_VIEW_INFORMATION *CNgin::findViewByID(const uint32_t &id)
{
    if (m_info_cached[id] != nullptr)
    {
        return m_info_cached[id];
    }

    QList<const S_VIEW_INFORMATION *>::iterator it = m_infos.begin();
    while (it != m_infos.end())
    {
        if (id == (*it)->id)
        {
            m_info_cached[id] = (*it);
            return (*it);
        }
        ++it;
    }
    return nullptr;
}

const S_VIEW_EVENT *CNgin::findEventByID(const uchar &id)
{
    if (m_event_cached[id] != nullptr)
    {
        return m_event_cached[id];
    }

    QList<const S_VIEW_EVENT *>::iterator it = m_events.begin();
    while (it != m_events.end())
    {
        if (id == (*it)->event)
        {
            m_event_cached[id] = (*it);
            return (*it);
        }
        ++it;
    }
    return nullptr;
}

END_NAMESPACE
