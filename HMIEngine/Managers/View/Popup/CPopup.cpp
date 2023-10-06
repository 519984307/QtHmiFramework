#include "CPopup.h"

BEGIN_NAMESPACE(HmiNgin)
CPopup::CPopup(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;
    connect(this, &CPopup::signalVisible, [&](){ if(duration() > 0) m_timer.start(duration() * ONE_SEC);});
    connect(this, &CPopup::signalInvisible, [&](){ m_timer.stop(); });
    connect(&m_timer, &QTimer::timeout, [&](){ this->hide(); });
}

void CPopup::customizeProperties()
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())
    setWidth(400);
    setHeight(200);
    qvariant_cast<QObject *>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    this->setProperty("z", POPUP_z);
    CPP_LOG_DEBUG("[%s][Exit]", c_strType())
}

void CPopup::completed()
{
    if (duration() > 0)
    {
        m_timer.start(duration() * ONE_SEC);
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

END_NAMESPACE
