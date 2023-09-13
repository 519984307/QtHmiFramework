#include "CToast.h"

CToast::CToast(const S_VIEW_INFORMATION *info, QQuickItem *parent) : AView(info, parent)
{}

AView *CToast::customizeProperties()
{
    CPP_LOG_INFO("[Entry]")
    QObject *position = qvariant_cast<QObject*>(m_properties["anchors"]);
    position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
    position->setProperty("bottom", QVariant::fromValue(parentItem()->property("bottom")));
    position->setProperty("bottomMargin", 50);
    this->setProperty("z", NOTIFY_Z);
    CPP_LOG_INFO("[Exit]")
    return this;
}
