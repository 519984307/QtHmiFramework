#ifndef CNOTIFY_H
#define CNOTIFY_H

#include <CView.h>

namespace HmiNgin
{
    class CNotify : public CView
    {
        Q_OBJECT
    public:
        CNotify(QQuickItem *parent = nullptr);

        // CView interface
    public:
        virtual void customizeProperties() override;
    };
} // namespace HmiNgin

#endif // CNOTIFY_H
