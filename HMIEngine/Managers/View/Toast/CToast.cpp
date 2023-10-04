#include "CToast.h"

namespace HmiNgin
{
    CToast::CToast(QQuickItem *parent) : CView(parent)
    {
        m_str_type = __FUNCTION__;
    }

    void CToast::customizeProperties()
    {
        CPP_LOG_DEBUG("[%s][Entry]", c_strType())
        setWidth(340);
        setHeight(30);
        QObject *position = qvariant_cast<QObject *>(m_properties["anchors"]);
        position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
        position->setProperty("bottom", QVariant::fromValue(parentItem()->property("bottom")));
        position->setProperty("bottomMargin", 50);
        this->setProperty("z", NOTIFY_Z);
        CPP_LOG_DEBUG("[%s][Exit]", c_strType())
    }

} // namespace HmiNgin
