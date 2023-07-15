#include "CNgin.h"
#include "Utils/Utils.h"

#define QML_BASE "qrc:/QML_RESOURCE/QML/main.qml"

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

    m_viewManager       = new CViewManager(this);



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
        // [5] Loop: iterate over the list [m_viewInfos]
        for (QList<const S_VIEW_INFORMATION*>::Iterator it = m_viewInfos.begin();  it != m_viewInfos.end(); it++) {
            // [6] Check: if [destination] property of the current event itorator is not same as the current view iterator's [id]
            if((*evtIt)->destination != (*it)->id)
            {
                continue;
            }

            // Log event sent
            m_events_history[event] = (*it);
            break;
        }
    };
    // [1] Check: if event was ever sent
    if(m_events_history[event] == nullptr)
    {
        // [2] Loop: iterate over the list [m_event]
        for(QList<const S_VIEW_EVENT*>::iterator it = m_events.begin(); it != m_events.end(); it++)
        {
            // [3] Check: if the sent event is the same as the current iterator's [event]
            if(event == (*it)->event)
            {
                // [4] find View Info by the sent event
                _findInfoByEvent(it);
                break;
            }
        }
    }

    m_viewManager->pushEnter(m_events_history[event]);
    loadView();
}

void CNgin::previousView()
{
    m_viewManager->popExit();
    loadView();
}

void CNgin::loadView()
{
    if(m_viewManager->currentView() == nullptr) return;
    if(m_viewManager->currentView()->type == E_VIEW_TYPE::POPUP_TYPE)
    {
        loadQML("qml_root_popup_loader", m_viewManager->currentView()->path);
    }
    else if(m_viewManager->currentView()->type == E_VIEW_TYPE::SCREEN_TYPE)
    {
        loadQML("qml_root_popup_loader", "");
        loadQML("qml_root_screen_loader", m_viewManager->currentView()->path);
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
