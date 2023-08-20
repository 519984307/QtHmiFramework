#include "AAnimation.h"

bool AAnimation::event(QEvent *event)
{
    Q_UNUSED(event);
    return false;
}

void AAnimation::updateState(State newState, State oldState)
{
    Q_UNUSED(newState);
    Q_UNUSED(oldState);
}

void AAnimation::updateCurrentValue(const QVariant &value)
{
    Q_UNUSED(value)
}

AAnimation::AAnimation(QObject *target, const QByteArray &propertyName, QObject *parent) :QPropertyAnimation(parent), m_target(target), m_property_name(propertyName)
{}
