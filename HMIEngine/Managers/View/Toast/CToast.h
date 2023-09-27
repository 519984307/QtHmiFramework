#ifndef CTOAST_H
#define CTOAST_H

#include <CView.h>

class CToast : public CView
{
    Q_OBJECT
public:
    CToast(QQuickItem *parent = nullptr);


    // CView interface
public:
    virtual void customizeProperties() override;
};

#endif // CTOAST_H
