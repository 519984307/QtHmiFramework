#ifndef LOGGERDEFINES_H
#define LOGGERDEFINES_H

#include <QDebug>
#include "CLogger.h"

#define __LOG_INFO__    qInfo()
#define __LOG_WARN__    qWarning()
#define __LOG_FATAL__   qFatal()
#define __LOG_DEBUG__   qDebug()

#define CPP_LOG_INFO(message, ...) CLogger::instance(E_LOGGER_FLAG::CPP)->log(E_LOGGER_LEVEL::INFO, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define CPP_LOG_WARN(message, ...) CLogger::instance(E_LOGGER_FLAG::CPP)->log(E_LOGGER_LEVEL::WARN, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define CPP_LOG_FATAL(message, ...) CLogger::instance(E_LOGGER_FLAG::CPP)->log(E_LOGGER_LEVEL::FATAL, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define CPP_LOG_DEBUG(message, ...) CLogger::instance(E_LOGGER_FLAG::CPP)->log(E_LOGGER_LEVEL::DEBUG, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define QML_LOG_INFO(message, ...) CLogger::instance(E_LOGGER_FLAG::QML)->log(E_LOGGER_LEVEL::INFO, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define QML_LOG_WARN(message, ...) CLogger::instance(E_LOGGER_FLAG::QML)->log(E_LOGGER_LEVEL::WARN, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define QML_LOG_FATAL(message, ...) CLogger::instance(E_LOGGER_FLAG::QML)->log(E_LOGGER_LEVEL::FATAL, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#define QML_LOG_DEBUG(message, ...) CLogger::instance(E_LOGGER_FLAG::QML)->log(E_LOGGER_LEVEL::DEBUG, __FILE__, __FUNCTION__, __LINE__, message, ##__VA_ARGS__)

#endif // LOGGERDEFINES_H
