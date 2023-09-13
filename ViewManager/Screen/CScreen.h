#ifndef CSCREEN_H
#define CSCREEN_H

#include "AView.h"
class CScreen : public AView
{
    Q_OBJECT
public:
    CScreen(const S_VIEW_INFORMATION *info, QQuickItem *parent = nullptr);

    // AView interface
public:
    virtual AView *customizeProperties() override;


};

#endif // CSCREEN_H
