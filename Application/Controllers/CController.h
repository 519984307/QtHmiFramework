#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include <QObject>
#include "CommonDefine.h"

BEGIN_NAMESPACE(App)
class CController : public QObject
{
    Q_OBJECT
public:
    explicit CController(QObject *parent = nullptr);

signals:

};
END_NAMESPACE

#endif // CCONTROLLER_H
