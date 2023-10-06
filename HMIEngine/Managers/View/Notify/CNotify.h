#ifndef CNOTIFY_H
#define CNOTIFY_H

#include <CView.h>

BEGIN_NAMESPACE(HmiNgin)
class CNotify : public CView
{
    Q_OBJECT
public:
    CNotify(QQuickItem *parent = nullptr);

    // CView interface
public:
    virtual void customizeProperties() override;
};
END_NAMESPACE

#endif // CNOTIFY_H
