#include "AViewManager.h"

AViewManager::AViewManager(QObject *parent) : QObject(parent)
{}

AView *AViewManager::last_view() const
{
    return m_last_view;
}
