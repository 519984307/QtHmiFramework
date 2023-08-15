#ifndef CNOTIFY_H
#define CNOTIFY_H

#include "AView.h"

class CNotify : public AView
{
public:
    CNotify(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
};

#endif // CNOTIFY_H
