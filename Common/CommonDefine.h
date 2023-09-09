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
#define __MAIN_WINDOW_WIDTH__ 640
#define __MAIN_WINDOW_HEIGHT__ 720

#elif __unix
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __MAIN_WINDOW_WIDTH__ 480
#define __MAIN_WINDOW_HEIGHT__ 640
#endif

#define UNUSED(x) (void)x;

#endif // COMMONDEFINE_H
