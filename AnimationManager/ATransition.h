#ifndef ATRANSITION_H
#define ATRANSITION_H

#include <QObject>
#include "AAnimation.h"
class ATransition : public QObject
{
public:
    explicit ATransition(QObject *parent = nullptr);

protected:
    QList<AAnimation*>                  m_animations;
};

#endif // ATRANSITION_H
