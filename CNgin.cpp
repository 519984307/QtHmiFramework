#include "CNgin.h"
#include "Utils/Utils.h"
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
    m_qmlNgin           = new QQmlApplicationEngine(this);
    m_qmlCtx            = m_qmlNgin->rootContext();

    m_viewManager       = new CViewManager(m_qmlNgin, this);
}

CNgin::~CNgin()
{
    safeRelease(m_viewManager);
    safeRelease(m_popupTimer);
    safeRelease(m_qmlNgin);
}

void CNgin::initialize(QGuiApplication&app, uint32_t screenWidth, uint32_t screenHeight, uchar event)
{
    const QUrl url(QStringLiteral(QML_BASE));

    QObject::connect(m_qmlNgin, &QQmlApplicationEngine::objectCreated,
                     &app, [event, url, this](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
        else
        {
            emit initCompleted();

            m_rootObject = m_qmlNgin->rootObjects().at(0);

            CNgin::instance()->sendEvent(event);
        }
    }, Qt::QueuedConnection);


    if(screenHeight * screenHeight > 0)
    {
        setCtxProperty("QmlRootScreenWidth", screenWidth);
        setCtxProperty("QmlRootScreenHeight", screenHeight);
    }

    setCtxProperty("QmlNgin", QVariant::fromValue(this));
    setCtxProperty("QmlViewManager", QVariant::fromValue(m_viewManager));

    // register QML types


    // do other things
}

void CNgin::completed()
{
    if(m_qmlNgin != nullptr)
    {
        m_qmlNgin->load(QML_BASE);
    }
}

void CNgin::setCtxProperty(QString label, QVariant value)
{
    if(m_qmlCtx != nullptr)
    {
        m_qmlCtx->setContextProperty(label, value);
    }
}

void CNgin::registerViews(const S_VIEW_INFORMATION *views, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        m_viewInfos.append(&views[i]);
    }
}

void CNgin::registerEvents(const S_VIEW_EVENT *events, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        m_events.append(&events[i]);
    }
}

void CNgin::sendEvent(uchar event)
{
    // the lambda function capture current object and the sent event
    auto _findInfoByEvent = [this, event](QList<const S_VIEW_EVENT*>::iterator evtIt)
    {
        // [1.1.2.1] Loop: iterate over the list [m_viewInfos]
        for (QList<const S_VIEW_INFORMATION*>::Iterator it = m_viewInfos.begin();  it != m_viewInfos.end(); it++) {
            // [1.1.2.1.1] Check: if [destination] property of the current event iterator is not same as the current view iterator's [id]
            if((*evtIt)->destination != (*it)->id)
            {
                continue;
            }

            // [1.1.2.1.2] Log event sent
            m_events_history[event] = (*it);

            break;
        }
    };

    // [1] Loop: iterate over the list [m_event]
    for(QList<const S_VIEW_EVENT*>::iterator it = m_events.begin(); it != m_events.end(); it++)
    {
        // [1.1] Check: if the sent event is the same as the current iterator's [event]
        if(event == (*it)->event)
        {
            // [1.1.1] Check: if [destination] property of the current event iterator is [E_SCREEN_ANY_ID] OR [E_POPUP_ANY_ID]
            if((*it)->destination == E_SCREEN_ID::E_SCREEN_ANY_ID || (*it)->destination == E_POPUP_ID::E_POPUP_ANY_ID)
            {
                // [1.1.1.1] pop view on top of the stack
                m_viewManager->popExit();
                break;
            }

            // [1.1.2] Check: if event was ever sent
            if(m_events_history[event] == nullptr)
            {
                // [1.1.2.1] find View Info by the sent event
                _findInfoByEvent(it);
            }
            // [1.1.3] push view to the stack
            m_viewManager->pushEnter(m_events_history[event]);


            break;
        }
        // [1.2] continue
        else
        {
            continue;
        }
    }
}


void CNgin::loadQML(QString objName, const QString& path)
{
    QObject* _loader = nullptr;
    _loader = m_rootObject->findChild<QObject*>(objName);

    if(_loader != nullptr)
    {
        _loader->setProperty("source", path);
    }
}
