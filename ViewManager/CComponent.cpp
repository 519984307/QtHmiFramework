#include "CComponent.h"
#include "Utils.h"

CComponent::CComponent(const S_VIEW_INFORMATION *info, QQuickItem *item, QObject *parent)
    : QObject{parent}
{
    m_info = info;
    m_item = item;
    m_timer= new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &CComponent::onVisibleTimeout);
}

CComponent::~CComponent()
{
    safeRelease(m_timer);
}

const S_VIEW_INFORMATION *CComponent::info() const
{
    return m_info;
}

QQuickItem *CComponent::item() const
{
    return m_item;
}

void CComponent::setItem(QQuickItem *newItem)
{
    m_item = newItem;
}

QHash<QString, QObject *> CComponent::properties() const
{
    return m_properties;
}

void CComponent::setProperty(QString key, QObject *val)
{
    m_properties[key] = val;
}

void CComponent::onVisibleTimeout()
{
    emit visibleTimeout();
}


