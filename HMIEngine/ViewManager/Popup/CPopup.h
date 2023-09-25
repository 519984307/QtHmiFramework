#ifndef CPOPUP_H
#define CPOPUP_H

#include <CView.h>

class CPopup : public CView
{
    Q_OBJECT
public:
    CPopup(QQuickItem *parent = nullptr);

    // CView interface
public:
    virtual CView *customizeProperties() override;

    // QQuickItem interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CPOPUP_H
