#include "CScreen.h"


CScreen::CScreen(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{
}

AView *CScreen::customizeProperties()
{
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("fill", QVariant::fromValue(parentItem()));
    m_item->setProperty("z", SCREEN_Z);

    return this;
}

