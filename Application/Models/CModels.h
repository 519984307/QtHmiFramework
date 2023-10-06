#ifndef CMODELS_H
#define CMODELS_H

#include <QObject>
#include "CommonDefine.h"

BEGIN_NAMESPACE(App)
class CModels : public QObject
{
    Q_OBJECT
public:
    explicit CModels(QObject *parent = nullptr);

signals:

};
END_NAMESPACE

#endif // CMODELS_H
