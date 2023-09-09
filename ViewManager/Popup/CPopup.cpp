#include "CPopup.h"

CPopup::CPopup(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{}

CPopup::~CPopup()
{}

AView *CPopup::customizeProperties()
{
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    m_item->setProperty("z", POPUP_z);

    return this;
}
