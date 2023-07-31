#ifndef CTOAST_H
#define CTOAST_H

#include "CComponent.h"

class CToast : public CComponent
{
public:
    explicit CToast(QObject *parent = nullptr);
};

#endif // CTOAST_H
