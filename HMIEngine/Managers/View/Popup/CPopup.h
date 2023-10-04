#ifndef CPOPUP_H
#define CPOPUP_H

#include <CView.h>

namespace HmiNgin
{
    class CPopup : public CView
    {
        Q_OBJECT
    public:
        CPopup(QQuickItem *parent = nullptr);

        // CView interface
    public:
        virtual void customizeProperties() override;
        virtual void completed() override;

        // QQuickItem interface
    protected:
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        E_POPUP_PRIORITY_LEVEL m_priority_level;
    };

} // namespace HmiNgin

#endif // CPOPUP_H
