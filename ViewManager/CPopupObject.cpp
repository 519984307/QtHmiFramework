#include "CPopupObject.h"
#include "Utils.h"

CPopupObject::CPopupObject(QObject *parent)
    : QObject{parent}
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &CPopupObject::onPopupTimeout);
}

CPopupObject::~CPopupObject()
{
    safeRelease(m_timer);
}

void CPopupObject::setData(const S_VIEW_INFORMATION *view)
{
    m_info = view;
    m_timer->setInterval(view->duration * 1000);
}

void CPopupObject::setDuration(uint32_t milliseconds)
{
    m_timer->setInterval(milliseconds);
}

void CPopupObject::show()
{
    m_timer->start();
}

void CPopupObject::close()
{
    m_timer->stop();
}

void CPopupObject::onPopupTimeout()
{
    close();
}
