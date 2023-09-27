#include "CScreen.h"

CScreen::CScreen(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;
}

void CScreen::customizeProperties()
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("fill", QVariant::fromValue(parentItem()));
    this->setProperty("z", SCREEN_Z);
    CPP_LOG_DEBUG("[%s][Exit]", c_strType())
}

void CScreen::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_DEBUG("mousePressEvent")
}

void CScreen::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_DEBUG("mouseReleaseEvent")
}
