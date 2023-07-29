#include "ViewStates.h"
#include "Logger/LoggerDefines.h"

void SCREEN_A_ENTRY() { CPP_LOG_INFO("[ENTRY][SCREEN A]");}
void SCREEN_A_BACK() { CPP_LOG_INFO("[BACK][SCREEN A]");}
void SCREEN_A_EXIT() { CPP_LOG_INFO("[EXIT][SCREEN A]");}

void SCREEN_B_ENTRY() { CPP_LOG_INFO("[ENTRY][SCREEN B]");}
void SCREEN_B_BACK() { CPP_LOG_INFO("[BACK][SCREEN B]");}
void SCREEN_B_EXIT() { CPP_LOG_INFO("[EXIT][SCREEN B]");}

void SCREEN_C_ENTRY() { CPP_LOG_INFO("[ENTRY][SCREEN C]");}
void SCREEN_C_BACK() { CPP_LOG_INFO("[BACK][SCREEN C]");}
void SCREEN_C_EXIT() { CPP_LOG_INFO("[EXIT][SCREEN C]");}

void POPUP_X_ENTRY() { CPP_LOG_INFO("[ENTRY][POPUP X]");}
void POPUP_X_BACK() { CPP_LOG_INFO("[BACK][POPUP X]");}
void POPUP_X_EXIT() { CPP_LOG_INFO("[EXIT][POPUP X]");}

void POPUP_Y_ENTRY() { CPP_LOG_INFO("[ENTRY][POPUP Y]");}
void POPUP_Y_BACK() { CPP_LOG_INFO("[BACK][POPUP Y]");}
void POPUP_Y_EXIT() { CPP_LOG_INFO("[EXIT][POPUP Y]");}

void POPUP_Z_ENTRY() { CPP_LOG_INFO("[ENTRY][POPUP Z]");}
void POPUP_Z_BACK() { CPP_LOG_INFO("[BACK][POPUP Z]");}
void POPUP_Z_EXIT() { CPP_LOG_INFO("[EXIT][POPUP Z]");}

void TOAST_SUCCESS_ENTRY() {}
void TOAST_SUCCESS_BACK() {}
void TOAST_SUCCESS_EXIT() {}

void TOAST_FAIL_ENTRY() {}
void TOAST_FAIL_BACK() {}
void TOAST_FAIL_EXIT() {}

void NOTIFY_INFO_ENTRY() {}
void NOTIFY_INFO_BACK() {}
void NOTIFY_INFO_EXIT() {}

void NOTIFY_WARN_ENTRY() {}
void NOTIFY_WARN_BACK() {}
void NOTIFY_WARN_EXIT() {}

void NOTIFY_ERROR_ENTRY() {}
void NOTIFY_ERROR_BACK() {}
void NOTIFY_ERROR_EXIT() {}
