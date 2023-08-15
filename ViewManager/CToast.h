#ifndef CTOAST_H
#define CTOAST_H

#include "AView.h"

class CToast : public AView
{
public:
    CToast(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
};

#endif // CTOAST_H
