#include "CLogger.h"

CLogger *CLogger::s_instance = nullptr;
CLogger *CLogger::instance(const E_LOGGER_FLAG &flag)
{
    s_instance = (s_instance == nullptr)? new CLogger(): s_instance;
    s_instance->m_flag = flag;
    return s_instance;
}

CLogger::CLogger(QObject *parent)
    : QObject{parent}
{

}

CLogger::~CLogger()
{

}
