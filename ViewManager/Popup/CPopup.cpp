#include "CPopup.h"

CPopup::CPopup(const S_VIEW_INFORMATION *info, QObject *parent) : AView(info, parent)
{
//    if(info->duration > 0)
//    {
//        m_timer = new QTimer(this);
//        m_timer->setSingleShot(true);
//        m_timer->start(info->duration * ONE_SEC);

//        connect(m_timer, &QTimer::timeout, this, [&]() {this->hide();}, Qt::DirectConnection);
//    }
}

CPopup::~CPopup()
{
    safeRelease(m_timer);
}

void CPopup::customizeProperties()
{
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
}

bool CPopup::event(QEvent *event)
{
    qInfo() << __FUNCTION__ << event->type();
    if (event->type() == QEvent::DynamicPropertyChange) {
        QDynamicPropertyChangeEvent *pe = static_cast<QDynamicPropertyChangeEvent *>(event);
        qInfo() << pe->propertyName();
        return true; // if you handled it and want to stop further handling
    }
    return AView::event(event); // don't forget this
}
