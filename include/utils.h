#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "entry.h"

std::string getUnicodeSubstring(std::string s, size_t n, size_t start);
std::string getNextToken(const std::string& s, const std::string& delim, size_t& currentPosition);
DictionaryEntry::EntryType parseEntryType(std::string s);
std::string toLowerCase(std::string s);
#endif // UTILS_H
