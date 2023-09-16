#include "CScreen.h"

CScreen::CScreen(QQuickItem *parent) : CView(parent)
{
    m_str_type = __FUNCTION__;
}

CView *CScreen::customizeProperties()
{
    CPP_LOG_INFO("[Entry]")
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("fill", QVariant::fromValue(parentItem()));
    this->setProperty("z", SCREEN_Z);
    CPP_LOG_INFO("[Exit]")
    return this;
}

void CScreen::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_INFO("mousePressEvent")
}

void CScreen::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    CPP_LOG_INFO("mouseReleaseEvent")
}
