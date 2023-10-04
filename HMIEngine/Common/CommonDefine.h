#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

#include <QtSystemDetection>
#include <QtGlobal>
#include <string>

#define ONE_SEC 1000

#define SCREEN_Z 1
#define POPUP_z 1000
#define NOTIFY_Z 1000000


#define SIZE_OF_ARRAY(arr) sizeof(arr)/sizeof(*(arr))
#define stringify(name) # name


#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#elif __unix
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifdef _WIN32
#define __MAIN_WINDOW_WIDTH__ 640
#define __MAIN_WINDOW_HEIGHT__ 720
#elif __ANDROID__
#define __MAIN_WINDOW_WIDTH__ 480
#define __MAIN_WINDOW_HEIGHT__ 640
#endif

#define DECLARE_SCREEN_INFO(NAME) \
static const HmiNgin::S_VIEW_INFORMATION NAME##_INFORMATION = { E_SCREEN_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, HmiNgin::E_DURATION::NONE, HmiNgin::E_VIEW_TYPE::SCREEN_TYPE, NAME };
#define DECLARE_POPUP_INFO(NAME, DURATION) \
static const HmiNgin::S_VIEW_INFORMATION NAME##_INFORMATION = { E_POPUP_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, HmiNgin::E_VIEW_TYPE::POPUP_TYPE, NAME };
#define DECLARE_TOAST_INFO(NAME, DURATION) \
static const HmiNgin::S_VIEW_INFORMATION NAME##_INFORMATION = { E_TOAST_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, HmiNgin::E_VIEW_TYPE::TOAST_TYPE, NAME };
#define DECLARE_NOTIFY_INFO(NAME, DURATION) \
static const HmiNgin::S_VIEW_INFORMATION NAME##_INFORMATION = { E_NOTIFY_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, HmiNgin::E_VIEW_TYPE::NOTIFY_TYPE, NAME };

#define DECLARE_FUNC_STATE(NAME) \
    void NAME##_ENTRY(); \
    void NAME##_BACK(); \
    void NAME##_EXIT();

#define DEFINE_EMPTY_FUNC_STATE(NAME) \
    inline void NAME##_ENTRY(){} \
    inline void NAME##_BACK(){} \
    inline void NAME##_EXIT(){}


#define EVENT_REGISTER_LISTENER_NO_ARG(SPACE, INS,LISTENER, EVENT) \
    m_##LISTENER##CallBack = std::bind(&SPACE::on##LISTENER, INS);\
    CEventManager::instance()->registerListener(EVENT, m_##LISTENER##CallBack);

#define EVENT_REGISTER_LISTENER_1_ARG(SPACE, INS, LISTENER, EVENT) \
    m_##LISTENER##CallBack = std::bind(&SPACE::on##LISTENER, INS, std::placeholders::_1);\
    CEventManager::instance()->registerListener(EVENT, m_##LISTENER##CallBack);

#define EVENT_REGISTER_LISTENER_2_ARGS(SPACE, INS, LISTENER, EVENT) \
    m_##LISTENER##CallBack = std::bind(&SPACE::on##LISTENER, INS, std::placeholders::_1, std::placeholders::_2);\
    CEventManager::instance()->registerListener(EVENT, m_##LISTENER##CallBack);

#define EVENT_REGISTER_LISTENER_N_ARGS(SPACE, INS, LISTENER, EVENT, ...) \
    m_##LISTENER##CallBack = std::bind(&SPACE::on##LISTENER, INS, __VA_ARGS__ ); \
    CEventManager::instance()->registerListener(EVENT, m_##LISTENER##CallBack);

#define UNUSED(x) (void)x;


#endif // COMMONDEFINE_H
