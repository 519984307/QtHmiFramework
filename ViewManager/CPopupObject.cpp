#include "CPopupObject.h"
#include "Utils.h"

CPopupObject::CPopupObject(const S_VIEW_INFORMATION *view,
                           QQmlApplicationEngine *ngin,
                           QObject *parent) : QQmlComponent(ngin, view->path, parent)
{
    m_ngin = ngin;
    m_info = view;
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(m_info->duration * 1000);
    connect(m_timer, &QTimer::timeout, this, [&](){
        // exit
    });
}

CPopupObject::~CPopupObject()
{
    safeRelease(m_timer);
}

