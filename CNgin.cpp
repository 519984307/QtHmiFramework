#include "CNgin.h"
#include "Utils.h"
#include "Logger/LoggerDefines.h"
#include "Screen/CScreenManager.h"
#include "Popup/CPopupManager.h"
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
    m_base               = new QQmlComponent(m_qml_ngin, this);

    m_view_managers[E_VIEW_TYPE::SCREEN_TYPE] = new CScreenManager(this);
    m_view_managers[E_VIEW_TYPE::POPUP_TYPE] = new CPopupManager(this);

    initConnections();
}

CNgin::~CNgin()
{
    safeRelease(m_qml_ngin);
    safeRelease(m_base);

    QHash<E_VIEW_TYPE, AViewManager*>::iterator it = m_view_managers.begin();
    while(it != m_view_managers.end())
    {
        safeRelease(it.value());
        ++it;
    }
}

void CNgin::initConnections()
{
    connect(this, &CNgin::initCompleted, this, &CNgin::onCompleted);
    connect(m_base, &QQmlComponent::statusChanged, this, &CNgin::onStatusChanged);

    QHash<E_VIEW_TYPE, AViewManager*>::iterator it = m_view_managers.begin();
    while(it != m_view_managers.end())
    {
        connect(it.value(),
                &AViewManager::signalPushEnter,
                this,
                &CNgin::onSignalPushEnter, Qt::QueuedConnection);
        ++it;
    }
}

void CNgin::updateLastViewType(E_VIEW_TYPE type)
{
    m_last_view_type = type;
}

void CNgin::initialize(QGuiApplication&app, uint32_t screenWidth, uint32_t screenHeight, uchar event)
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
            emit initCompleted();

            CNgin::instance()->sendEvent(event);

        }
    }, Qt::QueuedConnection);


    if(screenHeight * screenHeight > 0)
    {
        setCtxProperty("QmlRootScreenWidth", screenWidth);
        setCtxProperty("QmlRootScreenHeight", screenHeight);
    }

    // set context
    setCtxProperty("QmlNgin", QVariant::fromValue(this));
    setCtxProperty("QmlScreens", QVariant::fromValue(m_view_managers[E_VIEW_TYPE::SCREEN_TYPE]));
    setCtxProperty("QmlPopups", QVariant::fromValue(m_view_managers[E_VIEW_TYPE::POPUP_TYPE]));


    // register QML types
    qmlRegisterType<CViewEnums>("VIEWENUMS", 1, 0, "EVT");
    qmlRegisterSingletonInstance("Api.Common", 1, 0, "Logger", CLogger::instance(E_LOGGER_FLAG::QML));


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

void CNgin::sendEvent(uchar evtId)
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

    m_last_view_type = info->type;
    m_last_event = evt->event; // event id
    evt->fn();

    if(anyId.contains(evt->destination))
    {
        this->popExit(info);
    }
    else
    {
        info = findViewByID(evt->destination);
        if(info == nullptr)
        {
            CPP_LOG_WARN("Screen with ID [%u] not found!!!", evt->destination)
            return;
        }
        this->pushEnter(info);
    }
}

void CNgin::onCompleted()
{
    m_root_object = m_qml_ngin->rootObjects().at(0);
    if (m_root_object == nullptr) return;
    if (m_window == nullptr)
    {
        m_window = qobject_cast<QQuickWindow*>(m_root_object);
        m_qml_parent = m_window->contentItem();
    }
}

void CNgin::onProgressChanged(qreal progress)
{
    Q_UNUSED(progress)
}

void CNgin::onStatusChanged(QQmlComponent::Status status)
{
    switch (status) {
    case QQmlComponent::Null:
        CPP_LOG_INFO("This QQmlComponent has no data. Call loadUrl() or setData() to add QML content.")
        break;
    case QQmlComponent::Ready:
    {
        CPP_LOG_INFO("This QQmlComponent is ready and create() may be called.")

        QQuickItem *item = qobject_cast<QQuickItem*>(m_base->create());
        item->setParentItem(m_qml_parent);
        m_view_managers[m_last_view_type]->last_view()
            ->initialize(item)
            ->customizeProperties()
            ->show();

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

void CNgin::onSignalPushEnter(AView *newView)
{
    if(newView == nullptr || m_last_view_type == E_VIEW_TYPE::NONE_TYPE) return;
    CPP_LOG_DEBUG("Path %s", newView->info()->path);
    m_base->loadUrl(QUrl(newView->info()->path), QQmlComponent::Asynchronous);
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

void CNgin::pushEnter(const S_VIEW_INFORMATION *view)
{
    if(~m_last_view_type & (E_VIEW_TYPE::NONE_TYPE | E_VIEW_TYPE::SCREEN_TYPE) && view->type == E_VIEW_TYPE::SCREEN_TYPE) return;
    m_view_managers[m_last_view_type]->pushEnter(view);
}

void CNgin::popExit(const S_VIEW_INFORMATION *view)
{
    if(~m_last_view_type & (E_VIEW_TYPE::NONE_TYPE | E_VIEW_TYPE::SCREEN_TYPE) && view->type == E_VIEW_TYPE::SCREEN_TYPE) return;
    m_view_managers[m_last_view_type]->popExit();
}
