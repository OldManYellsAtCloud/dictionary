#include "entry.h"
#include "utils.h"
#include <loglibrary.h>

Entry parseEntry(std::string s)
{
    Entry ret;
    if (s.length() == 0){
        ERROR("Can't parse empty string into Entry object!");
        return ret;
    }

    std::string delimiter = "\t";
    size_t pos = 0;

    ret.original = getNextToken(s, delimiter, pos);
    if (pos == s.length()) {
        ERROR("Given string has not enough token to parse: {}", s);
        return ret;
    }

    ret.translation = getNextToken(s, delimiter, pos);
    if (pos == s.length()) {
        ERROR("Given string has not enough token to parse: {}", s);
        return ret;
    }

    ret.entryType = parseEntryType(getNextToken(s, delimiter, pos));
    if (pos == s.length()) {
        ERROR("Given string has not enough token to parse: {}", s);
        return ret;
    }

    ret.niche = getNextToken(s, delimiter, pos);

    return ret;
}
