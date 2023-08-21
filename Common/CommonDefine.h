#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

#include <QtGlobal>
#include <string>

#define ONE_SEC 1000
#define SCREEN_Z 1
#define POPUP_z 1000
#define SIZE_OF_ARRAY(arr) sizeof(arr)/sizeof(*(arr))
#define stringify(name) # name
#ifdef Q_OS_WIN
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#elif Q_OS_UNIX
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define UNUSED(x) (void)x;

#endif // COMMONDEFINE_H
