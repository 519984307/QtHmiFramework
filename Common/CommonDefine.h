#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

#include <string.h>

#define SIZE_OF_ARRAY(arr) sizeof(arr)/sizeof(*(arr))
#define stringify(name) # name
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#endif // COMMONDEFINE_H
