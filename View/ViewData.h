#ifndef VIEWDATA_H
#define VIEWDATA_H

#include "Common.h"
#include "ViewStates.h"
#include "CViewEnums.h"
#include "ViewDefines.h"

#define DECLARE_SCREEN_INFO(NAME) \
    static const S_VIEW_INFORMATION NAME##_INFORMATION = { E_SCREEN_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, E_DURATION::NONE, E_VIEW_TYPE::SCREEN_TYPE, NAME };
#define DECLARE_POPUP_INFO(NAME, DURATION) \
    static const S_VIEW_INFORMATION NAME##_INFORMATION = { E_POPUP_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, E_VIEW_TYPE::POPUP_TYPE, NAME };
#define DECLARE_TOAST_INFO(NAME, DURATION) \
    static const S_VIEW_INFORMATION NAME##_INFORMATION = { E_TOAST_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, E_VIEW_TYPE::TOAST_TYPE, NAME };
#define DECLARE_NOTIFY_INFO(NAME, DURATION) \
    static const S_VIEW_INFORMATION NAME##_INFORMATION = { E_NOTIFY_ID::E_##NAME##_ID, &NAME##_ENTRY, &NAME##_EXIT, DURATION, E_VIEW_TYPE::NOTIFY_TYPE, NAME };

// [screens]
DECLARE_SCREEN_INFO(SCREEN_A);
DECLARE_SCREEN_INFO(SCREEN_B);
DECLARE_SCREEN_INFO(SCREEN_C);

// [popups]
DECLARE_POPUP_INFO(POPUP_X, E_DURATION::IN_2_SECS)
DECLARE_POPUP_INFO(POPUP_Y, E_DURATION::IN_5_SECS)
DECLARE_POPUP_INFO(POPUP_Z, E_DURATION::NONE)

// [toast]
DECLARE_TOAST_INFO(TOAST_SUCCESS, E_DURATION::IN_2_SECS)
DECLARE_TOAST_INFO(TOAST_FAIL, E_DURATION::IN_2_SECS)

// [notify]
DECLARE_NOTIFY_INFO(NOTIFY_INFO, E_DURATION::IN_5_SECS)
DECLARE_NOTIFY_INFO(NOTIFY_WARN, E_DURATION::IN_10_SECS)
DECLARE_NOTIFY_INFO(NOTIFY_ERROR, E_DURATION::IN_2_SECS)


static const S_VIEW_INFORMATION ALL_INFOR[11] = {
    SCREEN_A_INFORMATION,
    SCREEN_B_INFORMATION,
    SCREEN_C_INFORMATION,
    POPUP_X_INFORMATION,
    POPUP_Y_INFORMATION,
    POPUP_Z_INFORMATION,
    TOAST_SUCCESS_INFORMATION,
    TOAST_FAIL_INFORMATION,
    NOTIFY_INFO_INFORMATION,
    NOTIFY_WARN_INFORMATION,
    NOTIFY_ERROR_INFORMATION,
};

static const S_VIEW_EVENT  ALL_EVENTS[] = {
    // [screen A]
    {E_SCREEN_ID::E_SCREEN_A_ID, CViewEnums::E_SCREEN_A_EVT_SHOW, &SCREEN_A_ENTRY, E_SCREEN_ID::E_SCREEN_A_ID},
    {E_SCREEN_ID::E_SCREEN_A_ID, CViewEnums::E_SCREEN_A_EVT_BACK, &SCREEN_A_BACK, E_SCREEN_ID::E_SCREEN_ANY_ID},
    {E_SCREEN_ID::E_SCREEN_A_ID, CViewEnums::E_SCREEN_A_EVT_NAV_SCREEN_B, &SCREEN_B_ENTRY, E_SCREEN_ID::E_SCREEN_B_ID},
    {E_SCREEN_ID::E_SCREEN_A_ID, CViewEnums::E_SCREEN_A_EVT_NAV_SCREEN_C, &SCREEN_C_ENTRY, E_SCREEN_ID::E_SCREEN_C_ID},
    {E_SCREEN_ID::E_SCREEN_A_ID, CViewEnums::E_SCREEN_A_EVT_OPEN_POPUP_X, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    // [screen B]
    {E_SCREEN_ID::E_SCREEN_B_ID, CViewEnums::E_SCREEN_B_EVT_SHOW, &SCREEN_B_ENTRY, E_SCREEN_ID::E_SCREEN_B_ID},
    {E_SCREEN_ID::E_SCREEN_B_ID, CViewEnums::E_SCREEN_B_EVT_BACK, &SCREEN_B_BACK, E_SCREEN_ID::E_SCREEN_ANY_ID},
    {E_SCREEN_ID::E_SCREEN_B_ID, CViewEnums::E_SCREEN_B_EVT_NAV_SCREEN_A, &SCREEN_A_ENTRY, E_SCREEN_ID::E_SCREEN_A_ID},
    {E_SCREEN_ID::E_SCREEN_B_ID, CViewEnums::E_SCREEN_B_EVT_NAV_SCREEN_C, &SCREEN_C_ENTRY, E_SCREEN_ID::E_SCREEN_C_ID},
    {E_SCREEN_ID::E_SCREEN_B_ID, CViewEnums::E_SCREEN_B_EVT_OPEN_POPUP_X, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    // [screen C]
    {E_SCREEN_ID::E_SCREEN_C_ID, CViewEnums::E_SCREEN_C_EVT_SHOW, &SCREEN_C_ENTRY, E_SCREEN_ID::E_SCREEN_C_ID},
    {E_SCREEN_ID::E_SCREEN_C_ID, CViewEnums::E_SCREEN_C_EVT_BACK, &SCREEN_C_BACK, E_SCREEN_ID::E_SCREEN_ANY_ID},
    {E_SCREEN_ID::E_SCREEN_C_ID, CViewEnums::E_SCREEN_C_EVT_NAV_SCREEN_A, &SCREEN_A_ENTRY, E_SCREEN_ID::E_SCREEN_A_ID},
    {E_SCREEN_ID::E_SCREEN_C_ID, CViewEnums::E_SCREEN_C_EVT_NAV_SCREEN_B, &SCREEN_B_ENTRY, E_SCREEN_ID::E_SCREEN_B_ID},
    {E_SCREEN_ID::E_SCREEN_C_ID, CViewEnums::E_SCREEN_C_EVT_OPEN_POPUP_X, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    // [popup X]
    {E_POPUP_ID::E_POPUP_X_ID, CViewEnums::E_POPUP_X_EVT_SHOW, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    {E_POPUP_ID::E_POPUP_X_ID, CViewEnums::E_POPUP_X_EVT_CONFIRM, &NOTIFY_ERROR_ENTRY, E_TOAST_ID::E_TOAST_SUCCESS_ID},
    {E_POPUP_ID::E_POPUP_X_ID, CViewEnums::E_POPUP_X_EVT_CANCEL, &POPUP_X_BACK, E_POPUP_ID::E_POPUP_ANY_ID},
    {E_POPUP_ID::E_POPUP_X_ID, CViewEnums::E_POPUP_X_EVT_OPEN_POPUP_Y, &POPUP_Y_ENTRY, E_POPUP_ID::E_POPUP_Y_ID},
    {E_POPUP_ID::E_POPUP_X_ID, CViewEnums::E_POPUP_X_EVT_OPEN_POPUP_Z, &POPUP_Z_ENTRY, E_POPUP_ID::E_POPUP_Z_ID},
    // [popup Y]
    {E_POPUP_ID::E_POPUP_Y_ID, CViewEnums::E_POPUP_Y_EVT_SHOW, &POPUP_Y_ENTRY, E_POPUP_ID::E_POPUP_Y_ID},
    {E_POPUP_ID::E_POPUP_Y_ID, CViewEnums::E_POPUP_Y_EVT_CANCEL, &POPUP_Y_BACK, E_POPUP_ID::E_POPUP_ANY_ID},
    {E_POPUP_ID::E_POPUP_Y_ID, CViewEnums::E_POPUP_Y_EVT_OPEN_POPUP_X, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    {E_POPUP_ID::E_POPUP_Y_ID, CViewEnums::E_POPUP_Y_EVT_OPEN_POPUP_Z, &POPUP_Z_ENTRY, E_POPUP_ID::E_POPUP_Z_ID},
    // [popup Z]
    {E_POPUP_ID::E_POPUP_Z_ID, CViewEnums::E_POPUP_Z_EVT_SHOW, &POPUP_Z_ENTRY, E_POPUP_ID::E_POPUP_Z_ID},
    {E_POPUP_ID::E_POPUP_Z_ID, CViewEnums::E_POPUP_Z_EVT_CANCEL, &POPUP_Z_BACK, E_POPUP_ID::E_POPUP_ANY_ID},
    {E_POPUP_ID::E_POPUP_Z_ID, CViewEnums::E_POPUP_Z_EVT_OPEN_POPUP_X, &POPUP_X_ENTRY, E_POPUP_ID::E_POPUP_X_ID},
    {E_POPUP_ID::E_POPUP_Z_ID, CViewEnums::E_POPUP_Z_EVT_OPEN_POPUP_Y, &POPUP_Y_ENTRY, E_POPUP_ID::E_POPUP_Y_ID}
};

#endif // VIEWDATA_H
