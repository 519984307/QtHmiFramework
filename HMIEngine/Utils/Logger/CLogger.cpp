#include "CLogger.h"
#include "LoggerDefines.h"

CLogger *CLogger::s_instance = nullptr;
CLogger *CLogger::instance(const HmiNgin::E_LOGGER_FLAG &flag)
{
    s_instance = (s_instance == nullptr)? new CLogger(): s_instance;

    if(flag != HmiNgin::E_LOGGER_FLAG::NOFLAG)
    {
        if(flag == HmiNgin::E_LOGGER_FLAG::QML)
        {
            QJSEngine::setObjectOwnership(s_instance, QJSEngine::JavaScriptOwnership);
        }
        s_instance->m_flag = flag;
    }

    return s_instance;
}

void CLogger::selectQtLog(const uint64_t &fn, const char *msg)
{
    switch (fn) {
    case HmiNgin::E_LOGGER_LEVEL::FATAL:
        qFatal() << msg;
        break;
    case HmiNgin::E_LOGGER_LEVEL::INFO:
        qInfo() << msg;
        break;
    case HmiNgin::E_LOGGER_LEVEL::WARN:
        qWarning() << msg;
        break;
    case HmiNgin::E_LOGGER_LEVEL::DEBUG:
        qDebug() << msg;
        break;
    default:
        break;
    }
}

CLogger::CLogger(QObject *parent)
    : QObject{parent}
{}

CLogger::~CLogger()
{}
