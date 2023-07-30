#include "CNgin.h"
#include "Utils.h"
#include "Logger/LoggerDefines.h"
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

    m_view_manager       = new CViewManager(m_qml_ngin, this);

    initConnections();
}

CNgin::~CNgin()
{
    safeRelease(m_view_manager);
    safeRelease(m_qml_ngin);
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

void CNgin::initConnections()
{
    connect(this, &CNgin::initCompleted, m_view_manager, &CViewManager::onCompleted);
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

            m_root_object = m_qml_ngin->rootObjects().at(0);
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
    setCtxProperty("QmlViewManager", QVariant::fromValue(m_view_manager));
    setCtxProperty("QmlLogger", QVariant::fromValue(CLogger::instance(E_LOGGER_FLAG::QML)));

    // register QML types


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

    CPP_LOG_WARN("The Event [%u] [%s] processing", evtId, m_event_is_processing? "is":"is not");
    if(m_event_is_processing)
    {
        m_events_queue.enqueue(evtId);
        return;
    }

    const QList<uint32_t> anyId = {E_SCREEN_ID::E_SCREEN_ANY_ID, E_POPUP_ID::E_POPUP_ANY_ID};
    const S_VIEW_EVENT* evt = findEventByID(evtId);

    if(evt == nullptr)
    {
        CPP_LOG_WARN("Event with ID [%u] has not been defined!!!", evtId);
        return;
    }

    m_last_event = evt->event; // event id
    evt->fn();

    if(anyId.contains(evt->destination))
    {
        m_view_manager->popExit();
    }
    else
    {
        const S_VIEW_INFORMATION* info = findViewByID(evt->destination);
        if(info == nullptr)
        {
            CPP_LOG_WARN("Screen with ID [%u] not found!!!", evt->destination);
            return;
        }
        m_view_manager->pushEnter(info);
    }
}


void CNgin::loadQML(QString objName, const QString& path)
{
    QObject* _loader = nullptr;
    _loader = m_root_object->findChild<QObject*>(objName);

    if(_loader != nullptr)
    {
        _loader->setProperty("source", path);
    }
}
