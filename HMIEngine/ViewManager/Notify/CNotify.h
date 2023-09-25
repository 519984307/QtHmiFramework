#ifndef CNOTIFY_H
#define CNOTIFY_H

#include <CView.h>

class CNotify : public CView
{
    Q_OBJECT
public:
    CNotify(QQuickItem *parent = nullptr);

    // CView interface
public:
    virtual CView *customizeProperties() override;
};

#endif // CNOTIFY_H
