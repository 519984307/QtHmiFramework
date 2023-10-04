#include "CNotify.h"

namespace HmiNgin
{
    CNotify::CNotify(QQuickItem *parent) : CView(parent)
    {
        m_str_type = __FUNCTION__;
    }

    void CNotify::customizeProperties()
    {
        CPP_LOG_DEBUG("[%s][Entry]", c_strType())
        setWidth(420);
        setHeight(50);
        QObject *position = qvariant_cast<QObject *>(m_properties["anchors"]);
        position->setProperty("horizontalCenter", QVariant::fromValue(parentItem()->property("horizontalCenter")));
        position->setProperty("top", QVariant::fromValue(parentItem()->property("top")));
        position->setProperty("topMargin", 50);
        this->setProperty("z", NOTIFY_Z);
        CPP_LOG_DEBUG("[%s][Exit]", c_strType())
    }

} // namespace HmiNgin
