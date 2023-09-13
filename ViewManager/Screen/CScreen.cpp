#include "CScreen.h"


CScreen::CScreen(const S_VIEW_INFORMATION *info, QQuickItem *parent) : AView(info, parent)
{
}

AView *CScreen::customizeProperties()
{
    CPP_LOG_INFO("[Entry]")
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("fill", QVariant::fromValue(parentItem()));
    this->setProperty("z", SCREEN_Z);
    CPP_LOG_INFO("[Exit]")
    return this;
}

