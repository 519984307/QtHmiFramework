#include "CPopup.h"

CPopup::CPopup(const S_VIEW_INFORMATION *info, QQuickItem *parent) : AView(info, parent)
{}

CPopup::~CPopup()
{}

AView *CPopup::customizeProperties()
{
    CPP_LOG_INFO("[Entry]")
    qvariant_cast<QObject*>(m_properties["anchors"])->setProperty("centerIn", QVariant::fromValue(parentItem()));
    this->setProperty("z", POPUP_z);
    CPP_LOG_INFO("[Exit]")
    return this;
}
