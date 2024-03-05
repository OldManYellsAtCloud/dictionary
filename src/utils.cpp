#include "utils.h"

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
    const char* sChr = s.c_str();
    size_t byteCounter = 0;
    size_t charCounter = 0;
    while (charCounter < n && *sChr){
        if (*sChr >= ASCII_PRINTABLE_START && *sChr <= ASCII_PRINTABLE_END)
            ++charCounter;
        ++byteCounter;
        *sChr++;
    }

    return s.substr(start, --byteCounter);
/*
    while ( charCounter < n && *sChr){
        if ((*sChr++ & 0xc0) != 0x80){
            ++charCounter;
        }
        ++byteCounter;
    }
    ret = s.substr(start, byteCounter);

    // If the last character is not printable, that means
    // that a Unicode character was cut in half somewhere.
    // This is hopefully not overly naive for the German charset.
    // Nevertheless, this can only work as long there is only 1
    // accented character in the substring... definitely needs a
    // bit more eyeballing.
    if (ret[ret.length() - 1] < ASCII_PRINTABLE_START || ret[ret.length() - 1] > ASCII_PRINTABLE_END)
        ret = s.substr(start, byteCounter + 1);
*/
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
