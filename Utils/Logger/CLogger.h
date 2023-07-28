#ifndef CLOGGER_H
#define CLOGGER_H

#include <QObject>
#include "CommonEnums.h"

class CLogger : public QObject
{
    Q_OBJECT
public:
    static CLogger *instance(const E_LOGGER_FLAG &);

signals:

private:
    explicit CLogger(QObject *parent = nullptr);
    ~CLogger();

private:
    static CLogger  *s_instance;
    E_LOGGER_FLAG    m_flag = E_LOGGER_FLAG::CPP;
};

#endif // CLOGGER_H
