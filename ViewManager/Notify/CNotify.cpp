#include "CNotify.h"

CNotify::CNotify(const S_VIEW_INFORMATION *info, QQuickItem *parent) : AView(info, parent)
{}

CNotify::~CNotify()
{}

AView *CNotify::customizeProperties()
{
    CPP_LOG_INFO("[Entry]")
    QObject *position = qvariant_cast<QObject*>(m_properties["anchors"]);
    position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
    position->setProperty("top", QVariant::fromValue(parentItem()->property("top")));
    position->setProperty("topMargin", 50);
    this->setProperty("z", NOTIFY_Z);
    CPP_LOG_INFO("[Exit]")
    return this;
}
