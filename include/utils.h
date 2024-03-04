#ifndef UTILS_H
#define UTILS_H
#include <string>

std::string getUnicodeSubstring(std::string s, size_t n, size_t start){
    std::string ret;
    const char* sChr = s.c_str();
    size_t byteCounter = 0;
    size_t charCounter = 0;
    while ( charCounter < n && *sChr){
        if ((*sChr++ & 0xc0) != 0x80){
            ++charCounter;
        }
        ++byteCounter;
    }
    return s.substr(start, byteCounter);
}

#endif // UTILS_H
