#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include <QObject>

class CController : public QObject
{
    Q_OBJECT
public:
    explicit CController(QObject *parent = nullptr);

signals:

};

#endif // CCONTROLLER_H
