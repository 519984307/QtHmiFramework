#ifndef __IANIMATION_H__
#define __IANIMATION_H__

#include "CommonDefine.h"

BEGIN_NAMESPACE(HmiNgin)
class IAnimation
{
public:
    virtual void pause() = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
};
END_NAMESPACE

#endif // __IANIMATION_H__