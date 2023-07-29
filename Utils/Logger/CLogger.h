#ifndef CLOGGER_H
#define CLOGGER_H

#include <QObject>
#include <string>
#include <QDebug>
#include <mutex>
#include <thread>
#include "Utils.h"
#include "CommonEnums.h"

class CLogger : public QObject
{
    Q_OBJECT
public:
    static CLogger *instance(const E_LOGGER_FLAG &flag = E_LOGGER_FLAG::CPP);

    template<typename ...TArgs>
    void log(const E_LOGGER_LEVEL& level, const char* file, const char* fn, const uint32_t& line, const char* fm, TArgs... args)
    {
        std::string flag = dec64ToASCII(m_flag);
        std::string lv  = dec64ToASCII(level);
        std::string func = "on" + lv + "Invoked";

        time_t now = time(nullptr);
        tm *localTime = localtime(&now);
        char time_str[100];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localTime);

        QString info = QString("[%1][%2][%3][fn: %4, line: %5] >>>>> ")
                           .arg(time_str)
                           .arg(flag.c_str())
                           .arg(lv.c_str())
                           .arg(fn)
                           .arg(line);

        int size_s = std::snprintf( nullptr, 0, fm, args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, fm, args ... );
        std::string message = info.toStdString() + std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
        selectQtLog(level, message.c_str());
    }

    void selectQtLog(const uint64_t&, const char*);

private:
    explicit CLogger(QObject *parent = nullptr);
    ~CLogger();

private:
    static CLogger  *s_instance;
    E_LOGGER_FLAG    m_flag = E_LOGGER_FLAG::CPP;
    std::mutex       m_mutex;
};


#endif // CLOGGER_H
