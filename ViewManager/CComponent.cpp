#include "CComponent.h"
#include "Utils.h"

CComponent::CComponent(QObject *parent):QObject{parent} {
}

CComponent::~CComponent()
{
}

const S_VIEW_INFORMATION *CComponent::info() const
{
    return m_info;
}

void CComponent::setInfo(const S_VIEW_INFORMATION *info)
{
    m_info = info;
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
