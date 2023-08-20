#ifndef CSCREENTRANSITIONS_H
#define CSCREENTRANSITIONS_H

#include <QObject>
#include "ATransition.h"

class CScreenTransitions: public ATransition
{
public:
    explicit CScreenTransitions(QObject *parent = nullptr);
    void pushEnter();
    void popExit();
};

#endif // CSCREENTRANSITIONS_H
