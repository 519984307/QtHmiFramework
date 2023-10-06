#ifndef CTOAST_H
#define CTOAST_H

#include <CView.h>

BEGIN_NAMESPACE(HmiNgin)
    class CToast : public CView
    {
        Q_OBJECT
    public:
        CToast(QQuickItem *parent = nullptr);

        // CView interface
    public:
        virtual void customizeProperties() override;
    };

END_NAMESPACE

#endif // CTOAST_H
