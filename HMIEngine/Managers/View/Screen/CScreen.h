#ifndef CSCREEN_H
#define CSCREEN_H

#include <CView.h>

namespace HmiNgin
{
    class CScreen : public CView
    {
        Q_OBJECT
    public:
        CScreen(QQuickItem *parent = nullptr);

        // CView interface
    public:
        virtual void customizeProperties() override;

        // QQuickItem interface
    protected:
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
    };

} // namespace HmiNgin

#endif // CSCREEN_H
