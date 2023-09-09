#include "CPopup.h"

CPopup::CPopup(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{
    if(info->duration > 0)
    {
        m_timer = new QTimer(this);
        m_timer->setSingleShot(true);
        m_timer->start(info->duration * ONE_SEC);

        connect(m_timer, &QTimer::timeout, this, &CPopup::signalWaittingForTimeout, Qt::DirectConnection);
    }
}

CPopup::~CPopup()
{
    safeRelease(m_timer);
}

AView *CPopup::customizeProperties()
{
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    m_item->setProperty("z", POPUP_z);

    return this;
}
