#ifndef CVIEWENUMS_H
#define CVIEWENUMS_H

#include <QObject>

class CViewEnums: public QObject
{
    Q_OBJECT

public:
    enum E_SCREEN_ID
    {
        E_SCREEN_ID_MIN = 0 ,
        E_SCREEN_ANY_ID     ,
        E_SCREEN_A_ID       ,
        E_SCREEN_B_ID       ,
        E_SCREEN_C_ID       ,
        E_SCREEN_ID_MAX
    };

    enum E_POPUP_ID
    {
        E_POPUP_ID_MIN = E_SCREEN_ID_MAX + 1,
        E_POPUP_ANY_ID                      ,
        E_POPUP_X_ID                        ,
        E_POPUP_Y_ID                        ,
        E_POPUP_Z_ID                        ,
        E_POPUP_ID_MAX
    };

    enum E_TOAST_ID
    {
        E_TOAST_ID_MIN = E_POPUP_ID_MAX + 1     ,
        E_TOAST_ANY_ID                          ,
        E_TOAST_SUCCESS_ID                      ,
        E_TOAST_FAIL_ID                         ,
        E_TOAST_ID_MAX
    };

    enum E_NOTIFY_ID
    {
        E_NOTIFY_ID_MIN = E_TOAST_ID_MAX + 1     ,
        E_NOTIFY_ANY_ID                          ,
        E_NOTIFY_INFO_ID                         ,
        E_NOTIFY_WARN_ID                         ,
        E_NOTIFY_ERROR_ID                        ,
        E_NOTIFY_ID_MAX
    };


    enum E_SCREEN_A_EVT
    {
        E_SCREEN_A_EVT_MIN = E_NOTIFY_ID_MAX + 1    ,
        E_SCREEN_A_EVT_SHOW                         ,
        E_SCREEN_A_EVT_BACK                         ,
        E_SCREEN_A_EVT_NAV_SCREEN_B                 ,
        E_SCREEN_A_EVT_NAV_SCREEN_C                 ,
        E_SCREEN_A_EVT_OPEN_POPUP_X                 ,
        E_SCREEN_A_EVT_MAX
    };

    enum E_SCREEN_B_EVT
    {
        E_SCREEN_B_EVT_MIN = E_SCREEN_A_EVT_MAX + 1 ,
        E_SCREEN_B_EVT_SHOW                         ,
        E_SCREEN_B_EVT_BACK                         ,
        E_SCREEN_B_EVT_NAV_SCREEN_A                 ,
        E_SCREEN_B_EVT_NAV_SCREEN_C                 ,
        E_SCREEN_B_EVT_OPEN_POPUP_X                 ,
        E_SCREEN_B_EVT_MAX
    };

    enum E_SCREEN_C_EVT
    {
        E_SCREEN_C_EVT_MIN = E_SCREEN_B_EVT_MAX + 1 ,
        E_SCREEN_C_EVT_SHOW                         ,
        E_SCREEN_C_EVT_BACK                         ,
        E_SCREEN_C_EVT_NAV_SCREEN_A                 ,
        E_SCREEN_C_EVT_NAV_SCREEN_B                 ,
        E_SCREEN_C_EVT_OPEN_POPUP_X                 ,
        E_SCREEN_C_EVT_MAX
    };

    enum E_POPUP_X_EVT
    {
        E_POPUP_X_EVT_MIN = E_SCREEN_C_EVT_MAX + 1  ,
        E_POPUP_X_EVT_SHOW                          ,
        E_POPUP_X_EVT_CANCEL                        ,
        E_POPUP_X_EVT_CONFIRM                       ,
        E_POPUP_X_EVT_OPEN_POPUP_Y                  ,
        E_POPUP_X_EVT_OPEN_POPUP_Z                  ,
        E_POPUP_X_EVT_MAX
    };

    enum E_POPUP_Y_EVT
    {
        E_POPUP_Y_EVT_MIN = E_POPUP_X_EVT_MAX + 1   ,
        E_POPUP_Y_EVT_SHOW                          ,
        E_POPUP_Y_EVT_CANCEL                        ,
        E_POPUP_Y_EVT_CONFIRM                       ,
        E_POPUP_Y_EVT_OPEN_POPUP_X                  ,
        E_POPUP_Y_EVT_OPEN_POPUP_Z                  ,
        E_POPUP_Y_EVT_MAX
    };

    enum E_POPUP_Z_EVT
    {
        E_POPUP_Z_EVT_MIN = E_POPUP_Y_EVT_MAX + 1   ,
        E_POPUP_Z_EVT_SHOW                          ,
        E_POPUP_Z_EVT_CANCEL                        ,
        E_POPUP_Z_EVT_CONFIRM                       ,
        E_POPUP_Z_EVT_OPEN_POPUP_X                  ,
        E_POPUP_Z_EVT_OPEN_POPUP_Y                  ,
        E_POPUP_Z_EVT_MAX
    };

    enum E_TOAST_SUCCESS_EVT
    {
        E_TOAST_SUCCESS_EVT_MIN = E_POPUP_Z_EVT_MAX + 1   ,
        E_TOAST_SUCCESS_EVT_SHOW                          ,
        E_TOAST_SUCCESS_EVT_HIDE                          ,
        E_TOAST_SUCCESS_EVT_MAX
    };

    enum E_TOAST_FAIL_EVT
    {
        E_TOAST_FAIL_EVT_MIN = E_TOAST_SUCCESS_EVT_MAX + 1      ,
        E_TOAST_FAIL_EVT_SHOW                                   ,
        E_TOAST_FAIL_EVT_HIDE                                   ,
        E_TOAST_FAIL_EVT_MAX
    };

    enum E_NOTIFY_INFO_EVT
    {
        E_NOTIFY_INFO_EVT_MIN = E_TOAST_FAIL_EVT_MAX + 1    ,
        E_NOTIFY_INFO_EVT_SHOW                              ,
        E_NOTIFY_INFO_EVT_REMOVE                              ,
        E_NOTIFY_INFO_EVT_MAX
    };

    enum E_NOTIFY_WARN_EVT
    {
        E_NOTIFY_WARN_EVT_MIN = E_NOTIFY_INFO_EVT_MAX + 1   ,
        E_NOTIFY_WARN_EVT_SHOW                              ,
        E_NOTIFY_WARN_EVT_REMOVE                              ,
        E_NOTIFY_WARN_EVT_MAX
    };

    enum E_NOTIFY_ERROR_EVT
    {
        E_NOTIFY_ERROR_EVT_MIN = E_NOTIFY_WARN_EVT_MAX + 1      ,
        E_NOTIFY_ERROR_EVT_SHOW                                 ,
        E_NOTIFY_ERROR_EVT_REMOVE                                 ,
        E_NOTIFY_ERROR_EVT_MAX
    };

private:
    Q_ENUM(E_SCREEN_A_EVT)
    Q_ENUM(E_SCREEN_B_EVT)
    Q_ENUM(E_SCREEN_C_EVT)

    Q_ENUM(E_POPUP_X_EVT)
    Q_ENUM(E_POPUP_Y_EVT)
    Q_ENUM(E_POPUP_Z_EVT)

    Q_ENUM(E_TOAST_SUCCESS_EVT)
    Q_ENUM(E_TOAST_FAIL_EVT)

    Q_ENUM(E_NOTIFY_INFO_EVT)
    Q_ENUM(E_NOTIFY_WARN_EVT)
    Q_ENUM(E_NOTIFY_ERROR_EVT)
};

using E_SCREEN_ID   = CViewEnums::E_SCREEN_ID;
using E_POPUP_ID    = CViewEnums::E_POPUP_ID;
using E_TOAST_ID    = CViewEnums::E_TOAST_ID;
using E_NOTIFY_ID   = CViewEnums::E_NOTIFY_ID;

#endif // CVIEWENUMS_H
