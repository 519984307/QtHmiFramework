#include "AView.h"
#include "Utils.h"

AView::AView(const S_VIEW_INFORMATION *info, QQuickItem *parent):CQmlRootContainer{parent}
{
    m_info = info;
    if(info->type > E_VIEW_TYPE::SCREEN_TYPE)
    {
        if(info->duration > 0)
        {
            m_timer = new QTimer(this);
            m_timer->setSingleShot(true);
            m_timer->start(info->duration * ONE_SEC);
        }
    }
    initConnections();
}

AView::~AView()
{
    safeRelease(m_timer);
}

AView * AView::initialize(QQuickItem *parent)
{
    CPP_LOG_INFO("[Entry]")
    this->setParentItem(parent);
    readProperties();
    CPP_LOG_INFO("[Exit]")
    return this;
}

void AView::readProperties()
{
    CPP_LOG_INFO("[Entry]")
    m_properties["x"]           = this->property("x").toReal();
    m_properties["y"]           = this->property("y").toReal();
    m_properties["z"]           = this->property("z").toReal();
    m_properties["width"]       = this->property("width").toReal();
    m_properties["height"]      = this->property("height").toReal();
    m_properties["anchors"]     = this->property("anchors");
    CPP_LOG_INFO("[Exit]")
}

bool AView::event(QEvent *event)
{
    return QObject::event(event);
}

bool AView::eventFilter(QObject *watched, QEvent *event)
{
    return QObject::eventFilter(watched, event);
}

void AView::setInfo(const S_VIEW_INFORMATION *newInfo)
{
    m_info = newInfo;
}

void AView::initConnections()
{
    if(m_timer != nullptr)
    {
        connect(m_timer, &QTimer::timeout, this, &AView::signalWaittingForTimeout, Qt::DirectConnection);
    }
}
