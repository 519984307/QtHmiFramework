#ifndef CPOPUP_H
#define CPOPUP_H

#include "AView.h"

class CPopup : public AView
{
public:
    CPopup(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
};

#endif // CPOPUP_H
