#include "CNotify.h"

CNotify::CNotify(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{}

CNotify::~CNotify()
{}

AView *CNotify::customizeProperties()
{
    QObject *position = qvariant_cast<QObject*>(m_properties["anchors"]);
    position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
    position->setProperty("top", QVariant::fromValue(parentItem()->property("top")));
    position->setProperty("topMargin", 50);

    m_item->setProperty("z", NOTIFY_Z);
    return this;
}
