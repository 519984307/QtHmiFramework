#ifndef UTILS_H
#define UTILS_H

template<class T>
inline void safeRelease(T* ptr)
{
    if(ptr == nullptr) return;
    delete ptr;
    ptr = nullptr;
}

#endif // UTILS_H
