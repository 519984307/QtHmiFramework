#include "AViewManager.h"

AViewManager::AViewManager(QObject *parent) : QObject(parent)
{}

AView *AViewManager::lastView() const
{
    return m_last_view;
}
