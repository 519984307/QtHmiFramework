#include "CToast.h"

CToast::CToast(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{}

AView *CToast::customizeProperties()
{
    QObject *position = qvariant_cast<QObject*>(m_properties["anchors"]);
    position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
    position->setProperty("bottom", QVariant::fromValue(parentItem()->property("bottom")));
    position->setProperty("bottomMargin", 50);

    m_item->setProperty("z", NOTIFY_Z);
    return this;
}
