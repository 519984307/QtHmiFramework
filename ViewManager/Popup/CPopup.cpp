#include "CPopup.h"

CPopup::CPopup(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;
}

CView *CPopup::customizeProperties()
{
    CPP_LOG_DEBUG("[Entry]")
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    this->setProperty("z", POPUP_z);
    CPP_LOG_DEBUG("[Exit]")
    return this;
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
