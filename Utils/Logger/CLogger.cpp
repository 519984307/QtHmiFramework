#include "CLogger.h"
#include "LoggerDefines.h"
#include <QJSEngine>

CLogger *CLogger::s_instance = nullptr;
CLogger *CLogger::instance(const E_LOGGER_FLAG &flag)
{
    s_instance = (s_instance == nullptr)? new CLogger(): s_instance;

    if(flag != NOFLAG)
    {
        if(flag == E_LOGGER_FLAG::QML)
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

void CLogger::qmlLogInfo(QString msg)
{
    QML_LOG_INFO(msg.toStdString().c_str());
}

void CLogger::qmlLogWarn(QString msg)
{
    QML_LOG_WARN(msg.toStdString().c_str());
}

void CLogger::qmlLogFatal(QString msg)
{
    QML_LOG_FATAL(msg.toStdString().c_str());
}

void CLogger::qmlLogDebug(QString msg)
{
    QML_LOG_DEBUG(msg.toStdString().c_str());
}

void CLogger::qmlLogError(QString msg)
{
    Q_UNUSED(msg)
//    QML_LOG_ERROR(msg.toStdString().c_str());
}

void CLogger::qmlLogTrace(QString msg)
{
    Q_UNUSED(msg)
//    QML_LOG_TRACE(msg.toStdString().c_str());
}
CLogger::CLogger(QObject *parent)
    : QObject{parent}
{

}

CLogger::~CLogger()
{

}
