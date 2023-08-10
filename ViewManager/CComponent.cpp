#include "CComponent.h"
#include "Utils.h"
#include "ViewManagerDefines.h"

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

CComponent *CComponent::setProperty(QString key, QObject *val)
{
    m_properties[key] = val;
    return this;
}

void CComponent::setPositionByAnchors(QQuickItem *parent)
{
    if(parent == nullptr) return;
    if(m_info->type == E_VIEW_TYPE::SCREEN_TYPE)
    {
        m_properties["anchors"]->setProperty("fill", QVariant::fromValue(parent));
    }
    else if(m_info->type == E_VIEW_TYPE::POPUP_TYPE)
    {
        m_properties["anchors"]->setProperty("centerIn", QVariant::fromValue(parent));
    }
    else if(m_info->type == E_VIEW_TYPE::TOAST_TYPE)
    {
        m_properties["anchors"]->setProperty("horizontalCenter", QVariant::fromValue(parent->property("horizontalCenter")));
        m_properties["anchors"]->setProperty("bottom", QVariant::fromValue(parent->property("bottom")));
        m_properties["anchors"]->setProperty("bottomMargin", TOAST_MARGIN_BOTTOM);
    }
    else if(m_info->type == E_VIEW_TYPE::NOTIFY_TYPE)
    {
        m_properties["anchors"]->setProperty("horizontalCenter", QVariant::fromValue(parent->property("horizontalCenter")));
        m_properties["anchors"]->setProperty("top", QVariant::fromValue(parent->property("top")));
        m_properties["anchors"]->setProperty("topMargin", NOTIFY_MARGIN_TOP);
    }
}
