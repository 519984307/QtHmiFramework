#include "CLogger.h"

CLogger *CLogger::s_instance = nullptr;
CLogger *CLogger::instance(const E_LOGGER_FLAG &flag)
{
    s_instance = (s_instance == nullptr)? new CLogger(): s_instance;
    s_instance->m_flag = flag;
    return s_instance;
}

void CLogger::selectQtLog(const uint64_t &fn, const char *msg)
{
    switch (fn) {
    case E_LOGGER_LEVEL::FATAL:
        qFatal() << msg;
        break;
    case E_LOGGER_LEVEL::INFO:
        qInfo() << msg;
        break;
    case E_LOGGER_LEVEL::WARN:
        qWarning() << msg;
        break;
    case E_LOGGER_LEVEL::DEBUG:
        qDebug() << msg;
        break;
    default:
        break;
    }
}

CLogger::CLogger(QObject *parent)
    : QObject{parent}
{

}

CLogger::~CLogger()
{

}
