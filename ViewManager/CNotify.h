#ifndef CNOTIFY_H
#define CNOTIFY_H

#include "CComponent.h"

class CNotify : public CComponent
{
public:
    explicit CNotify(QObject *parent = nullptr);
};

#endif // CNOTIFY_H
