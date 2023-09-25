#include "CPopup.h"

CPopup::CPopup(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;
}

CView *CPopup::customizeProperties()
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())
    setWidth(400);
    setHeight(200);
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    this->setProperty("z", POPUP_z);
    CPP_LOG_DEBUG("[%s][Exit]", c_strType())
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
