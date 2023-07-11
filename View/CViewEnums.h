#ifndef CVIEWENUMS_H
#define CVIEWENUMS_H

#include <QObject>

class CViewEnums: public QObject
{
    Q_OBJECT
    Q_ENUMS(E_SCREEN_A_EVT)
    Q_ENUMS(E_SCREEN_B_EVT)
    Q_ENUMS(E_SCREEN_C_EVT)

    Q_ENUMS(E_POPUP_X_EVT)
    Q_ENUMS(E_POPUP_Y_EVT)
    Q_ENUMS(E_POPUP_Z_EVT)

public:

    enum E_SCREEN_ID
    {
        E_SCREEN_ID_MIN = 0 ,
        E_SCREEN_A_ID       ,
        E_SCREEN_B_ID       ,
        E_SCREEN_C_ID       ,
        E_SCREEN_ID_MAX
    };

    enum E_POPUP_ID
    {
        E_POPUP_ID_MIN = E_SCREEN_ID_MAX + 1,
        E_POPUP_X_ID                        ,
        E_POPUP_Y_ID                        ,
        E_POPUP_Z_ID                        ,
        E_POPUP_ID_MAX
    };


    enum E_SCREEN_A_EVT
    {
        E_SCREEN_A_EVT_MIN = E_POPUP_ID_MAX + 1 ,
        E_SCREEN_A_EVT_SHOW                     ,
        E_SCREEN_A_EVT_NAV_SCREEN_B             ,
        E_SCREEN_A_EVT_NAV_SCREEN_C             ,
        E_SCREEN_A_EVT_OPEN_POPUP_X             ,
        E_SCREEN_A_EVT_MAX
    };

    enum E_SCREEN_B_EVT
    {
        E_SCREEN_B_EVT_MIN = E_SCREEN_A_EVT_MAX + 1 ,
        E_SCREEN_B_EVT_SHOW                         ,
        E_SCREEN_B_EVT_NAV_SCREEN_A                 ,
        E_SCREEN_B_EVT_NAV_SCREEN_C                 ,
        E_SCREEN_B_EVT_OPEN_POPUP_X                 ,
        E_SCREEN_B_EVT_MAX
    };

    enum E_SCREEN_C_EVT
    {
        E_SCREEN_C_EVT_MIN = E_SCREEN_B_EVT_MAX + 1 ,
        E_SCREEN_C_EVT_SHOW                         ,
        E_SCREEN_C_EVT_NAV_SCREEN_A                 ,
        E_SCREEN_C_EVT_NAV_SCREEN_B                 ,
        E_SCREEN_C_EVT_OPEN_POPUP_X                 ,
        E_SCREEN_C_EVT_MAX
    };

    enum E_POPUP_X_EVT
    {
        E_POPUP_X_EVT_MIN = E_SCREEN_C_EVT_MAX + 1  ,
        E_POPUP_X_EVT_SHOW                          ,
        E_POPUP_X_EVT_NAV_SCREEN_A                  ,
        E_POPUP_X_EVT_MAX
    };

    enum E_POPUP_Y_EVT
    {
        E_POPUP_Y_EVT_MIN = E_POPUP_X_EVT_MAX + 1   ,
        E_POPUP_Y_EVT_SHOW                          ,
        E_POPUP_Y_EVT_NAV_SCREEN_B                  ,
        E_POPUP_Y_EVT_MAX
    };

    enum E_POPUP_Z_EVT
    {
        E_POPUP_Z_EVT_MIN = E_POPUP_Y_EVT_MAX + 1  ,
        E_POPUP_Z_EVT_SHOW                          ,
        E_POPUP_Z_EVT_NAV_SCREEN_C                  ,
        E_POPUP_Z_EVT_MAX
    };


};

using E_SCREEN_ID = CViewEnums::E_SCREEN_ID;
using E_POPUP_ID  = CViewEnums::E_POPUP_ID;




#endif // CVIEWENUMS_H
