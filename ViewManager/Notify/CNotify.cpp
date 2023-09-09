#include "CNotify.h"

CNotify::CNotify(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{
    if(info->duration > 0)
    {
        m_timer = new QTimer(this);
        m_timer->setSingleShot(true);
        m_timer->start(info->duration * ONE_SEC);

        connect(m_timer, &QTimer::timeout, this, &CNotify::signalWaittingForTimeout, Qt::DirectConnection);    }
}

CNotify::~CNotify()
{
    safeRelease(m_timer);
}

AView *CNotify::customizeProperties()
{
    QObject *position = qvariant_cast<QObject*>(m_properties["anchors"]);
    position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
    position->setProperty("top", QVariant::fromValue(parentItem()->property("top")));
    position->setProperty("topMargin", 50);

    m_item->setProperty("z", NOTIFY_Z);
    return this;
}
