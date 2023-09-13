#include "CQmlRootContainer.h"
#include <QRect>

CQmlRootContainer::CQmlRootContainer(QQuickItem *parent) : QQuickPaintedItem(parent)
{}

void CQmlRootContainer::paint(QPainter *painter)
{
    m_rect.setRect(0, 0, width(), height());
    painter->drawRect(m_rect);
    painter->fillRect(m_rect, QColor(m_color));
    update();
}

QString CQmlRootContainer::title() const
{
    return m_title;
}

void CQmlRootContainer::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString CQmlRootContainer::color() const
{
    return m_color;
}

void CQmlRootContainer::setColor(const QString &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}
