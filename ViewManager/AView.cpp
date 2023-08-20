#include "AView.h"
#include "Utils.h"

AView::AView(const S_VIEW_INFORMATION *info, QObject *parent):QObject{parent}
{
    m_info = info;

    initConnections();
}

AView::~AView()
{
}

QQuickItem *AView::parentItem() const
{
    return m_item->parentItem();
}

AView * AView::initialize(QQuickItem *item)
{
    m_item = item;
    readProperties();
    return this;
}

void AView::readProperties()
{
    m_properties["x"]           = m_item->property("x").toReal();
    m_properties["y"]           = m_item->property("y").toReal();
    m_properties["z"]           = m_item->property("z").toReal();
    m_properties["width"]       = m_item->property("width").toReal();
    m_properties["height"]      = m_item->property("height").toReal();
    m_properties["anchors"]     = m_item->property("anchors");
}

QQuickItem *AView::item() const
{
    return m_item;
}

void AView::initConnections()
{
}
