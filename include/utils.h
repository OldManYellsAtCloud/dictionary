#ifndef UTILS_H
#define UTILS_H

#include <string>

// https://www.ascii-code.com/characters/printable-characters
#define ASCII_PRINTABLE_START 0x21
#define ASCII_PRINTABLE_END   0x7E

std::string getUnicodeSubstring(std::string s, size_t n, size_t start);
std::string getNextToken(const std::string& s, const std::string& delim, size_t& currentPosition);

#endif // UTILS_H
