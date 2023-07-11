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
        m_viewManager->addView(&views[i]);
    }
}

void CNgin::registerEvents(const S_VIEW_EVENT *events, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        m_viewManager->addEvents(&events[i]);
    }
}

void CNgin::sendEvent(uchar event)
{
    m_viewManager->pushViewByEvt(event);
    loadView();
}

void CNgin::previousView()
{
    m_viewManager->popLastView();
    loadView();
}

void CNgin::onClosePopup()
{
    m_rootObject->findChild<QObject*>("qml_root_popup_loader")->setProperty("source", "");
}

void CNgin::onPopupTimeout()
{

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
