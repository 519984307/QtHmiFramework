#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <string>
#include <algorithm>

template<class T>
inline void safeRelease(T* ptr)
{
    if(ptr == nullptr) return;
    delete ptr;
    ptr = nullptr;
}

// function to convert decimal to hexadecimal
template<typename T>
inline std::string decToHexa(T n)
{
    // ans string to store hexadecimal number
    std::string ans = "";

    while (n != 0) {
        // remainder variable to store remainder
        int rem = 0;

        // ch variable to store each character
        char ch;
        // storing remainder in rem variable.
        rem = n % 16;

        // check if temp < 10
        if (rem < 10) {
            ch = rem + 48;
        }
        else {
            ch = rem + 55;
        }

        // updating the ans string with the character variable
        ans += ch;
        n = n / 16;
    }

    // reversing the ans string to get the final result
    int i = 0, j = ans.size() - 1;
    while(i <= j)
    {
        std::swap(ans[i], ans[j]);
        i++;
        j--;
    }
    return ans;
}

inline std::string hexToASCII(std::string hex)
{
    // initialize the ASCII code string as empty.
    std::string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        // extract two characters from hex string
        std::string part = hex.substr(i, 2);

        // change it into base 16 and
        // typecast as the character
        char ch = stoul(part, nullptr, 16);

        // add this char to final ASCII string
        ascii += ch;
    }
    return ascii;
}

inline std::string dec64ToASCII(uint64_t dec)
{
    std::string hex = decToHexa<uint64_t>(dec);
    std::string str = hexToASCII(hex);
    return str;
}

inline const char* qstrTochars(const QString &str)
{
    return str.toStdString().c_str();
}
#endif // UTILS_H
