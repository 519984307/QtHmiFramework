#ifndef CTOAST_H
#define CTOAST_H

#include "AView.h"

class CToast : public AView
{
public:
    CToast(const S_VIEW_INFORMATION *info, QQuickItem *parent = nullptr);

    // AView interface
public:
    virtual AView *customizeProperties() override;
};

#endif // CTOAST_H
