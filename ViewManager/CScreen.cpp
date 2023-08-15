#include "CScreen.h"


CScreen::CScreen(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{
}

void CScreen::customizeProperties()
{
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("fill", QVariant::fromValue(parentItem()));
}

