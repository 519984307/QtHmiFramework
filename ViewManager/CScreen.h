#ifndef CSCREEN_H
#define CSCREEN_H

#include "AView.h"

class CScreen : public AView
{
    Q_OBJECT
public:
    CScreen(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);

    // AView interface
public:
    virtual void customizeProperties() override;
};

#endif // CSCREEN_H
