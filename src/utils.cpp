#include "utils.h"
#include <loglibrary.h>
#include <unicode/unistr.h>
#include <algorithm>

/**
 * @brief getUnicodeSubstring
 * Strings with Unicode encoding require special handling, when it
 * comes to operations involving the length of the string due to
 * multibyte characters. This helper returns a substring of a Unicode
 * string.
 * @param s
 * The Unicode string.
 * @param n
 * The number of charecters to return.
 * @param start
 * The start of the substring.
 * @return
 * The substring between position `n` and `n+s`.
 */
std::string getUnicodeSubstring(std::string s, size_t n, size_t start){
    std::string ret;
    icu_73::UnicodeString unicodeString, target;

    unicodeString = icu_73::UnicodeString::fromUTF8(icu_73::StringPiece(s.c_str()));

    unicodeString.extract(start, n, target);
    target.toUTF8String(ret);
    return ret;
}

/**
 * @brief getNextToken
 * Split a string into tokens by a given delimiter, and return the token
 * comes right after `currentPosition`.
 * @param s
 * The string to split.
 * @param delim
 * The delimiter.
 * @param currentPosition
 * The position to start looking for the new token. Note that this is also
 * an output parameter. In case `currentPosition == s.length()`, there are
 * no more tokens present.
 * @return
 * The next token. In case there are no more tokens, it returns an empty string.
 * In case there are multiple consecutive delimiters, they are not mangled, but
 * an empty string is returned from between the delimiters - check the
 * value of `currentPosition` to see if there are still available tokens to be
 * extracted.
 */
std::string getNextToken(const std::string& s, const std::string& delim, size_t& currentPosition){
    std::string ret{};
    if (s.length() <= currentPosition)
        return ret;

    size_t endOfNextToken = s.find(delim, currentPosition);
    if (endOfNextToken == std::string::npos) {
        ret = s.substr(currentPosition);
        currentPosition = s.length();
    } else {
        ret = s.substr(currentPosition, endOfNextToken - currentPosition);
        currentPosition = endOfNextToken + delim.size();
    }

    return ret;
}

/**
 * @brief parseEntryType
 * Match the given string to the corresponding entrytype.
 * @param s
 * The string to match.
 * @return
 * The matched entrytype.
 */
DictionaryEntry::EntryType parseEntryType(std::string s){
    if (DictionaryEntry::entryTypeLookupTable.count(s) == 0){
        ERROR("{} is an unknown entry type!", s);
        return DictionaryEntry::EntryType::NAN;
    }

    return DictionaryEntry::entryTypeLookupTable[s];
}

/**
 * @brief toLowerCase
 * Convert string to lowercase.
 * @return
 * The lower case version of the argument.
 */
std::string toLowerCase(std::string s)
{
    std::string ret;
    icu_73::UnicodeString us = icu_73::UnicodeString::fromUTF8(icu_73::StringPiece(s.c_str()));
    us = us.toLower();
    us.toUTF8String(ret);
    return ret;
}
