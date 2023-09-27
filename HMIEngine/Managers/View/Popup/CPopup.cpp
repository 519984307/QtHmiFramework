#include "CPopup.h"

CPopup::CPopup(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;

    m_timer = new QTimer(this);
    m_timer->setInterval(ONE_SEC);
    connect(m_timer, &QTimer::timeout, [&](){
        m_timer->stop();
        m_timer->start();
    });
}

void CPopup::customizeProperties()
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())
    setWidth(400);
    setHeight(200);
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    this->setProperty("z", POPUP_z);
    CPP_LOG_DEBUG("[%s][Exit]", c_strType())
}

void CPopup::completed()
{
    if(duration() > 0)
    {
        m_timer->start();
    }
}

void CPopup::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_DEBUG("mousePressEvent")
}

void CPopup::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_DEBUG("mouseReleaseEvent")
}
